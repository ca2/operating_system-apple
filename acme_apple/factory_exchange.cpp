#include "framework.h"


extern "C"
void acme_posix_factory_exchange(::factory_map * pfactorymap);


extern "C"
void acme_apple_factory_exchange(::factory_map * pfactorymap)
{
   
   acme_posix_factory_exchange(pfactorymap);

   pfactorymap->create_factory < ::acme::apple::node, ::acme::node > ();
   //create_factory < ::posix::file_memory_map, ::file::memory_map >();

   //create_factory < ::posix::pipe , ::process::pipe          >();

}



