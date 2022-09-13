#include "framework.h"
#include "node.h"
#include "stdio_file.h"


__FACTORY_EXPORT void acme_posix_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void acme_apple_factory(::factory::factory * pfactory)
{
   
   acme_posix_factory(pfactory);

   pfactory->add_factory_item < ::acme_apple::node, ::acme::node > ();
   //create_factory < ::posix::file_memory_map, ::file::memory_map >();

   //create_factory < ::posix::pipe , ::process::pipe          >();
   
   pfactory->add_factory_item < ::acme_apple::stdio_file , ::file::text_file          >();

}



