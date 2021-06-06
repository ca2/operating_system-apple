// Created by camilo 2021-01
// Recreated by camilo 2021-02-10 <3TBS_!!
// Recreated by camilo on 2021-06-06 02:03 <3ThomasBS_!!
#include "framework.h"


unsigned long apple_get_fonts(char ***p);


namespace write_text_quartz2d
{

   
   font_enumeration::font_enumeration()
   {

   }


   font_enumeration::~font_enumeration()
   {

   }


   ::e_status font_enumeration::on_enumerate_fonts()
   {

      char ** ppszFontNames = nullptr;

      unsigned long c = apple_get_fonts(&ppszFontNames);

      if(c > 0)
      {

         for(unsigned long u = 0; u < c; u++)
         {
            
            auto pszFontName = ppszFontNames[u];
            
            if(::is_null(pszFontName))
            {
               
               continue;
               
            }
            
            auto pfontenumerationitem = __new(::write_text::font_enumeration_item(pszFontName, pszFontName));

            m_pitema->add(pfontenumerationitem);

            free(pszFontName);

         }

      }
      
      if(::is_null(ppszFontNames))
      {
         
         free(ppszFontNames);

      }

      return ::success;

   }


} // namespace write_text_quartz2d



