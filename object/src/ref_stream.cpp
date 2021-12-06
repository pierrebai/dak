#include "dak/object/ref_stream.h"
#include "dak/object/transaction.h"

#include <dak/any_op/stream_op.h>

#include <iomanip>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Output stream wrapper data.

   namespace
   {
      template <class T>
      int64_t get_thing_id(std::unordered_map<T, int64_t>& ids, const T& thing)
      {
         if (!thing.is_valid())
            return 0;

         const auto pos = ids.find(thing);
         if (pos != ids.end())
            return -pos->second;

         // Note: 0 is reserved for invalid things.
         const int64_t id = static_cast<int64_t>(ids.size()) + 1;
         ids[thing] = id;
         return id;
      }
   }

   int64_t ref_ostream_t::get_object_id(const ref_t<object_t>& object) const
   {
      return get_thing_id<ref_t<object_t>>(my_object_ids, object);
   }

   int64_t ref_ostream_t::get_name_id(const exact_name_t& name) const
   {
      return get_thing_id<exact_name_t>(my_name_ids, name);
   }

   void ref_ostream_t::clear()
   {
      my_object_ids.clear();
      my_name_ids.clear();
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Output stream printing.

   const ref_ostream_t& ref_ostream_t::print(const weak_ref_t<namespace_t>& ns) const
   {
      if (!ns.is_valid())
         return *this;

      auto& ostr = get_stream();

      valid_ref_t<namespace_t> valid_ns(ns);

      print(valid_ns->get_parent());

      ostr << L" : " << std::quoted(valid_ns->to_text());

      return *this;
   }

   const ref_ostream_t& ref_ostream_t::print(const name_t& n) const
   {
      if (n.is_valid())
         print(n.get_namespace());

      const auto id = get_name_id(exact_name_t(n));
      *this << L" / " << id;
      if (id <= 0)
         return *this;

      *this << L" " << std::quoted(n.to_text());

      const auto& metadata = n.get_metadata();
      if (metadata.size() <= 0)
         return *this;

      *this << L" {\n";
      for (const name_t& n : metadata)
         *this << n << L",\n";

      *this << L"}";

      return *this;
   }

   const ref_ostream_t& ref_ostream_t::print(const ref_t<object_t>& o) const
   {
      const auto id = get_object_id(o);
      *this << L"ref " << id;
      if (id <= 0)
         return *this;

      return *this << L" " << *valid_ref_t<object_t>(o);
   }

   const ref_ostream_t& ref_ostream_t::print(const weak_ref_t<object_t>& w) const
   {
      return *this << ref_t<object_t>(w);
   }

   const ref_ostream_t& ref_ostream_t::print(const array_t& a) const
   {
      *this << L"[\n";
      for (const element_t& e : a)
         *this << e << L",\n";
      *this << L"]";
      return *this;
   }

   const ref_ostream_t& ref_ostream_t::print(const dict_t& d) const
   {
      *this << L"{\n";
      for (const auto& [n, e] : d)
         *this << n << L": " << e << L",\n";
      *this << L"}";
      return *this;
   }

   const ref_ostream_t& ref_ostream_t::print(const any_t& d) const
   {
      // TODO: not writing the actual type makes it impossible to read this back.
      dak::any_op::stream(get_stream(), d);
      return *this;
   }

   const ref_ostream_t& ref_ostream_t::print(const object_t& o) const
   {
      *this << L"{\n";
      for (const auto& [n, e] : o)
         *this << n << L": " << e << L",\n";
      *this << L"}";
      return *this;
   }

   const ref_ostream_t& ref_ostream_t::print(const element_t& e) const
   {
      switch (e.get_type())
      {
         case datatype_t::unknown:  return *this << L"u unknown";
         case datatype_t::boolean:  return *this << L"b " << (bool)e;
         case datatype_t::integer:  return *this << L"i " << (int64_t)e;
         case datatype_t::ref:      return *this << L"r " << (const ref_t<object_t> &) e;
         case datatype_t::weak_ref: return *this << L"w " << (const weak_ref_t<object_t> &) e;
         case datatype_t::name:     return *this << L"n " << (const name_t&)e;
         case datatype_t::real:     return *this << L"f " << (double)e;
         case datatype_t::array:    return *this << L"a " << (const array_t&)e;
         case datatype_t::dict:     return *this << L"d " << (const dict_t&)e;
         case datatype_t::data:     return *this << L"y " << (const any_t&)e;
         case datatype_t::text:     return *this << L"t " << std::quoted((str_ptr_t)e);
         default:                   return *this;
      }
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Input stream sigil parsers.

   namespace
   {
      bool parse_optional_sigil(std::wistream& istr, const wchar_t expected_sigil)
      {
         wchar_t sigil = 0;
         istr >> std::ws >> sigil;
         if (expected_sigil == sigil)
            return true;

         istr.putback(sigil);
         return false;
      }

      bool parse_sigil(std::wistream& istr, const wchar_t expected_sigil)
      {
         if (parse_optional_sigil(istr, expected_sigil))
            return true;

         istr.setstate(std::ios::failbit);
         return false;
      }

      bool parse_sigil(std::wistream& istr, const str_ptr_t expected_sigil)
      {
         text_t sigil;
         istr >> std::ws >> sigil;
         if (sigil == expected_sigil)
            return true;

         istr.setstate(std::ios::failbit);
         return false;
      }

      bool is_end(std::wistream& istr, const wchar_t possible_end)
      {
         wchar_t c = 0;
         istr >> std::ws >> c;
         if (possible_end == c)
            return true;

         istr.putback(c);
         return false;
      }
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Input stream constructors.

   ref_istream_t::ref_istream_t(std::wistream& s, const valid_ref_t<namespace_t>& into_ns, transaction_t& transaction)
      : my_stream(s)
      , my_transaction(transaction)
      , my_target_namespace(into_ns)
   {
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Input stream data.

   namespace
   {
      template <class T>
      void add_thing_with_id(std::unordered_map<int64_t, T>& ids, const T& thing, const int64_t id)
      {
         ids[std::abs(id)] = thing;
      }

      template <class T>
      const T& get_thing_with_id(const std::unordered_map<int64_t, T>& ids, const int64_t id)
      {
         const auto pos = ids.find(std::abs(id));
         if (pos != ids.end())
            return pos->second;

         static const T empty;
         return empty;
      }

   }

   void ref_istream_t::add_object_with_id(const ref_t<object_t>& obj, int64_t id) const
   {
      return add_thing_with_id(my_object_with_ids, obj, id);
   }

   const ref_t<object_t>& ref_istream_t::get_object_with_id(int64_t id) const
   {
      return get_thing_with_id(my_object_with_ids, id);
   }

   void ref_istream_t::add_name_with_id(const exact_name_t& name, int64_t id) const
   {
      return add_thing_with_id(my_name_with_ids, name, id);
   }

   const exact_name_t& ref_istream_t::get_name_with_id(int64_t id) const
   {
      return get_thing_with_id(my_name_with_ids, id);
   }

   void ref_istream_t::clear()
   {
      my_object_with_ids.clear();
      my_name_with_ids.clear();
      get_stream().clear();
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Input stream parsing.

   const ref_istream_t& ref_istream_t::parse(name_t& n) const
   {
      auto& istr = get_stream();

      bool in_top = true;
      valid_ref_t<namespace_t> current_ns = my_target_namespace;
      while (parse_optional_sigil(istr, L':'))
      {
         text_t text;
         istr >> std::quoted(text);
         if (!in_top || current_ns->to_text() != text)
         {
            ref_t<namespace_t> sub_ns = current_ns->get_namespace(text);
            if (sub_ns.is_null())
            {
               current_ns = namespace_t::make(current_ns->modify(my_transaction), text);
            }
            else
            {
               current_ns = sub_ns;
            }
         }
         in_top = false;
      }

      if (!parse_sigil(istr, L'/'))
         return *this;

      int64_t id = 0;
      istr >> std::ws >> id;
      if (id > 0)
      {
         text_t text;
         istr >> std::ws >> std::quoted(text);
         n = current_ns->get_name(text);
         if (!n.is_valid())
         {
            edit_ref_t edit_ns = current_ns->modify(my_transaction);
            n = name_t(edit_ns, text);
         }

         // Parse metadata.
         if (parse_optional_sigil(istr, L'{'))
         {
            while (istr.good())
            {
               name_t metaname;
               *this >> metaname;

               if (metaname.is_valid())
                  n.add_metadata(metaname, my_transaction);

               if (!parse_sigil(istr, L','))
                  break;
            }
         }

         add_name_with_id(exact_name_t(n), id);
      }
      else
      {
         n = get_name_with_id(-id);
      }

      return *this;
   }

   const ref_istream_t& ref_istream_t::parse(ref_t<object_t>& o) const
   {
      auto& istr = get_stream();

      if (!parse_sigil(istr, L"ref"))
         return *this;

      int64_t id = 0;
      istr >> std::ws >> id;
      if (id > 0)
      {
         edit_ref_t<object_t> new_obj = object_t::make();
         add_object_with_id(new_obj, id);
         parse(*new_obj);
         o = new_obj;
      }
      else
      {
         o = get_object_with_id(-id);
      }
      return *this;
   }

   const ref_istream_t& ref_istream_t::parse(weak_ref_t<object_t>& w) const
   {
      ref_t<object_t> r;
      parse(r);
      w = r;
      return *this;
   }

   const ref_istream_t& ref_istream_t::parse(array_t& a) const
   {
      auto& istr = get_stream();

      if (!parse_sigil(istr, L'['))
         return *this;

      while (istr.good()) {
         if (is_end(istr, L']'))
            break;

         element_t e;
         istr >> std::ws;
         *this >> e;
         a.append(e);

         if (!parse_sigil(istr, L','))
            break;
      }

      return *this;
   }

   const ref_istream_t& ref_istream_t::parse(dict_t& d) const
   {
      auto& istr = get_stream();

      if (!parse_sigil(istr, L'{'))
         return *this;

      while (istr.good()) {

         if (is_end(istr, L'}'))
            break;

         name_t n;
         istr >> std::ws;
         *this >> n;

         if (!parse_sigil(istr, L':'))
            break;

         element_t e;
         istr >> std::ws;
         *this >> e;
         d[n] = e;

         if (!parse_sigil(istr, L','))
            break;
      }

      return *this;
   }

   const ref_istream_t& ref_istream_t::parse(object_t& o) const
   {
      auto& istr = get_stream();

      if (!parse_sigil(istr, L'{'))
         return *this;

      while (istr.good()) {

         if (is_end(istr, L'}'))
            break;

         name_t n;
         istr >> std::ws;
         *this >> n;

         if (!parse_sigil(istr, L':'))
            break;

         element_t e;
         istr >> std::ws;
         *this >> e;
         o[n] = e;

         if (!parse_sigil(istr, L','))
            break;
      }

      return *this;
   }

   const ref_istream_t& ref_istream_t::parse(any_t& d) const
   {
      // TODO: not knowing in advance the actual type makes it impossible to read this back.
      dak::any_op::stream(get_stream(), d);

      return *this;
   }

   const ref_istream_t& ref_istream_t::parse(element_t& e) const
   {
      auto& istr = get_stream();

      wchar_t type_sigil;
      istr >> std::ws >> type_sigil >> std::ws;

      switch (type_sigil)
      {
      case L'u':
      {
         e.reset();
         break;
      }
      case L'b':
      {
         bool b;
         istr >> b;
         e = b;
         break;
      }
      case L'i':
      {
         int64_t i;
         istr >> i;
         e = i;
         break;
      }
      case L'r':
      {
         ref_t<object_t> r;
         *this >> r;
         if (r.is_valid())
         {
            e = valid_ref_t<object_t>(r);
         }
         else
         {
            istr.setstate(std::ios::failbit);
            e.reset();
         }
         break;
      }
      case L'w':
      {
         weak_ref_t<object_t> w;
         *this >> w;
         e = weak_ref_t<object_t>(w);
         break;
      }
      case L'n':
      {
         name_t n;
         *this >> n;
         e = n;
         break;
      }
      case L'f':
      {
         double f;
         istr >> f;
         e = f;
         break;
      }
      case L'a':
      {
         array_t a;
         *this >> a;
         e = a;
         break;
      }
      case L'd':
      {
         dict_t d;
         *this >> d;
         e = d;
         break;
      }
      case L'y':
      {
         any_t d;
         *this >> d;
         e = d;
         break;
      }
      case L't':
      {
         text_t t;
         istr >> std::quoted(t);
         e = t;
         break;
      }
      default:
         istr.setstate(std::ios::failbit);
         break;
      }

      return *this;
   }
}

