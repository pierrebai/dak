#include <dak/ui/qt/widget_mouse_emitter.h>

#include <QtGui/qevent.h>

namespace dak::ui::qt
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Helpers.

   namespace
   {
      buttons_t translate(const Qt::MouseButtons b)
      {
         buttons_t tb = buttons_t::none;
         if (b & Qt::MouseButton::LeftButton)
            tb = tb | buttons_t::one;
         if (b & Qt::MouseButton::MiddleButton)
            tb = tb | buttons_t::three;
         if (b & Qt::MouseButton::RightButton)
            tb = tb | buttons_t::two;
         return tb;
      }

      modifiers_t translate(const Qt::KeyboardModifiers m)
      {
         modifiers_t tm = modifiers_t::none;
         if (m & Qt::Modifier::SHIFT)
            tm = tm | modifiers_t::shift;
         if (m & Qt::Modifier::CTRL)
            tm = tm | modifiers_t::control;
         if (m & Qt::Modifier::ALT)
            tm = tm | modifiers_t::alt;
         return tm;
      }

      ui::mouse::event_t translate(QMouseEvent* qme)
      {
         if (!qme)
            return ui::mouse::event_t(point_t(), buttons_t::none, modifiers_t::none, 0);

         qme->accept();

         return ui::mouse::event_t(point_t(qme->x(), qme->y()),
            translate(qme->buttons()), translate(qme->modifiers()), 0);
      }

      ui::mouse::event_t translate(QWheelEvent* qwe)
      {
         if (!qwe)
            return ui::mouse::event_t(point_t(), buttons_t::none, modifiers_t::none, 0);

         qwe->accept();

         return ui::mouse::event_t(point_t(qwe->position().x(), qwe->position().y()),
            translate(qwe->buttons()), translate(qwe->modifiers()), qwe->delta());
      }
   }

   ////////////////////////////////////////////////////////////////////////////
   //
   // QtWidget mouse emitter.

   widget_emitter_t::widget_emitter_t(QWidget& w)
   : widget(w)
   {
      widget.installEventFilter(this);
      widget.setMouseTracking(true);
   }

   widget_emitter_t::~widget_emitter_t()
   {
      widget.removeEventFilter(this);
   }

   bool widget_emitter_t::eventFilter(QObject* obj, QEvent* ev)
   {
      switch (ev->type())
      {
         case QEvent::Type::Enter:
            mouse_entered(translate(dynamic_cast<QMouseEvent *>(ev)));
            return true;
         case QEvent::Type::Leave:
            mouse_exited(translate(dynamic_cast<QMouseEvent *>(ev)));
            return true;
         case QEvent::Type::MouseButtonPress:
            mouse_pressed(translate(dynamic_cast<QMouseEvent *>(ev)));
            return true;
         case QEvent::Type::MouseButtonRelease:
            mouse_released(translate(dynamic_cast<QMouseEvent *>(ev)));
            return true;
         case QEvent::Type::MouseMove:
         {
            auto me = translate(dynamic_cast<QMouseEvent *>(ev));
            if (me.has_buttons(buttons_t::all))
               mouse_dragged(me);
            else
               mouse_moved(me);
            return true;
         }
         case QEvent::Type::DragEnter:
            mouse_entered(translate(dynamic_cast<QMouseEvent *>(ev)));
            return true;
         case QEvent::Type::DragLeave:
            mouse_exited(translate(dynamic_cast<QMouseEvent *>(ev)));
            return true;
         case QEvent::Type::DragMove:
            mouse_dragged(translate(dynamic_cast<QMouseEvent *>(ev)));
            return true;
         case QEvent::Type::Wheel:
            mouse_wheel(translate(dynamic_cast<QWheelEvent *>(ev)));
            return true;
         case QEvent::Type::MouseButtonDblClick:
            mouse_clicked(translate(dynamic_cast<QMouseEvent *>(ev)));
            return true;
      }

      return false;
   }
}

// vim: sw=3 : sts=3 : et : sta : 
