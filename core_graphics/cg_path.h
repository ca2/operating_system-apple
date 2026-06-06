// Created by camilo on 2026-06-04 19:22 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
// From innate_subsystem_macos on 2026-06-05 17:00 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/nano/graphics/path.h"



namespace core_graphics
{


class CLASS_DECL_CORE_GRAPHICS cg_path :
virtual public ::particle
{
public:
   
   //CGMutablePathRef m_ppath;
   
   cg_path_t m_cgpath;
   
   cg_path();
   ~cg_path();
   
   
   virtual void add_arc(
       const cg_affine_transform * paffinetransform,
       ::f64 x,
                        ::f64 y,
                        ::f64 radius,
                        ::f64 startAngle,
                        ::f64 endAngle,
       bool clockwise
   );
   virtual void close_sub_path();
   
};



} // namespace core_graphics



