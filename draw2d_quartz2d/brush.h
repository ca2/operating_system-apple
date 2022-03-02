#pragma once


#include "aura/graphics/draw2d/brush.h"


namespace draw2d_quartz2d
{

   
   class CLASS_DECL_DRAW2D_QUARTZ2D brush : 
      virtual public ::draw2d_quartz2d::object,
      virtual public ::draw2d::brush
   {
   public:
      
      
      CGGradientRef     m_gradientref;
      CGColorRef        m_colorref;
      CGColorSpaceRef   m_colorspaceref;
      
      
      brush();
      ~brush() override;
      
      
      //virtual void * get_os_data() const;
      
      void create(::draw2d::graphics * pgraphics, i8 iCreate) override;

      void destroy() override;
      void destroy_os_data() override;
     
      void dump(dump_context & dumpcontext) const override;

   };


} // namespace draw2d_quartz2d





