#include "framework.h"
#include "graphics.h"
#include "bitmap.h"
#include "image.h"
#include "brush.h"
#include "pen.h"
#include "font.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/scoped_restore.h"
//#include "acme/primitive/geometry2d/shape_array.h"
//#include "acme/primitive/geometry2d/shape.h"
//#include "acme/primitive/geometry2d/item.h"
#include "aura/graphics/image/context_image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/write_text/text_out.h"
#include "aura/graphics/write_text/draw_text.h"
#include "aura/platform/context.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
//#include <math.h>
//#include <memory.h>
#include <CoreFoundation/CFDictionary.h>
//#include "acme/primitive/geometry2d/_geometry2d.h"
//#include "acme/primitive/geometry2d/_collection.h"
//#include "acme/primitive/geometry2d/_defer.h"
//#include "acme/primitive/geometry2d/_defer_item.h"
//#include "aura/graphics/write_text/_defer_geometry2d_item.h"


//unsigned long apple_get_fonts(char *** p);
double nsfont_get_ctweight(int iWeight);


CGContextRef cg_create_bitmap_context(CGSize size);


namespace draw2d_quartz2d
{

   void copy(CGAffineTransform & affine, const ::draw2d::matrix & m)
   {

      affine.a = m.a1;
      affine.b = m.a2;
      affine.c = m.b1;
      affine.d = m.b2;
      affine.tx = m.c1;
      affine.ty = m.c2;

   }


   void copy(::draw2d::matrix & m, const CGAffineTransform & affine)
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
      m_cgcontext             = nullptr;
      m_cglayer           = nullptr;

   }


   graphics::~graphics()
   {

      destroy();

   }


   void graphics::destroy()
   {
      
      destroy_os_data();
      
      ::draw2d::graphics::destroy();
      
   }

   
   void graphics::destroy_os_data()
   {

      DeleteDC();

   }


//#if 0

