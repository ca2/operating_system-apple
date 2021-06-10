#include "framework.h"


extern "C"
void apex_posix_factory_exchange(::factory_map * pfactorymap);


extern "C"
void acme_apple_factory_exchange(::factory_map * pfactorymap);


extern "C"
void apex_apple_factory_exchange(::factory_map * pfactorymap)
{

   apex_posix_factory_exchange(pfactorymap);
   
   acme_apple_factory_exchange(pfactorymap);


//   pfactorymap->create_factory < ::file::os_watcher, ::file::watcher >();
//   pfactorymap->create_factory < ::file::os_watch, ::file::watch >();

   pfactorymap->create_factory < ::apex::posix::node, ::acme::node > ();

   pfactorymap->create_factory < ::posix::file_context, ::file_context >();
   
   pfactorymap->create_factory < ::ansios::process, ::process::process >();

   
}



