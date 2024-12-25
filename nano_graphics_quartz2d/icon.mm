//
//  icon.mm
//  innate_ui_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-09-20 18:50
//
//
//
#include "framework.h"
#include "device.h"
#ifdef APPLE_IOS
#import <UIKit/UIKit.h>
#elif defined(MACOS)
#import <AppKit/AppKit.h>
#else
#error "todo"
#endif

#include "icon.h"


namespace quartz2d
{

   namespace nano
   {

  
      namespace graphics
   {


void icon::load_image_file(const void *p, memsize size)

{
   
   //auto buffer = m_memory.data();
   //auto size = m_memory.size();
   
   NSData *imageData = [[NSData alloc] initWithBytes:p length:size];
#ifdef APPLE_IOS
    // Create NSImage from NSData
    UIImage *image = [[UIImage alloc] initWithData:imageData];
    
    m_pUIImage = (__bridge_retained void *) image;
    
#elif defined(MACOS)
    
   // Create NSImage from NSData
   NSImage *image = [[NSImage alloc] initWithData:imageData];
   
   m_pNSImage = (__bridge_retained void *) image;
    
#endif
   
}

      
      
      void icon::_draw_in_context(::quartz2d::nano::graphics::device * pdevice, int x, int y, int cx, int cy)
      {
         
#ifdef MACOS
         
         auto pnsgraphicscontext = [NSGraphicsContext graphicsContextWithCGContext:pdevice->m_cgcontext flipped: true];
         
         [ NSGraphicsContext setCurrentContext:pnsgraphicscontext ];
         
         NSRect nsrect;
         
         nsrect.origin.x = x;
         nsrect.origin.y = y;
         nsrect.size.width = cx;
         nsrect.size.height = cy;
          NSImage * puiimage = (__bridge NSImage *)m_pNSImage;

         [puiimage drawInRect:nsrect];
          
#elif defined(APPLE_IOS)
          
          UIGraphicsPushContext(pdevice->m_pdc);
          
          CGRect nsrect;
          
          nsrect.origin.x = x;
          nsrect.origin.y = y;
          nsrect.size.width = cx;
          nsrect.size.height = cy;
          
          UIImage * puiimage = (__bridge UIImage *)m_pUIImage;
          
          [ puiimage drawInRect : nsrect ];
          
          UIGraphicsPopContext();
          
#else
#error "todo"
#endif
         
      }
//
//void icon::__icon_release()
//{
// 
//   m_pnsimage = nil;
//   
//}

      
      } // namespace graphics
      } // namespace nano
      } // namespace quartz2d



