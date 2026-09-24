#include "framework.h"
#include "bitmap.h"
#include "graphics.h"
#include "acme/graphics/image/pixmap.h"
#include "aura/graphics/draw2d/domain.h"


namespace draw2d_quartz2d
{
   
   
   bitmap::bitmap()
   {
      
      m_size.cx = 0;
      m_size.cy = 0;
//      m_cgcontextref = nullptr;
      m_iStride = 0;
      
   }
   
   
   bitmap::~bitmap()
   {
      
      destroy();
      
   }
   
   
   void bitmap::CreateBitmap(::draw2d::graphics * pgraphics, const ::i32_size & size, ::u32 nPlanes, ::u32 nBitcount, const void * pdata, int iStride)
   {
      
      if(nPlanes != 1 || nBitcount != 32)
      {
         
         throw ::exception(error_not_implemented);;
         
      }
      
      destroy();
      
      try
      {
      
         m_memoryDraw2dBitmap.set_size(size.cy * iStride);
         
      }
      catch(...)
      {
         
      }
      
      m_pdata = (color32_t *) m_memoryDraw2dBitmap.data();
      
      if(m_pdata == nullptr)
      {
         
         throw exception(error_no_memory);
         
      }
      
      CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
      
      m_cgcontextref = CGBitmapContextCreate(m_pdata, size.cx, size.cy, 8, iStride, colorspace, kCGImageAlphaPremultipliedLast);
      
      CGColorSpaceRelease(colorspace);
      
      if(m_cgcontextref == nullptr)
      {
         
         destroy();
         
         throw exception(::error_resource);
         
      }
      
      m_iStride = (int) CGBitmapContextGetBytesPerRow(m_cgcontextref);
      
      if(m_iStride <= 0)
      {
         
         destroy();
         
         throw ::exception(error_failed);
         
      }
      
      if(pdata != nullptr)
      {
      
         ::memory_copy(m_pdata, pdata, size.cy * iStride);
         
      }
      
      m_size = size;
      
      //m_osdata[0] = m_cgcontextref;
      
   }
   
  
   //void bitmap::create_bitmap(::draw2d::graphics * pgraphics, const ::i32_size & size, void ** //ppdata, int * piStride)
void bitmap::create_bitmap(::draw2d::graphics * pgraphics, const ::i32_size & size)
   {
      
      CreateBitmap(pgraphics, size, 1, 32, nullptr, size.cx * sizeof(color32_t));

//      if(ppdata != nullptr)
//      {
//         
//         *ppdata = m_pdata;
//         
//      }
//      
//      if(piStride)
//      {
//         
//         *piStride = m_iScan;
//         
//      }
//      
   }
   
   
//   void bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, ::u32 flInit, const void *pjBits, ::u32 iUsage)
//   {
//      
//   }

void bitmap::update_bitmap_as_image_render_target(
   ::image::image * pimage,
   ::draw2d::domain * pdraw2ddomain,
   ::draw2d::graphics * pdraw2dgraphics)
{
   
   ::draw2d::bitmap::update_bitmap_as_image_render_target(pimage, pdraw2ddomain, pdraw2dgraphics);
   
   //::draw2d::bitmap::update_bitmap_as_image_render_target(pimage, pdraw2dgraphics);
   
   if(::is_set(pdraw2dgraphics))
   {
      
      ::cast < ::draw2d_quartz2d::graphics> pgraphics = pdraw2dgraphics;
      
      pgraphics->m_cgcontextref = m_cgcontextref;
      
      if(!pgraphics->m_pdraw2ddomain)
      {
         
         pgraphics->m_pdraw2ddomain = pdraw2ddomain;
         
      }
      
   }
   
}
   
   
   ::u32 bitmap::SetBitmapBits(::u32 dwCount, const void * lpBits)
   {
      
      return 0;
      
   }
   
   
   ::u32 bitmap::GetBitmapBits(::u32 dwCount, void * lpBits) const
   {

      return 0;
      
   }
   
   
   void bitmap::read_pixels(
      const ::i32_size & size,
      const ::i32_point & point,
      ::image32_t * pimage32,
      ::i32 iScan)
   {

      if(size.cx <= 0 || size.cy <= 0)
      {

         return;

      }

      if(!pimage32)
      {

         throw ::exception(error_null_pointer);

      }

      if(!m_cgcontextref)
      {

         throw ::exception(error_wrong_state);

      }

      auto iRowBytes = (::memsize) size.cx * sizeof(color32_t);

      // defer_read_pixels clips the rectangle; validate direct callers too.
      if(point.x < 0 || point.y < 0
         || (::i64) point.x + size.cx > m_size.cx
         || (::i64) point.y + size.cy > m_size.cy
         || iScan < iRowBytes)
      {

         throw ::exception(error_bad_argument);

      }

      CGContextFlush(m_cgcontextref);

      auto pdata = (const ::u8 *) CGBitmapContextGetData(m_cgcontextref);
      auto iSourceStride = (::memsize) CGBitmapContextGetBytesPerRow(m_cgcontextref);

      if(!pdata || iSourceStride < ((::memsize) point.x + size.cx) * sizeof(color32_t)
         || (::i64) point.x + size.cx > (::i64) CGBitmapContextGetWidth(m_cgcontextref)
         || (::i64) point.y + size.cy > (::i64) CGBitmapContextGetHeight(m_cgcontextref))
      {

         throw ::exception(error_wrong_state);

      }

      auto psource = pdata + (::memsize) point.y * iSourceStride
         + (::memsize) point.x * sizeof(color32_t);
      auto ptarget = (::u8 *) pimage32;

      // Preserve Quartz's native premultiplied RGBA pixels and row order.
      for(::i32 y = 0; y < size.cy; y++)
      {

         if(ptarget != psource)
         {

            ::memory_copy(ptarget, psource, iRowBytes);

         }

         psource += iSourceStride;
         ptarget += iScan;

      }

   }


