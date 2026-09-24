//
//  enum.m
//  write_text_quartz2d
//
//  Created by Camilo Sasuke on 28/05/21.
//
//#import <Foundation/Foundation.h>
#include "framework.h"



BOOL IsFontUsable(NSString *fontName)
{
    if (fontName == nil || fontName.length == 0)
    {
        return NO;
    }

    CTFontRef font = CTFontCreateWithName(
        (__bridge CFStringRef)fontName,
        12.0,
        NULL);

    if (font == NULL)
    {
        return NO;
    }

    BOOL usable = YES;

    CFStringRef familyName =
        CTFontCopyName(font, kCTFontFamilyNameKey);

    if (familyName != NULL)
    {
        NSString *family =
            (__bridge NSString *)familyName;

        if ([family caseInsensitiveCompare:@"GB18030 Bitmap"] == NSOrderedSame)
        {
            usable = NO;
        }

        CFRelease(familyName);
    }

    if (usable)
    {
        CFDataRef head = CTFontCopyTable(
            font,
            kCTFontTableHead,
            kCTFontTableOptionNoOptions);

        if (head == NULL)
        {
            usable = NO;
        }
        else
        {
            CFRelease(head);
        }
    }

    CFRelease(font);

    return usable;
}

unsigned long apple_get_fonts(char ***p)
{
    
#ifdef APPLE_IOS
    NSArray *fonts = [UIFont familyNames];
#else

   NSArray *fonts = [[NSFontManager sharedFontManager] availableFontFamilies];
#endif
   
   unsigned long c = [fonts count];
   
   if(c == 0)
   {
      
      return 0;
      
   }
   
   *p = (char **) malloc(sizeof(char *) * c);
   
   int iFinalCount = 0;
   
   for(unsigned long u = 0; u < c; u++)
   {
      
      NSString * pstr =[fonts objectAtIndex: u];
      
      if(!IsFontUsable(pstr))
      {
         
         continue;
         
      }
      
      (*p)[iFinalCount] = strdup([pstr UTF8String]);
      
      iFinalCount++;
      
   }
   
   return iFinalCount;

}





