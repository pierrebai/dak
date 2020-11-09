#pragma once

#ifndef DAK_UTILITY_NO_COPY_H
#define DAK_UTILITY_NO_COPY_H

namespace dak::utility
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Prevent copy construction and assignments when used as a base class.

   struct no_copy_t
   {
   protected:
      no_copy_t() = default;

   private:
      no_copy_t(const no_copy_t&) = delete;
      no_copy_t& operator =(const no_copy_t&) = delete;
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // Prevent move construction and assignments when used as a base class.

   struct no_move_t
   {
   protected:
      no_move_t() = default;

   private:
      no_move_t(const no_move_t&&) = delete;
      no_move_t& operator =(const no_move_t&&) = delete;
   };
}

#endif /* DAK_UTILITY_NO_COPY_H */

