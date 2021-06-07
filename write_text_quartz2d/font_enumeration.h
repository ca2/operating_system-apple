// Rereated by camilo on 2021-06-06 02:03 <3ThomasBS_!!
#pragma once


namespace write_text_quartz2d
{


   class CLASS_DECL_WRITE_TEXT_QUARTZ2D font_enumeration :
      virtual public ::write_text::font_enumeration
   {
   public:


      font_enumeration();
      ~font_enumeration() override;


      ::e_status on_enumerate_fonts() override;


   };


} // namespace write_text_quartz2d



