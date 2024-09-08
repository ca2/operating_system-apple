#pragma once


#include "aura/graphics/image/image.h"


namespace draw2d_quartz2d
{


   class CLASS_DECL_DRAW2D_QUARTZ2D image :
      virtual public ::image::image
   {
   public:


//      ::draw2d::bitmap_pointer        m_pbitmap;
//      ::draw2d::graphics_pointer      m_spgraphics;


      image();
      ~image() override;

      void map(bool bApplyAlphaTransform = true) const override;
      void _unmap() override;

      
      //void detach(::image * pimage) override;
      

      ::draw2d::graphics * _get_graphics() const override;
      ::draw2d::bitmap_pointer get_bitmap() const override;
      ::draw2d::bitmap_pointer detach_bitmap() override;


      //virtual const color32_t * get_data() const override;

      void stretch_image(::image::image * pimage) override;

      void dc_select(bool bSelect = true) override;

      void create(const ::size_i32 & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, int iGoodStride = -1, bool bPreserve = false) override;
      //::e_status create(i32 iWidth, i32 iHeight, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, bool bPreserve = false) override;
      void create(::draw2d::graphics * pgraphics) override;
      void destroy() override;



//      bool from(const ::point_i32 & pointDest, ::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & sz) override;
//      bool to(::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & size, const ::point_i32 & pointSrc) override;

      void _draw_raw(const ::rectangle_i32 & rectDst, ::image::image * pimageSrc, const ::point_i32 & pointSrc) override;
      
      void SetIconMask(::image::icon * picon, i32 cx, i32 cy) override;

      void set_mapped() override;

      void blend(const ::point_i32 & pointDst, ::image::image * pimplSrc, const ::point_i32 & pointSrc, const ::size_i32 & size, ::u8 bA) override;


   };
      

} // namespace draw2d_quartz2d



