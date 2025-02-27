// Created by camilo on 2024-09-13 01:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "button.h"
#include "dialog.h"
#include "icon.h"
//#include "windowing_appkit/windowing.h"
//#include <QPushButton>


namespace innate_ui_appkit
{


   button::button()
   {
   }


   button::~button()
   {

      __button_release();
      
   }


   void button::set_callback_on_click(const ::procedure & callbackOnClickParam)
   {

      ::innate_ui::button::set_callback_on_click(callbackOnClickParam);

      // Callback function to handle the button click event
      // auto on_button_clicked = [](GtkWidget *widget, gpointer data)->void
      // {
      //    auto p = (button *) data;
      //    p->call_on_click();
      // };
      //
      //
      // g_signal_connect(m_pgtkwidget, "clicked", G_HANDLER(on_button_clicked), this);

//      auto ppushbutton = dynamic_cast< QPushButton*>(m_pqwidget);
//      m_pqwidget->connect(ppushbutton, &QPushButton::clicked, [this]() {
//         call_on_click();
//                 // Perform an action when the button is clicked
//                 //QMessageBox::information(this, "Lambda Slot", "Button clicked!");
//             });
      
      __set_callback();

   }


   void button::_create_child(window * pwindowParent)
   {

      m_pwindowParent = pwindowParent;

      // m_hwnd = CreateWindow(
      //    L"BUTTON",  // Predefined class; Unicode assumed
      //    L"",      // Button text
      //    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
      //    10,         // x position
      //    10,         // y position
      //    100,        // Button width
      //    100,        // Button height
      //    pwindowParent->m_hwnd,     // Parent window
      //    NULL,       // No menu.
      //    (HINSTANCE)GetWindowLongPtr(pwindowParent->m_hwnd, GWLP_HINSTANCE),
      //    NULL);

      ::pointer < ::innate_ui_appkit::window > pappkitwindowParent = pwindowParent;

      
      __øcreate();
      //m_pqwidget = new QPushButton(pappkitwindowParent->m_pqwidget);

      //gtk_widget_set_visible(m_pgtkwidget, true);

   }


//   void button::set_text(const ::scoped_string & scopedstr)
//   {
//
//      ::string str(scopedstr);
//
//      post([this, str]
//      ()
//         {
//
//            //gtk_button_set_label(GTK_BUTTON(m_pgtkwidget), str);
//
////         auto pqpushbutton = dynamic_cast<QPushButton*>(m_pqwidget);
////
////         if(pqpushbutton)
////         {
////
////            pqpushbutton->setText(str.c_str());
////
////         }
//
//});
//
//   }


   void button::set_icon(::innate_ui::icon * piconParam)
   {

      ::pointer <icon > picon = piconParam;

      sync([this, picon]()
      {

         //::SendMessage(m_hwnd, BM_SETICON, (WPARAM) picon->m_hicon, 0);

         });

   }


} // namespace innate_ui_appkit
