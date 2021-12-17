#include <dak/object_io/ref_istream.h>
#include <dak/object/transaction.h>

#include <iomanip>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Input stream constructors.

   ref_istream_t::ref_istream_t(std::wistream& s, const valid_ref_t<namespace_t>& into_ns, transaction_t& transaction)
      : ref_input_t(into_ns, transaction)
      , my_stream(s)
   {
   }

   // Abort the input, called on errors, when abort_on_unknown() is true.
   void ref_istream_t::abort() const
   {
      get_stream().setstate(std::ios::failbit);
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

      abort();
      return false;
   }
}

