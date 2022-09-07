#include "framework.h"
#include "bitmap.h"


namespace draw2d_quartz2d
{
   
   
   bitmap::bitmap()
   {
      
      m_size.cx = 0;
      m_size.cy = 0;
      m_pdc = nullptr;
      m_iScan = 0;
      
   }
   
   
   bitmap::~bitmap()
   {
      
      destroy();
      
   }
   
   
   void bitmap::CreateBitmap(::draw2d::graphics * pgraphics, const ::size_i32 & size, ::u32 nPlanes, ::u32 nBitcount, const void * pdata, i32 iStride)
   {
      
      if(nPlanes != 1 || nBitcount != 32)
      {
         
         throw ::exception(error_not_implemented);;
         
      }
      
      destroy();
      
      try
      {
      
         m_memory.set_size(size.cy * iStride);
         
      }
      catch(...)
      {
         
      }
      
      m_pdata = (color32_t *) m_memory.get_data();
      
      if(m_pdata == nullptr)
      {
         
         throw exception(error_no_memory);
         
      }
      
      CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
      
      m_pdc = CGBitmapContextCreate(m_pdata, size.cx, size.cy, 8, iStride, colorspace, kCGImageAlphaPremultipliedLast);
      
      CGColorSpaceRelease(colorspace);
      
      if(m_pdc == nullptr)
      {
         
         destroy();
         
         throw exception(::error_resource);
         
      }
      
      m_iScan = (int) CGBitmapContextGetBytesPerRow(m_pdc);
      
      if(m_iScan <= 0)
      {
         
         destroy();
         
         throw ::exception(error_failed);
         
      }
      
      if(pdata != nullptr)
      {
      
         ::memcpy_dup(m_pdata, pdata, size.cy * iStride);
         
      }
      
      m_size = size;
      
      m_osdata[0] = m_pdc;
      
   }
   
  
   void bitmap::create_bitmap(::draw2d::graphics * pgraphics, const ::size_i32 & size, void ** ppdata, int * piStride)
   {
      
      CreateBitmap(pgraphics, size, 1, 32, nullptr, size.cx * sizeof(color32_t));

      if(ppdata != nullptr)
      {
         
         *ppdata = m_pdata;
         
      }
      
      if(piStride)
      {
         
         *piStride = m_iScan;
         
      }
      
   }
   
   
   void bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, ::u32 flInit, const void *pjBits, ::u32 iUsage)
   {
      
   }
   
   
   ::u32 bitmap::SetBitmapBits(::u32 dwCount, const void * lpBits)
   {
      
      return 0;
      
   }
   
   
   ::u32 bitmap::GetBitmapBits(::u32 dwCount, void * lpBits) const
   {

      return 0;
      
   }
   
   
   void bitmap::LoadBitmap(const char * lpszResourceName)
   {
      
   }
   
   
   size_i32 bitmap::SetBitmapDimension(i32 nWidth, i32 nHeight)
   {
      
      return ::size_i32(0, 0);
      
   }
   
   
   size_i32 bitmap::GetBitmapDimension() const
   {
      
      if(m_osdata[0] == nullptr)
      {

         return ::size_i32(0, 0);

      }
      
      return m_size;
      
   }
   
   
   void bitmap::LoadBitmap(::u32 nIDResource)
   {
      
   }
   
   
   void bitmap::LoadOEMBitmap(::u32 nIDBitmap)
   {
      
   }
   
   
   void bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics, i32 cx, i32 cy)
   {
      
      CreateBitmap(pgraphics, ::size_i32(cx, cy), 1, 32, nullptr, cx * sizeof(color32_t));
      
   }
   
   
   void bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight)
   {
      
      CreateCompatibleBitmap(pgraphics, nWidth, nHeight);
      
   }
   

   void bitmap::dump(dump_context & dumpcontext) const
   {

      ::draw2d::object::dump(dumpcontext);
      
      if(m_osdata[0] == nullptr)
      {
         
         return;
         
      }
       
      //dumpcontext << "bm.bmType = " << bm.bmType;
      dumpcontext << "\nbm.bmHeight = " << m_size.cy;
      dumpcontext << "\nbm.bmWidth = " << m_size.cx;
      dumpcontext << "\nbm.bmWidthBytes = " << m_iScan;
      dumpcontext << "\nbm.bmPlanes = " << 1;
      dumpcontext << "\nbm.bmBitsPixel = " << 32;
      dumpcontext << "\n";
      
   }
   

   void bitmap::Attach(void * pbitmapcontext)
   {
      
      destroy();
      
      m_memory.set_size(0);
      
      m_pdc       = (CGContextRef) pbitmapcontext;
      
      m_size.cx   = (int) CGBitmapContextGetWidth(m_pdc);
      
      m_size.cy   = (int) CGBitmapContextGetHeight(m_pdc);
      
      m_iScan     = (int) CGBitmapContextGetBytesPerRow(m_pdc);
      
      m_pdata     = (color32_t *) CGBitmapContextGetData(m_pdc);
      
   }
   

   void bitmap::destroy()
   {
      
      destroy_os_data();
      
      ::draw2d::bitmap::destroy();
      
   }


   void bitmap::destroy_os_data()
   {
      
      if(m_pdc != nullptr)
      {
         
         CGContextRelease(m_pdc);
         
         m_pdc = nullptr;
         
      }
      
      m_size.cx = 0;
      
      m_size.cy = 0;
      
      m_iScan = 0;
      
   }

   
} // namespace draw2d_quartz2d



