#include "framework.h"


__FACTORY_EXPORT void apex_posix_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void acme_apple_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void apex_apple_factory(::factory::factory * pfactory)
{

   apex_posix_factory(pfactory);
   
   acme_apple_factory(pfactory);


//   pfactory->add_factory_item < ::file::os_watcher, ::file::watcher >();
//   pfactory->add_factory_item < ::file::os_watch, ::file::watch >();

   pfactory->add_factory_item < ::apex_posix::node, ::acme::node > ();

   pfactory->add_factory_item < ::apex_apple::file_context, ::file_context >();
   
   pfactory->add_factory_item < ::apex_apple::process, ::operating_system::process >();
   
}



