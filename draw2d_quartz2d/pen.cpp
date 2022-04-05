#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   pen::pen()
   {
      
   }
   
   
   pen::~pen()
   {
      
      destroy();
      
   }
   
   
   void pen::dump(dump_context & dumpcontext) const
   {
      
      ::draw2d::object::dump(dumpcontext);
      
   }
   
   
} // namespace draw2d_quartz2d



