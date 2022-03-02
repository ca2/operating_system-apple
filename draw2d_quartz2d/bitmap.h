#pragma once


namespace draw2d_quartz2d
{

   
   class CLASS_DECL_DRAW2D_QUARTZ2D bitmap : 
      virtual public ::draw2d_quartz2d::object,
      virtual public ::draw2d::bitmap
   {
   public:
      

      memory                        m_memory;
      ::size_i32                        m_size;
      CGContextRef                  m_pdc;
      i32                           m_iScan;
      color32_t *                    m_pdata;
      
      
      bitmap();
      ~bitmap() override;
      
      
      //void * get_os_data() const override;
      
      
      void LoadBitmap(const char * lpszResourceName);
      void LoadBitmap(::u32 nIDResource);
      void LoadOEMBitmap(::u32 nIDBitmap); // for OBM_/OCR_/OIC_
//#ifndef ___NO_AFXCMN_SUPPORT
//      // xxx      bool LoadMappedBitmap(::u32 nIDBitmap, ::u32 nFlags = 0, LPCOLORMAP lpColorMap = nullptr, i32 nMapSize = 0);
//#endif
      void CreateBitmap(::draw2d::graphics * pgraphics, const ::size_i32 & size, ::u32 nPlanes, ::u32 nBitcount, const void * lpBits, i32 iStride) override;
//      void CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap) override;
      void CreateCompatibleBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight) override;
      void CreateDiscardableBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight) override;
      void create_bitmap(::draw2d::graphics * pgraphics, const ::size_i32 & size, void **ppvBits, int * piStride) override;
      void CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, ::u32 flInit, const void *pjBits, ::u32 iUsage) override;
      
      //i32 GetBitmap(BITMAP* pBitMap);
      
      ::u32 SetBitmapBits(::u32 dwCount, const void * lpBits) override;
      ::u32 GetBitmapBits(::u32 dwCount, void * lpBits) const override;
      ::size_i32 SetBitmapDimension(i32 nWidth, i32 nHeight);
      ::size_i32 GetBitmapDimension() const override;
      
      void dump(dump_context & dumpcontext) const override;
      
      virtual void Attach(void * posdata);
      
      void destroy() override;
      void destroy_os_data() override;

      
   };

   
} // namespace draw2d_quartz2d




