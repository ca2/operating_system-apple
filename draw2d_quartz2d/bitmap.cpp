#include "framework.h"
#include "bitmap.h"
#include "graphics.h"
#include "acme/graphics/image/pixmap.h"
#include "aura/graphics/image/image.h"
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

         throw ::exception(error_not_implemented);

      }

      if(size.cx <= 0 || size.cy <= 0 || iStride <= 0
         || (::i64) iStride < (::i64) size.cx * sizeof(color32_t))
      {

         throw ::exception(error_bad_argument);

      }

      // Tie the pixels to the context lifetime. Graphics may retain an older
      // context after the bitmap is resized, so it cannot borrow resizable memory.
      ::cfref<CGColorSpaceRef> colorspace = CGColorSpaceCreateDeviceRGB();
      ::cfref<CGContextRef> contextNew = CGBitmapContextCreate(nullptr,
         size.cx, size.cy, 8, iStride, colorspace, kCGImageAlphaPremultipliedLast);

      if(contextNew == nullptr)
      {

         throw ::exception(error_resource);

      }

      auto pdataNew = (color32_t *) CGBitmapContextGetData(contextNew);
      auto iStrideNew = (int) CGBitmapContextGetBytesPerRow(contextNew);

      if(!pdataNew || iStrideNew < iStride)
      {

         throw ::exception(error_failed);

      }

      if(pdata)
      {

         for(int y = 0; y < size.cy; y++)
         {

            ::memory_copy((::u8 *) pdataNew + (::memsize) y * iStrideNew,
               (const ::u8 *) pdata + (::memsize) y * iStride, iStride);

         }

      }
      else
      {

         ::memory_set(pdataNew, 0, (::memsize) iStrideNew * size.cy);

      }

      // Commit only after allocation and copying succeed (pdata may alias us).
      m_cgcontextref = contextNew;
      m_pdata = pdataNew;
      m_iStride = iStrideNew;
      m_size = size;

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

   // Resizing can replace the context even when no graphics argument was
   // supplied. The image may already have graphics cached for the old context.
   ::cast<::draw2d_quartz2d::graphics> pgraphicsOwned = pimage->m_pgraphicsOwned;
   if(pgraphicsOwned)
   {

      pgraphicsOwned->create_bitmap_graphics(this, pdraw2ddomain);

   }
   
   if(::is_set(pdraw2dgraphics))
   {
      
      ::cast < ::draw2d_quartz2d::graphics> pgraphics = pdraw2dgraphics;
      
      pgraphics->create_bitmap_graphics(this, pdraw2ddomain);
      
      if(::is_null(pgraphics->draw2d_domain()))
      {
         
         pgraphics->set_draw2d_domain(pdraw2ddomain);
         
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

      auto psource = (::image32_t *)(pdata + (::memsize) point.y * iSourceStride
         + (::memsize) point.x * sizeof(color32_t));
      auto ptarget = (::image32_t *)((::u8 *) pimage32);
      
      ptarget->y_swap_copy(size.cx, size.cy, iScan, psource, iSourceStride);

//      // Preserve Quartz's native premultiplied RGBA pixels and row order.
//      for(::i32 y = 0; y < size.cy; y++)
//      {
//
//         if(ptarget != psource)
//         {
//
//            ::memory_copy(ptarget, psource, iRowBytes);
//
//         }
//
//         psource += iSourceStride;
//         ptarget += iScan;
//
//      }

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
      
      if(!bTopDown)
      {
         
         information("!bTopDown");
         
      }

      // Copy native premultiplied RGBA pixels without touching row padding.
      for(::i32 y = 0; y < size.cy; y++)
      {

         auto ySource = bTopDown ? size.cy - 1 - y : y;
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


   void bitmap::preserve_image(const ::i32_size & size, ::image::image * pimage)
   {

      if(!pimage || size.is_empty() || pimage->m_pdraw2dbitmap != this)
      {

         throw ::exception(error_bad_argument);

      }

      if(pimage->has_active_destination_graphics_lease()
         || pimage->m_pimagepixmaplease
         || (pimage->m_ppixmapOwned && pimage->m_ppixmapOwned->m_interlockedcountMap > 0))
      {

         throw ::exception(error_wrong_state,
            "Cannot preserve an image while it is mapped or has active destination graphics");

      }

      if(m_cgcontextref == nullptr || !CGBitmapContextGetData(m_cgcontextref))
      {

         throw ::exception(error_wrong_state, "Quartz bitmap has no storage to preserve");

      }

      auto sizeRawNew = pimage->raw_size().maximum(pimage->m_point + size);

      if(sizeRawNew == pimage->raw_size())
      {

         pimage->m_size = size;
         return;

      }

      // Prepare the replacement before releasing the original storage.
      // Let CoreGraphics own the allocation, including its row alignment.
      ::cfref<CGContextRef> contextNew;
      contextNew = CGBitmapContextCreate(nullptr, sizeRawNew.cx, sizeRawNew.cy,
         CGBitmapContextGetBitsPerComponent(m_cgcontextref), 0,
         CGBitmapContextGetColorSpace(m_cgcontextref),
         CGBitmapContextGetBitmapInfo(m_cgcontextref));

      if(contextNew == nullptr)
      {

         throw ::exception(error_resource, "Could not allocate the preserved Quartz bitmap");

      }

      auto pdataNew = (color32_t *) CGBitmapContextGetData(contextNew);
      auto iStrideNew = (::i32) CGBitmapContextGetBytesPerRow(contextNew);
      ::memory_set(pdataNew, 0, (::memsize) iStrideNew * sizeRawNew.cy);

      // Mapping may have made the CPU pixels newer than the native bitmap.
      if(pimage->m_bWasMappedAfterLastGraphicsAcquisition && pimage->m_ppixmapOwned)
      {

         defer_write_pixels(*pimage->m_ppixmapOwned);

      }

      read_pixels(m_size, {}, (::image32_t *) pdataNew, iStrideNew);

      m_cgcontextref = contextNew;
      m_pdata = pdataNew;
      m_size = sizeRawNew;
      m_iStride = iStrideNew;

      // Owned graphics must stop referring to the context that was replaced.
      ::cast<::draw2d_quartz2d::graphics> pgraphics = pimage->m_pgraphicsOwned;
      if(pgraphics)
      {

         pgraphics->create_bitmap_graphics(this, pimage->draw2d_domain());

      }

      pimage->m_size = size;
      pimage->m_sizeRaw = sizeRawNew;
      pimage->m_iScan = m_iStride;
      pimage->m_ppixmapOwned.release();
      pimage->m_bGraphicsWasAcquiredAfterLastMap = true;
      pimage->m_bWasMappedAfterLastGraphicsAcquisition = false;

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
         
         auto colorspace = ::as_cfref(CGColorSpaceCreateDeviceRGB());
         
         m_cgcontextref = CGBitmapContextCreate(m_pdata, size.cx, size.cy, 8, m_iStride, colorspace, kCGImageAlphaPremultipliedLast);
         
         //CGColorSpaceRelease(colorspace);
         
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
