//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSorensen!!
//
//  coalescing common parts of appkit and uikit acme_window_bridge in apple_kit acme_window_bridge by camilo on 2024-11-28 00:57 <3ThomasBorregaardSorensen

#include "framework.h"
//#include "window.h"
#include "acme_window_bridge.h"
#include "acme/nano/graphics/device.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
//#include "acme/platform/sequencer.h"
#include "acme/platform/node.h"
#include "acme/user/micro/elemental.h"
#include "acme/user/user/frame_interaction.h"
#include "acme/user/user/mouse.h"
#include "acme/windowing/window.h"
#include <CoreGraphics/CoreGraphics.h>

void ns_main_post(dispatch_block_t block);

bool ns_app_is_running();

//void ns_app_run(int argc, char ** args, const char * pszClass);


void ns_app_stop();

CLASS_DECL_ACME void ns_get_main_screen_size(int & cx, int & cy);

void screen_coordinates_aware_copy(CGRect & rect, const ::int_rectangle &rectangle);

void screen_coordinates_aware_copy(CGPoint & cgpoint, const ::int_point & point);

void screen_coordinates_aware_copy(::int_point & point, const CGPoint & cgpoint);
namespace apple_kit
{


acme_window_bridge::acme_window_bridge()
{
   
}


acme_window_bridge::~acme_window_bridge()
{
   
}


void acme_window_bridge::on_left_button_up(double xHost, double yHost, double xAbsolute, double yAbsolute)
{
   
   auto pacmewindowingwindow = acme_windowing_window();
   
   auto pmouse = pacmewindowingwindow->øcreate_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
   
   ::cast < ::micro::elemental > pelemental = pacmewindowingwindow->m_pacmeuserinteraction;
   
   pelemental->fore_on_left_button_up(pmouse);
   
   if(pmouse->m_bRet)
   {
      
      return;
      
   }
   
   pelemental->back_on_left_button_up(pmouse);
   
}


void acme_window_bridge::on_left_button_down(double xHost, double yHost, double xAbsolute, double yAbsolute)
{
   
   auto pacmewindowingwindow = acme_windowing_window();
   
   auto pmouse = pacmewindowingwindow->øcreate_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
   
   ::cast < ::micro::elemental > pelemental = pacmewindowingwindow->m_pacmeuserinteraction;
   
   pelemental->fore_on_left_button_down(pmouse);
   
   if(pmouse->m_bRet)
   {
      
      return;
      
   }
   
   pelemental->back_on_left_button_down(pmouse);
   
}


void acme_window_bridge::on_right_button_up(double xHost, double yHost, double xAbsolute, double yAbsolute)
{
   
   auto pacmewindowingwindow = acme_windowing_window();
   
   auto pmouse = pacmewindowingwindow->øcreate_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
   
   ::cast < ::micro::elemental > pelemental = pacmewindowingwindow->m_pacmeuserinteraction;
   
   pelemental->fore_on_right_button_up(pmouse);
   
   if(pmouse->m_bRet)
   {
      
      return;
      
   }
   
   pelemental->back_on_right_button_up(pmouse);
   
}


void acme_window_bridge::on_right_button_down(double xHost, double yHost, double xAbsolute, double yAbsolute)
{
   
   auto pacmewindowingwindow = acme_windowing_window();
   
   auto pmouse = pacmewindowingwindow->øcreate_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
   
   ::cast < ::micro::elemental > pelemental = pacmewindowingwindow->m_pacmeuserinteraction;
   
   pelemental->fore_on_right_button_down(pmouse);
   
   if(pmouse->m_bRet)
   {
      
      return;
      
   }
      
   pelemental->back_on_right_button_down(pmouse);
      
}


void acme_window_bridge::on_mouse_move(double xHost, double yHost, double xAbsolute, double yAbsolute)
{
   
   auto pacmewindowingwindow = acme_windowing_window();
   
   auto pmouse = pacmewindowingwindow->øcreate_new <::user::mouse>();
   
   pmouse->m_pointHost = {xHost, yHost};
   
   pmouse->m_pointAbsolute = {xAbsolute, yAbsolute};
   
   ::cast < ::micro::elemental > pelemental = pacmewindowingwindow->m_pacmeuserinteraction;
   
   pelemental->fore_on_mouse_move(pmouse);
   
   if(pmouse->m_bRet)
   {
      
      return;
      
   }
   
   pelemental->back_on_mouse_move(pmouse);
   
}

//
//void acme_window_bridge::on_char(int iChar)
//{
//   
//   //pacmewindowingwindow->on_char(iChar);
//   
//}
//
//
//void acme_window_bridge::_on_draw_background(CGContextRef cg, CGSize sizeFrame)
//{
//   
//   //::pointer<quartz2d::nano::graphics::device>pnanodevice = ::place(new quartz2d::nano::graphics::device(cg));
//   
//   pacmewindowingwindow->_draw_background(cg);
//   
//}
//
//
//void acme_window_bridge::_on_draw_foreground(CGContextRef cg, CGSize sizeFrame)
//{
//   
//   //::pointer<quartz2d::nano::graphics::device>pnanodevice = ::place(new quartz2d::nano::graphics::device(cg));
//   
//   pacmewindowingwindow->_draw_foreground(cg);
//   
//}
//
//
//void acme_window_bridge::on_layout(int x, int y, int w, int h)
//{
//   
//   ::int_rectangle r;
//   r.left() = x;
//   r.top() = y;
//   r.right() = x+w;
//   r.bottom() = y+h;
//   
//   pacmewindowingwindow->m_pacmeuserinteraction->set_rectangle(r);
//   
//}
//
//
//bool acme_window_bridge::_is_top_most() const
//{
//   
//   //   return pacmewindowingwindow->m_pacmeuserinteraction->m_bTopMost;
//   
//   ::cast<::acme::user::frame_interaction> pelemental = pacmewindowingwindow->m_pacmeuserinteraction;
//   
//   if(!pelemental)
//   {
//      
//      return false;
//      
//   }
//   
//   return pelemental->m_bTopMost;
//   
//}
//
//
//bool acme_window_bridge::_is_popup_window() const
//{
//   
//   return pacmewindowingwindow->m_pacmeuserinteraction->is_popup_window();
//   
//}
//
//
//void acme_window_bridge::ios_window_become_main()
//{
//   
//   return pacmewindowingwindow->ios_window_become_main();
//   
//}
//
//
//void acme_window_bridge::ios_window_resign_main()
//{
//   
//   return pacmewindowingwindow->ios_window_resign_main();
//   
//}
//
//
//void acme_window_bridge::ios_window_become_key()
//{
//   
//   return pacmewindowingwindow->ios_window_become_key();
//   
//}
//
//
//void acme_window_bridge::ios_window_resign_key()
//{
//   
//   return pacmewindowingwindow->ios_window_resign_key();
//   
//}
//
//
//void acme_window_bridge::ios_window_on_show()
//{
//   
//   return pacmewindowingwindow->ios_window_on_show();
//   
//}


//void acme_window_bridge::ios_window_on_hide()
//{
//   
//   return pacmewindowingwindow->ios_window_on_hide();
//   
//}
//
//
//void acme_window_bridge::do_tasks()
//{
//   
//   ::task_run();
//   
//}
//
//
//
//ios_window * acme_window_bridge::_ios_window()
//{
//   
//   return nullptr;
//   
//}


::acme::windowing::window * acme_window_bridge::acme_windowing_window()
{
   
   return nullptr;
   
}


} // namespace apple_kit
