#pragma once


#include "object.h"
#include "aura/graphics/draw2d/brush.h"


namespace draw2d_quartz2d
{

   
   class CLASS_DECL_DRAW2D_QUARTZ2D brush : 
      virtual public ::draw2d_quartz2d::object,
      virtual public ::draw2d::brush
   {
   public:
      
      
      CGGradientRef     m_cggradientref;
      CGColorRef        m_cgcolorref;
      CGColorSpaceRef   m_cgcolorspaceref;
      
      
      brush();
      ~brush() override;
      
      
      //virtual void * get_os_data() const;
      
      void update(::draw2d::graphics * pgraphics) override;

      void destroy() override;
      //void destroy_os_data() override;
     
      //void dump(dump_context & dumpcontext) const override;

   };


} // namespace draw2d_quartz2d





