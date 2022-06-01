//
//  image.m
//  aura_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 01/06/22.
//
#include "framework.h"
#import <CoreGraphics/CoreGraphics.h>

#ifdef APPLE_MACOS

void * ns_image_get_image_data(int & width, int & height, int & iScan, NSImage * image)
{
   
   CGImageRef inputCGImage = [image CGImageForProposedRect:NULL context:NULL hints:NULL];
   
   return cg_image_get_image_data(width, height, iScan, inputCGImage);
   
}

#else


#endif
