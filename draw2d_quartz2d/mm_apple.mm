//
//  draw2d_mm_apple.m
//  draw2d_quartz2d
//
//  Created by Camilo Sasuke Tsumanuma on 25/08/18.
//  Copyright © 2018 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
#import <Foundation/Foundation.h>

#ifdef MACOS
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

#ifdef MACOS
#define kCTFontWeightUltraLight NSFontWeightUltraLight
#define kCTFontWeightThin NSFontWeightThin
#define kCTFontWeightLight NSFontWeightLight
#define kCTFontWeightRegular NSFontWeightRegular
#define kCTFontWeightMedium NSFontWeightMedium
#define kCTFontWeightSemibold NSFontWeightSemibold
#define kCTFontWeightBold NSFontWeightBold
#define kCTFontWeightHeavy NSFontWeightHeavy
#define kCTFontWeightBlack NSFontWeightBlack
#else
#define kCTFontWeightUltraLight UIFontWeightUltraLight
#define kCTFontWeightThin UIFontWeightThin
#define kCTFontWeightLight UIFontWeightLight
#define kCTFontWeightRegular UIFontWeightRegular
#define kCTFontWeightMedium UIFontWeightMedium
#define kCTFontWeightSemibold UIFontWeightSemibold
#define kCTFontWeightBold UIFontWeightBold
#define kCTFontWeightHeavy UIFontWeightHeavy
#define kCTFontWeightBlack UIFontWeightBlack
#endif

//#define FW_THIN             100
//#define FW_EXTRALIGHT       200
//#define FW_LIGHT            300
//#define e_font_weight_normal           400
//#define FW_MEDIUM           500
//#define FW_SEMIBOLD         600
//#define e_font_weight_bold             700
//#define FW_EXTRABOLD        800
//#define FW_HEAVY            900


double nsfont_get_ctweight(int iWeight)
{
   
   double dCoreTextWeight = kCTFontWeightRegular;
   
   if (iWeight < 100 + 50) // FW_THIN
   {
      
      dCoreTextWeight = kCTFontWeightUltraLight;
      
   }
   else if (iWeight < 200 + 50) // FW_EXTRALIGHT FW_ULTRALIGHT
   {
      
      dCoreTextWeight = kCTFontWeightThin;
      
   }
   else if (iWeight < 300 + 50) // FW_LIGHT
   {

      dCoreTextWeight = kCTFontWeightLight;
      
   }
   else if (iWeight < 400 + 50) // FW_NORMAL FW_REGULAR
   {

      dCoreTextWeight = kCTFontWeightRegular;
      
   }
   else if (iWeight < 500 + 50) // FW_MEDIUM
   {

      dCoreTextWeight = kCTFontWeightMedium;
      
   }
   else if (iWeight < 600 + 50) // FW_SEMIBOLD FW_DEMIBOLD
   {

      dCoreTextWeight = kCTFontWeightSemibold;
      
   }
   else if (iWeight < 700 + 50) // FW_BOLD
   {
      
      dCoreTextWeight = kCTFontWeightBold;
      
   }
   else if (iWeight < 800 + 50) // FW_EXTRABOLD FW_ULTRABOLD
   {

      dCoreTextWeight = kCTFontWeightHeavy;
      
   }
   else // FW_BLACK FW_HEAVY 900
   {

      dCoreTextWeight = kCTFontWeightBlack;
      
   }

   return dCoreTextWeight;

}