   void bitmap::write_pixels(
      const ::i32_size & size,
      const ::i32_point & point,
      const ::image32_t * pimage32,
      ::i32 iScan,
      bool bTopDown)
   {

      if(size.cx <= 0 || size.cy <= 0)
      {

         return;

      }

      if(!pimage32)
      {

         throw ::exception(error_null_pointer);

      }

      if(!m_cgcontextref)
      {

         throw ::exception(error_wrong_state);

      }

      auto iRowBytes = (::memsize) size.cx * sizeof(color32_t);

      if(point.x < 0 || point.y < 0
         || (::i64) point.x + size.cx > m_size.cx
         || (::i64) point.y + size.cy > m_size.cy
         || iScan < iRowBytes)
      {

         throw ::exception(error_bad_argument);

      }

      // Finish drawing before modifying the context's backing storage.
      CGContextFlush(m_cgcontextref);

      auto pdata = (::u8 *) CGBitmapContextGetData(m_cgcontextref);
      auto iTargetStride = (::memsize) CGBitmapContextGetBytesPerRow(m_cgcontextref);

      if(!pdata || iTargetStride < ((::memsize) point.x + size.cx) * sizeof(color32_t)
         || (::i64) point.x + size.cx > (::i64) CGBitmapContextGetWidth(m_cgcontextref)
         || (::i64) point.y + size.cy > (::i64) CGBitmapContextGetHeight(m_cgcontextref))
      {

         throw ::exception(error_wrong_state);

      }

      // Copy native premultiplied RGBA pixels without touching row padding.
      for(::i32 y = 0; y < size.cy; y++)
      {

         auto ySource = bTopDown ? y : size.cy - 1 - y;
         auto psource = (const ::u8 *) pimage32 + (::memsize) ySource * iScan;
         auto ptarget = pdata + ((::memsize) point.y + y) * iTargetStride
            + (::memsize) point.x * sizeof(color32_t);

         if(ptarget != psource)
         {

            ::memory_copy(ptarget, psource, iRowBytes);

         }

      }

   }


   void bitmap::create_bitmap(::draw2d::graphics * pgraphics, const ::i32_size & size, ::pixmap * ppixmap)
   {

      // The base implementation only changes CPU storage and metadata. Quartz
      // must also replace the native context so its dimensions and stride agree.
      ::memory memoryPixels;
      ::i32 iSourceStride = 0;
      bool bTopDown = true;

      if(ppixmap && ppixmap->m_iScan > 0
         && (::i64) ppixmap->m_iScan >= (::i64) size.cx * sizeof(color32_t)
         && ppixmap->m_memoryPixmap.size() >= (::memsize) ppixmap->m_iScan * size.cy)
      {

         iSourceStride = ppixmap->m_iScan;
         bTopDown = ppixmap->m_bTopLeft;
         // Snapshot before replacing storage that the pixmap may reference.
         memoryPixels.set_size((::memsize) iSourceStride * size.cy);
         ::memory_copy(memoryPixels.data(), ppixmap->m_memoryPixmap.data(), memoryPixels.size());

      }

      create_bitmap(pgraphics, size);

      if(iSourceStride > 0)
      {

         write_pixels(size, {}, (const ::image32_t *) memoryPixels.data(), iSourceStride, bTopDown);

      }

   }


