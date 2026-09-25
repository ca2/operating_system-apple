#include "framework.h"
#include "graphics.h"
#include "bitmap.h"
#include "image.h"
#include "brush.h"
#include "pen.h"
#include "font.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/scoped_restore.h"
//#include "acme/prototype/geometry2d/shape_array.h"
//#include "acme/prototype/geometry2d/shape.h"
//#include "acme/prototype/geometry2d/item.h"
#include "acme/prototype/geometry2d/ellipse.h"
#include "aura/graphics/draw2d/domain.h"
#include "aura/graphics/draw2d/graphics_lease.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/write_text/text_out.h"
#include "aura/graphics/write_text/draw_text.h"
#include "aura/platform/context.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/operating_system/apple/cfref.h"
#include "acme/operating_system/apple/cgref.h"
//#include <math.h>
//#include <memory.h>
#include <CoreFoundation/CFDictionary.h>
//#include "acme/prototype/geometry2d/_geometry2d.h"
//#include "acme/prototype/geometry2d/_collection.h"
//#include "acme/prototype/geometry2d/_defer.h"
//#include "acme/prototype/geometry2d/_defer_item.h"
//#include "aura/graphics/write_text/_defer_geometry2d_item.h"


//unsigned long apple_get_fonts(char *** p);
double nsfont_get_ctweight(int iWeight);


::cfref <CGContextRef> cg_create_bitmap_context(CGSize size);


namespace draw2d_quartz2d
{

   void copy(CGAffineTransform & affine, const ::geometry2d::matrix & m)
   {

      affine.a = m.a1;
      affine.b = m.a2;
      affine.c = m.b1;
      affine.d = m.b2;
      affine.tx = m.c1;
      affine.ty = m.c2;

   }


   void copy(::geometry2d::matrix & m, const CGAffineTransform & affine)
   {

      m.a1 = affine.a;
      m.a2 = affine.b;
      m.b1 = affine.c;
      m.b2 = affine.d;
      m.c1 = affine.tx;
      m.c2 = affine.ty;

   }


   graphics::graphics()
   {
      
      m_iType = -1;
      defer_create_synchronization();

      m_iSaveGraphicsContext         = 0;
      m_bPrinting       = false;
      //m_pimageimplAlphaBlend  = nullptr;
      m_ewritetextrendering  = ::write_text::e_rendering_anti_alias_grid_fit;
      m_bOwnGraphicsContext          = false;
      //m_cgcontextref             = nullptr;
      //m_cglayerref           = nullptr;

   }


   graphics::~graphics()
   {

      destroy();

   }


   void graphics::destroy()
   {
      
      ::draw2d::graphics::destroy();
      
      DeleteDC();
      
//      destroy_os_data();
//      
//      ::draw2d::graphics::destroy();
//      
   }

   
//   void graphics::destroy_os_data()
//   {
//
//      DeleteDC();
//
//   }


//#if 0

//   void graphics::dump(dump_context & dumpcontext) const
//   {
//
//      ::draw2d::graphics::dump(dumpcontext);
//
//      dumpcontext << "\n";
//
//   }


   void graphics::_create_memory_graphics(const ::i32_size& sizeParam, ::draw2d::domain * pdraw2ddomain)
   {

      destroy();
      
      set_draw2d_domain(pdraw2ddomain);

      ::cfref<CGContextRef> cgcontextref;
      
      CGSize size;

      size.width = sizeParam.cx;

      size.height = sizeParam.cy;


      //if(pgraphics == nullptr || pgraphics->get_os_data() == nullptr)
      {

         cgcontextref = cg_create_bitmap_context(size);

      }
//      else
//      {
//
//         cg = (CGContextRef) pgraphics->get_os_data();
//
//      }


      m_cglayerref = CGLayerCreateWithContext(cgcontextref, size, nullptr);

      if(m_cglayerref)
      {
         
         m_cgcontextref = CGLayerGetContext(m_cglayerref);
         
         m_bOwnGraphicsContext = false;

      }

      if(!m_cgcontextref)
      {

         //CGLayerRelease(m_cglayerref);
         
         //m_cglayerref.release();

         //m_cglayerref = nullptr;

      }

      //if(pgraphics == nullptr || pgraphics->get_os_data() == nullptr)
      {

         //CGContextRelease(cgcontextref);
         
         //cgcontextref.release();

      }

      if(!m_cglayerref)
      {

         //CGContextRelease(cgcontextref);
         
         throw exception(error_resource);

      }

   }


   void graphics::create_bitmap_graphics(::draw2d::bitmap * pdraw2dbitmap, ::draw2d::domain * pdraw2ddomain)
   {

      ::cast < ::draw2d_quartz2d::bitmap > pbitmap = pdraw2dbitmap;
      
      auto context = (CGContextRef) pbitmap->m_cgcontextref;
      if(!context)
      {

         throw ::exception(error_wrong_state);

      }

      // Retain the particular context, not just the bitmap that can replace it.
      CGContextRetain(context);
      if(m_cgcontextref && m_bOwnGraphicsContext)
      {

         //CGContextRelease(m_cgcontextref);
         
         m_cgcontextref.release();

      }

      if(m_cglayerref)
      {

         //CGLayerRelease(m_cglayerref);
         //m_cglayerref = nullptr;
         
         m_cglayerref.release();

      }

      m_cgcontextref = context;
      m_pdraw2dbitmap = pdraw2dbitmap;
      m_bOwnGraphicsContext = true;
      m_bTargetRectangleModified = true;

   }


   int graphics::GetDeviceCaps(int nIndex)
   {
      
      throw ::exception(error_not_implemented);
      
      return 0;

   }


   f64_point graphics::GetBrushOrg()
   {

      throw ::exception(error_not_implemented);
      
      return ::f64_point();

   }


   f64_point graphics::SetBrushOrg(double x, double y)
   {

      throw ::exception(error_not_implemented);
      
      return ::f64_point();

   }


   f64_point graphics::SetBrushOrg(const ::f64_point & point)
   {

      throw ::exception(error_not_implemented);
      
      return ::f64_point();

   }


   void graphics::set(::draw2d::bitmap * pbitmap)
   {

      ::pointer < ::draw2d_quartz2d::bitmap > pbitmapQuartz = pbitmap;

      if(pbitmapQuartz.is_set())
      {

         attach(pbitmapQuartz->m_cgcontextref);

         m_bOwnGraphicsContext = false;

         m_pdraw2dbitmap = pbitmap;

      }

   }


   f64_size graphics::get_extents()
   {

      return ::f64_size(0, 0);
      
   }

   
   f64_point graphics::GetWindowOrg()
   {

      return ::f64_point();
      
   }


   f64_size graphics::GetWindowExt()
   {

      return ::f64_size(0, 0);
      
   }


//   f64_point graphics::set_origin(const ::f64_point & point)
//   {
//
//      return set_origin(point.x, point.y);
//
//   }


   f64_size graphics::set_extents(const ::f64_size & size)
   {

      return ::f64_size(0, 0);
      
   }


   f64_point graphics::SetWindowOrg(const ::f64_point & point)
   {

      return ::f64_point();
      
   }


//   f64_size graphics::set_window_ext(const ::f64_size & size)
//   {
//
//      return ::f64_size(0, 0);
//      
//   }


   void graphics::DPtoLP(::f64_rectangle * prectangle)
   {

   }


   void graphics::LPtoDP(::f64_rectangle * prectangle)
   {
      
   }


   void graphics::fill_region(::draw2d::region* pregion, ::draw2d::brush* pBrush)
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::frame_region(::draw2d::region* pregion, ::draw2d::brush* pBrush, double nWidth, double nHeight)
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::invert_region(::draw2d::region* pregion)
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::paint_region(::draw2d::region * pregion)
   {

      throw ::exception(error_not_implemented);;

   }


   f64_point graphics::current_position()
   {

      return m_pointCurrent;

   }


   void graphics::arc(double x, double y, double w, double h, ::f64_angle start, ::f64_angle extends)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      double end = start + extends;

      cg_context_scope cgcontextscope(m_cgcontextref);

      CGContextTranslateCTM(m_cgcontextref, x + w/2.0, y + h/2.0);

      CGContextScaleCTM(m_cgcontextref, w/2.0, h/2.0);

      CGContextAddArc(m_cgcontextref, 0.f, 0.f, 1.0f, start, end, extends < 0.0);

      //CGContextRestoreGState(m_cgcontextref);

