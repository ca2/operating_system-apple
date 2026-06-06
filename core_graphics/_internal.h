//
//  _internal.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/06/26. 17:49
//  <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#pragma once


#include <CoreGraphics/CoreGraphics.h>

//#include <CoreGraphics/CoreGraphics.h>

#define CGCONTEXT(s) ((CGContextRef)(s).m_u)
#define CGCOLOR(s) ((CGColorRef)(s).m_u)
#define CGIMAGE(s) ((CGImageRef)(s).m_u)
#define CGPATH(s) ((CGPathRef)(s).m_u)
#define CGFONT(s) ((CGFontRef)(s).m_u)


#define CTLINE(s) ((CTLineRef)(s).m_u)


namespace core_graphics
{

   struct cg_affine_transform_t :
      public CGAffineTransform
   {
      
      cg_affine_transform_t()
      {
         
         *((CGAffineTransform*) this) = CGAffineTransformIdentity;
         
      }
      cg_affine_transform_t(const CGAffineTransform & transform)
      {
         
         *((CGAffineTransform*) this) = transform;
         
      }
      
      cg_affine_transform_t & operator =(const CGAffineTransform & transform)
      {
         
         *((CGAffineTransform*) this) = transform;
         
         return * this;
         
      }
      
   };

}