   void bitmap::set_size(const ::i32_size & size, bool bPreserve)
   {

      if(m_cgcontextref && size == m_size)
      {

         return;

      }

      if(size.cx <= 0 || size.cy <= 0)
      {

         destroy();
         return;

      }

      ::memory memoryPixels;
      ::i32_size sizePreserved;
      ::i32 iPreservedStride = 0;

      if(bPreserve && m_cgcontextref)
      {

         sizePreserved.cx = minimum(size.cx, (int) CGBitmapContextGetWidth(m_cgcontextref));
         sizePreserved.cy = minimum(size.cy, (int) CGBitmapContextGetHeight(m_cgcontextref));
         iPreservedStride = sizePreserved.cx * sizeof(color32_t);
         memoryPixels.set_size((::memsize) iPreservedStride * sizePreserved.cy);
         read_pixels(sizePreserved, {}, (::image32_t *) memoryPixels.data(), iPreservedStride);

      }

      create_bitmap(nullptr, size);

      if(iPreservedStride > 0)
      {

         write_pixels(sizePreserved, {}, (const ::image32_t *) memoryPixels.data(), iPreservedStride, true);

      }

   }


   void bitmap::LoadBitmap(const char * lpszResourceName)
   {
      
   }
   
   
   i32_size bitmap::SetBitmapDimension(int nWidth, int nHeight)
   {
      
      return ::i32_size(0, 0);
      
   }
   
   
   i32_size bitmap::size() const
   {
      
//      if(m_osdata[0] == nullptr)
//      {
//
//         return ::i32_size(0, 0);
//
//      }
      
      return m_size;
      
   }
   
   
   void bitmap::LoadBitmap(::u32 nIDResource)
   {
      
   }
   
   
   void bitmap::LoadOEMBitmap(::u32 nIDBitmap)
   {
      
   }
   
   
//   void bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int cx, int cy)
//   {
//      
//      CreateBitmap(pgraphics, ::i32_size(cx, cy), 1, 32, nullptr, cx * sizeof(color32_t));
//      
//   }
//   
   
//   void bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight)
//   {
//      
//      CreateCompatibleBitmap(pgraphics, nWidth, nHeight);
//      
//   }
//   

//   void bitmap::dump(dump_context & dumpcontext) const
//   {
//
//      ::draw2d::object::dump(dumpcontext);
//      
//      if(m_osdata[0] == nullptr)
//      {
//         
//         return;
//         
//      }
//       
//      //dumpcontext << "bm.bmType = " << bm.bmType;
//      dumpcontext << "\nbm.bmHeight = " << m_size.cy;
//      dumpcontext << "\nbm.bmWidth = " << m_size.cx;
//      dumpcontext << "\nbm.bmWidthBytes = " << m_iScan;
//      dumpcontext << "\nbm.bmPlanes = " << 1;
//      dumpcontext << "\nbm.bmBitsPixel = " << 32;
//      dumpcontext << "\n";
//      
//   }
   

   void bitmap::_attach(CGContextRef cgcontextref)
   {
      
      destroy();
      
      m_memoryDraw2dBitmap.set_size(0);
      
      m_cgcontextref       = (CGContextRef) cgcontextref;
      
      m_size.cx   = (int) CGBitmapContextGetWidth(m_cgcontextref);
      
      m_size.cy   = (int) CGBitmapContextGetHeight(m_cgcontextref);
      
      m_iStride     = (int) CGBitmapContextGetBytesPerRow(m_cgcontextref);
      
      m_pdata     = (color32_t *) CGBitmapContextGetData(m_cgcontextref);
      
   }
   

//   void bitmap::destroy()
//   {
//      
//      destroy_os_data();
//      
//      ::draw2d::bitmap::destroy();
//      
//   }


   void bitmap::destroy()
   {
      
      m_cgcontextref.release();
      
      m_size.cx = 0;
      
      m_size.cy = 0;
      
      m_iStride = 0;
      
   }


   CGContextRef bitmap::_detach()
   {
      
      return m_cgcontextref.detach();
      
   }


   CGContextRef bitmap::_cg_context_ref()
   {
      
      if(!m_cgcontextref)
      {
         
         auto size = m_size;
         
         CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
         
         m_cgcontextref = CGBitmapContextCreate(m_pdata, size.cx, size.cy, 8, m_iStride, colorspace, kCGImageAlphaPremultipliedLast);
         
         CGColorSpaceRelease(colorspace);
         
         if(not m_cgcontextref)
         {
            
            destroy();
            
            throw exception(::error_resource);
            
         }
         
         m_iStride = (int) CGBitmapContextGetBytesPerRow(m_cgcontextref);
         
      }
   
      return m_cgcontextref;
      
   }
   

} // namespace draw2d_quartz2d