      return _draw();

   }


   void graphics::polyline(const f64_point* lpPoints, ::collection::count nCount)
   {

      if(nCount < 2)
      {
         
         throw exception(error_invalid_parameter);
         
      }

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGContextBeginPath(m_cgcontextref);

      set_polygon(lpPoints, nCount);

      _draw();
      
   }


   void graphics::fill_rectangle(const ::f64_rectangle & rectParam, ::draw2d::brush * pbrush)
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGRect rectangle;
      
      copy(rectangle, rectParam);
      
      CGContextBeginPath(m_cgcontextref);
      
      CGContextAddRect(m_cgcontextref, rectangle);
      
      _fill(pbrush);

   }


   void graphics::fill_rectangle(const ::f64_rectangle & rectangle)
   {

      fill_rectangle(rectangle, m_pdraw2dbrush);
      
   }
   
   
   void graphics::frame_rectangle(const ::f64_rectangle & rectParam, ::draw2d::brush* pBrush)
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGRect rectangle;

      copy(rectangle, rectParam);

      CGContextBeginPath(m_cgcontextref);

      CGContextAddRect(m_cgcontextref, rectangle);

      _draw(pBrush);

   }


   void graphics::draw_rectangle(const ::f64_rectangle & rectParam, ::draw2d::pen* ppen)
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGRect rectangle;
      
      copy(rectangle, rectParam);
      
      //CGContextBeginPath(m_cgcontextref);
      
      CGRect r;
      
      r.origin.x=0;
      r.origin.y=0;
      r.size.width=1;
      r.size.height=1;
      //CGContextSaveGState(m_cgcontextref);
      cg_context_scope cgcontextscope(m_cgcontextref);

      auto rUser = CGContextConvertRectToUserSpace(m_cgcontextref, r);
      
      auto pixelSizeInUserSpace = rUser.size;
      CGContextTranslateCTM(m_cgcontextref, pixelSizeInUserSpace.width/2.0f, pixelSizeInUserSpace.height/2.0f);

      CGContextAddRect(m_cgcontextref, rectangle);
      //CGFloat translation = 0.5f / [[UIScreen mainScreen] scale];
      //... your drawing here ...
      //CGContextRestoreGState(m_cgcontextref);
      _draw(ppen);

   }


   void graphics::draw_rectangle(const ::f64_rectangle & rectangle)
   {

      draw_rectangle(rectangle, m_pdraw2dpen);

   }
   
  
   void graphics::invert_rectangle(const ::f64_rectangle & rectangle)
   {

      throw ::exception(error_not_implemented);

   }


   void graphics::DrawFocusRect(const ::f64_rectangle & rectangle)
   {

      throw ::exception(error_not_implemented);;

   }
   

   void graphics::draw_ellipse(const ::f64_rectangle & rectParam)
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGRect rectangle;

      copy(rectangle, rectParam);

      _set(m_pdraw2dpen);

      CGContextStrokeEllipseInRect(m_cgcontextref, rectangle);

   }


   void graphics::fill_ellipse(const ::f64_rectangle & rectParam)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGRect rectangle;

      copy(rectangle, rectParam);
      
      CGContextBeginPath(m_cgcontextref);

      CGContextAddEllipseInRect(m_cgcontextref, rectangle);

      _fill();

   }


   void graphics::set_polygon(const DOUBLE_POINT * p, ::collection::count c)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGContextMoveToPoint(m_cgcontextref, p[0].x, p[0].y);

      for(int i = 1; i < c; i++)
      {

         CGContextAddLineToPoint(m_cgcontextref, p[i].x, p[i].y);

      }
      
      CGContextClosePath(m_cgcontextref);

   }


   void graphics::set_polygon(const f64_point * p, ::collection::count c)
   {
      
      set_polygon((const DOUBLE_POINT *) p, c);

   }


   void graphics::set_polygon(const DOUBLE_POINT * p, ::collection::count c, const DOUBLE_POINT & pointOffset)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGContextMoveToPoint(m_cgcontextref, p[0].x + pointOffset.x, p[0].y + pointOffset.y);

      for(int i = 1; i < c; i++)
      {

         CGContextAddLineToPoint(m_cgcontextref, p[i].x + pointOffset.x, p[i].y + pointOffset.y);

      }
      
      CGContextClosePath(m_cgcontextref);

   }


   void graphics::set_polygon(const f64_point * p, ::collection::count c, const f64_point & pointOffset)
   {

      set_polygon((const DOUBLE_POINT *) p, c, (const DOUBLE_POINT &) pointOffset);

   }


   void graphics::fill_polygon(const ::f64_point * pa, ::collection::count nCount)
   {

      if(nCount <= 0)
      {
         
         throw exception(::error_invalid_parameter);
         
      }
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGContextBeginPath(m_cgcontextref);

      set_polygon(pa, nCount);

      _fill();

   }


   void graphics::draw_polygon(const ::f64_point * pa, ::collection::count nCount)
   {

      if(nCount <= 0)
      {

         throw exception(::error_invalid_parameter);
         
      }
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGContextBeginPath(m_cgcontextref);

      set_polygon(pa, nCount);

      _draw();

   }


   void graphics::polygon(const ::f64_point * pa, ::collection::count nCount)
   {

      if(nCount <= 0)
      {
       
         throw exception(::error_invalid_parameter);
         
      }
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGContextBeginPath(m_cgcontextref);

      set_polygon(pa, nCount);

      _fill_and_draw();

   }


   void graphics::rectangle(const ::f64_rectangle & rectParam)
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGRect rectangle;
      
      copy(rectangle, rectParam);
      
      CGContextBeginPath(m_cgcontextref);
      
      CGContextAddRect(m_cgcontextref, rectangle);
      
      _fill_and_draw();

   }


   void graphics::round_rectangle(const ::f64_rectangle & rectangle, const double dRadius)
   {

      ::draw2d::graphics::round_rectangle(rectangle, dRadius);
      
   }
   
