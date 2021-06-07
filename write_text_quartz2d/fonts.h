// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


namespace write_text_quartz2d
{


   class CLASS_DECL_WRITE_TEXT_QUARTZ2D font_department :
      virtual public ::write_text::font_department
   {
   public:



      font_department();
      virtual ~font_department();


      virtual ::e_status initialize(::object * pobject) override;

      virtual void enum_fonts(::write_text::font_enum_item_array & itema) override;
      //virtual void sorted_fonts(::write_text::font_enum_item_array & itema);


   };


} // namespace write_text_quartz2d



