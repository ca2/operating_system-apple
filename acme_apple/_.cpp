#include "framework.h"


#include <dispatch/dispatch.h>


void ns_main_async(dispatch_block_t block);


void os_post_quit(::particle * pparticleQuit)
{
  
  ns_main_async(^()
  {

     pparticleQuit->run();
     
  });
  
}



