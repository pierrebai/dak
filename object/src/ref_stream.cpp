#include "dak/object/ref_stream.h"
#include "dak/object/transaction.h"

#include <iomanip>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Output stream wrapper data.

   int64_t ref_ostream_t::get_object_id(const ref_t<object_t>& object) const
   {
      if (object.is_null())
         return 0;

      const auto pos = my_object_ids.find(object);
      if (pos != my_object_ids.end())
         return -pos->second;

      // Note: 0 is reserved for null object ref.
      const int64_t id = static_cast<int64_t>(my_object_ids.size()) + 1;
      my_object_ids[object] = id;
      return id;
   }

   void ref_ostream_t::clear()
   {
      my_object_ids.clear();
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Output stream printing.

   const ref_ostream_t& ref_ostream_t::print(const namespace_t& ns) const
   {
      auto& ostr = get_stream();

      namespace_t::parent_t parent = ns.get_parent();
      if (parent.is_valid())
         print(*valid_ref_t(parent));

      ostr << L" : " << std::quoted(ns.to_text());

      return *this;
   }

   const ref_ostream_t& ref_ostream_t::print(const name_t& n) const
   {
      if (n.is_valid())
      {
         const namespace_t& ns = *n.get_namespace();
         *this << ns << L" / " << std::quoted(n.to_text());
      }
      else
      {
         get_stream() << L"?";
      }
      return *this;
   }

   const ref_ostream_t& ref_ostream_t::print(const ref_t<object_t>& o) const
   {
      const auto id = get_object_id(o);
      *this << L"ref " << id;
      if (id > 0)
         *this << " " << *valid_ref_t(o);
      return *this;
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
      switch (e.type())
      {
      case datatype_t::unknown:  return *this << L"u unknown";
      case datatype_t::boolean:  return *this << L"b " << (bool)e;
      case datatype_t::integer:  return *this << L"i " << (int64_t)e;
      case datatype_t::ref:      return *this << L"r " << (const ref_t<object_t> &) e;
      case datatype_t::name:     return *this << L"n " << (const name_t&)e;
      case datatype_t::real:     return *this << L"f " << (double)e;
      case datatype_t::array:    return *this << L"a " << (const array_t&)e;
      case datatype_t::dict:     return *this << L"d " << (const dict_t&)e;
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

   ref_istream_t::ref_istream_t(std::wistream& s, namespaces_t known_ns)
      : my_stream(s)
      , my_top_namespace()
   {
      for (const auto& ns : known_ns)
         my_top_namespace.add_namespace(ns);
   }

   ref_istream_t::ref_istream_t(std::wistream& s, const valid_ref_t<namespace_t>& known_ns)
      : my_stream(s)
      , my_top_namespace()
   {
      my_top_namespace.add_namespace(known_ns);
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Input stream data.

   void ref_istream_t::add_object_with_id(const valid_ref_t<object_t>& obj, int64_t id) const
   {
      my_object_with_ids[std::abs(id)] = obj;
   }

   ref_t<object_t> ref_istream_t::get_object_with_id(int64_t id) const
   {
      const auto pos = my_object_with_ids.find(std::abs(id));
      if (pos != my_object_with_ids.end())
         return pos->second;

      return ref_t<object_t>();
   }

   void ref_istream_t::clear()
   {
      my_object_with_ids.clear();
      get_stream().clear();
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Input stream parsing.

   const ref_istream_t& ref_istream_t::parse(name_t& n) const
   {
      auto& istr = get_stream();

      // Try parsing as an invalid name, return immediately if invalid.
      if (parse_optional_sigil(istr, L'?'))
         return *this;

      const namespace_t* current_ns = &my_top_namespace;
      while (parse_optional_sigil(istr, L':'))
      {
         text_t text;
         istr >> std::quoted(text);
         ref_t<namespace_t> sub_ns = current_ns->get_namespace(text);
         if (sub_ns.is_null())
         {
            istr.setstate(std::ios::failbit);
            return *this;
         }

         valid_ref_t<namespace_t> valid_sub_ns(sub_ns);
         current_ns = valid_sub_ns;
      }

      if (!parse_sigil(istr, L'/'))
         return *this;

      text_t text;
      istr >> std::quoted(text);
      n = current_ns->get_name(text);
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

