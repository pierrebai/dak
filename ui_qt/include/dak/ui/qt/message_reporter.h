#pragma once

#ifndef DAK_UI_QT_MESSAGE_REPORTER_H
#define DAK_UI_QT_MESSAGE_REPORTER_H

#include <string>
#include <vector>

class QWidget;
class QPainter;

namespace dak::ui::qt
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Reporting information to the user over a given widget.
   //
   // TODO: maybe connect it to a generic info reporting system.

   struct message_reporter_t
   {
      enum class category_t
      {
         info, warning, error
      };

      message_reporter_t(QWidget* on_widget);

      void report(const std::wstring& text, category_t cat);

      void paint(QPainter& painter);

   private:
      struct message
      {
         std::wstring text;
         category_t   category;
         double       opacity;
      };

      QWidget* widget = nullptr;
      std::vector<message> messages;
      bool has_repaint = false;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
