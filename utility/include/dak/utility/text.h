#pragma once

#ifndef DAK_UTILITY_TEXT_H
#define DAK_UTILITY_TEXT_H

#include <string>

namespace dak::utility
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Text widening.
   
   std::wstring convert(const std::string& text);
   std::wstring convert(const char* text);

   struct L
   {
      static const char* t(const char* some_text);
      static const wchar_t* t(const wchar_t* some_text);
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 