static bool cg_context_has_y_flip(CGContextRef context)
{
   if (!context)
      return false;

   CGAffineTransform t = CGContextGetCTM(context);

   // Where does the context's +Y unit vector point in device space?
   CGPoint p0 = CGPointApplyAffineTransform(
      CGPointMake(0.0, 0.0), t);

   CGPoint py = CGPointApplyAffineTransform(
      CGPointMake(0.0, 1.0), t);

   return py.y < p0.y;
}
   void graphics::_draw_raw(const ::image::image_drawing & imagedrawing)
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }
      
      auto rectangleSource = imagedrawing.source_rectangle();
      
      auto rectangleTarget = imagedrawing.target_rectangle();

      double xDst = rectangleTarget.left;
      double yDst = rectangleTarget.top;
      double xSrc = rectangleSource.left;
      double ySrc = rectangleSource.top;

      auto pimageDrawing = imagedrawing.image();
      
      if(rectangleSource.size() == rectangleTarget.size())
      {
      
         int nWidth = rectangleTarget.width();
         int nHeight = rectangleTarget.height();
      
         _synchronous_lock synchronouslock(synchronization());

         auto pimage = pimageDrawing->get_source_image();
         
//         ::draw2d::graphics * pgraphicsSrc = pimage->g();
//         
//         if(pgraphicsSrc == nullptr)
//         {
//
//            throw exception(::error_null_pointer);
//
//         }

//         _synchronous_lock slSrc(pgraphicsSrc->synchronization());
//
//         if(pgraphicsSrc->get_os_data() == nullptr)
//         {
//
//            throw ::exception(::error_null_pointer);
//
//         }

         //::pointer < ::draw2d_quartz2d::image > pimageSrc = pimage;

//         ::pointer < ::draw2d::graphics > imageGraphics;
//
//         if(imageSrc.is_set())
//         {
//
//            imageGraphics = imageSrc->g();
//
//         }
//         else
//         {
//
//            informationf("imageSrc nullptr");
//
//         }

         ///CGContextRef pdcSrc = (CGContextRef) pgraphicsSrc->get_os_data();

         //CGImageRef pimage = CGBitmapContextCreateImage(pdcSrc);
         ::pointer < ::draw2d_quartz2d::bitmap > pbitmapSrc = pimage->get_bitmap_as_source(this);
         
         auto cgcontextref = pbitmapSrc->_cg_context_ref();
         
         if(!cgcontextref)
         {
            
            throw exception(::error_null_pointer);

         }
         
         auto cgimageref = ::as_cfref(CGBitmapContextCreateImage(cgcontextref));
         
         if(!cgimageref)
         {

            throw exception(::error_null_pointer);

         }

         size_t SrcW = CGImageGetWidth(cgimageref);

         size_t SrcH = CGImageGetHeight(cgimageref);

         CGRect rectangle;

         rectangle.origin.x = xDst;
         rectangle.origin.y = yDst;
         rectangle.size.width = nWidth;
         rectangle.size.height = nHeight;

         CGRect rectSub;

         if(::comparison::order(xSrc, SrcW) > 0)
         {

            //CGImageRelease(cgimageref);
            
            cgimageref.release();

            return;

         }

         if(::comparison::order(ySrc, SrcH) > 0)
         {

            //CGImageRelease(cgimageref);
            
            cgimageref.release();

            return;

         }

         rectSub.origin.x = 0;
         rectSub.origin.y = 0;
         rectSub.size.width = SrcW;
         rectSub.size.height = SrcH;
         
         if(imagedrawing.is_opacity_filter())
         {
         
            CGContextSetAlpha(m_cgcontextref, (CGFloat) imagedrawing.opacity().f32_opacity());
            
         }
         
         if(m_pdraw2dregion.is_null())
         {

            if(xSrc == 0 && ySrc == 0 && nWidth == SrcW && nHeight == SrcH)
            {
               
//               if(cg_context_has_y_flip(m_cgcontextref))
//               {
//                  
//                  information("y-flipped");
//               }
//               else{
//                  
//                  information("normal quartz2d");
//                  
//               }
//               cg_context_scope cgcontextscope1(m_cgcontextref);
//               CGContextTranslateCTM(
//                                     m_cgcontextref,
//                  0.0,
//                  CGRectGetMinY(rectangle) + CGRectGetMaxY(rectangle));
//
//               CGContextScaleCTM(
//                                 m_cgcontextref,
//                  1.0,
//                  -1.0);

               CGContextDrawImage(m_cgcontextref, rectangle, cgimageref);

            }
            else
            {

               //CGContextSaveGState(m_cgcontextref);
               cg_context_scope cgcontextscope(m_cgcontextref);

               CGContextClipToRect(m_cgcontextref, rectangle);

               rectangle.origin.x -= xSrc;
               rectangle.origin.y -= ySrc;
               rectangle.size.width = SrcW;
               rectangle.size.height =  SrcH;

               CGContextDrawImage(m_cgcontextref, rectangle, cgimageref);

               //cg_context_scope cgcontextscope(m_cgcontextref);CGContextRestoreGState(m_cgcontextref);

            }

         }
         else
         {

            //CGContextSaveGState(m_cgcontextref);
            cg_context_scope cgcontextscope(m_cgcontextref);

            _clip(m_pdraw2dregion);

            if(xSrc == 0 && ySrc == 0 && nWidth == SrcW && nHeight == SrcH )
            {

            }
            else
            {

               CGContextClipToRect(m_cgcontextref, rectangle);

               rectangle.origin.x -= xSrc;
               rectangle.origin.y -= ySrc;
               rectangle.size.width = SrcW;
               rectangle.size.height =  SrcH;

            }

            if(rectangle.origin.x < 0)
            {
               rectangle.size.width += rectangle.origin.x;
               rectangle.origin.x = 0;
            }
            if(rectangle.origin.y < 0)
            {
               rectangle.size.height += rectangle.origin.y;
               rectangle.origin.y = 0;
            }

            CGContextDrawImage(m_cgcontextref, rectangle, cgimageref);

            //CGContextRestoreGState(m_cgcontextref);

         }

         //CGImageRelease(cgimageref);

         if(imagedrawing.is_opacity_filter())
         {
         
            CGContextSetAlpha(m_cgcontextref, (CGFloat) 1.f);
            
         }

      }
      else
      {
         
         double nDstWidth;
         double nDstHeight;
         double nSrcWidth;
         double nSrcHeight;

         ::f64_rectangle rectFinal = imagedrawing.m_rectangleTarget;

         nDstWidth = imagedrawing.m_rectangleTarget.width();
         nDstHeight = imagedrawing.m_rectangleTarget.height();
         nSrcWidth = rectangleSource.width();
         nSrcHeight = rectangleSource.height();

         if(imagedrawing.m_eplacement == ::image::e_placement_aspect_fit)
         {
            
            double dW = nDstWidth / nSrcWidth;

            double dH = nDstHeight / nSrcHeight;

            double d = minimum(dW, dH);
            
            rectFinal.left = 0.0;

            rectFinal.top = 0.0;

            rectFinal.right = d * nSrcWidth;

            rectFinal.bottom = d * nSrcHeight;

            rectFinal.align_rate(
               imagedrawing.m_pointAlign.x,
               imagedrawing.m_pointAlign.y,
               imagedrawing.m_rectangleTarget);
            
            nDstWidth = rectFinal.width();
            nDstHeight = rectFinal.height();

         }

         if(nDstWidth <= 0 || nDstHeight <= 0 || nSrcWidth <= 0 || nSrcHeight <= 0)
         {

            throw exception(::error_invalid_parameter);

         }

         //pimage->defer_update_image();
         
         auto pimage = pimageDrawing->get_source_image();
         
         //::draw2d::graphics * pgraphicsSrc = pimage->g();
         
//         if(pgraphicsSrc == nullptr)
//         {
//
//            throw exception(::error_null_pointer);
//
//         }
//
//         if(pgraphicsSrc->get_os_data() == nullptr)
//         {
//
//            throw exception(::error_null_pointer);
//
//         }

//         CGImageRef pimage = CGBitmapContextCreateImage((CGContextRef) pgraphicsSrc->get_os_data());
//
//         if(pimage == nullptr)
//         {
//
//            throw exception(::error_null_pointer);
//
//         }
         
         ::pointer < ::draw2d_quartz2d::bitmap > pbitmapSrc = pimage->get_bitmap_as_source(this);
         
         auto cgimageref = ::as_cfref(CGBitmapContextCreateImage(pbitmapSrc->m_cgcontextref));
         
         if(!cgimageref)
         {

            throw exception(::error_null_pointer);

         }

         auto SrcW = CGImageGetWidth(cgimageref);

         auto SrcH = CGImageGetHeight(cgimageref);

         CGRect rectangle;

         rectangle.origin.x = rectFinal.left;
         rectangle.origin.y = rectFinal.top;
         rectangle.size.width = rectFinal.width();
         rectangle.size.height = rectFinal.height();
         
         if(imagedrawing.is_opacity_filter())
         {
         
            CGContextSetAlpha(m_cgcontextref, (CGFloat) imagedrawing.opacity().f32_opacity());
            
         }

         if(xSrc == 0 && ySrc == 0 && SrcW == nSrcWidth && SrcH == nSrcHeight)
         {

            CGContextDrawImage(m_cgcontextref, rectangle, cgimageref);

         }
         else
         {

            CGRect rectSub;

            rectSub.origin.x = xSrc;
            rectSub.origin.y = ySrc;
            rectSub.size.width = nSrcWidth;
            rectSub.size.height = nSrcHeight;

            auto imageSub = ::as_cfref(CGImageCreateWithImageInRect(cgimageref, rectSub));

            if(imageSub != nullptr)
            {

               CGContextDrawImage(m_cgcontextref, rectangle, cgimageref);

               //CGImageRelease(imageSub);
               
               //imageSub.release();

            }

         }

         //CGImageRelease(cgimageref);
         
         if(imagedrawing.is_opacity_filter())
         {
         
            CGContextSetAlpha(m_cgcontextref, (CGFloat) 1.f);
            
         }

      }

   }


   ::color::color graphics::GetPixel(double x, double y)
   {

      throw ::exception(error_not_implemented);;
      
      return ::color::color();

   }


   ::color::color graphics::GetPixel(const ::f64_point & point)
   {

      throw ::exception(error_not_implemented);

      return ::color::transparent;

   }


   ::color::color graphics::SetPixel(double x, double y, const ::color::color & color)
   {

      throw ::exception(error_not_implemented);;

      return ::color::color();

   }


   ::color::color graphics::SetPixel(const ::f64_point & point, const ::color::color & color)
   {

      throw ::exception(error_not_implemented);

      return ::color::color();

   }


   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   //// COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

   void graphics::text_out(double x, double y, const ::scoped_string & scopedstr)
   {

      if (m_pimageAlphaBlend)
      {
         
         if (m_bTargetRectangleModified)
         {

            defer_on_target_rectangle_update();

         }


         ::f64_rectangle rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());

         auto rectText = ::f64_rectangle(::f64_point(x, y), ::f64_size(get_text_extent(scopedstr)));

         if (rectIntersect.intersect(rectIntersect, rectText))
         {

            rectText.bottom = rectText.top + rectText.height() * 2;

            auto pimage1 = image()->create_image(rectText.size(), draw2d_domain());
            
            {
               
               auto pdraw2dgraphicsImage1 = pimage1->acquire_graphics();
               
               
               pdraw2dgraphicsImage1->clear(::color::transparent);
               pdraw2dgraphicsImage1->set(get_current_font());
               pdraw2dgraphicsImage1->set(get_current_brush());
               pdraw2dgraphicsImage1->text_out(0, 0, scopedstr);
               
            }
            
            {
               
               auto ppixmapImage1 = pimage1->map();
               
               auto ppixmapImageAlphaBlend = m_pimageAlphaBlend->map();
               
               ppixmapImage1->blend(::f64_point(), ppixmapImageAlphaBlend, f64_point((int)maximum(0, x - m_pointAlphaBlend.x), (int)maximum(0, y - m_pointAlphaBlend.y)), rectText.size());
               
            }

            set_alpha_mode(::draw2d::e_alpha_mode_blend);

            auto rectangleDst=i32_rectangle(::i32_point((int)x, (int)y),
                                 rectText.size());
            
            f64_rectangle rectangleSource(i32_point(), rectangleDst.size());
            
            ::image::image_source imagesource(pimage1, rectangleSource);
            
            ::image::image_drawing_options imagedrawingoptions(rectangleDst);
            
            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);
            
            draw(imagedrawing);

         }
         
         return;

      }
      
      TextOutRaw(x, y, scopedstr);

   }


   ::u32 graphics::GetTextAlign()
   {

      throw ::exception(error_not_implemented);;

      return 0;

   }




   void graphics::get_output_text_metrics(::write_text::text_metric * lpMetrics)
   {

      throw ::exception(error_not_implemented);;

   }


   // graphics 3.1 Specific functions
   ::u32 graphics::SetBoundsRect(const ::f64_rectangle & rectBounds, ::u32 flags)
   {

      throw ::exception(error_not_implemented);

      return 0;

   }


   ::u32 graphics::GetBoundsRect(::f64_rectangle * rectBounds, ::u32 flags)
   {

      throw ::exception(error_not_implemented);
      
      return 0;

   }


   int graphics::StartPage()
   {

      throw ::exception(error_not_implemented);

      return 0;

   }


   int graphics::EndPage()
   {

      throw ::exception(error_not_implemented);;

      return 0;

   }


   int graphics::AbortDoc()
   {

      throw ::exception(error_not_implemented);;
      
      return 0;

   }


   int graphics::EndDoc()
   {

      throw ::exception(error_not_implemented);
      
      return 0;

   }


   void graphics::SetPixelV(double x, double y, const ::color::color & color)
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::SetPixelV(const ::f64_point & point, const ::color::color & color)
   {

      throw ::exception(error_not_implemented);

   }


   void graphics::angle_arc(double x, double y, double dRadius, ::f64_angle fStartAngle, ::f64_angle fSweepAngle)
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::arc_to(const ::f64_rectangle & rectangle, const ::f64_point & pointStart, const ::f64_point & pointEnd)
   {

      throw ::exception(error_not_implemented);;

   }


   ::draw2d::pen * graphics::get_current_pen()
   {

      return m_pdraw2dpen;

   }


   ::draw2d::brush * graphics::get_current_brush()
   {

      return m_pdraw2dbrush;

   }


   ::draw2d::palette * graphics::get_current_palette()
   {

      return (::draw2d::palette *)nullptr;

   }


   ::write_text::font * graphics::get_current_font()
   {

      return m_pwritetextfont;

   }


   ::draw2d::bitmap * graphics::get_current_bitmap()
   {

      return m_pdraw2dbitmap;

   }


   void graphics::abort_path()
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::begin_path()
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::close_figure()
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::end_path()
   {

      throw ::exception(error_not_implemented);
      
   }


   void graphics::fill_path()
   {

      throw ::exception(error_not_implemented);

   }


   void graphics::flatten_path()
   {

      throw ::exception(error_not_implemented);;

   }


   float graphics::GetMiterLimit()
   {

      throw ::exception(error_not_implemented);;

      return 0.f;

   }


   void graphics::SetMiterLimit(float fMiterLimit)
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::stroke_and_fill_path()
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::stroke_path()
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::widen_path()
   {

      throw ::exception(error_not_implemented);;

   }





   void graphics::DPtoHIMETRIC(::f64_size * psize)
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::HIMETRICtoDP(::f64_size * psize)
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::LPtoHIMETRIC(::f64_size * psize)
   {
      
      ASSERT(::is_memory_segment_ok(psize, sizeof(f64_size)));

      LPtoDP(psize);
      
      DPtoHIMETRIC(psize);
      
   }


   void graphics::HIMETRICtoLP(::f64_size * psize)
   {
      
      ASSERT(::is_memory_segment_ok(psize, sizeof(f64_size)));

      HIMETRICtoDP(psize);
      
      DPtoLP(psize);
      
   }


   void graphics::DeleteDC()
   {
      
      m_cglayerref.release();

//      if(m_cglayerref)
//      {
//         
//         CGLayerRelease(m_cglayerref);
//         
//         m_cglayerref = nullptr;
//         
//      }
      
      //m_cgcontextref.release();

      if(m_cgcontextref)
      {

         if(m_bOwnGraphicsContext)
         {
            
            m_cgcontextref.release();
            
         }
         else
         {
            
            m_cgcontextref.detach();
            
         }

      }

      m_pimageTarget = nullptr;

      m_ewritetextrendering  = ::write_text::e_rendering_anti_alias_grid_fit;

   }


   int graphics::save_graphics_context()
   {

      CGContextSaveGState(m_cgcontextref);

      m_iSaveGraphicsContext++;

      return m_iSaveGraphicsContext;

   }


   void graphics::restore_graphics_context(int nSavedDC)
   {

      bool bRestored = false;

      while(m_iSaveGraphicsContext >= maximum(1, nSavedDC))
      {

         CGContextRestoreGState(m_cgcontextref);

         m_iSaveGraphicsContext--;

         bRestored = true;

      }

   }


   void graphics::set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode)
   {

      if(einterpolationmode == ::draw2d::e_interpolation_mode_low_quality)
      {

         CGContextSetInterpolationQuality(m_cgcontextref, kCGInterpolationDefault);

      }
      else if(einterpolationmode == ::draw2d::e_interpolation_mode_high_quality_bicubic)
      {

         CGContextSetInterpolationQuality(m_cgcontextref, kCGInterpolationHigh);

      }
      else
      {

         CGContextSetInterpolationQuality(m_cgcontextref,kCGInterpolationLow);

      }

   }


