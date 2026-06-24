//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSorensen!!
//
//  coalescing common parts of appkit and uikit acme_window_bridge in apple_kit acme_window_bridge by camilo on 2024-11-28 00:57 <3ThomasBorregaardSorensen

#include "framework.h"
#include "window.h"
#include "acme_window_bridge.h"
#include "acme/constant/user_key.h"
#include "acme/nano/graphics/context.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
//#include "acme/platform/sequencer.h"
#include "acme/platform/node.h"
#include "acme/user/micro/elemental.h"
#include "acme/user/user/frame_interaction.h"
#include "acme/user/user/key.h"
#include "acme/user/user/mouse.h"
#include "acme/windowing/window.h"
#include <CoreGraphics/CoreGraphics.h>

void ns_main_post(dispatch_block_t block);

bool ns_app_is_running();

::user::e_key_state ns_pressed_buttons_to_e_button_state(unsigned int pressedButtons);

//void ns_app_run(int argc, char ** args, const char * pszClass);

void ns_app_stop();

CLASS_DECL_ACME void ns_get_main_screen_size(int & cx, int & cy);

void screen_coordinates_aware_copy(CGRect & rect, const ::i32_rectangle &rectangle);

void screen_coordinates_aware_copy(CGPoint & cgpoint, const ::i32_point & point);

void screen_coordinates_aware_copy(::i32_point & point, const CGPoint & cgpoint);

namespace apple_kit
{


//acme_window_bridge::acme_window_bridge()
//{
//   
//}
//
//
//acme_window_bridge::~acme_window_bridge()
//{
//   
//}

//void acme_window_bridge::attach_ns_acme_window(CGRect cgrect)
//{
//   
//   
//}


void acme_window_bridge::on_left_button_up(const ::user::e_key_state ekeystateMouse, double xHost, double yHost, double xAbsolute, double yAbsolute)
{
   
   auto pacmewindowingwindow = acme_windowing_window();
   
   auto pmouse = pacmewindowingwindow->create_newø <::user::mouse>();
   
   pmouse->m_eusermessage = ::user::e_message_left_button_up;
   
   pmouse->m_keystate = ekeystateMouse;
   
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


void acme_window_bridge::set_last_present_time()
{
   
   auto pacmewindowingwindow = acme_windowing_window();
   
   pacmewindowingwindow->set_last_present_time();
   
}

void acme_window_bridge::on_left_button_down(const ::user::e_key_state ekeystateMouse, double xHost, double yHost, double xAbsolute, double yAbsolute)
{
   
   auto pacmewindowingwindow = acme_windowing_window();
   
   auto pmouse = pacmewindowingwindow->create_newø <::user::mouse>();
   
   pmouse->m_eusermessage = ::user::e_message_left_button_down;
   
   pmouse->m_keystate = ekeystateMouse;
   
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


void acme_window_bridge::on_right_button_up(const ::user::e_key_state ekeystateMouse, double xHost, double yHost, double xAbsolute, double yAbsolute)
{
   
   auto pacmewindowingwindow = acme_windowing_window();
   
   auto pmouse = pacmewindowingwindow->create_newø <::user::mouse>();
   
   pmouse->m_eusermessage = ::user::e_message_right_button_up;
   
   pmouse->m_keystate = ekeystateMouse;
   
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


void acme_window_bridge::on_right_button_down(const ::user::e_key_state ekeystateMouse, double xHost, double yHost, double xAbsolute, double yAbsolute)
{
   
   auto pacmewindowingwindow = acme_windowing_window();
   
   auto pmouse = pacmewindowingwindow->create_newø <::user::mouse>();
   
   pmouse->m_eusermessage = ::user::e_message_right_button_down;
   
   pmouse->m_keystate = ekeystateMouse;
   
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


void acme_window_bridge::on_mouse_move(const ::user::e_key_state ekeystateMouse, double xHost, double yHost, double xAbsolute, double yAbsolute)
{
   
   auto pacmewindowingwindow = acme_windowing_window();
   
   auto pmouse = pacmewindowingwindow->create_newø <::user::mouse>();
   
   pmouse->m_eusermessage = ::user::e_message_mouse_move;
   
   pmouse->m_keystate = ekeystateMouse;
   
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


bool acme_window_bridge::on_key_down(::user::e_key  euserkey)
{
   
   auto pacmewindowingwindow = acme_windowing_window();
   
   auto pkey = pacmewindowingwindow->create_newø <::user::key>();
   
   //::user::enum_key ekey = ::user::e_key_none;
   
   pkey->m_eusermessage = ::user::e_message_key_down;
   
   pkey->m_ekey = euserkey;
   //throw "todo";
   
   ::cast < ::micro::elemental > pelemental = pacmewindowingwindow->m_pacmeuserinteraction;
   
   pelemental->on_key_down(pkey);

   
}
 bool acme_window_bridge::on_key_up(::user::e_key euserkey)
{
   
   auto pacmewindowingwindow = acme_windowing_window();
   
   auto pkey = pacmewindowingwindow->create_newø <::user::key>();
    
    //throw "todo";
    pkey->m_ekey = euserkey;
    
    pkey->m_eusermessage = ::user::e_message_key_up;
   
   ::cast < ::micro::elemental > pelemental = pacmewindowingwindow->m_pacmeuserinteraction;
   
   pelemental->on_key_up(pkey);
   
}


void acme_window_bridge::on_create()
{
   
   //auto pacmewindowingwindow = acme_windowing_window();
   
   //::cast < ::micro::elemental > pelemental = pacmewindowingwindow->m_pacmeuserinteraction;

   //pelemental->on_create();
   
   m_papplekitacmewindowingwindow->on_window_create(nullptr);
   
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


void acme_window_bridge::macos_window_draw(CGContextRef cgc, CGRect cgrect)
{
   
   m_papplekitacmewindowingwindow->macos_window_draw(cgc, cgrect);
   
}

void acme_window_bridge::_on_draw_background(CGContextRef cg, CGRect rect)
{
   
   //::pointer<quartz2d::nano::graphics::device>pnanodevice = ::place(new quartz2d::nano::graphics::device(cg));
   
   m_papplekitacmewindowingwindow->_draw_background(cg);
   
}


void acme_window_bridge::_on_draw_foreground(CGContextRef cg, CGRect rect)
{
   
   //::pointer<quartz2d::nano::graphics::device>pnanodevice = ::place(new quartz2d::nano::graphics::device(cg));
   
   m_papplekitacmewindowingwindow->_draw_foreground(cg);
   
}

//
//void acme_window_bridge::on_layout(int x, int y, int w, int h)
//{
//   
//   ::i32_rectangle r;
//   r.left = x;
//   r.top = y;
//   r.right = x+w;
//   r.bottom = y+h;
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
void acme_window_bridge::do_tasks()
{
   
   ::task_run();
   
}
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


::user::e_key_state ns_pressed_buttons_to_e_button_state(unsigned int pressedButtons)
{
   
   bool leftDown = (pressedButtons & (1 << 0)) != 0;
   
   bool rightDown = (pressedButtons & (1 << 1)) != 0;
   
   bool middleDown = (pressedButtons & (1 << 2)) != 0;
   
   ::user::e_key_state ekeystateMouse = ::user::e_key_state_none;
   
   if(leftDown)
   {
      
      ekeystateMouse |= ::user::e_key_state_left_button;
      
   }
   
   if(rightDown)
   {
      
      ekeystateMouse |= ::user::e_key_state_right_button;
      
   }
   
   if(middleDown)
   {
      
      ekeystateMouse |= ::user::e_key_state_middle_button;
      
   }
   
   return ekeystateMouse;
   
}



