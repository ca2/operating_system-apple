#pragma once


#include "aura/graphics/draw2d/draw2d.h"


namespace draw2d_quartz2d
{


   class CLASS_DECL_DRAW2D_QUARTZ2D draw2d :
      virtual public ::draw2d::draw2d
   {
   public:


      draw2d();
      ~draw2d() override;


      void initialize(::object * pobject) override;

      string write_text_get_default_library_name() override;

      
   };


} // namespace draw2d_quartz2d



