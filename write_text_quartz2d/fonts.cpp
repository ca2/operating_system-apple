// Created by camilo 2021-02-10 <3TBS_!!
#include "framework.h"
#include "acme/os/ansios/_pthread.h"


namespace write_text_quartz2d
{


   font_department::font_department()
   {


   }


   font_department::~font_department()
   {


   }


   ::e_status font_department::initialize(::object * pobject)
   {

      auto estatus = ::font_department::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status font_department::finalize()
   {

      auto estatus = ::font_department::finalize();

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void font_department::enum_fonts(::write_text::font_enum_item_array & itema)
   {
   }


} // namespace write_text_quartz2d



