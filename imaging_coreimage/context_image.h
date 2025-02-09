#pragma once


#include "aura/graphics/image/context.h"


namespace coreimage_imaging
{


   class CLASS_DECL_COREIMAGE_IMAGING image_context :
      virtual public ::image::image_context
   {
   public:


      image_context();
      ~image_context() override;

      void _load_image(::image::image * pimageParam, const ::payload & varFile, const ::image::load_options & options = ::image::load_options()) override;

      void _load_image(::image::image * pimage, ::pointer < ::image::image_frame_array > & pframea, memory & memory) override;
      void save_image(memory & memory, ::image::image * pimage, const ::image::encoding_options & encodingoptions) override;

//      virtual void * create_os_cursor(oswindow oswindow, const image * pimage, int xHotSpot, int yHotSpot);
//      //virtual HCURSOR load_default_cursor(e_cursor ecursor) override;
//      virtual void set_cursor_image(const image * pimage, int xHotSpot, int yHotSpot) override;

      //virtual ::e_status _load_image(::object * pobject, image_frame_array * pimageframea, const ::memory & memory);
      //virtual int_bool window_set_mouse_cursor(oswindow window, HCURSOR hcursor) override;

   };


} // namespace coreimage_imaging



