//
//  c_window.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 01/02/22.
//  23:26
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//  coalescing common parts of appkit and uikit acme_window_bridge in apple_kit acme_window_bridge by camilo on 2024-11-28 00:56 <3ThomasBorregaardSorensen
//
#pragma once



#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>


namespace apple_kit
{

   class acme_window_bridge :
   virtual public ::particle
   {
   public:
      
      //bool m_bRunningAppMainLoop;
      //::uikit::acme::windowing::window *     m_pwindow;
      //CFTypeRef                  m_pnsacmewindow;
      
      
      acme_window_bridge();
      ~acme_window_bridge() override;
      
//      void attach_ns_acme_window(CGRect cgrect);
//      
//      void display();
//      
//      void hide();
//      
//      void do_tasks();
      
      virtual void on_left_button_up(double xHost, double yHost, double xAbsolute, double yAbsolute);
      
      virtual void on_left_button_down(double xHost, double yHost, double xAbsolute, double yAbsolute);
      
      virtual void on_right_button_up(double xHost, double yHost, double xAbsolute, double yAbsolute);
      
      virtual void on_right_button_down(double xHost, double yHost, double xAbsolute, double yAbsolute);
      
      virtual void on_mouse_move(double xHost, double yHost, double xAbsolute, double yAbsolute);
      
      
//      virtual void on_char(int iChar);
//      
//      virtual void _on_draw_background(CGContextRef cg, CGSize sizeFrame);
//      
//      virtual void _on_draw_foreground(CGContextRef cg, CGSize sizeFrame);
//      
//      virtual void redraw();
//      
//      //virtual void stop();
//      
//      virtual void close();
//      
//      virtual void set_position(int x, int y);
//      
//      virtual void on_layout(int x, int y, int w, int h);
//      
//      virtual void ios_window_become_main();
//      
//      virtual void ios_window_resign_main();
//      
//      virtual void ios_window_become_key();
//      
//      virtual void ios_window_resign_key();
//      
//      virtual CGRect get_frame();
//      
//      virtual void _run_modal_loop();
//      
//      virtual bool _is_top_most() const;
//      
//      virtual bool _is_popup_window() const;
//      
//      virtual void ios_window_on_show();
//      
//      virtual void ios_window_on_hide();
      
      
      virtual ::acme::windowing::window * acme_windowing_window();
      
   };


} // namespace apple_kit



