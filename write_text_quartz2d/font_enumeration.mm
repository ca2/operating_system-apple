//
//  enum.m
//  write_text_quartz2d
//
//  Created by Camilo Sasuke on 28/05/21.
//
//#import <Foundation/Foundation.h>
#include "framework.h"



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
   
   for(unsigned long u = 0; u < c; u++)
   {
      
      NSString * pstr =[fonts objectAtIndex: u];
      
      (*p)[u] = strdup([pstr UTF8String]);
      
   }
   
   return c;

}





