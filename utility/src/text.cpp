#define _CRT_SECURE_NO_WARNINGS
#include <dak/utility/text.h>

#include <clocale>
#undef _CRT_SECURE_NO_WARNINGS

namespace dak::utility
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Text widening and narrowing

   text_t widen_text(const std::string& text)
   {
      return widen_text(text.c_str());
   }

   text_t widen_text(const char* text)
   {
      const size_t needed = strlen(text) + 1;
      std::wstring converted(needed, L'#');
      size_t used = 0;
      mbstowcs_s(&used, &converted[0], converted.size(), text, needed);
      // Note: we don't want the terminating nul in the wstring, so we subtract one.
      converted.resize(used > 0 ? used - 1 : used);
      return converted;
   }

   std::string narrow_text(const text_t& text)
   {
      return narrow_text(text.c_str());
   }

   std::string narrow_text(str_ptr_t text)
   {
      const size_t needed = wcslen(text) + 1;
      std::string converted(needed, '#');
      size_t used = 0;
      wcstombs_s(&used, &converted[0], converted.size(), text, needed);
      // Note: we don't want the terminating nul in the wstring, so we subtract one.
      converted.resize(used > 0 ? used - 1 : used);
      return converted;
   }

   ////////////////////////////////////////////////////////////////////////////
   //
   // TODO: text localisation

   const char* L::t(const char* some_text)
   {
      return some_text;
   }

   const wchar_t* L::t(const wchar_t* some_text)
   {
      return some_text;
   }

   const std::string& L::t(const std::string& some_text)
   {
      return some_text;
   }
   
   const text_t& L::t(const text_t& some_text)
   {
      return some_text;
   }

   ////////////////////////////////////////////////////////////////////////////
   //
   // Text format and join

   text_t format(str_ptr_t text_format, ...)
   {
      va_list args;
      va_start(args, text_format);
      text_t formatted = format(text_format, args);
      va_end(args);
      return formatted;
   }

   text_t format(const text_t& text_format, va_list args)
   {
      return format(text_format.c_str(), args);
   }

   text_t format(str_ptr_t text_format, va_list args)
   {
      const int required_count = _vsnwprintf((wchar_t*)nullptr, 0, text_format, args);

      text_t formatted;
      formatted.resize(required_count + 1);

      while (true)
      {
         const int count = _vsnwprintf(formatted.data(), formatted.size(), text_format, args);
         if (count >= 0 && count < formatted.size())
         {
            formatted.resize(required_count);
            break;
         }
         formatted.resize(formatted.size() * 2);
      }

      return formatted;
   }

   text_t join(const std::vector<text_t>& parts, const text_t sep)
   {
      text_t joined;
      for (const text_t& part : parts)
      {
         if (joined.size())
            joined += sep;
         joined += part;
      }
      return joined;
   }
}

// vim: sw=3 : sts=3 : et : sta : 
