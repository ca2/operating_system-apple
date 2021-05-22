#include "framework.h"


CLASS_DECL_DRAW2D_QUARTZ2D ::e_status initialize_quartz2d();
CLASS_DECL_DRAW2D_QUARTZ2D ::e_status terminate_quartz2d();


namespace draw2d_quartz2d
{


   draw2d::draw2d()
   {
      
      initialize_quartz2d();


   }


   draw2d::~draw2d()
   {

      terminate_quartz2d();

   }


   ::e_status draw2d::initialize(::object * pobject)
   {

      auto estatus = ::draw2d::draw2d::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }
   
      estatus = initialize_quartz2d();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;
   
   }


   string draw2d::write_text_get_default_library_name()
   {

      return "quartz2d";

   }


} // namespace draw2d_quartz2d


CLASS_DECL_DRAW2D_QUARTZ2D ::e_status initialize_quartz2d()
{
   
   return ::success;
   
}


CLASS_DECL_DRAW2D_QUARTZ2D ::e_status terminate_quartz2d()
{
   
   return ::success;
   
}



