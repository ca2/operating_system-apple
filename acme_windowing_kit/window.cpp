//
//  window.cpp
//  acme_windowing_kit
//
//  created by camilo on 2026-02-06 01:26 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "window.h"
#include "acme_window_bridge.h"

namespace apple_kit
{

class acme_window_bridge;
namespace acme
{


namespace windowing
{


window::window()
{
   
   
}


window::~window()
{
   
}

::particle * window::get_acme_window_bridge()
{
   
   return m_pacmewindowbridge.cast < ::particle >();
   
}


void window::_draw_background(CGContextRef cgcontextref)
{
   
}

 void window::_draw_foreground(CGContextRef cgcontextref)
{
    
    
 }



} //namespace windowing

} // namespace acme


} // namespace apple_kit
