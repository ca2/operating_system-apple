#pragma once


#include "aura/graphics/image/context_image.h"


namespace coreimage_imaging
{


   class CLASS_DECL_COREIMAGE_IMAGING context_image :
      virtual public ::context_image
   {
   public:


      context_image();
      ~context_image() override;

      void _load_image(::image * pimageParam, const ::payload & varFile, const ::image::load_options & options = ::image::load_options()) override;

      void _load_image(::image * pimage, ::pointer < image_frame_array > & pframea, memory & memory) override;
      void save_image(memory & memory, ::image * pimage, const ::save_image * psaveimage = nullptr) override;

//      virtual void * create_os_cursor(oswindow oswindow, const image * pimage, int xHotSpot, int yHotSpot);
//      //virtual HCURSOR load_default_cursor(e_cursor ecursor) override;
//      virtual void set_cursor_image(const image * pimage, int xHotSpot, int yHotSpot) override;

      //virtual ::e_status _load_image(::object * pobject, image_frame_array * pimageframea, const ::memory & memory);
      //virtual int_bool window_set_mouse_cursor(oswindow window, HCURSOR hcursor) override;

   };


} // namespace coreimage_imaging