//   f64_point graphics::get_origin()
//   {
//
//      return ::draw2d::graphics::get_origin();
//
//   }


   void graphics::_get(::geometry2d::matrix & matrix)
   {

      _synchronous_lock synchronouslock(synchronization());

      CGAffineTransform affine = CGContextGetCTM(m_cgcontextref);

      copy(matrix, affine);

   }


   void graphics::_set(const ::geometry2d::matrix & matrix)
   {

      _synchronous_lock synchronouslock(synchronization());

      CGAffineTransform affine = CGContextGetCTM(m_cgcontextref);

      CGAffineTransform affineInverted;

      affineInverted = CGAffineTransformInvert(affine);

      CGContextConcatCTM(m_cgcontextref, affineInverted);
      
      if(m_iYFlipHeight > 0)
      {
         
         CGAffineTransform affineFlip;
         
         affineFlip = CGAffineTransform(1, 0,  0, -1, 0, m_iYFlipHeight);
         
         CGContextConcatCTM(m_cgcontextref, affineFlip);
         
      }

      CGAffineTransform affineSet;

      copy(affineSet, matrix);

      CGContextConcatCTM(m_cgcontextref, affineSet);

   }


//   f64_point graphics::set_origin(double x, double y)
//   {
//
//      f64_point pt =get_origin();
//      
//      pt.x = x - pt.x;
//      pt.y = y - pt.y;
//      
//      return offset_origin(pt.x, pt.y);
//      
//   }


//   f64_point graphics::offset_origin(double nWidth, double nHeight)
//   {
//
//      return ::draw2d::graphics::offset_origin(nWidth, nHeight);
//
//   }


   void graphics::clear_current_point()
   {
   
   }


   f64_size graphics::set_extents(double x, double y)
   {

      throw ::exception(error_not_implemented);
      
      return ::f64_size(0, 0);

   }


   f64_size graphics::scale_extents(double xNum, double xDenom, double yNum, double yDenom)
   {

      return ::draw2d::graphics::scale_extents(xNum, xDenom, yNum, yDenom);

   }


   f64_point graphics::SetWindowOrg(double x, double y)
   {

      throw ::exception(error_not_implemented);
      
      return ::f64_point();

   }


   f64_point graphics::offset_window_org(double nWidth, double nHeight)
   {

      throw ::exception(error_not_implemented);
      
      return ::f64_point();


   }


//   f64_size graphics::set_window_ext(double x, double y)
//   {
//
//      throw ::exception(error_not_implemented);
//      
//      return ::f64_size(0, 0);
//
//   }

//
//   f64_size graphics::scale_window_ext(double xNum, double xDenom, double yNum, double yDenom)
//   {
//
//      throw ::exception(error_not_implemented);
//      
//      return ::f64_size(0, 0);
//
//   }


   int graphics::get_clip_box(::f64_rectangle & rectangle)
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGRect cgrect = CGContextGetClipBoundingBox (m_cgcontextref);
      
      ::copy(rectangle, cgrect);
      
//      prectangle->left = rectangle.origin.x;
//      prectangle->top = rectangle.origin.y;
//      prectangle->right = prectangle->left + rectangle.size.width;
//      prectangle->bottom = prectangle->top + rectangle.size.height;

      return rectangle.is_empty() ? 0 : 1;

   }


   ::u32 graphics::SetTextAlign(::u32 nFlags)
   {

      throw ::exception(error_not_implemented);;

      return 0;

   }


   ::u32 graphics::GetLayout()
   {

      throw ::exception(error_not_implemented);;

      return 0;

   }


   ::u32 graphics::SetLayout(::u32 dwSetLayout)
   {

      throw ::exception(error_not_implemented);;
   
      return 0;

   }


   void graphics::reset_clip()
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }
      
      CGContextResetClip(m_cgcontextref);
   
   }


   void graphics::_intersect_clip()
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }
      
      if(CGContextIsPathEmpty(m_cgcontextref))
      {
         
         return;
         
      }
      
      CGContextClip(m_cgcontextref);
      
   }

   
   void graphics::intersect_clip(const ::f64_rectangle & rectangle)
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGRect r;

      //auto rectangleOffset = rectangle;

      //rectangleOffset += m_pointAddShapeTranslate;

      copy(r, rectangle);

//      CGContextBeginPath(m_cgcontextref);
//
//      CGContextAddRect(m_cgcontextref, r);
//
//      CGContextClip(m_cgcontextref);

      CGContextClipToRect(m_cgcontextref, r);

   }


//   void graphics::intersect_clip(const ::f64_ellipse & ellipse)
//   {
//
//      CGRect r;
//
//      //auto rectangleOffset = ellipse;
//
//      //rectangleOffset += m_pointAddShapeTranslate;
//
//      copy(r, ellipse);
//
//      CGContextBeginPath(m_cgcontextref);
//
//      CGContextAddEllipseInRect(m_cgcontextref, r);
//
//      CGContextClip(m_cgcontextref);
//
//   }
//
//
//   void graphics::intersect_clip(const ::f64_polygon & polygon)
//   {
//
//      CGContextBeginPath(m_cgcontextref);
//
//      set_polygon(polygon.data(), polygon.count());
//
//      CGContextClip(m_cgcontextref);
//
//   }
//
//
//   void graphics::_add_clipping_shape(const ::f64_rectangle & rectangle, ::draw2d::region * pregion)
//   {
//
//      _add_shape(rectangle);
//
//      _intersect_clip();
//
//   }
//
//
//   void graphics::_add_clipping_shape(const ::f64_ellipse & ellipse, ::draw2d::region * pregion)
//   {
//
//      _add_shape(ellipse);
//
//      _intersect_clip();
//
//   }
//
//
//   void graphics::_add_clipping_shape(const ::f64_polygon & polygon, ::draw2d::region * pregion)
//   {
//
//      _add_shape(polygon);
//
//      _intersect_clip();
//
//   }


   void graphics::_eo_clip()
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }
      
      if(CGContextIsPathEmpty(m_cgcontextref))
      {
         
         return;
         
      }
      
      CGContextEOClip(m_cgcontextref);
      
   }


   void graphics::_add_shape(const ::f64_rectangle & rectangle)
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }
   
      CGRect r;
      
//      auto rectangleOffset = rectangle;
//
//      rectangleOffset += m_pointAddShapeTranslate;
      
      copy(r, rectangle);
   
      CGContextAddRect(m_cgcontextref, r);
      
   }


   void graphics::_add_shape(const ::f64_ellipse & ellipse)
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }
   
      CGRect r;
      
      copy(r, ellipse);
   
      //CGContextBeginPath(m_cgcontextref);
   
      CGContextAddEllipseInRect(m_cgcontextref, r);
      
   }


   void graphics::_add_shape(const ::f64_polygon_base & polygon)
   {
   
      //CGContextBeginPath(m_cgcontextref);
   
      set_polygon(polygon.data(), polygon.count());
      
   }


   void graphics::LPtoDP(::f64_size * psize)
   {

      throw ::exception(error_not_implemented);;

      return;

   }


   void graphics::DPtoLP(::f64_size * psize)
   {

      throw ::exception(error_not_implemented);;

      return;

   }

//
//   int graphics::draw_text(const char * lpszString, int nCount, const ::f64_rectangle & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
//   {
//
//      draw_text(string(lpszString, nCount), rectangle, ealign, edrawtext);
//
//      return 0;
//      
//   }


//   f64_size graphics::get_text_extent(const ::scoped_string * lpszString, character_count nCount, int iIndex)
//   {
//
//      f64_size sz;
//
//      get_text_extent(sz, lpszString, nCount, iIndex);
//
//      return f64_size((int) sz.cx, (int) sz.cy);
//
//   }
//
//
//   f64_size graphics::get_text_extent(const char * lpszString, character_count nCount)
//   {
//
//      ::f64_size f64_size;
//
//      get_text_extent(f64_size, lpszString, nCount, (int) nCount);
//
//      return ::f64_size(f64_size.cx, f64_size.cy);
//
//   }


//   f64_size graphics::get_text_extent(const block & block)
//   {
//
//      ::f64_size size;
//
//      get_text_extent(size, (const char *) block.get_data(), (int)block.get_size());
//
//      return size;
//
//   }


   ::f64_size graphics::_get_text_extent(const ::scoped_string & scopedstr, ::collection::index iIndex)
   {
      
      _synchronous_lock synchronouslock(synchronization());
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGFloat ascent, descent, leading, width;

      string_array stra;
      
      auto range = scopedstr(0, minimum(iIndex, scopedstr.size()));

      stra.add_lines(range);
      
      ::f64_size size;

      size.cy = 0;

      size.cx = 0;

      for(auto str : stra)
      {
         
         const_cast < graphics * > (this)->internal_show_text(0, 0, 0, str, kCGTextInvisible, e_align_top_left, e_draw_text_none, false, &ascent, &descent, &leading, &width, nullptr, nullptr, m_pwritetextfont);

         size.cy += ascent + descent + leading;

//         if(leading <= 0)
//         {
//
//            size.cy += descent;
//
//         }

         size.cx = maximum(size.cx, width);

      }
      
      return size;

   }


   ::f64_size graphics::_get_text_extent(const ::scoped_string & scopedstr)
   {

      return _get_text_extent(scopedstr, (int) scopedstr.size());

   }


