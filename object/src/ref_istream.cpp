#include "dak/object/ref_istream.h"
#include "dak/object/transaction.h"

#include <iomanip>

namespace dak::object
{
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
   // Input stream tracked objects and names.

      void ref_istream_t::add_object_with_id(const edit_ref_t<object_t>& obj, int64_t id) const
   {
      my_object_with_ids.insert(std::pair(id, obj));
   }

   const edit_ref_t<object_t>& ref_istream_t::get_object_with_id(int64_t id) const
   {
      const auto pos = my_object_with_ids.find(std::abs(id));
      if (pos != my_object_with_ids.end())
         return pos->second;

      static const edit_ref_t<object_t> empty = object_t::make();
      return empty;
   }

   void ref_istream_t::add_name_with_id(const exact_name_t& name, int64_t id) const
   {
      my_name_with_ids[std::abs(id)] = name;
   }

   const exact_name_t& ref_istream_t::get_name_with_id(int64_t id) const
   {
      const auto pos = my_name_with_ids.find(std::abs(id));
      if (pos != my_name_with_ids.end())
         return pos->second;

      static const exact_name_t empty;
      return empty;
   }

   void ref_istream_t::clear()
   {
      my_object_with_ids.clear();
      my_name_with_ids.clear();
      get_stream().clear();
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Input stream sigil parsers.

   bool ref_istream_t::parse_optional_sigil(const wchar_t expected_sigil) const
   {
      std::wistream& istr = get_stream();

      wchar_t sigil = 0;
      istr >> std::ws >> sigil;
      if (expected_sigil == sigil)
         return true;

      istr.putback(sigil);
      return false;
   }

   bool ref_istream_t::parse_sigil(const wchar_t expected_sigil) const
   {
      std::wistream& istr = get_stream();

      if (parse_optional_sigil(expected_sigil))
         return true;

      istr.setstate(std::ios::failbit);
      return false;
   }

   bool ref_istream_t::parse_sigil(const str_ptr_t expected_sigil) const
   {
      std::wistream& istr = get_stream();

      text_t sigil;
      istr >> std::ws >> sigil;
      if (sigil == expected_sigil)
         return true;

      istr.setstate(std::ios::failbit);
      return false;
   }

}

