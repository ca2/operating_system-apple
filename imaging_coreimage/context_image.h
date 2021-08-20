#pragma once


namespace coreimage_imaging
{


   class CLASS_DECL_COREIMAGE_IMAGING context_image :
      virtual public ::context_image
   {
   public:


      context_image();
      ~context_image() override;

      ::e_status _load_image(::image * pimageParam, const ::payload & varFile, bool bSync, bool bCreateHelperMaps) override;

      ::e_status _load_image(::image * pimage, __pointer(image_frame_array) & pframea, memory & memory) override;
      ::e_status save_image(memory & memory, const ::image * pimage, const ::save_image * psaveimage = nullptr) override;

//      virtual void * create_os_cursor(oswindow oswindow, const image * pimage, int xHotSpot, int yHotSpot);
//      //virtual HCURSOR load_default_cursor(e_cursor ecursor) override;
//      virtual void set_cursor_image(const image * pimage, int xHotSpot, int yHotSpot) override;

      //virtual ::e_status _load_image(::object * pobject, image_frame_array * pimageframea, const ::memory & memory);
      //virtual int_bool window_set_mouse_cursor(oswindow window, HCURSOR hcursor) override;

   };


} // namespace coreimage_imaging