//   void graphics::get_text_extent(f64_size & size, const string & str)
//   {
//
//      return ::draw2d::graphics::get_text_extent(size, str);
//
//   }


   void graphics::fill_rectangle(const ::f64_rectangle & rectParam, const ::color::color & color)
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGRect rectangle;

      copy(rectangle, rectParam);

      internal_set_fill_color(color);

      CGContextFillRect(m_cgcontextref, rectangle);

   }


   void graphics::TextOutRaw(double x, double y, const ::scoped_string & scopedstr)
   {

      internal_show_text(x, y, 0, string((const char *) scopedstr.data(), scopedstr.size()), kCGTextFill, e_align_top_left, e_draw_text_none, true);

   }


   void graphics::internal_show_text(double x, double y, double wAlign, const string & str, CGTextDrawingMode emode, const ::e_align & ealign, const ::e_draw_text & edrawtext, bool bDraw, CGFloat * pascent, CGFloat * pdescent, CGFloat * pleading, CGFloat * pwidth, ::draw2d::pen * ppen, ::draw2d::brush * pbrush, ::write_text::font * pfont)
   {
      
//      // xxxtext
//
//      return;
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }
      
      if(pfont == nullptr)
      {
         
         if(m_pwritetextfont.is_null())
         {

            constructø(m_pwritetextfont);
            
            m_pwritetextfont->create_font(e_font_sans, 16_px);

         }
         
         pfont = m_pwritetextfont;
         
      }

      if(bDraw && pbrush == nullptr)
      {
         
         pbrush = m_pdraw2dbrush;
         
      }

      if(bDraw && ppen == nullptr)
      {
         
         ppen = m_pdraw2dpen;
         
      }

      return internal_show_text(pfont, pbrush, ppen, x, y, wAlign, str, emode, ealign, edrawtext, bDraw, pascent, pdescent, pleading, pwidth);

   }


   void graphics::line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen)
   {
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      CGContextBeginPath(m_cgcontextref);

      CGContextMoveToPoint(m_cgcontextref, x1, y1);

      CGContextAddLineToPoint(m_cgcontextref, x2, y2);

      _draw(ppen);

      m_pointCurrent.x = x2;
      
      m_pointCurrent.y = y2;

   }

