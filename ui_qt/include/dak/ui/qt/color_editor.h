#pragma once

#ifndef DAK_UI_QT_COLOR_EDITOR_H
#define DAK_UI_QT_COLOR_EDITOR_H

#include <dak/ui/color.h>

#include <QtWidgets/qwidget>

class QPushButton;

namespace dak::ui::qt
{
   class color_editor_t : public QWidget
   {
   public:
      using on_color_changed_t = std::function<void(ui::color_t a_color)>;

      on_color_changed_t on_color_changed;

      color_editor_t(QWidget* parent);
      color_editor_t(QWidget* parent, const wchar_t* label_text);
      color_editor_t(QWidget* parent, const wchar_t* label_text, color_t value);
      color_editor_t(QWidget* parent, const wchar_t* label_text, color_t value, on_color_changed_t on_color_changed);

      void set_color(color_t a_new_value, bool call_callback = false);

   private:
      void build_ui(const wchar_t* label_text);

      void select_color();

      QPushButton*   my_color_button = nullptr;

      color_t my_color;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
