#pragma once


#include "object.h"
#include "aura/graphics/draw2d/bitmap.h"
#include "acme/prototype/prototype/memory.h"


namespace draw2d_quartz2d
{

   
   class CLASS_DECL_DRAW2D_QUARTZ2D bitmap : 
      virtual public ::draw2d_quartz2d::object,
      virtual public ::draw2d::bitmap
   {
   public:
      

      memory                        m_memory;
      ::int_size                    m_size;
      CGContextRef                  m_cgcontext;
      int                           m_iScan;
      color32_t *                   m_pdata;
      
      
      bitmap();
      ~bitmap() override;
      
      
      //void * get_os_data() const override;
      
      
      void LoadBitmap(const char * lpszResourceName);
      void LoadBitmap(unsigned int nIDResource);
      void LoadOEMBitmap(unsigned int nIDBitmap); // for OBM_/OCR_/OIC_
//#ifndef ___NO_AFXCMN_SUPPORT
//      // xxx      bool LoadMappedBitmap(unsigned int nIDBitmap, unsigned int nFlags = 0, LPCOLORMAP lpColorMap = nullptr, int nMapSize = 0);
//#endif
      void CreateBitmap(::draw2d::graphics * pgraphics, const ::int_size & size, unsigned int nPlanes, unsigned int nBitcount, const void * lpBits, int iStride) override;
//      void CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap) override;
      void CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight) override;
      void CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight) override;
      void create_bitmap(::draw2d::graphics * pgraphics, const ::int_size & size, void **ppvBits, int * piStride) override;
      void CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, unsigned int flInit, const void *pjBits, unsigned int iUsage) override;
      
      //int GetBitmap(BITMAP* pBitMap);
      
      unsigned int SetBitmapBits(unsigned int dwCount, const void * lpBits) override;
      unsigned int GetBitmapBits(unsigned int dwCount, void * lpBits) const override;
      ::int_size SetBitmapDimension(int nWidth, int nHeight);
      ::int_size GetBitmapDimension() const override;
      
      //void dump(dump_context & dumpcontext) const override;
      
      virtual void Attach(void * posdata);
      
      void destroy() override;
      void destroy_os_data() override;

      
   };

   
} // namespace draw2d_quartz2d




