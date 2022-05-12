#include "framework.h"





void os_post_quit(::element * pelementQuit)
{
   
   ns_main_async(^()
   {

      pelementQuit->run();
      
   });
   
}



