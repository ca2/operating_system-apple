//
//  window.h
//  acme_windowing_kit
//
//  created by camilo on 2026-02-06 01:23 <3ThomasBorregaardSørensen!!
//
#pragma once

#include "acme/windowing/window.h"
#include <CoreGraphics/CoreGraphics.h>



namespace apple_kit
{


class acme_window_bridge;


namespace acme
{


namespace windowing
{
class  window :

virtual public ::acme::windowing::window
{
public:
   
   ::pointer<::apple_kit::acme_window_bridge>   m_pacmewindowbridge;
   
   
   window();
   ~window() override;


   ::particle * get_acme_window_bridge() override;


   virtual void _draw_background(CGContextRef cgcontextref);
   
   virtual void _draw_foreground(CGContextRef cgcontextref);
   
};



} //namespace windowing

} // namespace acme


} // namespace apple_kit