//
//   void graphics::line(const ::f64_point & p1, const ::f64_point & p2)
//   {
//
//      CGContextBeginPath(m_cgcontextref);
//
//      CGContextMoveToPoint(m_cgcontextref, p1.x, p1.y);
//
//      CGContextAddLineToPoint(m_cgcontextref, p2.x, p2.y);
//
//      _draw();
//
//      m_pointCurrent = p2;
//
//   }


   void graphics::set_alpha_mode(::draw2d::enum_alpha_mode ealphamode)
   {


      if(m_cgcontextref == nullptr)
      {

         throw exception(error_null_pointer);

      }

      ::draw2d::graphics::set_alpha_mode(ealphamode);

      if(m_ealphamode == ::draw2d::e_alpha_mode_blend)
      {

         CGContextSetBlendMode(m_cgcontextref, kCGBlendModeNormal);

      }
      else if(m_ealphamode == ::draw2d::e_alpha_mode_set)
      {

         CGContextSetBlendMode(m_cgcontextref, kCGBlendModeCopy);

      }
  
   }


   void graphics::set_text_rendering_hint(::write_text::enum_rendering etextrenderinghint)
   {

      ::draw2d::graphics::set_text_rendering_hint(etextrenderinghint);

   }


   void graphics::_attach(CGContextRef cgcontextref, bool bLightAttachment)
   {
      
      destroy();

      m_iType = 10;

      m_cgcontextref = cgcontextref;

      m_bOwnGraphicsContext = !bLightAttachment;
      
      //m_osdata[0] = (void *) m_cgcontextref;

   }


   CGContextRef graphics::_detach()
   {

      auto cgcontextref = m_cgcontextref;
      
      m_cgcontextref = nullptr;
      
      m_bOwnGraphicsContext = false;

      return cgcontextref;

   }


   void graphics::attach(void * p)
   {
      
      _attach((CGContextRef) p, true);
      
   }


   void graphics::blur(bool bExpand, double dRadius, const ::f64_rectangle & rectangle)
   {


   }


   double graphics::get_dpix()
   {

      return 72.0;

   }



   void graphics::_set(::draw2d::brush * pbrush)
   {

      if(pbrush == nullptr || pbrush->m_ebrush == ::draw2d::e_brush_linear_gradient_point_color)
      {

         throw exception(error_null_pointer);
         
      }

      CGContextSetRGBFillColor(m_cgcontextref, __expand_f32_rgba(pbrush->m_color));

   }


   void graphics::_set(::draw2d::pen * ppen)
   {

      if(ppen == nullptr)
      {
         
         throw exception(error_null_pointer);
         
      }

      if(ppen->m_epen == ::draw2d::e_pen_brush && ppen->m_pdraw2dbrush)
      {

         if(ppen->m_pdraw2dbrush->m_ebrush == ::draw2d::e_brush_solid)
         {

            CGContextSetRGBStrokeColor(m_cgcontextref, __expand_f32_rgba(ppen->m_pdraw2dbrush->m_color));

         }

      }
      else
      {

         CGContextSetRGBStrokeColor(m_cgcontextref, __expand_f32_rgba(ppen->m_color));

      }
      
      if(ppen->m_elinecapBeg == ::draw2d::e_line_cap_round
         && ppen->m_elinecapEnd == ::draw2d::e_line_cap_round)
      {
         
         CGContextSetLineCap(m_cgcontextref, kCGLineCapRound);
         
      }
      else if(ppen->m_elinecapBeg == ::draw2d::e_line_cap_flat
         && ppen->m_elinecapEnd == ::draw2d::e_line_cap_flat)
      {
         
         CGContextSetLineCap(m_cgcontextref, kCGLineCapButt);
         
      }

      CGContextSetLineWidth(m_cgcontextref, ppen->m_dWidth);

   }


   void graphics::_set_pen(::draw2d::brush * pbrush, double dWidth)
   {

      if(pbrush == nullptr || pbrush->m_ebrush == ::draw2d::e_brush_null)
      {

         throw exception(error_null_pointer);

      }

      CGContextSetRGBStrokeColor(m_cgcontextref, __expand_f32_rgba(pbrush->m_color));

      CGContextSetLineWidth(m_cgcontextref, dWidth);

   }


   void graphics::_fill_and_draw()
   {

      _fill(m_pdraw2dbrush);

      _draw(m_pdraw2dpen);

   }


   void graphics::_fill(::draw2d::brush * pbrush)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      auto cgcontextref = m_cgcontextref;

      //CGContextSaveGState(cgcontextref);
      cg_context_scope cgcontextscope(m_cgcontextref);

      _fill(pbrush, true);

      //CGContextRestoreGState(cgcontextref);

   }


   void graphics::_fill(::draw2d::brush * pbrush, bool bContextClip)
   {

      if(pbrush == nullptr || pbrush->m_ebrush == ::draw2d::e_brush_null)
      {
         
         return;
         
      }
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      auto cgcontextref = m_cgcontextref;
      
      if(pbrush->m_ebrush == ::draw2d::e_brush_box_gradient)
      {
         
         pbrush->defer_update(this);

         if(bContextClip)
         {
         
            _intersect_clip();
            
         }

         _clip(m_pdraw2dregion);
         
         f32_rectangle outer(pbrush->m_point, pbrush->m_size);
         f32_rectangle inner(outer);
         
         float fRadius = pbrush->m_dRadius;
         
         inner.deflate(fRadius);

         CGPoint s, e;
         
         s.x = 0;
         s.y = 0;
         e.x = 0;
         e.y = 0;
         
         CGContextSetAllowsAntialiasing(m_cgcontextref, TRUE);
         CGContextSetShouldAntialias(m_cgcontextref, TRUE);
         
         //set_alpha_mode(::draw2d::e_alpha_mode_set);
         
         ::cast < ::draw2d_quartz2d::brush > pdraw2dquartz2dbrush = pbrush;
         
         auto cggradientref = pdraw2dquartz2dbrush->m_cggradientref;

         CGRect r;
         
         float f1 = 0.666f;
         //top-left
         //CGContextSaveGState(m_cgcontextref);
         {
            
            cg_context_scope cgcontextscope(m_cgcontextref);
            
            r.origin.x = outer.left + f1;
            r.origin.y = outer.top + f1;
            r.size.width = fRadius;
            r.size.height = fRadius;
            CGContextClipToRect(m_cgcontextref, r);
            CGContextTranslateCTM(m_cgcontextref, inner.left, inner.top);
            CGContextScaleCTM(m_cgcontextref, fRadius, fRadius);
            CGContextDrawRadialGradient(m_cgcontextref, cggradientref, s, 0, e, 1.0f, kCGGradientDrawsBeforeStartLocation);
            //CGContextRestoreGState(m_cgcontextref);
            
         }

         //top-right
         {
            
            cg_context_scope cgcontextscope(m_cgcontextref);
            //CGContextSaveGState(m_cgcontextref);
            r.origin.x = inner.right - f1;
            r.origin.y = outer.top + f1;
            r.size.width = fRadius;
            r.size.height = fRadius;
            CGContextClipToRect(m_cgcontextref, r);
            CGContextTranslateCTM(m_cgcontextref, inner.right, inner.top);
            CGContextScaleCTM(m_cgcontextref, fRadius, fRadius);
            CGContextDrawRadialGradient(m_cgcontextref, cggradientref, s, 0, e, 1.0f, kCGGradientDrawsBeforeStartLocation);
            //CGContextRestoreGState(m_cgcontextref);
            
         }

         
         //bottom-right
         {
            cg_context_scope cgcontextscope(m_cgcontextref);
            //CGContextSaveGState(m_cgcontextref);
            r.origin.x = inner.right - f1;
            r.origin.y = inner.bottom - f1;
            r.size.width = fRadius;
            r.size.height = fRadius;
            CGContextClipToRect(m_cgcontextref, r);
            CGContextTranslateCTM(m_cgcontextref, inner.right, inner.bottom);
            CGContextScaleCTM(m_cgcontextref, fRadius, fRadius);
            CGContextDrawRadialGradient(m_cgcontextref, cggradientref, s, 0, e, 1.0f, kCGGradientDrawsBeforeStartLocation);
            //CGContextRestoreGState(m_cgcontextref);
            
         }

         //bottom-left
         {
            cg_context_scope cgcontextscope(m_cgcontextref);
            //CGContextSaveGState(m_cgcontextref);
            r.origin.x = outer.left + f1;
            r.origin.y = inner.bottom - f1;
            r.size.width = fRadius;
            r.size.height = fRadius;
            CGContextClipToRect(m_cgcontextref, r);
            CGContextTranslateCTM(m_cgcontextref, inner.left, inner.bottom);
            CGContextScaleCTM(m_cgcontextref, fRadius, fRadius);
            CGContextDrawRadialGradient(m_cgcontextref, cggradientref, s, 0, e, 1.0f, kCGGradientDrawsBeforeStartLocation);
            //CGContextRestoreGState(m_cgcontextref);
            
         }

         float f5 = 0.25f;
         
         r.origin.x = inner.left - f5;
         r.origin.y = inner.top - f5;
         r.size.width = inner.width() + f5 * 2.0f;
         r.size.height = inner.height() + f5 * 2.0f;

         CGContextSetRGBFillColor(m_cgcontextref, __expand_f32_rgba(pbrush->m_color1));
         CGContextFillRect(m_cgcontextref, r);
         
         float f2 = 0.444f;
         //bottom
         r.origin.x = inner.left + f2;
         r.origin.y = inner.bottom - f2;
         r.size.width = inner.width() - (f2 * 2.0f);
         r.size.height = fRadius;
         {
            cg_context_scope cgcontextscope(m_cgcontextref);
            //}
            CGContextSaveGState(m_cgcontextref);
            CGContextClipToRect(m_cgcontextref, r);
            s.x = inner.center_x();
            e.x = inner.center_x();
            s.y = inner.bottom;
            e.y = outer.bottom;
            CGContextDrawLinearGradient(cgcontextref, cggradientref, s, e, 0);
            //CGContextRestoreGState(m_cgcontextref);
            
         }

         // top
         r.origin.x = inner.left + f2;
         r.origin.y = outer.top + f2;
         r.size.width = inner.width() - (f2 * 2.0f);
         r.size.height = fRadius;
         //CGContextSaveGState(m_cgcontextref);
         {
            cg_context_scope cgcontextscope(m_cgcontextref);
            CGContextClipToRect(m_cgcontextref, r);
            s.x = inner.center_x();
            e.x = inner.center_x();
            e.y = outer.top;
            s.y = inner.top;
            CGContextDrawLinearGradient(cgcontextref, cggradientref, s, e, 0);
            //CGContextRestoreGState(m_cgcontextref);
            
         }

         // right
         r.origin.x = inner.right - f2;
         r.origin.y = inner.top + f2;
         r.size.width = fRadius;
         r.size.height = inner.height() - (f2 * 2.0f);
         {
            cg_context_scope cgcontextscope(m_cgcontextref);
            //CGContextSaveGState(m_cgcontextref);
            CGContextClipToRect(m_cgcontextref, r);
            s.x = inner.right;
            e.x = outer.right;
            e.y = inner.center_y();
            s.y = inner.center_y();
            CGContextDrawLinearGradient(cgcontextref, cggradientref, s, e, 0);
            //CGContextRestoreGState(m_cgcontextref);
         }

         // left
         r.origin.x = outer.left + f2;
         r.origin.y = inner.top + f2;
         r.size.width = fRadius;
         r.size.height = inner.height() - (f2 * 2.0f);
         {
            cg_context_scope cgcontextscope(m_cgcontextref);
            //CGContextSaveGState(m_cgcontextref);
            CGContextClipToRect(m_cgcontextref, r);
            s.x = inner.left;
            e.x = outer.left;
            e.y = inner.center_y();
            s.y = inner.center_y();
            CGContextDrawLinearGradient(cgcontextref, cggradientref, s, e, 0);
            //CGContextRestoreGState(m_cgcontextref);
         }

         CGContextSetAllowsAntialiasing(m_cgcontextref, TRUE);
         CGContextSetShouldAntialias(m_cgcontextref, TRUE);

      }
      else if(pbrush->m_ebrush == ::draw2d::e_brush_radial_gradient_color)
      {
         
         pbrush->defer_update(this);

         if(bContextClip)
         {

            _intersect_clip();

         }

         _clip(m_pdraw2dregion);

         CGPoint myStartPoint, myEndPoint;
         
         ::cast < ::draw2d_quartz2d::brush > pdraw2dquartz2dbrush = pbrush;
         
         auto cggradientref = pdraw2dquartz2dbrush->m_cggradientref;

         CGContextTranslateCTM(cgcontextref, pdraw2dquartz2dbrush->m_point.x, pdraw2dquartz2dbrush->m_point.y);

         CGContextScaleCTM(cgcontextref, pdraw2dquartz2dbrush->m_size.cx, pdraw2dquartz2dbrush->m_size.cy);

         myStartPoint.x = 0;

         myStartPoint.y = 0;

         myEndPoint.x = 0;

         myEndPoint.y = 0;

         CGContextDrawRadialGradient(cgcontextref, cggradientref, myStartPoint, 0, myEndPoint, 1.0f, kCGGradientDrawsBeforeStartLocation);

      }
      else if(pbrush->m_ebrush == ::draw2d::e_brush_linear_gradient_point_color)
      {
         
         pbrush->defer_update(this);

         if(bContextClip)
         {

            _intersect_clip();

         }

         _clip(m_pdraw2dregion);

         CGPoint point1, point2;
         
         ::cast < ::draw2d_quartz2d::brush > pdraw2dquartz2dbrush = pbrush;
         
         auto cggradientref = pdraw2dquartz2dbrush->m_cggradientref;

         point1.x = pdraw2dquartz2dbrush->m_point1.x;

         point1.y = pdraw2dquartz2dbrush->m_point1.y;

         point2.x = pdraw2dquartz2dbrush->m_point2.x;

         point2.y = pdraw2dquartz2dbrush->m_point2.y;
         
         CGRect r;
         
         r.origin = point1;
         r.size.width = point2.x - point1.x;
         r.size.height = point2.y - point1.y;
         
         CGContextDrawLinearGradient(cgcontextref, cggradientref, point1, point2, 0);
         
      }
      else if(pbrush->m_ebrush == ::draw2d::e_brush_pattern)
      {

         if(bContextClip)
         {

            _intersect_clip();

         }

         _clip(m_pdraw2dregion);

         scoped_restore(m_bPat);

         CGRect rectangle = CGContextGetClipBoundingBox(cgcontextref);
         
         ::i32_rectangle i32_rectangle;
         
         copy(i32_rectangle, rectangle);
         
         if(!i32_rectangle.is_empty())
         {
            
            ::image::image_source imagesource(pbrush->m_pimage);
            
            ::image::image_drawing_options imagedrawingoptions(i32_rectangle);
            
            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);
            
            draw(imagedrawing);
            
         }

      }
      else if(pbrush->m_ebrush == ::draw2d::e_brush_solid)
      {
         
         pbrush->defer_update(this);
         
         ::cast < ::draw2d_quartz2d::brush > pdraw2dquartz2dbrush = pbrush;
         
         auto cgcolorref = pdraw2dquartz2dbrush->m_cgcolorref;

         if(cgcolorref)
         {
            
            if(m_pdraw2dregion.is_null())
            {

               CGContextSetFillColorWithColor(cgcontextref, cgcolorref);

               CGContextFillPath(cgcontextref);

            }
            else
            {

               CGContextSetFillColorWithColor(cgcontextref, cgcolorref);

               if(bContextClip)
               {

                  _intersect_clip();

               }

               _clip(m_pdraw2dregion);

               CGContextAddRect(cgcontextref, CGContextGetClipBoundingBox(cgcontextref));

               CGContextFillPath(cgcontextref);

            }
            
         }
         else
         {
            
            if(m_pdraw2dregion.is_null())
            {

               CGContextSetFillColorWithColor(m_cgcontextref, cgcolorref);

               CGContextFillPath(cgcontextref);

            }
            else
            {

               CGContextSetFillColorWithColor(m_cgcontextref, cgcolorref);

               if(bContextClip)
               {

                  _intersect_clip();

               }

               _clip(m_pdraw2dregion);

               CGContextAddRect(cgcontextref, CGContextGetClipBoundingBox(cgcontextref));

               CGContextFillPath(cgcontextref);

            }
            
         }

      }

   }


   void graphics::_draw(::draw2d::pen * ppen)
   {

      if(ppen == nullptr || ppen->m_epen == ::draw2d::e_pen_null)
      {

         return;
         
      }

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      //CGContextSaveGState(m_cgcontextref);
      cg_context_scope cgcontextscope(m_cgcontextref);

      _set(ppen);

      if(ppen->m_epen == ::draw2d::e_pen_brush && ppen->m_pdraw2dbrush.is_set()
            && (ppen->m_pdraw2dbrush->m_ebrush == ::draw2d::e_brush_linear_gradient_point_color
                || ppen->m_pdraw2dbrush->m_ebrush == ::draw2d::e_brush_radial_gradient_color
                || ppen->m_pdraw2dbrush->m_ebrush == ::draw2d::e_brush_pattern)
        )
      {

         CGContextReplacePathWithStrokedPath(m_cgcontextref);

         // Turn the fillable path in to a clipping region.
//            _intersect_clip();;

         _fill(ppen->m_pdraw2dbrush);

      }
      else
      {

         CGContextStrokePath(m_cgcontextref);

      }

      //CGContextRestoreGState(m_cgcontextref);

   }


   void graphics::_draw(::draw2d::brush * pbrush)
   {

      if(pbrush == nullptr || pbrush->m_ebrush == ::draw2d::e_brush_null)
         return;
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      cg_context_scope cgcontextscope(m_cgcontextref);
      //CGContextSaveGState(m_cgcontextref);

      _set(pbrush);

      if(pbrush->m_ebrush == ::draw2d::e_brush_linear_gradient_point_color
            || pbrush->m_ebrush == ::draw2d::e_brush_radial_gradient_color
            || pbrush->m_ebrush == ::draw2d::e_brush_pattern)

      {

         CGContextReplacePathWithStrokedPath(m_cgcontextref);

         // Turn the fillable path in to a clipping region.
         //_intersect_clip();;

         _fill(pbrush);

      }
      else
      {

         CGContextStrokePath(m_cgcontextref);

      }

      //CGContextRestoreGState(m_cgcontextref);

   }


   
