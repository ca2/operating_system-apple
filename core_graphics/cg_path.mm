//
//  cg_path.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/06/26 21:12
//  <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#include <CoreGraphics/CoreGraphics.h>
#include "_mm.h"



void cg_path_release(cg_path_t & cgpath)
{
 
   if(cgpath.is_set())
   {
      
      CGPathRelease(CGPATH(cgpath));
      
      cgpath.clear();
      
   }
   
   
}


cg_path_t cg_mutable_path_create()
{
   
   CGMutablePathRef mutablepathref = CGMutablePathCreate();

   return {(::uptr) mutablepathref};

}




void cg_path_add_arc(cg_path_t cgpath,
                     const cg_affine_transform_t * ptransfrom,
                     cg_float x, cg_float y, cg_float radius, cg_float startAngle, cg_float endAngle,
                     bool clockwise)
{
   
   CGPathAddArc(CGPATH(cgpath), ptransform, x, y, radius, startAngle, endAngle, clockwise);
   
}
void cg_path_close_subpath(cg_path_t cgpath)
{
   
   CGPathCloseSubPath(CGPATH(cgpath));
}


