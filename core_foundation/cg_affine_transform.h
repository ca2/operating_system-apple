//
//  cg_affine_transform.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-06-05 17:47
//  <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//

#pragma once



namespace core_graphics
{


   class CLASS_DECL_CORE_GRAPHICS cg_affine_transform :
      virtual public ::particle
   {
   public:
      
      
      cg_affine_transform_t * m_paffinetransform;
      
      
      cg_affine_transform();
      ~cg_affine_transform() override;
      
      cg_affine_transform & operator = (const cg_affine_transform & affinetransform);
      
      virtual void translate(::f64 Δx, ::f64 Δy);
      virtual void translate(const ::f64_size & Δ);
      virtual void scale(::f64 rx, ::f64 ry);
      virtual void scale(const ::f64_size &  r);
      
   };


} // namespace core_graphics

