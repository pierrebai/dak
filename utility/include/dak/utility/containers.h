#pragma once

#ifndef DAK_UTILITY_CONTAINERS_H
#define DAK_UTILITY_CONTAINERS_H

#include <map>
#include <vector>
#include <set>
#include <algorithm>

namespace dak::utility
{
   // Verify if a container contains a value.
   // Implemented for vector, map and set.
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

   template <class K, class V>
   bool contains(const std::map<K, V>& map, const K& key)
   {
      return map.count(key) > 0;
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
   // Return true if a value was removed.
   template <class T>
   bool remove_one(std::vector<T>& vec, const T& val)
   {
      const auto iter = find(vec, val);
      if (iter == vec.end())
         return false;
      vec.erase(iter);
      return true;
   }

   // Remove the all occurences of a value in a vector.
   // Return true if at least one value was removed.
   template <class T>
   bool remove_all(std::vector<T>& vec, const T& val)
   {
      if (!remove_one(vec, val))
         return false;
      while (remove_one(vec, val))
      {
      }
      return true;
   }
}

#endif

// vim: sw=3 : sts=3 : et : sta : 

