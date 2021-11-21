#pragma once

#ifndef DAK_OBJECT_STREAM_H
#define DAK_OBJECT_STREAM_H

#include <dak/utility/types.h>
#include <dak/object/array.h>
#include <dak/object/dict.h>
#include <dak/object/object.h>

#include <iostream>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Stream operations on known data types.

   std::wostream& operator<<(std::wostream& ostr, const element_t& e);
   std::wostream& operator<<(std::wostream& ostr, const array_t& a);
   std::wostream& operator<<(std::wostream& ostr, const dict_t& d);
   std::wostream& operator<<(std::wostream& ostr, const object_t& o);
   std::wostream& operator<<(std::wostream& ostr, const name_t& n);
}

#endif /* DAK_OBJECT_STREAM_H */
