#include "framework.h"
#include "file_context.h"
#include "node.h"
//#include "stdio_file.h"
#include "exception_translator.h"


DECLARE_FACTORY(acme_darwin);


IMPLEMENT_FACTORY(acme_apple)
{
   
   acme_darwin_factory(pfactory);

   pfactory->add_factory_item < ::acme_apple::node, ::acme::node > ();
   //create_factory < ::posix::file_memory_map, ::file::memory_map >();
   pfactory->add_factory_item < ::acme_apple::file_context, ::file_context >();
   

   //create_factory < ::posix::pipe , ::process::pipe          >();
   
   //pfactory->add_factory_item < ::acme_apple::stdio_file , ::file::text_file          >();
   pfactory->add_factory_item < ::acme_apple::exception_translator , ::exception_translator          >();

}



