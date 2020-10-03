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
}

#endif

// vim: sw=3 : sts=3 : et : sta : 

