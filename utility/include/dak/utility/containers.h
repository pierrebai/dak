#pragma once

#ifndef DAK_UTILITY_CONTAINERS_H
#define DAK_UTILITY_CONTAINERS_H

#include <vector>
#include <set>
#include <algorithm>

namespace dak::utility
{
   // Verify if a container contains a value.
   // Impkemented for vector and set.
   template <class T>
   bool contains(const std::vector<T>& vec, const T& val)
   {
      const auto iter = std::find(vec.begin(), vec.end(), val);
      return iter != vec.end();
   }

   template <class T>
   bool contains(const std::set<T>& set, const T& val)
   {
      return set.count(val) > 0;
   }

   // Find a value in a vector, without having to pass iterators.
   template <class T>
   typename std::vector<T>::const_iterator find(const std::vector<T>& vec, const T& val)
   {
      return std::find(vec.begin(), vec.end(), val);
   }

   template <class T>
   typename std::vector<T>::iterator find(std::vector<T>& vec, const T& val)
   {
      return std::find(vec.begin(), vec.end(), val);
   }

   // Remove the first occurence of a value in a vector.
   template <class T>
   bool remove(std::vector<T>& vec, const T& val)
   {
      const auto iter = find(vec, val);
      if (iter == vec.end())
         return false;
      vec.erase(iter);
      return true;
   }
}

#endif

// vim: sw=3 : sts=3 : et : sta : 

