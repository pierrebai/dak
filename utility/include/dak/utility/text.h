#pragma once

#ifndef DAK_UTILITY_TEXT_H
#define DAK_UTILITY_TEXT_H

#include <dak/utility/types.h>

#include <stdarg.h>
#include <vector>

namespace dak::utility
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Text widening and narrowing
   
   text_t widen_text(const std::string& text);
   text_t widen_text(const char* text);

   std::string narrow_text(const text_t& text);
   std::string narrow_text(str_ptr_t text);

   ////////////////////////////////////////////////////////////////////////////
   //
   // Text localisation

   struct L
   {
      static const char* t(const char* some_text);
      static const wchar_t* t(const wchar_t* some_text);
      static const std::string& t(const std::string& some_text);
      static const text_t& t(const text_t& some_text);
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // Text format and join

   text_t format(str_ptr_t text_format, ...);
   text_t format(const text_t& text_format, va_list);
   text_t format(str_ptr_t text_format, va_list);

   text_t join(const std::vector<text_t>& parts, const text_t sep = L" ");
}

#endif

// vim: sw=3 : sts=3 : et : sta : 

