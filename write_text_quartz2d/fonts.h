// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


#include "aura/graphics/write_text/fonts.h"


namespace write_text_quartz2d
{


   class CLASS_DECL_WRITE_TEXT_QUARTZ2D fonts :
      virtual public ::write_text::fonts
   {
   public:



      fonts();
      ~fonts() override;


      void initialize(::particle * pparticle) override;

      //virtual void enum_fonts(::write_text::font_enum_item_array & itema) override;
      //virtual void sorted_fonts(::write_text::font_enum_item_array & itema);


   };


} // namespace write_text_quartz2d



