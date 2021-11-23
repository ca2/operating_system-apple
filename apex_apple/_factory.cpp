#include "framework.h"


__FACTORY_EXPORT void apex_posix_factory(::factory_map * pfactorymap);


__FACTORY_EXPORT void acme_apple_factory(::factory_map * pfactorymap);


__FACTORY_EXPORT void apex_apple_factory(::factory_map * pfactorymap)
{

   apex_posix_factory(pfactorymap);
   
   acme_apple_factory(pfactorymap);


//   pfactorymap->create_factory < ::file::os_watcher, ::file::watcher >();
//   pfactorymap->create_factory < ::file::os_watch, ::file::watch >();

   pfactorymap->create_factory < ::apex::posix::node, ::acme::node > ();

   pfactorymap->create_factory < ::posix::file_context, ::file_context >();
   
   pfactorymap->create_factory < ::ansios::process, ::operating_system::process >();
   
}