//   void graphics::dump(dump_context & dumpcontext) const
//   {
//
//      ::draw2d::graphics::dump(dumpcontext);
//
//      dumpcontext << "\n";
//
//   }


   void graphics::CreateCompatibleDC(::draw2d::graphics * pgraphics)
   {

      destroy();

      CGContextRef cg   = nullptr;

      if(pgraphics == nullptr || pgraphics->get_os_data() == nullptr)
      {

         cg = cg_create_bitmap_context({1, 1});

      }
      else
      {

         cg = (CGContextRef) pgraphics->get_os_data();

      }

      CGSize size;

      size.width = 1;

      size.height = 1;

      m_cglayer = CGLayerCreateWithContext(cg, size, nullptr);

      if(m_cglayer != nullptr)
      {
         
         m_cgcontext = CGLayerGetContext(m_cglayer);
         
         m_bOwnGraphicsContext = false;

      }

      if(m_cgcontext == nullptr)
      {

         CGLayerRelease(m_cglayer);

         m_cglayer = nullptr;

      }

      if(pgraphics == nullptr || pgraphics->get_os_data() == nullptr)
      {

         CGContextRelease(cg);

      }

      if(m_cglayer == nullptr)
      {

         CGContextRelease(cg);
         
         throw exception(error_resource);

      }

   }


   i32 graphics::GetDeviceCaps(i32 nIndex)
   {
      
      throw ::exception(error_not_implemented);
      
      return 0;

   }


   point_f64 graphics::GetBrushOrg()
   {

      throw ::exception(error_not_implemented);
      
      return ::point_f64();

   }


   point_f64 graphics::SetBrushOrg(double x, double y)
   {

      throw ::exception(error_not_implemented);
      
      return ::point_f64();

   }


   point_f64 graphics::SetBrushOrg(const ::point_f64 & point)
   {

      throw ::exception(error_not_implemented);
      
      return ::point_f64();

   }


   void graphics::set(::draw2d::bitmap * pbitmap)
   {

      ::pointer < ::draw2d_quartz2d::bitmap > pbitmapQuartz = pbitmap;

      if(pbitmapQuartz.is_set())
      {

         attach(pbitmapQuartz->m_cgcontext);

         m_bOwnGraphicsContext = false;

         m_pbitmap = pbitmap;

      }

   }


   size_f64 graphics::get_extents()
   {

      return ::size_f64(0, 0);
      
   }

   
   point_f64 graphics::GetWindowOrg()
   {

      return ::point_f64();
      
   }


   size_f64 graphics::GetWindowExt()
   {

      return ::size_f64(0, 0);
      
   }


   point_f64 graphics::set_origin(const ::point_f64 & point)
   {

      return set_origin(point.x(), point.y());

   }


   size_f64 graphics::set_extents(const ::size_f64 & size)
   {

      return ::size_f64(0, 0);
      
   }


   point_f64 graphics::SetWindowOrg(const ::point_f64 & point)
   {

      return ::point_f64();
      
   }


   size_f64 graphics::set_window_ext(const ::size_f64 & size)
   {

      return ::size_f64(0, 0);
      
   }


   void graphics::DPtoLP(::rectangle_f64 * prectangle)
   {

   }


   void graphics::LPtoDP(::rectangle_f64 * prectangle)
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


   point_f64 graphics::current_position()
   {

      return m_point;

   }


   void graphics::arc(double x, double y, double w, double h, ::angle_f64 start, ::angle_f64 extends)
   {

      double end = start + extends;

      CGContextSaveGState(m_cgcontext);

      CGContextTranslateCTM(m_cgcontext, x + w/2.0, y + h/2.0);

      CGContextScaleCTM(m_cgcontext, w/2.0, h/2.0);

      CGContextAddArc(m_cgcontext, 0.f, 0.f, 1.0f, start, end, extends < 0.0);

      CGContextRestoreGState(m_cgcontext);

      return _draw();

   }


   void graphics::polyline(const point_f64* lpPoints, count nCount)
   {

      if(nCount < 2)
      {
         
         throw exception(error_invalid_parameter);
         
      }

      CGContextBeginPath(m_cgcontext);

      set_polygon(lpPoints, nCount);

      _draw();
      
   }


   void graphics::fill_rectangle(const ::rectangle_f64 & rectParam, ::draw2d::brush * pbrush)
   {

      CGRect rectangle;
      
      copy(rectangle, rectParam);
      
      CGContextBeginPath(m_cgcontext);
      
      CGContextAddRect(m_cgcontext, rectangle);
      
      _fill(pbrush);

   }


   void graphics::fill_rectangle(const ::rectangle_f64 & rectangle)
   {

      fill_rectangle(rectangle, m_pbrush);
      
   }
   
   
   void graphics::frame_rectangle(const ::rectangle_f64 & rectParam, ::draw2d::brush* pBrush)
   {

      CGRect rectangle;

      copy(rectangle, rectParam);

      CGContextBeginPath(m_cgcontext);

      CGContextAddRect(m_cgcontext, rectangle);

      _draw(pBrush);

   }


   void graphics::draw_rectangle(const ::rectangle_f64 & rectParam, ::draw2d::pen* ppen)
   {

      CGRect rectangle;
      
      copy(rectangle, rectParam);
      
      CGContextBeginPath(m_cgcontext);
      
      CGContextAddRect(m_cgcontext, rectangle);
      
      _draw(ppen);

   }


   void graphics::draw_rectangle(const ::rectangle_f64 & rectangle)
   {

      draw_rectangle(rectangle, m_ppen);

   }
   
  
   void graphics::invert_rectangle(const ::rectangle_f64 & rectangle)
   {

      throw ::exception(error_not_implemented);

   }


   void graphics::DrawFocusRect(const ::rectangle_f64 & rectangle)
   {

      throw ::exception(error_not_implemented);;

   }
   

   void graphics::draw_ellipse(const ::rectangle_f64 & rectParam)
   {
      
      CGRect rectangle;

      copy(rectangle, rectParam);

      _set(m_ppen);

      CGContextStrokeEllipseInRect(m_cgcontext, rectangle);

   }


   void graphics::fill_ellipse(const ::rectangle_f64 & rectParam)
   {

       
      CGRect rectangle;

      copy(rectangle, rectParam);
      
      CGContextBeginPath(m_cgcontext);

      CGContextAddEllipseInRect(m_cgcontext, rectangle);

      _fill();

   }


   void graphics::set_polygon(const POINT_F64 * p, count c)
   {

      CGContextMoveToPoint(m_cgcontext, p[0].x, p[0].y);

      for(i32 i = 1; i < c; i++)
      {

         CGContextAddLineToPoint(m_cgcontext, p[i].x, p[i].y);

      }
      
      CGContextClosePath(m_cgcontext);

   }


   void graphics::set_polygon(const point_f64 * p, count c)
   {

      set_polygon((const POINT_F64 *) p, c);

   }


   void graphics::set_polygon(const POINT_F64 * p, count c, const POINT_F64 & pointOffset)
   {

      CGContextMoveToPoint(m_cgcontext, p[0].x + pointOffset.x, p[0].y + pointOffset.y);

      for(i32 i = 1; i < c; i++)
      {

         CGContextAddLineToPoint(m_cgcontext, p[i].x + pointOffset.x, p[i].y + pointOffset.y);

      }
      
      CGContextClosePath(m_cgcontext);

   }


   void graphics::set_polygon(const point_f64 * p, count c, const point_f64 & pointOffset)
   {

      set_polygon((const POINT_F64 *) p, c, (const POINT_F64 &) pointOffset);

   }


   void graphics::fill_polygon(const ::point_f64 * pa, count nCount)
   {

      if(nCount <= 0)
      {
         
         throw exception(::error_invalid_parameter);
         
      }

      CGContextBeginPath(m_cgcontext);

      set_polygon(pa, nCount);

      _fill();

   }


   void graphics::draw_polygon(const ::point_f64 * pa, count nCount)
   {

      if(nCount <= 0)
      {

         throw exception(::error_invalid_parameter);
         
      }

      CGContextBeginPath(m_cgcontext);

      set_polygon(pa, nCount);

      _draw();

   }


   void graphics::polygon(const ::point_f64 * pa, count nCount)
   {

      if(nCount <= 0)
      {
       
         throw exception(::error_invalid_parameter);
         
      }

      CGContextBeginPath(m_cgcontext);

      set_polygon(pa, nCount);

      _fill_and_draw();

   }


   void graphics::rectangle(const ::rectangle_f64 & rectParam)
   {

      CGRect rectangle;
      
      copy(rectangle, rectParam);
      
      CGContextBeginPath(m_cgcontext);
      
      CGContextAddRect(m_cgcontext, rectangle);
      
      _fill_and_draw();

   }


   void graphics::round_rectangle(const ::rectangle_f64 & rectangle, const double dRadius)
   {

      ::draw2d::graphics::round_rectangle(rectangle, dRadius);
      
   }
   

   void graphics::_draw_raw(const image_drawing & imagedrawing)
   {
      
      auto rectangleSource = imagedrawing.source_rectangle();
      
      auto rectangleTarget = imagedrawing.target_rectangle();

      double xDst = rectangleTarget.left;
      double yDst = rectangleTarget.top;
      double xSrc = rectangleSource.left;
      double ySrc = rectangleSource.top;

      auto pimage = imagedrawing.image();
      
      if(rectangleSource.size() == rectangleTarget.size())
      {
      
         i32 nWidth = rectangleTarget.width();
         i32 nHeight = rectangleTarget.height();
      
         synchronous_lock synchronouslock(synchronization());

         pimage->defer_update_image();
         
         ::draw2d::graphics * pgraphicsSrc = pimage->g();
         
         if(pgraphicsSrc == nullptr)
         {

            throw exception(::error_null_pointer);

         }

         synchronous_lock slSrc(pgraphicsSrc->synchronization());

         if(pgraphicsSrc->get_os_data() == nullptr)
         {

            throw ::exception(::error_null_pointer);

         }

         ::pointer < ::draw2d_quartz2d::image > imageSrc = pgraphicsSrc->m_pimage;

         ::pointer < ::draw2d::graphics > imageGraphics;

         if(imageSrc.is_set())
         {

            imageGraphics = imageSrc->g();

         }
         else
         {

            TRACE("imageSrc nullptr");

         }

         CGContextRef pdcSrc = (CGContextRef) pgraphicsSrc->get_os_data();

         CGImageRef pimage = CGBitmapContextCreateImage(pdcSrc);

         if(pimage == nullptr)
         {

            throw exception(::error_null_pointer);

         }

         size_t SrcW = CGImageGetWidth(pimage);

         size_t SrcH = CGImageGetHeight(pimage);

         CGRect rectangle;

         rectangle.origin.x = xDst;
         rectangle.origin.y = yDst;
         rectangle.size.width = nWidth;
         rectangle.size.height = nHeight;

         CGRect rectSub;

         if(::comparison::order(xSrc, SrcW) > 0)
         {

            CGImageRelease(pimage);

            return;

         }

         if(::comparison::order(ySrc, SrcH) > 0)
         {

            CGImageRelease(pimage);

            return;

         }

         rectSub.origin.x = 0;
         rectSub.origin.y = 0;
         rectSub.size.width = SrcW;
         rectSub.size.height = SrcH;
         
         if(imagedrawing.is_opacity_filter())
         {
         
            CGContextSetAlpha(m_cgcontext, (CGFloat) imagedrawing.opacity().get_opacity_rate());
            
         }
         
         if(m_pregion.is_null())
         {

            if(xSrc == 0 && ySrc == 0 && nWidth == SrcW && nHeight == SrcH)
            {

               CGContextDrawImage(m_cgcontext, rectangle, pimage);

            }
            else
            {

               CGContextSaveGState(m_cgcontext);

               CGContextClipToRect(m_cgcontext, rectangle);

               rectangle.origin.x -= xSrc;
               rectangle.origin.y -= ySrc;
               rectangle.size.width = SrcW;
               rectangle.size.height =  SrcH;

               CGContextDrawImage(m_cgcontext, rectangle, pimage);

               CGContextRestoreGState(m_cgcontext);

            }

         }
         else
         {

            CGContextSaveGState(m_cgcontext);

            _clip(m_pregion);

            if(xSrc == 0 && ySrc == 0 && nWidth == SrcW && nHeight == SrcH )
            {

            }
            else
            {

               CGContextClipToRect(m_cgcontext, rectangle);

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

            CGContextDrawImage(m_cgcontext, rectangle, pimage);

            CGContextRestoreGState(m_cgcontext);

         }

         CGImageRelease(pimage);

         if(imagedrawing.is_opacity_filter())
         {
         
            CGContextSetAlpha(m_cgcontext, (CGFloat) 1.f);
            
         }

      }
      else
      {
         
         double nDstWidth;
         double nDstHeight;
         double nSrcWidth;
         double nSrcHeight;

         ::rectangle_f64 rectFinal = imagedrawing.m_rectangleTarget;

         nDstWidth = imagedrawing.m_rectangleTarget.width();
         nDstHeight = imagedrawing.m_rectangleTarget.height();
         nSrcWidth = rectangleSource.width();
         nSrcHeight = rectangleSource.height();

         if(imagedrawing.m_eplacement == e_placement_aspect_fit)
         {
            
            double dW = nDstWidth / nSrcWidth;

            double dH = nDstHeight / nSrcHeight;

            double d = minimum(dW, dH);
            
            rectFinal.left = 0.0;

            rectFinal.top = 0.0;

            rectFinal.right = d * nSrcWidth;

            rectFinal.bottom = d * nSrcHeight;

            rectFinal.align_rate(
               imagedrawing.m_pointAlign.x(),
               imagedrawing.m_pointAlign.y(),
               imagedrawing.m_rectangleTarget);
            
            nDstWidth = rectFinal.width();
            nDstHeight = rectFinal.height();

         }

         if(nDstWidth <= 0 || nDstHeight <= 0 || nSrcWidth <= 0 || nSrcHeight <= 0)
         {

            throw exception(::error_invalid_parameter);

         }

         pimage->defer_update_image();
         
         ::draw2d::graphics * pgraphicsSrc = pimage->g();
         
         if(pgraphicsSrc == nullptr)
         {

            throw exception(::error_null_pointer);

         }

         if(pgraphicsSrc->get_os_data() == nullptr)
         {

            throw exception(::error_null_pointer);

         }

         CGImageRef pimage = CGBitmapContextCreateImage((CGContextRef) pgraphicsSrc->get_os_data());

         if(pimage == nullptr)
         {

            throw exception(::error_null_pointer);

         }

         auto SrcW = CGImageGetWidth(pimage);

         auto SrcH = CGImageGetHeight(pimage);

         CGRect rectangle;

         rectangle.origin.x = rectFinal.left;
         rectangle.origin.y = rectFinal.top;
         rectangle.size.width = rectFinal.width();
         rectangle.size.height = rectFinal.height();
         
         if(imagedrawing.is_opacity_filter())
         {
         
            CGContextSetAlpha(m_cgcontext, (CGFloat) imagedrawing.opacity().get_opacity_rate());
            
         }

         if(xSrc == 0 && ySrc == 0 && SrcW == nSrcWidth && SrcH == nSrcHeight)
         {

            CGContextDrawImage(m_cgcontext, rectangle, pimage);

         }
         else
         {

            CGRect rectSub;

            rectSub.origin.x = xSrc;
            rectSub.origin.y = ySrc;
            rectSub.size.width = nSrcWidth;
            rectSub.size.height = nSrcHeight;

            CGImageRef imageSub = CGImageCreateWithImageInRect(pimage, rectSub);

            if(imageSub != nullptr)
            {

               CGContextDrawImage(m_cgcontext, rectangle, imageSub);

               CGImageRelease(imageSub);

            }

         }

         CGImageRelease(pimage);
         
         if(imagedrawing.is_opacity_filter())
         {
         
            CGContextSetAlpha(m_cgcontext, (CGFloat) 1.f);
            
         }

      }

   }


   ::color::color graphics::GetPixel(double x, double y)
   {

      throw ::exception(error_not_implemented);;
      
      return ::color::color();

   }


   ::color::color graphics::GetPixel(const ::point_f64 & point)
   {

      throw ::exception(error_not_implemented);

      return false;

   }


   ::color::color graphics::SetPixel(double x, double y, const ::color::color & color)
   {

      throw ::exception(error_not_implemented);;

      return ::color::color();

   }


   ::color::color graphics::SetPixel(const ::point_f64 & point, const ::color::color & color)
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

         ::rectangle_f64 rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());

         auto rectText = ::rectangle_f64(::point_f64(x, y), ::size_f64(get_text_extent(scopedstr)));

         if (rectIntersect.intersect(rectIntersect, rectText))
         {

            rectText.bottom = rectText.top + rectText.height() * 2;

            auto pimage1 = m_pcontext->m_pauracontext->create_image(rectText.size());
            
            pimage1->fill(0, 0, 0, 0);
            pimage1->get_graphics()->set(get_current_font());
            pimage1->get_graphics()->set(get_current_brush());
            pimage1->get_graphics()->text_out(0, 0, scopedstr);

            pimage1->blend(::point_f64(), m_pimageAlphaBlend, point_f64((int)maximum(0, x - m_pointAlphaBlend.x()), (int)maximum(0, y - m_pointAlphaBlend.y())), rectText.size());

            set_alpha_mode(::draw2d::e_alpha_mode_blend);

            auto rectangleDst=rectangle_i32(::point_i32((int)x, (int)y),
                                 rectText.size());
            
            rectangle_f64 rectangleSource(point_i32(), rectangleDst.size());
            
            image_source imagesource(pimage1, rectangleSource);
            
            image_drawing_options imagedrawingoptions(rectangleDst);
            
            image_drawing imagedrawing(imagedrawingoptions, imagesource);
            
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
   ::u32 graphics::SetBoundsRect(const ::rectangle_f64 & rectBounds, ::u32 flags)
   {

      throw ::exception(error_not_implemented);

      return 0;

   }


   ::u32 graphics::GetBoundsRect(::rectangle_f64 * rectBounds, ::u32 flags)
   {

      throw ::exception(error_not_implemented);
      
      return 0;

   }


   i32 graphics::StartPage()
   {

      throw ::exception(error_not_implemented);

      return 0;

   }


   i32 graphics::EndPage()
   {

      throw ::exception(error_not_implemented);;

      return 0;

   }


   i32 graphics::AbortDoc()
   {

      throw ::exception(error_not_implemented);;
      
      return 0;

   }


   i32 graphics::EndDoc()
   {

      throw ::exception(error_not_implemented);
      
      return 0;

   }


   void graphics::SetPixelV(double x, double y, const ::color::color & color)
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::SetPixelV(const ::point_f64 & point, const ::color::color & color)
   {

      throw ::exception(error_not_implemented);

   }


   void graphics::angle_arc(double x, double y, double dRadius, ::angle_f64 fStartAngle, ::angle_f64 fSweepAngle)
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::arc_to(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd)
   {

      throw ::exception(error_not_implemented);;

   }


   ::draw2d::pen * graphics::get_current_pen()
   {

      return m_ppen;

   }


   ::draw2d::brush * graphics::get_current_brush()
   {

      return m_pbrush;

   }


   ::draw2d::palette * graphics::get_current_palette()
   {

      return (::draw2d::palette *)nullptr;

   }


   ::write_text::font * graphics::get_current_font()
   {

      return m_pfont;

   }


   ::draw2d::bitmap * graphics::get_current_bitmap()
   {

      return m_pbitmap;

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





   void graphics::DPtoHIMETRIC(::size_f64 * psize)
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::HIMETRICtoDP(::size_f64 * psize)
   {

      throw ::exception(error_not_implemented);;

   }


   void graphics::LPtoHIMETRIC(::size_f64 * psize)
   {
      
      ASSERT(::is_memory_segment_ok(psize, sizeof(size_f64)));

      LPtoDP(psize);
      
      DPtoHIMETRIC(psize);
      
   }


   void graphics::HIMETRICtoLP(::size_f64 * psize)
   {
      
      ASSERT(::is_memory_segment_ok(psize, sizeof(size_f64)));

      HIMETRICtoDP(psize);
      
      DPtoLP(psize);
      
   }


   void graphics::DeleteDC()
   {

      if(m_cglayer != nullptr)
      {

         CGLayerRelease(m_cglayer);

         m_cglayer = nullptr;

      }

      if(m_cgcontext != nullptr)
      {

         if(m_bOwnGraphicsContext)
         {
         
            CGContextRelease(m_cgcontext);
            
            m_bOwnGraphicsContext = false;
            
         }
         
         m_cgcontext = nullptr;

      }

      m_pimage = nullptr;

      m_ewritetextrendering  = ::write_text::e_rendering_anti_alias_grid_fit;

   }


   i32 graphics::save_graphics_context()
   {

      CGContextSaveGState(m_cgcontext);

      m_iSaveGraphicsContext++;

      return m_iSaveGraphicsContext;

   }


   void graphics::restore_graphics_context(i32 nSavedDC)
   {

      bool bRestored = false;

      while(m_iSaveGraphicsContext >= maximum(1, nSavedDC))
      {

         CGContextRestoreGState(m_cgcontext);

         m_iSaveGraphicsContext--;

         bRestored = true;

      }

   }


   void graphics::set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode)
   {

      if(einterpolationmode == ::draw2d::e_interpolation_mode_low_quality)
      {

         CGContextSetInterpolationQuality(m_cgcontext, kCGInterpolationDefault);

      }
      else if(einterpolationmode == ::draw2d::e_interpolation_mode_high_quality_bicubic)
      {

         CGContextSetInterpolationQuality(m_cgcontext, kCGInterpolationHigh);

      }
      else
      {

         CGContextSetInterpolationQuality(m_cgcontext,kCGInterpolationLow);

      }

   }


   point_f64 graphics::get_origin()
   {

      return ::draw2d::graphics::get_origin();

   }


   void graphics::_get(::draw2d::matrix & matrix)
   {

      synchronous_lock synchronouslock(synchronization());

      CGAffineTransform affine = CGContextGetCTM(m_cgcontext);

      copy(matrix, affine);

   }


   void graphics::_set(const ::draw2d::matrix & matrix)
   {

      synchronous_lock synchronouslock(synchronization());

      CGAffineTransform affine = CGContextGetCTM(m_cgcontext);

      CGAffineTransform affineInverted;

      affineInverted = CGAffineTransformInvert(affine);

      CGContextConcatCTM(m_cgcontext, affineInverted);

      CGAffineTransform affineSet;

      copy(affineSet, matrix);

      CGContextConcatCTM(m_cgcontext, affineSet);

   }


   point_f64 graphics::set_origin(double x, double y)
   {

      point_f64 pt =get_origin();
      
      pt.x() = x - pt.x();
      pt.y() = y - pt.y();
      
      return offset_origin(pt.x(), pt.y());
      
   }


   point_f64 graphics::offset_origin(double nWidth, double nHeight)
   {

      return ::draw2d::graphics::offset_origin(nWidth, nHeight);

   }


   void graphics::clear_current_point()
   {
   
   }


   size_f64 graphics::set_extents(double x, double y)
   {

      throw ::exception(error_not_implemented);
      
      return ::size_f64(0, 0);

   }


   size_f64 graphics::scale_extents(double xNum, double xDenom, double yNum, double yDenom)
   {

      return ::draw2d::graphics::scale_extents(xNum, xDenom, yNum, yDenom);

   }


   point_f64 graphics::SetWindowOrg(double x, double y)
   {

      throw ::exception(error_not_implemented);
      
      return ::point_f64();

   }


   point_f64 graphics::offset_window_org(double nWidth, double nHeight)
   {

      throw ::exception(error_not_implemented);
      
      return ::point_f64();


   }


   size_f64 graphics::set_window_ext(double x, double y)
   {

      throw ::exception(error_not_implemented);
      
      return ::size_f64(0, 0);

   }


   size_f64 graphics::scale_window_ext(double xNum, double xDenom, double yNum, double yDenom)
   {

      throw ::exception(error_not_implemented);
      
      return ::size_f64(0, 0);

   }


   i32 graphics::get_clip_box(::rectangle_f64 & rectangle)
   {

      CGRect cgrect = CGContextGetClipBoundingBox (m_cgcontext);
      
      ::copy(rectangle, cgrect);
      
//      prectangle->left = rectangle.origin.x;
//      prectangle->top = rectangle.origin.y;
//      prectangle->right = prectangle->left + rectangle.size.width;
//      prectangle->bottom = prectangle->top + rectangle.size.height;

      return 0;

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
   
      CGContextResetClip(m_cgcontext);
   
   }


   void graphics::_intersect_clip()
   {
      
      if(CGContextIsPathEmpty(m_cgcontext))
      {
         
         return;
         
      }
      
      CGContextClip(m_cgcontext);
      
   }

   
   void graphics::intersect_clip(const ::rectangle_f64 & rectangle)
   {
      
      CGRect r;
      
      //auto rectangleOffset = rectangle;
      
      //rectangleOffset += m_pointAddShapeTranslate;
      
      copy(r, rectangle);
      
      CGContextBeginPath(m_cgcontext);
   
      CGContextAddRect(m_cgcontext, r);
      
      CGContextClip(m_cgcontext);

   }


   void graphics::intersect_clip(const ::ellipse_f64 & ellipse)
   {
      
      CGRect r;
      
      //auto rectangleOffset = ellipse;
      
      //rectangleOffset += m_pointAddShapeTranslate;
      
      copy(r, ellipse);

      CGContextBeginPath(m_cgcontext);
   
      CGContextAddEllipseInRect(m_cgcontext, r);
      
      CGContextClip(m_cgcontext);

   }


   void graphics::intersect_clip(const ::polygon_f64 & polygon)
   {
      
      CGContextBeginPath(m_cgcontext);
   
      set_polygon(polygon.data(), polygon.count());

      CGContextClip(m_cgcontext);

   }

   
   void graphics::_add_clipping_shape(const ::rectangle_f64 & rectangle, ::draw2d::region * pregion)
   {
   
      _add_shape(rectangle);
      
      _intersect_clip();
      
   }


   void graphics::_add_clipping_shape(const ::ellipse_f64 & ellipse, ::draw2d::region * pregion)
   {
      
      _add_shape(ellipse);
      
      _intersect_clip();
      
   }


   void graphics::_add_clipping_shape(const ::polygon_f64 & polygon, ::draw2d::region * pregion)
   {
      
      _add_shape(polygon);
      
      _intersect_clip();
      
   }


   void graphics::_intersect_eo_clip()
   {
      
      if(CGContextIsPathEmpty(m_cgcontext))
      {
         
         return;
         
      }
      
      CGContextEOClip(m_cgcontext);
      
   }


   void graphics::_add_shape(const ::rectangle_f64 & rectangle)
   {
   
      CGRect r;
      
//      auto rectangleOffset = rectangle;
//
//      rectangleOffset += m_pointAddShapeTranslate;
      
      copy(r, rectangle);
   
      CGContextAddRect(m_cgcontext, r);
      
   }


   void graphics::_add_shape(const ::ellipse_f64 & ellipse)
   {
   
      CGRect r;
      
      copy(r, ellipse);
   
      CGContextBeginPath(m_cgcontext);
   
      CGContextAddEllipseInRect(m_cgcontext, r);
      
   }


   void graphics::_add_shape(const ::polygon_f64 & polygon)
   {
   
      CGContextBeginPath(m_cgcontext);
   
      set_polygon(polygon.data(), polygon.count());
      
   }


   void graphics::LPtoDP(::size_f64 * psize)
   {

      throw ::exception(error_not_implemented);;

      return;

   }


   void graphics::DPtoLP(::size_f64 * psize)
   {

      throw ::exception(error_not_implemented);;

      return;

   }


   i32 graphics::draw_text(const char * lpszString, i32 nCount, const ::rectangle_f64 & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      draw_text(string(lpszString, nCount), rectangle, ealign, edrawtext);

      return 0;
      
   }


//   size_f64 graphics::get_text_extent(const ::scoped_string * lpszString, strsize nCount, i32 iIndex)
//   {
//
//      size_f64 sz;
//
//      get_text_extent(sz, lpszString, nCount, iIndex);
//
//      return size_f64((int) sz.cx(), (int) sz.cy());
//
//   }
//
//
//   size_f64 graphics::get_text_extent(const char * lpszString, strsize nCount)
//   {
//
//      ::size_f64 size_f64;
//
//      get_text_extent(size_f64, lpszString, nCount, (int) nCount);
//
//      return ::size_f64(size_f64.cx(), size_f64.cy());
//
//   }


//   size_f64 graphics::get_text_extent(const block & block)
//   {
//
//      ::size_f64 size;
//
//      get_text_extent(size, (const char *) block.get_data(), (int)block.get_size());
//
//      return size;
//
//   }


   ::size_f64 graphics::get_text_extent(const ::scoped_string & scopedstr, ::index iIndex)
   {
      
      synchronous_lock synchronouslock(synchronization());

      CGFloat ascent, descent, leading, width;

      string_array stra;

      stra.add_lines(scopedstr(0, minimum(iIndex, scopedstr.size())));
      
      ::size_f64 size;

      size.cy() = 0;

      size.cx() = 0;

      for(auto str : stra)
      {

         const_cast < graphics * > (this)->internal_show_text(0, 0, 0, str, kCGTextInvisible, e_align_top_left, e_draw_text_none, false, &ascent, &descent, &leading, &width, nullptr, nullptr, m_pfont);

         size.cy() += ascent + descent + leading;

//         if(leading <= 0)
//         {
//
//            size.cy() += descent;
//
//         }

         size.cx() = maximum(size.cx(), width);

      }
      
      return size;

   }


   ::size_f64 graphics::get_text_extent(const ::scoped_string & scopedstr)
   {

      return get_text_extent(scopedstr, (i32) scopedstr.size());

   }


//   void graphics::get_text_extent(size_f64 & size, const string & str)
//   {
//
//      return ::draw2d::graphics::get_text_extent(size, str);
//
//   }


   void graphics::fill_rectangle(const ::rectangle_f64 & rectParam, const ::color::color & color)
   {

      CGRect rectangle;

      copy(rectangle, rectParam);

      internal_set_fill_color(color);

      CGContextFillRect(m_cgcontext, rectangle);

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
      
      if(pfont == nullptr)
      {
         
         if(m_pfont.is_null())
         {

            m_pfont.create(this);
            
            auto psystem = acmesystem();
            
            auto pnode = psystem->node();

            m_pfont->create_pixel_font(pnode->font_name(e_font_sans), 16.0);

         }
         
         pfont = m_pfont;
         
      }

      if(bDraw && pbrush == nullptr)
      {
         
         pbrush = m_pbrush;
         
      }

      if(bDraw && ppen == nullptr)
      {
         
         ppen = m_ppen;
         
      }

      return internal_show_text(pfont, pbrush, ppen, x, y, wAlign, str, emode, ealign, edrawtext, bDraw, pascent, pdescent, pleading, pwidth);

   }


   void graphics::draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen)
   {

      CGContextBeginPath(m_cgcontext);

      CGContextMoveToPoint(m_cgcontext, x1, y1);

      CGContextAddLineToPoint(m_cgcontext, x2, y2);

      _draw(ppen);

      m_point.x() = x2;
      
      m_point.y() = y2;

   }


   void graphics::line_to(const ::point_f64 & point)
   {

      CGContextBeginPath(m_cgcontext);

      CGContextMoveToPoint(m_cgcontext, m_point.x(), m_point.y());

      CGContextAddLineToPoint(m_cgcontext, point.x(), point.y());

      _draw();

      m_point = point;

   }


   void graphics::set_alpha_mode(::draw2d::enum_alpha_mode ealphamode)
   {


      if(m_cgcontext == nullptr)
      {

         throw exception(error_null_pointer);

      }

      ::draw2d::graphics::set_alpha_mode(ealphamode);

      if(m_ealphamode == ::draw2d::e_alpha_mode_blend)
      {

         CGContextSetBlendMode(m_cgcontext, kCGBlendModeNormal);

      }
      else if(m_ealphamode == ::draw2d::e_alpha_mode_set)
      {

         CGContextSetBlendMode(m_cgcontext, kCGBlendModeCopy);

      }
  
   }


   void graphics::set_text_rendering_hint(::write_text::enum_rendering etextrenderinghint)
   {

      ::draw2d::graphics::set_text_rendering_hint(etextrenderinghint);

   }


   void graphics::attach(void * pdata)
   {
      
      destroy();

      m_iType = 10;

      m_cgcontext = (CGContextRef) pdata;

      m_bOwnGraphicsContext = false;
      
      m_osdata[0] = (void *) m_cgcontext;

   }


   void * graphics::detach()
   {

      CGContextRef pgraphics = m_cgcontext;

      m_cgcontext = nullptr;

      return pgraphics;

   }


   void graphics::blur(bool bExpand, double dRadius, const ::rectangle_f64 & rectangle)
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

      CGContextSetRGBFillColor(m_cgcontext, pbrush->m_color.dr(), pbrush->m_color.dg(), pbrush->m_color.db(), pbrush->m_color.da());

   }


   void graphics::_set(::draw2d::pen * ppen)
   {

      if(ppen == nullptr)
      {
         
         throw exception(error_null_pointer);
         
      }

      if(ppen->m_epen == ::draw2d::e_pen_brush && ppen->m_pbrush)
      {

         if(ppen->m_pbrush->m_ebrush == ::draw2d::e_brush_solid)
         {

            CGContextSetRGBStrokeColor(m_cgcontext, ppen->m_pbrush->m_color.dr(), ppen->m_pbrush->m_color.dg(), ppen->m_pbrush->m_color.db(), ppen->m_pbrush->m_color.da());

         }

      }
      else
      {

         CGContextSetRGBStrokeColor(m_cgcontext, ppen->m_color.dr(), ppen->m_color.dg(), ppen->m_color.db(), ppen->m_color.da());

      }
      
      if(ppen->m_elinecapBeg == ::draw2d::e_line_cap_round
         && ppen->m_elinecapEnd == ::draw2d::e_line_cap_round)
      {
         
         CGContextSetLineCap(m_cgcontext, kCGLineCapRound);
         
      }
      else if(ppen->m_elinecapBeg == ::draw2d::e_line_cap_flat
         && ppen->m_elinecapEnd == ::draw2d::e_line_cap_flat)
      {
         
         CGContextSetLineCap(m_cgcontext, kCGLineCapButt);
         
      }

      CGContextSetLineWidth(m_cgcontext, ppen->m_dWidth);

   }


   void graphics::_set_pen(::draw2d::brush * pbrush, double dWidth)
   {

      if(pbrush == nullptr || pbrush->m_ebrush == ::draw2d::e_brush_null)
      {

         throw exception(error_null_pointer);

      }

      CGContextSetRGBStrokeColor(m_cgcontext, pbrush->m_color.dr(), pbrush->m_color.dg(), pbrush->m_color.db(), pbrush->m_color.da());

      CGContextSetLineWidth(m_cgcontext, dWidth);

   }


   void graphics::_fill_and_draw()
   {

      _fill(m_pbrush);

      _draw(m_ppen);

   }


   void graphics::_fill(::draw2d::brush * pbrush)
   {

      CGContextRef pgraphics = m_cgcontext;

      CGContextSaveGState(pgraphics);

      _fill(pbrush, true);

      CGContextRestoreGState(pgraphics);

   }


   void graphics::_fill(::draw2d::brush * pbrush, bool bContextClip)
   {

      if(pbrush == nullptr || pbrush->m_ebrush == ::draw2d::e_brush_null)
      {
         
         return;
         
      }

      CGContextRef pgraphics = m_cgcontext;
      
      if(pbrush->m_ebrush == ::draw2d::e_brush_box_gradient)
      {
         
         pbrush->defer_update(this, 0);

         if(bContextClip)
         {
         
            _intersect_clip();
            
         }

         _clip(m_pregion);
         
         rectangle_f32 outer(pbrush->m_point, pbrush->m_size);
         rectangle_f32 inner(outer);
         
         float fRadius = pbrush->m_dRadius;
         
         inner.deflate(fRadius);

         CGPoint s, e;
         
         s.x = 0;
         s.y = 0;
         e.x = 0;
         e.y = 0;
         
         CGContextSetAllowsAntialiasing(m_cgcontext, TRUE);
         CGContextSetShouldAntialias(m_cgcontext, TRUE);
         
         //set_alpha_mode(::draw2d::e_alpha_mode_set);
         
         CGGradientRef grad = (CGGradientRef) pbrush->m_osdata[0];

         CGRect r;
         
         float f1 = 0.666f;
         //top-left
         CGContextSaveGState(m_cgcontext);
         r.origin.x = outer.left + f1;
         r.origin.y = outer.top + f1;
         r.size.width = fRadius;
         r.size.height = fRadius;
         CGContextClipToRect(m_cgcontext, r);
         CGContextTranslateCTM(m_cgcontext, inner.left, inner.top);
         CGContextScaleCTM(m_cgcontext, fRadius, fRadius);
         CGContextDrawRadialGradient(m_cgcontext, grad, s, 0, e, 1.0f, kCGGradientDrawsBeforeStartLocation);
         CGContextRestoreGState(m_cgcontext);

         //top-right
         CGContextSaveGState(m_cgcontext);
         r.origin.x = inner.right - f1;
         r.origin.y = outer.top + f1;
         r.size.width = fRadius;
         r.size.height = fRadius;
         CGContextClipToRect(m_cgcontext, r);
         CGContextTranslateCTM(m_cgcontext, inner.right, inner.top);
         CGContextScaleCTM(m_cgcontext, fRadius, fRadius);
         CGContextDrawRadialGradient(m_cgcontext, grad, s, 0, e, 1.0f, kCGGradientDrawsBeforeStartLocation);
         CGContextRestoreGState(m_cgcontext);

         
         //bottom-right
         CGContextSaveGState(m_cgcontext);
         r.origin.x = inner.right - f1;
         r.origin.y = inner.bottom - f1;
         r.size.width = fRadius;
         r.size.height = fRadius;
         CGContextClipToRect(m_cgcontext, r);
         CGContextTranslateCTM(m_cgcontext, inner.right, inner.bottom);
         CGContextScaleCTM(m_cgcontext, fRadius, fRadius);
         CGContextDrawRadialGradient(m_cgcontext, grad, s, 0, e, 1.0f, kCGGradientDrawsBeforeStartLocation);
         CGContextRestoreGState(m_cgcontext);

         //bottom-left
         CGContextSaveGState(m_cgcontext);
         r.origin.x = outer.left + f1;
         r.origin.y = inner.bottom - f1;
         r.size.width = fRadius;
         r.size.height = fRadius;
         CGContextClipToRect(m_cgcontext, r);
         CGContextTranslateCTM(m_cgcontext, inner.left, inner.bottom);
         CGContextScaleCTM(m_cgcontext, fRadius, fRadius);
         CGContextDrawRadialGradient(m_cgcontext, grad, s, 0, e, 1.0f, kCGGradientDrawsBeforeStartLocation);
         CGContextRestoreGState(m_cgcontext);

         float f5 = 0.25f;
         
         r.origin.x = inner.left - f5;
         r.origin.y = inner.top - f5;
         r.size.width = inner.width() + f5 * 2.0f;
         r.size.height = inner.height() + f5 * 2.0f;

         CGContextSetRGBFillColor(m_cgcontext, pbrush->m_color1.dr(), pbrush->m_color1.dg(), pbrush->m_color1.db(), pbrush->m_color1.da());
         CGContextFillRect(m_cgcontext, r);
         
         float f2 = 0.444f;
         //bottom
         r.origin.x = inner.left + f2;
         r.origin.y = inner.bottom - f2;
         r.size.width = inner.width() - (f2 * 2.0f);
         r.size.height = fRadius;
         CGContextSaveGState(m_cgcontext);
         CGContextClipToRect(m_cgcontext, r);
         s.x = inner.center_x();
         e.x = inner.center_x();
         s.y = inner.bottom;
         e.y = outer.bottom;
         CGContextDrawLinearGradient(pgraphics, (CGGradientRef) pbrush->m_osdata[0], s, e, 0);
         CGContextRestoreGState(m_cgcontext);

         // top
         r.origin.x = inner.left + f2;
         r.origin.y = outer.top + f2;
         r.size.width = inner.width() - (f2 * 2.0f);
         r.size.height = fRadius;
         CGContextSaveGState(m_cgcontext);
         CGContextClipToRect(m_cgcontext, r);
         s.x = inner.center_x();
         e.x = inner.center_x();
         e.y = outer.top;
         s.y = inner.top;
         CGContextDrawLinearGradient(pgraphics, (CGGradientRef) pbrush->m_osdata[0], s, e, 0);
         CGContextRestoreGState(m_cgcontext);

         // right
         r.origin.x = inner.right - f2;
         r.origin.y = inner.top + f2;
         r.size.width = fRadius;
         r.size.height = inner.height() - (f2 * 2.0f);
         CGContextSaveGState(m_cgcontext);
         CGContextClipToRect(m_cgcontext, r);
         s.x = inner.right;
         e.x = outer.right;
         e.y = inner.center_y();
         s.y = inner.center_y();
         CGContextDrawLinearGradient(pgraphics, (CGGradientRef) pbrush->m_osdata[0], s, e, 0);
         CGContextRestoreGState(m_cgcontext);

         // left
         r.origin.x = outer.left + f2;
         r.origin.y = inner.top + f2;
         r.size.width = fRadius;
         r.size.height = inner.height() - (f2 * 2.0f);
         CGContextSaveGState(m_cgcontext);
         CGContextClipToRect(m_cgcontext, r);
         s.x = inner.left;
         e.x = outer.left;
         e.y = inner.center_y();
         s.y = inner.center_y();
         CGContextDrawLinearGradient(pgraphics, (CGGradientRef) pbrush->m_osdata[0], s, e, 0);
         CGContextRestoreGState(m_cgcontext);

         CGContextSetAllowsAntialiasing(m_cgcontext, TRUE);
         CGContextSetShouldAntialias(m_cgcontext, TRUE);

      }
      else if(pbrush->m_ebrush == ::draw2d::e_brush_radial_gradient_color)
      {
         
         pbrush->defer_update(this, 0);

         if(bContextClip)
         {

            _intersect_clip();

         }

         _clip(m_pregion);

         CGPoint myStartPoint, myEndPoint;

         CGContextTranslateCTM(pgraphics, pbrush->m_point.x(), pbrush->m_point.y());

         CGContextScaleCTM(pgraphics, pbrush->m_size.cx(), pbrush->m_size.cy());

         myStartPoint.x = 0;

         myStartPoint.y = 0;

         myEndPoint.x = 0;

         myEndPoint.y = 0;

         CGContextDrawRadialGradient(pgraphics, (CGGradientRef) pbrush->m_osdata[0], myStartPoint, 0, myEndPoint, 1.0f, kCGGradientDrawsBeforeStartLocation);

      }
      else if(pbrush->m_ebrush == ::draw2d::e_brush_linear_gradient_point_color)
      {
         
         pbrush->defer_update(this, 0);

         if(bContextClip)
         {

            _intersect_clip();

         }

         _clip(m_pregion);

         CGPoint point1, point2;

         point1.x = pbrush->m_point1.x();

         point1.y = pbrush->m_point1.y();

         point2.x = pbrush->m_point2.x();

         point2.y = pbrush->m_point2.y();
         
         CGRect r;
         
         r.origin = point1;
         r.size.width = point2.x - point1.x;
         r.size.height = point2.y - point1.y;
         
         CGContextDrawLinearGradient(pgraphics, (CGGradientRef) pbrush->m_osdata[0], point1, point2, 0);
         
      }
      else if(pbrush->m_ebrush == ::draw2d::e_brush_pattern)
      {

         if(bContextClip)
         {

            _intersect_clip();

         }

         _clip(m_pregion);

         scoped_restore(m_bPat);

         CGRect rectangle = CGContextGetClipBoundingBox(pgraphics);
         
         ::rectangle_i32 rectangle_i32;
         
         copy(rectangle_i32, rectangle);
         
         image_source imagesource(pbrush->m_pimage);
         
         image_drawing_options imagedrawingoptions(rectangle_i32);
         
         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         draw(imagedrawing);

      }
      else if(pbrush->m_ebrush == ::draw2d::e_brush_solid)
      {
         
         pbrush->defer_update(this, 0);
         
         CGColorRef cgcolorref = (CGColorRef) pbrush->m_osdata[0];

         if(cgcolorref)
         {
            
            if(m_pregion.is_null())
            {

               CGContextSetFillColorWithColor(pgraphics, cgcolorref);

               CGContextFillPath(pgraphics);

            }
            else
            {

               CGContextSetFillColorWithColor(pgraphics, cgcolorref);

               if(bContextClip)
               {

                  _intersect_clip();

               }

               _clip(m_pregion);

               CGContextAddRect(pgraphics, CGContextGetClipBoundingBox(pgraphics));

               CGContextFillPath(pgraphics);

            }
            
         }
         else
         {
            
            if(m_pregion.is_null())
            {

               CGContextSetFillColorWithColor(m_cgcontext, cgcolorref);

               CGContextFillPath(pgraphics);

            }
            else
            {

               CGContextSetFillColorWithColor(m_cgcontext, cgcolorref);

               if(bContextClip)
               {

                  _intersect_clip();

               }

               _clip(m_pregion);

               CGContextAddRect(pgraphics, CGContextGetClipBoundingBox(pgraphics));

               CGContextFillPath(pgraphics);

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

      CGContextSaveGState(m_cgcontext);

      _set(ppen);

      if(ppen->m_epen == ::draw2d::e_pen_brush && ppen->m_pbrush.is_set()
            && (ppen->m_pbrush->m_ebrush == ::draw2d::e_brush_linear_gradient_point_color
                || ppen->m_pbrush->m_ebrush == ::draw2d::e_brush_radial_gradient_color
                || ppen->m_pbrush->m_ebrush == ::draw2d::e_brush_pattern)
        )
      {

         CGContextReplacePathWithStrokedPath(m_cgcontext);

         // Turn the fillable path in to a clipping region.
//            _intersect_clip();;

         _fill(ppen->m_pbrush);

      }
      else
      {

         CGContextStrokePath(m_cgcontext);

      }

      CGContextRestoreGState(m_cgcontext);

   }


   void graphics::_draw(::draw2d::brush * pbrush)
   {

      if(pbrush == nullptr || pbrush->m_ebrush == ::draw2d::e_brush_null)
         return;

      CGContextSaveGState(m_cgcontext);

      _set(pbrush);

      if(pbrush->m_ebrush == ::draw2d::e_brush_linear_gradient_point_color
            || pbrush->m_ebrush == ::draw2d::e_brush_radial_gradient_color
            || pbrush->m_ebrush == ::draw2d::e_brush_pattern)

      {

         CGContextReplacePathWithStrokedPath(m_cgcontext);

         // Turn the fillable path in to a clipping region.
         //_intersect_clip();;

         _fill(pbrush);

      }
      else
      {

         CGContextStrokePath(m_cgcontext);

      }

      CGContextRestoreGState(m_cgcontext);

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

      synchronous_lock ml(synchronization());

      double greekdeltax;

      double greekdeltay;

      greekdeltax = 0.;

      greekdeltay = 0.;

      str.find_replace("\t", "        ");

      string_array stra;

      stra.add_lines(str);

      int offsety = 0;

      CGFloat ascent, descent, leading, width;

      for(auto str : stra)
      {

         internal_show_text(
                            textout.m_point.x() + greekdeltax,
                            textout.m_point.y() + greekdeltay + offsety,
                            0, str,
                             kCGTextStroke,
                            e_align_top_left,
                            e_draw_text_none, true, &ascent, &descent, &leading, &width, ppen, nullptr, textout.m_pfont);

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

      synchronous_lock ml(synchronization());

      double greekdeltax;

      double greekdeltay;

      greekdeltax = 0.;

      greekdeltay = 0.;

      str.find_replace("\t", "        ");

      string_array stra;

      stra.add_lines(str);

      int offsety = 0;

      CGFloat ascent, descent, leading, width;

      for(auto str : stra)
      {

         internal_show_text(
                            textout.m_point.x() + greekdeltax,
                            textout.m_point.y() + greekdeltay + offsety,
                            0, str,
                             kCGTextFill,
                            e_align_top_left,
                            e_draw_text_none, true, &ascent, &descent, &leading, &width, nullptr, pbrush,  textout.m_pfont);

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

      synchronous_lock ml(synchronization());

      double greekdeltax;

      double greekdeltay;

      greekdeltax = 0.;

      greekdeltay = 0.;

      str.find_replace("\t", "        ");

      string_array stra;

      stra.add_lines(str);

      int offsety = 0;

      CGFloat ascent, descent, leading, width;

      for(auto str : stra)
      {

         internal_show_text(
                            drawtext.m_rectangle.left + greekdeltax,
                            drawtext.m_rectangle.top + greekdeltay + offsety,
                            0,
                            str, kCGTextStroke,
                            e_align_top_left,
                            e_draw_text_none,
                            true, &ascent, &descent, &leading, &width, ppen, nullptr, drawtext.m_pfont);

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

      synchronous_lock ml(synchronization());

      double greekdeltax;

      double greekdeltay;

      greekdeltax = 0.;

      greekdeltay = 0.;

      str.find_replace("\t", "        ");

      string_array stra;

      stra.add_lines(str);

      int offsety = 0;

      CGFloat ascent, descent, leading, width;

      for(auto str : stra)
      {

         internal_show_text(
                            drawtext.m_rectangle.left + greekdeltax,
                            drawtext.m_rectangle.top + greekdeltay + offsety,
                            0,
                            str, kCGTextFill,
                            e_align_top_left,
                            e_draw_text_none,
                            true, &ascent, &descent, &leading, &width, nullptr, pbrush, drawtext.m_pfont);

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

      return _fill(m_pbrush);

   }


   void graphics::_draw()
   {

      return _draw(m_ppen);

   }


   void graphics::internal_set_fill_color(const ::color::color & color)
   {

      CGContextSetRGBFillColor(m_cgcontext, color.dr(), color.dg(), color.db(), color.da());

   }


   void graphics::draw_text(const string & strParam,const ::rectangle_f64 & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      string str(strParam);

      synchronous_lock ml(synchronization());

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
         m_pbrush,
         m_pfont);

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
               m_pbrush,
               m_pfont);

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
                                  e_align_top_left,
                                  edrawtext,
               true,
               &ascent,
               &descent,
               &leading,
               nullptr,
               nullptr,
               m_pbrush,
               m_pfont);

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

            rectangle_f64 rectUpper(rectangle);

            rectangle_f64 rectLower(rectangle);

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
               e_align_center,
               e_draw_text_none,
               true,
               &ascent,
               &descent,
               &leading,
               nullptr,
               nullptr,
               m_pbrush,
               m_pfont);

               double greekdeltay = ascent + descent + leading;

//                  if(leading <= 0)
//                  {
//
//                     greekdeltay += descent;
//
//                  }

               rectUpper.bottom -= greekdeltay/2.0;

               rectLower.top += greekdeltay/2.0;

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

      synchronous_lock synchronouslock(synchronization());

      //CGContextRef pgraphics = m_cgcontext;

      if(str == "GB18030 Bitmap")
      {
         
         ::output_debug_string("GB18030 Bitmap");
         
      }

      //::pointer < ::draw2d_quartz2d::font > f = spfont;
      
      if(!pfont)
      {
         
         throw exception(error_null_pointer);
         
      }

      if(str.trimmed().is_empty())
      {

         return;
         //throw exception(error_invalid_empty_argument);

      }
      
      CTFontRef font = (CTFontRef) pfont->get_os_data(this);

      if(pfont == nullptr)
      {
         
         throw exception(error_null_pointer);
         
      }

      bool bFill = false;

      bool bStroke = false;

      color32_t crFill;

      color32_t crStroke;

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

               crFill = ::is_null(pbrush) ? argb(255, 0, 0, 0) : pbrush->m_color;

            }

         }

         if(emode == kCGTextStroke|| emode == kCGTextFillStroke)
         {

            bStroke = true;

            crStroke = ::is_null(ppen) ? argb(255, 0, 0, 0) : ppen->m_color;

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

//      ::draw2d_quartz2d::font::metrics & m = f->m_mapMetrics[str];

      CFStringRef string = CFStringCreateWithCString(nullptr, str, kCFStringEncodingUTF8);

      if(string == nullptr)
      {

         throw exception(error_null_pointer);

      }

      array < const void * > pkeys;
      
      array < const void * > pvals;
      
      array < CFTypeRef > cfrel;
      
      array < CGColorRef > crrel;
      
      pkeys.add(kCTFontAttributeName);

      pvals.add(font);

      if(pfont->m_bUnderline)
      {

         int iUnderlineStyle = kCTUnderlineStyleSingle;

         CFNumberRef num = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &iUnderlineStyle);

         pkeys.add(kCTUnderlineStyleAttributeName);
         pvals.add(num);
         cfrel.add(num);

      }

//      if(emode != kCGTextInvisible && bDraw && (bFill || bStroke || emode == kCGTextClip))
         if(emode != kCGTextInvisible && bDraw && (bFill || bStroke))
      {

         CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
         
         CGFloat components[4];

         //if(bFill || emode == kCGTextClip)
         if(bFill)
         {

            components[0] = colorref_get_r_value(crFill) / 255.f;
            components[1] = colorref_get_g_value(crFill) / 255.f;
            components[2] = colorref_get_b_value(crFill) / 255.f;
            components[3] = colorref_get_a_value(crFill) / 255.f;

            pkeys.add(kCTForegroundColorAttributeName);
            auto color = CGColorCreate(rgbColorSpace, components);
            pvals.add(color);
            crrel.add(color);

         }

         if(bStroke)
         {

            double dStroke = ::is_null(ppen) ? 3.0 : ppen->m_dWidth * 100.0 / pfont->m_dFontSize;

            pkeys.add(kCTStrokeWidthAttributeName);
            pvals.add(CFNumberCreate(kCFAllocatorDefault, kCFNumberDoubleType, &dStroke));
            cfrel.add(pvals.last());

            components[0] = colorref_get_r_value(crStroke) / 255.f;
            components[1] = colorref_get_g_value(crStroke) / 255.f;
            components[2] = colorref_get_b_value(crStroke) / 255.f;
            components[3] = colorref_get_a_value(crStroke) / 255.f;

            pkeys.add(kCTStrokeColorAttributeName);
            auto color = CGColorCreate(rgbColorSpace, components);
            pvals.add(color);
            crrel.add(color);

         }

         CGColorSpaceRelease(rgbColorSpace);

      }
      
      ///int iSize = pkeys.get_size();


      CFDictionaryRef attributes = CFDictionaryCreate(
                                   kCFAllocatorDefault,
                                   pkeys.data(),
                                   pvals.data(),
                                   pkeys.size(),
                                   &kCFTypeDictionaryKeyCallBacks,
                                   &kCFTypeDictionaryValueCallBacks);

      CFAttributedStringRef attrString = CFAttributedStringCreate(kCFAllocatorDefault, string, attributes);
      CFRelease(string);
      CFRelease(attributes);
      
      for(index i = 0; i < cfrel.count(); i++)
      {

         CFRelease(cfrel[i]);

      }

      for(index i = 0; i < crrel.count(); i++)
      {

         CGColorRelease(crrel[i]);

      }
      
      CTLineRef line = CTLineCreateWithAttributedString(attrString);

      CFRelease(attrString);
      
      CGFloat width;
      
      CGFloat ascent;
      
      CGFloat descent;
      
      CGFloat leading;
      
      width = CTLineGetTypographicBounds(line, &ascent,  &descent, &leading);
                  
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
         internal_draw_text(emode, x, y + ascent, line, pbrush);
         //internal_draw_text(emode, x, y, line, pbrush);
//         if(pbrush)
//         {
//
//            pbrush->m_point1.y -= ascent;
//            pbrush->m_point2.y -= ascent;
//
//         }

      }

      if(line)
      {

         CFRelease(line);

      }

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

      synchronous_lock synchronouslock(synchronization());
      
      CGContextRef cgcontext = m_cgcontext;

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
 
         //pbrush->m_point1 -= point_i32(x, y);
         //pbrush->m_point2 -= point_i32(x, y);
         //_fill(pbrush, emode >= kCGTextFillClip);
         _fill(pbrush, false);
         //pbrush->m_point1 += point_i32(x, y);
         //pbrush->m_point2 += point_i32(x, y);

      }

   }


} // namespace draw2d_quartz2d


CGContextRef cg_create_bitmap_context(CGSize size)
{

   CGColorSpaceRef space = CGColorSpaceCreateDeviceRGB();

   CGContextRef ctx = CGBitmapContextCreate(nil, size.width, size.height, 8, size.width * 4, space, kCGImageAlphaPremultipliedLast);

   CGColorSpaceRelease(space);

   return ctx;

}



