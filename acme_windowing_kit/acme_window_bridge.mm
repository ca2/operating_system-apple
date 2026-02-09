//
//  nswindow.m
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 01/02/22.
//  23:25
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//  coalescing common parts of appkit and uikit acme_window_bridge in apple_kit acme_window_bridge by camilo on 2024-11-28 00:57 <3ThomasBorregaardSorensen

#include <Foundation/Foundation.h>
//#include <UIKit/UIKit.h>
//#include <Carbon/Carbon.h>
//#include "ns_acme_window.h"
#include "acme_window_bridge.h"
//#include "ns_acme_impact.h"
//#import "ios_app.h"


void ns_main_post(dispatch_block_t block);

bool ns_app_is_running();

void ns_main_post(dispatch_block_t block);

void ns_main_send(dispatch_block_t block);

namespace apple_kit
{


acme_window_bridge::acme_window_bridge()
{
   
   m_bRunningAppMainLoop = false;
   m_pnsacmewindowAppleKit = nullptr;
   
}


acme_window_bridge::~acme_window_bridge()
{
   
//   auto pnsacmewindow =  (__bridge ns_acme_window *) m_pnsacmewindow;
//   
//   pnsacmewindow->m_pacmewindowbridge = nullptr;
//   
//   pnsacmewindow->m_pnsacmeimpact->m_pnsacmewindow = nil;
//   
//   ns_main_post(^{
//      
//      //[ pnsacmewindow close];
//      
//   });;
//   
//   
   
}


void acme_window_bridge::attach_ns_acme_window(CGRect CGRect)
{
   
//   ns_main_send(^()
//                {
//      
//      //auto rect = [[UIScreen mainScreen]bounds];
//      
//      ios_app * p = (ios_app*)[[UIApplication sharedApplication] delegate];
//      
//      m_pnsacmewindow = (__bridge_retained CFTypeRef) p->m_pnsacmewindow;
//      
//      [p->m_pnsacmewindow setBridge: this];
//      
//      
//      
//   });
   
}


void acme_window_bridge::display()
{
   
//   ns_main_post(^()
//                {
//      
//      //auto pnsacmewindow =  (__bridge ns_acme_window *) m_pnsacmewindow;
//      
//      //id appName = [ [ NSProcessInfo processInfo ] processName ];
//      
//      //      if (![ NSApp mainMenu ])
//      //      {
//      //
//      //         [ NSApplication sharedApplication ];
//      //
//      //         id menubar = [ NSMenu new ];
//      //         id appMenuItem = [ NSMenuItem new ];
//      //         [ menubar addItem : appMenuItem ];
//      //
//      //         id appMenu = [ NSMenu new ] ;
//      //         id quitTitle = [ @"Quit " stringByAppendingString : appName];
//      //         id quitMenuItem = [ [ NSMenuItem alloc ] initWithTitle : quitTitle action: @selector(terminate:) keyEquivalent: @"q" ];
//      //         [ appMenu addItem : quitMenuItem ];
//      //         [ appMenuItem setSubmenu : appMenu ];
//      //
//      //         [ NSApp setMainMenu : menubar ];
//      //
//      //      }
//      
//      //[ pnsacmewindow setTitle : appName];
//      
//      if(_is_top_most())
//      {
//         
//         //[ pnsacmewindow setLevel: NSPopUpMenuWindowLevel ];
//         
//      }
//      else if(_is_popup_window())
//      {
//         
//         //[ pnsacmewindow setLevel: NSModalPanelWindowLevel ];
//         
//      }
//      
//      //      //[ pnsacmewindow display];
//      //      //[ pnsacmewindow makeKeyAndOrderFront : pnsacmewindow ];
//      //
//      //
//      //
//      //       [ pnsacmewindow makeKeyAndOrderFront:nil ];
//      //
//      //
//      //
//      //      //[ pnsacmewindow orderFront: nil ];
//      //      //[ pnsacmewindow display ];
//      //      //[ pnsacmewindow makeFirstResponder : pnsacmewindow ];
//      //      //[ NSApp activateIgnoringOtherApps : YES ];
//      //      //[ [ pnsacmewindow windowController ] showWindow:nil ];
//      //      //[ NSApp runModalForWindow : pnsacmewindow ];
//      
//   });
//   
   
}


void acme_window_bridge::hide()
{
   
//   auto pnsacmewindow =  (__bridge ns_acme_window *) m_pnsacmewindow;
//   
//   if(!pnsacmewindow)
//   {
//      
//      return;
//      
//   }
//   
//   ns_main_send(^()
//                {
//      //
//      //
//      //      //[ pnsacmewindow resignKeyWindow];
//      //      //[ pnsacmewindow resignMainWindow ];
//      //
//      //
//      //
//      //
//      //      [ pnsacmewindow orderOut: pnsacmewindow ];
//      //
//   });
//   
}


void acme_window_bridge::redraw()
{
   
//   if(m_pnsacmewindow)
//   {
//      
//      auto pnsacmewindow =  (__bridge ns_acme_window *) m_pnsacmewindow;
//      
//      ns_main_post(^{
//         [ pnsacmewindow setNeedsDisplay];
//         auto pimpact = pnsacmewindow->m_pnsacmeimpact;
//         [ pimpact setNeedsDisplay];
//      });
//      
//      
//      
//   }
//   
}


//void acme_window_bridge::stop()
//{
//
//   auto pnsacmewindow =  (__bridge ns_acme_window *) m_pnsacmewindow;
//
//   if(!pnsacmewindow)
//   {
//
//      return;
//
//   }
//
//   ns_main_post(^{
//
//   if(!ns_app_is_running())
//   {
//
//      if(m_bRunningAppMainLoop)
//      {
//
//         [ NSApp stop : nil ];
//
//         m_bRunningAppMainLoop = false;
//
//      }
//
//   }
//
//
//
////)
//
////      [pnsacmewindow->m_pwindowcontroller close];
////      macos_app * papp = (macos_app *) [ [ NSApplication sharedApplication ] delegate ];
////
////     [ papp removeWindowController: pnsacmewindow->m_pwindowcontroller ];
////
////
////      pnsacmewindow->m_pwindowcontroller = nil;
//
//   //[NSApp stopModal];
////      [ pnsacmewindow setLevel: NSNormalWindowLevel ];
////      [ pnsacmewindow setAnimationBehavior:NSWindowAnimationBehaviorNone];
////   [ pnsacmewindow orderOut: pnsacmewindow ];
////      //[ pnsacmewindow setIsVisible: false];
////      //[ pnsacmewindow setViewsNeedDisplay:TRUE];
//      //pnsacmewindow->m_pimpactChild = nil;
//      //[ pnsacmewindow orderOut:nil];
//      [ pnsacmewindow orderOut:nil ];
//
//      //m_pnsacmewindow = nullptr;
//      //CFRelease(m_pnsacmewindow);
//
//   });
//
//
//}

void acme_window_bridge::close()
{
   
//   auto pnsacmewindow =  (__bridge ns_acme_window *) m_pnsacmewindow;
//   
//   if(!pnsacmewindow)
//   {
//      
//      return;
//      
//   }
//   
//   ns_main_send(^{
//      
//      //[ pnsacmewindow close ];
//      
//      do_tasks();
//      
//   });
//   
   
}


void acme_window_bridge::set_position(int x, int y)
{
   
//   if(!m_pnsacmewindow)
//   {
//      
//      return;
//      
//   }
//   
//   auto pnsacmewindow =  (__bridge ns_acme_window *) m_pnsacmewindow;
//   
//   CGPoint point;
//   
//   point.x = x;
//   
//   point.y = y;
//   
//   CGRect frame = [ pnsacmewindow frame ];
//   
//   //int w = frame.size.width;
//   
//   int h = frame.size.height;
//   
//   point.y = (int) [[UIScreen mainScreen] bounds].size.height - point.y - h;
//   
//   CGRect r = [pnsacmewindow frame];
//   r.origin = point;
//   [ pnsacmewindow setFrame:r ];
//   
}


//bool apple_is_action_key(int i)
//{
//
////   if(i==kVK_Return       ) return true;
////   if(i==kVK_Tab          ) return true;
////   //if(i==kVK_Space      ) return true;
////   if(i==kVK_Delete       ) return true;
////   if(i==kVK_Escape       ) return true;
////   if(i==kVK_Command      ) return true;
////   if(i==kVK_Shift        ) return true;
////   if(i==kVK_CapsLock     ) return true;
////   if(i==kVK_Option       ) return true;
////   if(i==kVK_Control      ) return true;
////   if(i==kVK_RightShift   ) return true;
////   if(i==kVK_RightOption  ) return true;
////   if(i==kVK_RightControl ) return true;
////   if(i==kVK_Function     ) return true;
////   if(i==kVK_F17          ) return true;
////   if(i==kVK_VolumeUp     ) return true;
////   if(i==kVK_VolumeDown   ) return true;
////   if(i==kVK_Mute         ) return true;
////   if(i==kVK_F18          ) return true;
////   if(i==kVK_F19          ) return true;
////   if(i==kVK_F20          ) return true;
////   if(i==kVK_F5           ) return true;
////   if(i==kVK_F6           ) return true;
////   if(i==kVK_F7           ) return true;
////   if(i==kVK_F3           ) return true;
////   if(i==kVK_F8           ) return true;
////   if(i==kVK_F9           ) return true;
////   if(i==kVK_F11          ) return true;
////   if(i==kVK_F13          ) return true;
////   if(i==kVK_F16          ) return true;
////   if(i==kVK_F14          ) return true;
////   if(i==kVK_F10          ) return true;
////   if(i==kVK_F12          ) return true;
////   if(i==kVK_F15          ) return true;
////   if(i==kVK_Help         ) return true;
//   if(i==kVK_Home         ) return true;
//   if(i==kVK_PageUp       ) return true;
//   if(i==kVK_ForwardDelete) return true;
//   if(i==kVK_F4           ) return true;
//   if(i==kVK_End          ) return true;
//   if(i==kVK_F2           ) return true;
//   if(i==kVK_PageDown     ) return true;
//   if(i==kVK_F1           ) return true;
//   if(i==kVK_LeftArrow    ) return true;
//   if(i==kVK_RightArrow   ) return true;
//   if(i==kVK_DownArrow    ) return true;
//   if(i==kVK_UpArrow      ) return true;
//
//   return false;
//
//}



void acme_window_bridge::_run_modal_loop()
{
   m_bRunningAppMainLoop = true;
   //[ NSApp run ];
   
   //   if(!ns_app_is_running())
   //   {
   //      [ NSApp runModalForWindow : (__bridge ns_acme_window *)m_pnsacmewindow ];
   //
   //   }
   
}


CGRect acme_window_bridge::get_frame()
{
   
   return {};
   
//   auto pnsacmewindow =  (__bridge ns_acme_window *) m_pnsacmewindow;
//   
//   CGRect frame = [ pnsacmewindow frame ];
//   
//   return frame;
//   
}


} // namespace apple_kit


