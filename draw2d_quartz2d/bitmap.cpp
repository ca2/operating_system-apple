#include "framework.h"
#include "bitmap.h"


namespace draw2d_quartz2d
{
   
   
   bitmap::bitmap()
   {
      
      m_size.cx = 0;
      m_size.cy = 0;
      m_cgcontext = nullptr;
      m_iScan = 0;
      
   }
   
   
   bitmap::~bitmap()
   {
      
      destroy();
      
   }
   
   
   void bitmap::CreateBitmap(::draw2d::graphics * pgraphics, const ::int_size & size, unsigned int nPlanes, unsigned int nBitcount, const void * pdata, int iStride)
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
      
      m_pdata = (color32_t *) m_memory.data();
      
      if(m_pdata == nullptr)
      {
         
         throw exception(error_no_memory);
         
      }
      
      CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
      
      m_cgcontext = CGBitmapContextCreate(m_pdata, size.cx, size.cy, 8, iStride, colorspace, kCGImageAlphaPremultipliedLast);
      
      CGColorSpaceRelease(colorspace);
      
      if(m_cgcontext == nullptr)
      {
         
         destroy();
         
         throw exception(::error_resource);
         
      }
      
      m_iScan = (int) CGBitmapContextGetBytesPerRow(m_cgcontext);
      
      if(m_iScan <= 0)
      {
         
         destroy();
         
         throw ::exception(error_failed);
         
      }
      
      if(pdata != nullptr)
      {
      
         ::memory_copy(m_pdata, pdata, size.cy * iStride);
         
      }
      
      m_size = size;
      
      m_osdata[0] = m_cgcontext;
      
   }
   
  
   void bitmap::create_bitmap(::draw2d::graphics * pgraphics, const ::int_size & size, void ** ppdata, int * piStride)
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
   
   
   void bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, unsigned int flInit, const void *pjBits, unsigned int iUsage)
   {
      
   }
   
   
   unsigned int bitmap::SetBitmapBits(unsigned int dwCount, const void * lpBits)
   {
      
      return 0;
      
   }
   
   
   unsigned int bitmap::GetBitmapBits(unsigned int dwCount, void * lpBits) const
   {

      return 0;
      
   }
   
   
   void bitmap::LoadBitmap(const char * lpszResourceName)
   {
      
   }
   
   
   int_size bitmap::SetBitmapDimension(int nWidth, int nHeight)
   {
      
      return ::int_size(0, 0);
      
   }
   
   
   int_size bitmap::GetBitmapDimension() const
   {
      
      if(m_osdata[0] == nullptr)
      {

         return ::int_size(0, 0);

      }
      
      return m_size;
      
   }
   
   
   void bitmap::LoadBitmap(unsigned int nIDResource)
   {
      
   }
   
   
   void bitmap::LoadOEMBitmap(unsigned int nIDBitmap)
   {
      
   }
   
   
   void bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int cx, int cy)
   {
      
      CreateBitmap(pgraphics, ::int_size(cx, cy), 1, 32, nullptr, cx * sizeof(color32_t));
      
   }
   
   
   void bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight)
   {
      
      CreateCompatibleBitmap(pgraphics, nWidth, nHeight);
      
   }
   

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
   

   void bitmap::Attach(void * pbitmapcontext)
   {
      
      destroy();
      
      m_memory.set_size(0);
      
      m_cgcontext       = (CGContextRef) pbitmapcontext;
      
      m_size.cx   = (int) CGBitmapContextGetWidth(m_cgcontext);
      
      m_size.cy   = (int) CGBitmapContextGetHeight(m_cgcontext);
      
      m_iScan     = (int) CGBitmapContextGetBytesPerRow(m_cgcontext);
      
      m_pdata     = (color32_t *) CGBitmapContextGetData(m_cgcontext);
      
   }
   

   void bitmap::destroy()
   {
      
      destroy_os_data();
      
      ::draw2d::bitmap::destroy();
      
   }


   void bitmap::destroy_os_data()
   {
      
      if(m_cgcontext != nullptr)
      {
         
         CGContextRelease(m_cgcontext);
         
         m_cgcontext = nullptr;
         
      }
      
      m_size.cx = 0;
      
      m_size.cy = 0;
      
      m_iScan = 0;
      
   }

   
} // namespace draw2d_quartz2d



