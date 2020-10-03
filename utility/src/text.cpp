#include <dak/utility/text.h>

#include <clocale>

namespace dak::utility
{
   std::wstring convert(const char* text)
   {
      const size_t needed = strlen(text) + 1;
      std::wstring converted(needed, L'#');
      size_t used = 0;
      mbstowcs_s(&used, &converted[0], converted.size(), text, needed);
      // Note: we don't want the terminating nul in the wstring, so we subtract one.
      converted.resize(used > 0 ? used - 1 : used);
      return converted;
   }

   std::wstring convert(const std::string& text)
   {
      return convert(text.c_str());
   }

   const char* L::t(const char* some_text)
   {
      return some_text;
   }

   const wchar_t* L::t(const wchar_t* some_text)
   {
      return some_text;
   }
}

// vim: sw=3 : sts=3 : et : sta : 
