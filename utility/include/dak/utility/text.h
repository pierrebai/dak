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
      static const std::string& t(const std::string& some_text);
      static const std::wstring& t(const std::wstring& some_text);
   };

   // TODO: printf for wstring using any_t as values. Use var-args templates.
}

#endif

// vim: sw=3 : sts=3 : et : sta : 

