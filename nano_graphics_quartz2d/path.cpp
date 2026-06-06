// Created by camilo on 2026-06-04 19:27 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
// From innate_subsystem_macos on 2026-06-05 17:00 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "path.h"
#include "core_graphics/cg_affine_transform.h"
#include "core_graphics/cg_path.h"
#include "acme/prototype/geometry2d/rectangle.h"

namespace quartz2d
{

   namespace nano
   {

  
      namespace graphics
   {
      
path::path()
{
    
   
}

path::~path()
{
   

}

void path::add_arc(::f64 x, ::f64 y, ::f64 w, ::f64 h, const ::f64_angle &angleStart,
       const ::f64_angle &angleSweep)
{
   
   defer_construct_newø(m_pcgpath);
   
   auto rectangle = ::f64_rectangle_dimension(x, y, w, h);
   
   auto pointCenter = rectangle.center();

   auto sizeRadius = rectangle.radius();
   
   auto pcgaffinetransform = create_newø<::core_graphics::cg_affine_transform>();

   pcgaffinetransform->translate(pointCenter);

   pcgaffinetransform->scale(sizeRadius);

   auto angleEnd = angleStart + angleSweep;
   
   auto fStartRad = angleStart.radians();
   
   auto fEndRad = angleEnd.radians();
   
   bool clockwise = angleSweep > 0.;

   
   m_pcgpath->add_arc(
                      pcgaffinetransform,
       0.0,
       0.0,
       1.0,
       fStartRad,
       fEndRad,
       clockwise);
   
}


void path::close_figure()
{
   
   m_pcgpath->close_sub_path();
   
}

      
      } // namespace graphics
      } // namespace nano
      } // namespace quartz2d



