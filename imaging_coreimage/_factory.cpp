#include "framework.h"


//namespace coreimage_imaging
//{
//
//
//#define new ACME_NEW
//
//
//   factory_exchange::factory_exchange()
//   {
//
//      create_factory < imaging, ::imaging >();
//
//   }
//
//
//   factory_exchange::~factory_exchange()
//   {
//
//   }
//
//
//} // namespace coreimage_imaging


__FACTORY_EXPORT void imaging_coreimage_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::coreimage_imaging::image_context, ::image::image_context >();
   //coreimage_imaging::factory_exchange factoryexchange;

}