//   void graphics::_draw_inline(___shape <::draw2d::path> * pshape, ::draw2d::pen * ppen)
//   {
//
//      switch(pshape->eshape())
//      {
//      case e_shape_text_out:
//         _draw_inline(pshape->shape < write_text::text_out >(), ppen);
//         break;
//         case e_shape_draw_text:
//            _draw_inline(pshape->shape < write_text::draw_text>(), ppen);
//            break;
//      default:
//         break;
//      }
//
//   }
//
//
//   void graphics::_fill_inline(___shape < ::draw2d::path > * pshape, ::draw2d::brush * pbrush)
//   {
//
//      switch(pshape->eshape())
//      {
//      case e_shape_text_out:
//         _fill_inline(pshape->shape < write_text::text_out >(), pbrush);
//         return;
//         case e_shape_draw_text:
//            _fill_inline(pshape->shape < write_text::draw_text>(), pbrush);
//            return;
//      default:
//         break;
//      }
//
//      throw exception(error_null_pointer);
//
//   }


   void graphics::_draw_inline(::write_text::text_out & textout, ::draw2d::pen * ppen)
   {

      string str(textout.m_strText);

      _synchronous_lock ml(synchronization());

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      double Δx;

      double Δy;

      Δx = 0.;

      Δy = 0.;

      str.find_replace("\t", "        ");

      string_array stra;

      stra.add_lines(str);

      int offsety = 0;

      CGFloat ascent, descent, leading, width;

      for(auto str : stra)
      {

         internal_show_text(
                            textout.m_point.x + Δx,
                            textout.m_point.y + Δy + offsety,
                            0, str,
                             kCGTextStroke,
                            e_align_top_left,
                            e_draw_text_none, true, &ascent, &descent, &leading, &width, ppen, nullptr, textout.m_pwritetextfont);

         offsety += ascent + descent + leading;

//         if(leading <= 0)
//         {
//
//            offsety += descent;
//
//         }

      }

   }


   void graphics::_fill_inline(::write_text::text_out & textout, ::draw2d::brush * pbrush)
   {

      string str(textout.m_strText);

      _synchronous_lock ml(synchronization());
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      double Δx;

      double Δy;

      Δx = 0.;

      Δy = 0.;

      str.find_replace("\t", "        ");

      string_array stra;

      stra.add_lines(str);

      int offsety = 0;

      CGFloat ascent, descent, leading, width;

      for(auto str : stra)
      {

         internal_show_text(
                            textout.m_point.x + Δx,
                            textout.m_point.y + Δy + offsety,
                            0, str,
                             kCGTextFill,
                            e_align_top_left,
                            e_draw_text_none, true, &ascent, &descent, &leading, &width, nullptr, pbrush,  textout.m_pwritetextfont);

         offsety += ascent + descent + leading;

//         if(leading <= 0)
//         {
//
//            offsety += descent;
//
//         }

      }

   }


   void graphics::_draw_inline(::write_text::draw_text & drawtext, ::draw2d::pen * ppen)
   {

      string str(drawtext.m_strText);

      _synchronous_lock ml(synchronization());

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      double Δx;

      double Δy;

      Δx = 0.;

      Δy = 0.;

      str.find_replace("\t", "        ");

      string_array stra;

      stra.add_lines(str);

      int offsety = 0;

      CGFloat ascent, descent, leading, width;

      for(auto str : stra)
      {

         internal_show_text(
                            drawtext.m_rectangle.left + Δx,
                            drawtext.m_rectangle.top + Δy + offsety,
                            0,
                            str, kCGTextStroke,
                            e_align_top_left,
                            e_draw_text_none,
                            true, &ascent, &descent, &leading, &width, ppen, nullptr, drawtext.m_pwritetextfont);

         offsety += ascent + descent + leading;

//         if(leading <= 0)
//         {
//
//            offsety += descent;
//
//         }

      }

   }


   void graphics::_fill_inline(::write_text::draw_text & drawtext, ::draw2d::brush * pbrush)
   {

      string str(drawtext.m_strText);

      _synchronous_lock ml(synchronization());

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      double Δx;

      double Δy;

      Δx = 0.;

      Δy = 0.;

      str.find_replace("\t", "        ");

      string_array stra;

      stra.add_lines(str);

      int offsety = 0;

      CGFloat ascent, descent, leading, width;

      for(auto str : stra)
      {

         internal_show_text(
                            drawtext.m_rectangle.left + Δx,
                            drawtext.m_rectangle.top + Δy + offsety,
                            0,
                            str, kCGTextFill,
                            e_align_top_left,
                            e_draw_text_none,
                            true, &ascent, &descent, &leading, &width, nullptr, pbrush, drawtext.m_pwritetextfont);

         offsety += ascent + descent + leading;

//         if(leading <= 0)
//         {
//
//            offsety += descent;
//
//         }

      }

   }


   void graphics::_fill()
   {

      return _fill(m_pdraw2dbrush);

   }


   void graphics::_draw()
   {

      return _draw(m_pdraw2dpen);

   }


   void graphics::internal_set_fill_color(const ::color::color & color)
   {

      CGContextSetRGBFillColor(m_cgcontextref, __expand_f32_rgba(color));

   }


   void graphics::draw_text(const ::scoped_string & strParam,const ::f64_rectangle & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      string str(strParam);

      _synchronous_lock ml(synchronization());

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      if(edrawtext & e_draw_text_expand_tabs)
      {

         str.find_replace("\t", "        ");

      }
      else
      {

         str.find_replace("\t", "");

      }
      
      double y;

      if(ealign & e_align_bottom)
      {

         y = rectangle.bottom;

      }
      else if(ealign & e_align_vertical_center)
      {

         y = rectangle.top + ::height(rectangle) / 2.0;

      }
      else
      {

         y = rectangle.top;

      }

      if(edrawtext & e_draw_text_single_line)
      {

         str.find_replace("\r\n", " ");

         str.find_replace("\n", " ");

         str.find_replace("\r", " ");

         internal_show_text(
         rectangle.left,
         y,
         ::width(rectangle),
         str,
         kCGTextFill,
         ealign,
         edrawtext,
         true,
         nullptr,
         nullptr,
         nullptr,
         nullptr,
         nullptr,
         m_pdraw2dbrush,
         m_pwritetextfont);

      }
      else
      {

         string_array stra;

         stra.add_lines(str);

         //CGFloat ascent, descent, leading, width;

         CGFloat ascent, descent, leading;

         if(!(ealign & e_align_bottom) && ! (ealign & e_align_vertical_center))
         {

            for(auto str : stra)
            {

               internal_show_text(
               rectangle.left,
               y,
               ::width(rectangle),
                                  str,
               kCGTextFill,
                                  e_align_top_left,
                                  edrawtext,
               true,
               &ascent,
               &descent,
               &leading,
               nullptr,
               nullptr,
               m_pdraw2dbrush,
               m_pwritetextfont);

               y += ascent + descent + leading;

//               if(leading <= 0)
//               {
//
//                  y += descent;
//
//               }

            }

         }
         else if(ealign & e_align_bottom)
         {

            for(auto str : stra)
            {

               internal_show_text(
               rectangle.left,
               y,
               ::width(rectangle),
               str,
               kCGTextFill,
                                  (ealign & e_align_horizontal) | e_align_bottom,
                                  edrawtext,
               true,
               &ascent,
               &descent,
               &leading,
               nullptr,
               nullptr,
               m_pdraw2dbrush,
               m_pwritetextfont);

               y -= ascent + descent + leading;

//                  if(leading <= 0)
//                  {
//
//                     y -= descent;
//
//                  }

            }

         }
         else if(ealign & e_align_vertical_center)
         {

            f64_rectangle rectUpper(rectangle);

            f64_rectangle rectLower(rectangle);

            rectUpper.bottom = y;

            rectLower.top = y;

            if(stra.get_count() % 2 == 1)
            {

               internal_show_text(
               rectangle.left,
               y,
               ::width(rectangle),
               stra[stra.get_middle_index()],
               kCGTextFill,
               (ealign & e_align_horizontal) | e_align_vertical_center,
               e_draw_text_none,
               true,
               &ascent,
               &descent,
               &leading,
               nullptr,
               nullptr,
               m_pdraw2dbrush,
               m_pwritetextfont);

               double Δy = ascent + descent + leading;

//                  if(leading <= 0)
//                  {
//
//                     Δy += descent;
//
//                  }

               rectUpper.bottom -= Δy/2.0;

               rectLower.top += Δy/2.0;

            }

            if(stra.get_count() >= 2)
            {

               draw_text(
               stra.implode("\n", 0, stra.get_middle_index() + 1),
               rectUpper,
               (ealign & ~e_align_vertical_center) | e_align_bottom);

               draw_text(
               stra.implode("\n", stra.get_middle_index() + 1),
               rectLower,
               (ealign & ~e_align_vertical_center) | e_align_top);

            }

         }

      }

   }


   void graphics::internal_show_text(::write_text::font * pfont,::draw2d::brush * pbrush,::draw2d::pen * ppen, double x, double y, double wAlign, const string & str,CGTextDrawingMode emode,const ::e_align & ealign, const ::e_draw_text & edrawtext,   bool bDraw, CGFloat * pascent, CGFloat * pdescent, CGFloat * pleading, CGFloat * pwidth)
   {
      
//      // xxxtext
//
//      return;

      _synchronous_lock synchronouslock(synchronization());

      //CGContextRef pgraphics = m_cgcontextref;

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      if(str == "GB18030 Bitmap")
      {
         
         ::output_debug_string("GB18030 Bitmap");
         
      }

      //::pointer < ::draw2d_quartz2d::font > f = spfont;
      
      if(!pfont)
      {
         
         throw exception(error_null_pointer);
         
      }

      // Many times user may want to measure spaces
//      if(str.trimmed().is_empty())
//      {
//
//         return;
//         //throw exception(error_invalid_empty_argument);
//
//      }
      
      pfont->defer_update(this);
      
      ::cast < ::draw2d_quartz2d::font > pdraw2dquartz2dfont = pfont;
      
      if(!pdraw2dquartz2dfont->m_ctfontref)
      {
         
         throw exception(error_null_pointer);
         
      }
      
      auto ctfontref = pdraw2dquartz2dfont->m_ctfontref;

      bool bFill = false;

      bool bStroke = false;

      ::color::color colorFill;

      ::color::color colorStroke;

      ::draw2d::brush * pbrushDraw = nullptr;

      //bool bCacheLine = false;

      if(bDraw)
      {

         if(emode == kCGTextFill || emode == kCGTextFillStroke)
         {

            if(::is_set(pbrush) &&
                  (pbrush->m_ebrush == ::draw2d::e_brush_linear_gradient_point_color
                   || pbrush->m_ebrush == ::draw2d::e_brush_radial_gradient_color
                   || pbrush->m_ebrush == ::draw2d::e_brush_pattern))
            {

               pbrushDraw = pbrush;

               emode = kCGTextClip;

            }
            else
            {

               bFill = true;

               colorFill = ::is_null(pbrush) ? argb(255, 0, 0, 0) : pbrush->m_color;

            }

         }

         if(emode == kCGTextStroke|| emode == kCGTextFillStroke)
         {

            bStroke = true;

            colorStroke = ::is_null(ppen) ? argb(255, 0, 0, 0) : ppen->m_color;

         }

      }

      if(!bDraw)
      {

//         auto passoc = f->m_mapMetrics.plookup(str);
//
//         if(passoc != nullptr)
//         {
//
//            ::draw2d_quartz2d::font::metrics & m = passoc->element2();
//
//            m.get(pascent, pdescent, pleading, pwidth);
//
//            return true;
//
//         }

      }
      else if(ansi_scan(str, "0123456789") == nullptr)
      {

//         auto passoc = f->m_mapMetrics.plookup(str);
//
//         if(passoc != nullptr)
//         {
//
//            ::draw2d_quartz2d::font::metrics & m = passoc->element2();
//
//            CTLineRef line = m.m_map[emode][crFill][crStroke];
//
//            if(line != nullptr)
//            {
//
//               m.align(x, y, wAlign, nFormat);
//
//               CGContextSaveGState(pgraphics);
//
//               internal_draw_text(emode, x, y + m.ascent, line, pbrush);
//
//               CGContextRestoreGState(pgraphics);
//
//               m.get(pascent, pdescent, pleading, pwidth);
//
//               return true;
//
//            }
//
//         }

      }

      // ::draw2d_quartz2d::font::metrics & m = f->m_mapMetrics[str];
      
      //ref_array refa;

      auto cfrefString = ::as_cfref(CFStringCreateWithCString(nullptr, str, kCFStringEncodingUTF8));
      
      

      if(!cfrefString)
      {

         throw exception(error_null_pointer);

      }

      array < const void * > pkeys;
      
      cf_array pvals;
      
      //array < cftyperef > cftyperefa;
      
      //array < cgcolorref > cgcolorrefa;
      
      pkeys.add(kCTFontAttributeName);

      pvals.add(ctfontref);

      if(pfont->m_bUnderline)
      {

         int iUnderlineStyle = kCTUnderlineStyleSingle;

         pkeys.add(kCTUnderlineStyleAttributeName);
         pvals.add(CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &iUnderlineStyle));
         //cftyperefa.add(num);

      }

      // if(emode != kCGTextInvisible && bDraw && (bFill || bStroke || emode == kCGTextClip))
      if(emode != kCGTextInvisible && bDraw && (bFill || bStroke))
      {

         auto rgbColorSpace = ::as_cfref(CGColorSpaceCreateDeviceRGB());
         
         CGFloat components[4];

         //if(bFill || emode == kCGTextClip)
         if(bFill)
         {

            components[0] = colorFill.f32_red();
            components[1] = colorFill.f32_green();
            components[2] = colorFill.f32_blue();
            components[3] = colorFill.f32_opacity();

            pkeys.add(kCTForegroundColorAttributeName);
            pvals.add(CGColorCreate(rgbColorSpace, components));
            //cgcolorrefa.add(color);

         }

         if(bStroke)
         {

            double dStroke = ::is_null(ppen) ? 3.0 : ppen->m_dWidth * 100.0 / pfont->m_fontsize.as_f64();

            pkeys.add(kCTStrokeWidthAttributeName);
            pvals.add(CFNumberCreate(kCFAllocatorDefault, kCFNumberDoubleType, &dStroke));
            //cftyperefa.add(pvals.last());

            components[0] = colorStroke.f32_red();
            components[1] = colorStroke.f32_green();
            components[2] = colorStroke.f32_blue();
            components[3] = colorStroke.f32_opacity();

            pkeys.add(kCTStrokeColorAttributeName);
            pvals.add(CGColorCreate(rgbColorSpace, components));
            //cgcolorrefa.add(color);

         }

         //CGColorSpaceRelease(rgbColorSpace);

      }
      
      auto iSize = pkeys.get_size();


      auto attributes = ::as_cfref(CFDictionaryCreate(
                                   kCFAllocatorDefault,
                                   pkeys.data(),
                                   pvals.data(),
                                   iSize,
                                   &kCFTypeDictionaryKeyCallBacks,
                                   &kCFTypeDictionaryValueCallBacks));

      auto cfrefAttrString = ::as_cfref(CFAttributedStringCreate(kCFAllocatorDefault, cfrefString, attributes));
      //CFRelease(string);
      //CFRelease(attributes);
      
      auto ctlineref = ::as_cfref(CTLineCreateWithAttributedString(cfrefAttrString));

      //CFRelease(attrString);
      
      CGFloat width;
      
      CGFloat ascent;
      
      CGFloat descent;
      
      CGFloat leading;
      
      width = CTLineGetTypographicBounds(ctlineref, &ascent,  &descent, &leading);
                  
      if(bDraw)
      {

         if(ealign & e_align_right)
         {
            
            x += wAlign - width;
   
         }
         else if(ealign & e_align_horizontal_center)
         {
   
            x += (wAlign - width) / 2.0;
   
         }
   
         if(ealign & (e_align_bottom | e_align_vertical_center))
         {
   
            //double cy = -(ascent + descent + leading);
            
            double cy = (ascent + descent);
   
//            if(leading <= 0)
//            {
//
//               cy -= descent;
//
//            }
   
            if(ealign & e_align_vertical_center)
            {
   
               cy /= 2.0;
   
            }
   
            y -= cy;
   
         }
//         if(pbrush)
//         {
//
//            pbrush->m_point1.y += ascent;
//            pbrush->m_point2.y += ascent;
//
//         }
         internal_draw_text(emode, x, y + ascent, ctlineref, pbrush);
         //internal_draw_text(emode, x, y, line, pbrush);
//         if(pbrush)
//         {
//
//            pbrush->m_point1.y -= ascent;
//            pbrush->m_point2.y -= ascent;
//
//         }

      }

