#include "framework.h"


__FACTORY_EXPORT void acme_posix_factory(::factory_map * pfactorymap);


__FACTORY_EXPORT void acme_apple_factory(::factory_map * pfactorymap)
{
   
   acme_posix_factory(pfactorymap);

   pfactorymap->create_factory < ::acme::apple::node, ::acme::node > ();
   //create_factory < ::posix::file_memory_map, ::file::memory_map >();

   //create_factory < ::posix::pipe , ::process::pipe          >();

}



