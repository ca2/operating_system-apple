// Created by camilo on 2026-06-04 19:27 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
// From innate_subsystem_macos on 2026-06-05 17:00 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "cg_path.h"

#include <CoreGraphics/CoreGraphics.h>

namespace core_graphics
{


path::path()
{
   m_cgpath.m_u = (::uptr) (CGPathRef) CGPathCreateMutable();
   
}

path::~path()
{
   
   if(m_cgpath.m_u)
   {
      
      CGPathRelease((CGPathRef) m_cgpath.m_u);
      
   }
   
}

void path::add_arc(const cg_affine_transform * paffinetransform,
                   ::f64 x,
                                    ::f64 y,
                                    ::f64 radius,
                                    ::f64 startAngle,
                                    ::f64 endAngle,
                   bool clockwise)
{
   
//   CGRect rect = CGRectMake(x, y, w, h);
//
//   CGFloat cx = rect.origin.x + rect.size.width  / 2.0;
//   CGFloat cy = rect.origin.y + rect.size.height / 2.0;
//
//   CGFloat rx = rect.size.width  / 2.0;
//   CGFloat ry = rect.size.height / 2.0;
//
//   CGAffineTransform t =
//       CGAffineTransformTranslate(
//           CGAffineTransformIdentity,
//           cx,
//           cy);
//
//   t = CGAffineTransformScale(t, rx, ry);
//
//   auto angleEnd = angleStart + angleSweep;
//   
//   auto fStartRad = angleStart.radians();
//   
//   auto fEndRad = angleEnd.radians();
//   
//   bool clockwise = angleSweep > 0.;

   CGAffineTransform * pcgaffinetransform = nullptr;
   
   if(pcgaffinetransform)
   {
      
      pcgaffinetransform = paffinetransfrom->m_paffinetransform;
      
   }
   
   CGPathAddArc(
       (CGPathRef) m_cgpath.m_u,
                pcgaffinetransform,
       0.0,
       0.0,
       1.0,
       startAngle,
       endAngle,
       clockwise);
   
}


void path::close_sub_path()
{
   
   CGPathCloseSubpath((CGPathRef) m_cgpath.m_u);
   
}

      
      } // namespace core_graphics



