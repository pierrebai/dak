#include <dak/ui/qt/color_editor.h>
#include <dak/ui/qt/convert.h>

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel>
#include <QtWidgets/qpushbutton>
#include <QtWidgets/qcolordialog.h>


namespace dak::ui::qt
{
   color_editor_t::color_editor_t(QWidget* a_parent)
      : color_editor_t(a_parent, nullptr, color_t(), nullptr)
   {
   }

   color_editor_t::color_editor_t(QWidget* a_parent, const wchar_t* some_text)
   : color_editor_t(a_parent, some_text, color_t(), nullptr)
   {
   }

   color_editor_t::color_editor_t(QWidget* a_parent, const wchar_t* some_text, color_t a_color)
   : color_editor_t(a_parent, some_text, a_color, nullptr)
   {
   }

   color_editor_t::color_editor_t(QWidget* a_parent, const wchar_t* some_text, color_t a_color, on_color_changed_t a_color_changed)
   : QWidget(a_parent), my_color(), on_color_changed(a_color_changed)
   {
      build_ui(some_text);
      set_color(a_color);
   }

   void color_editor_t::set_color(color_t a_color, bool call_callback)
   {
      if (my_color == a_color)
         return;

      my_color = a_color;

      QPixmap color_pixmap(16, 16);
      color_pixmap.fill(ui::qt::convert(a_color));
      my_color_button->setIcon(QIcon(color_pixmap));

      if (call_callback && on_color_changed)
         on_color_changed(a_color);
   }

   void color_editor_t::build_ui(const wchar_t* some_text)
   {
      auto layout = new QHBoxLayout(this);
      layout->setContentsMargins(0, 0, 0, 0);

      my_color_button = new QPushButton;
      layout->addWidget(my_color_button);

      if (some_text)
         my_color_button->setText(QString::fromWCharArray(some_text));

      my_color_button->connect(my_color_button, &QPushButton::clicked, [self = this]()
      {
         self->select_color();
      });

      layout->addStretch();
   }

   void color_editor_t::select_color()
   {
      QString label = my_color_button->text();
      QString title;
      if (label.length() > 0)
         title = QString::asprintf(tr("Select %s Color").toUtf8().constData(), label.toUtf8().constData());
      else
         title = tr("Select Color");
      const QColor new_color = QColorDialog::getColor(ui::qt::convert(my_color), this, title, QColorDialog::ColorDialogOption::ShowAlphaChannel);
      set_color(ui::qt::convert(new_color), true);
   }
}

// vim: sw=3 : sts=3 : et : sta : 