//      if(line)
//      {
//
//         CFRelease(line);
//
//      }

      if(pascent)
      {
      
         *pascent = ascent;
         
      }
      
      if(pdescent)
      {
      
         *pdescent = descent;
         
      }
      
      if(pleading)
      {
      
         *pleading = leading;
         
      }
      
      if(pwidth)
      {

         *pwidth = width;
         
      }

   }


   void graphics::internal_draw_text(CGTextDrawingMode emode, double x, double y, CTLineRef line, ::draw2d::brush * pbrush)
   {

      _synchronous_lock synchronouslock(synchronization());
      
      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      auto cgcontext = m_cgcontextref;

      CGContextSetTextPosition(cgcontext, 0, 0);

      // CGContextSetTextMatrix(pgraphics, CGAffineTransformScale(CGAffineTransformMakeTranslation(x, y), 1.f, -1.f));
      CGContextTranslateCTM(cgcontext, x, y);
      CGContextScaleCTM(cgcontext, 1.0, -1.0);

      //CGContextSetTextMatrix(pgraphics, CGAffineTransformIdentity);
      //CGContextSetTextPosition(pgraphics, 0, 0);
      
      //CGContextSetTextMatrix(pgraphics, CGAffineTransformMakeScale(1.f, -1.f));
      //CGContextTranslateCTM(pgraphics, x, y);
      //CGContextScaleCTM(pgraphics, 1.0, -1.0);
      // CGContextSetTextMatrix(pgraphics, CGAffineTransformScale(CGAffineTransformMakeTranslation(x, y), 1.f, -1.f));
      
      //CGContextSetTextMatrix(pgraphics, CGA,0ffineTransformMakeScale(1.f, -1.f));
      
      
      CGContextSetTextDrawingMode(cgcontext, emode);

      CTLineDraw(line, cgcontext);

      CGContextScaleCTM(cgcontext, 1.0, -1.0);
      CGContextTranslateCTM(cgcontext, -x, -y);
      
      if(pbrush != nullptr)
      {
 
         //pbrush->m_point1 -= i32_point(x, y);
         //pbrush->m_point2 -= i32_point(x, y);
         //_fill(pbrush, emode >= kCGTextFillClip);
         _fill(pbrush, false);
         //pbrush->m_point1 += i32_point(x, y);
         //pbrush->m_point2 += i32_point(x, y);

      }

   }


} // namespace draw2d_quartz2d


cfref<CGContextRef> cg_create_bitmap_context(CGSize size)
{

   auto space = ::as_cfref(CGColorSpaceCreateDeviceRGB());

   auto ctx = ::as_cfref(CGBitmapContextCreate(nil, size.width, size.height, 8, size.width * 4, space, kCGImageAlphaPremultipliedLast));

   //CGColorSpaceRelease(space);

   return ctx;

}
