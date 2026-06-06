//
//  cg_affine_transform.cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/06/26 17:52
//  <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#include "framework.h"
#include "cg_affine_transform.h"


#include <CoreGraphics/CoreGraphics.h>

namespace core_graphics
{

   cg_affine_transform::cg_affine_transform()
   {
      
      m_paffinetransform = new cg_affine_transform_t;
      
      *m_paffinetransform = CGAffineTransformIdentity;
      
   }


   cg_affine_transform::~cg_affine_transform()
   {
   
      if(m_paffinetransform)
      {
       
         delete m_paffinetransform;
         
      }
      
   }
   

   cg_affine_transform & cg_affine_transform::operator = (const cg_affine_transform & affinetransform)
   {
      
      *m_paffinetransform = *affinetransform.m_paffinetransform;
      
      return *this;
      
   }


void cg_affine_transform::translate(::f64 Δx, ::f64 Δy)
{
   
   *m_paffinetransform = CGAffineTransformTranslate(*m_paffinetransform, Δx, Δy);
   
}


void cg_affine_transform::translate(const ::f64_size & Δ) {translate(Δ.cx, Δ.cy);}

void cg_affine_transform::scale(::f64 rx, ::f64 ry)
{
   
   *m_paffinetransform = CGAffineTransformScale(*m_paffinetransform, rx, ry);
   
}
void cg_affine_transform::scale(const ::f64_size &  r) {scale(r.cx, r.cy);};


}
