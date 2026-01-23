#pragma once


#include "aura/graphics/draw2d/brush.h"


namespace typeface_quartz2d
{


   class CLASS_DECL_TYPEFACE_QUARTZ2D brush : 
      virtual public ::draw2d::brush
   {
   public:


      brush();
      virtual ~brush();


      // void dump(dump_context & dumpcontext) const override;


   };


} // namespace typeface_quartz2d


