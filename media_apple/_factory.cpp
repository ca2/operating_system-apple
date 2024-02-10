#include "framework.h"
#include "media_item.h"

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


__FACTORY_EXPORT void media_apple_factory(::factory::factory * pfactory)
{
   
   pfactory->add_factory_item < ::media_apple::media_item, ::aqua::media_item >();

}



