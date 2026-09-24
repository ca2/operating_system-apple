#pragma once


#include "aura/graphics/draw2d/draw2d.h"
#include "acme/operating_system/apple/cgref.h"


namespace draw2d_quartz2d
{


   class CLASS_DECL_DRAW2D_QUARTZ2D draw2d :
      virtual public ::draw2d::draw2d
   {
   public:

      class private_font :
         virtual public ::particle
      {
      public:
         
         cfref<CGFontRef>     m_cgfontref;
         
      };
      
      string_map < ::pointer < private_font > >         m_mapPrivateFont;

      draw2d();
      ~draw2d() override;


      void initialize(::particle * pparticle) override;

      string write_text_get_default_implementation_name() override;

      
      CGFontRef private_cgfontref(::platform::context * pcontext, const ::file::path & path);
      
      
   };


} // namespace draw2d_quartz2d



