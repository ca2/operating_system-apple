//
//  icon.mm
//  innate_ui_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-09-20 18:50
//
//
//
#include "framework.h"
#import <AppKit/AppKit.h>
#include "icon.h"


namespace innate_ui_appkit
{



void icon::__create()
{
   
   auto buffer = m_memory.data();
   auto size = m_memory.size();
   
   NSData *imageData = [[NSData alloc] initWithBytes:buffer length:size];
   
   // Create NSImage from NSData
   NSImage *image = [[NSImage alloc] initWithData:imageData];
   
   m_pnsimage = image;
   
}


void icon::__icon_release()
{
 
   m_pnsimage = nil;
   
}

} // namespace innate_ui_appkit




