#include "framework.h"


extern "C"
void aura_posix_factory_exchange(::factory_map * pfactorymap);


extern "C"
void apex_apple_factory_exchange(::factory_map * pfactorymap);



extern "C"
void aura_apple_factory_exchange(::factory_map * pfactorymap)
{
   
   aura_posix_factory_exchange(pfactorymap);
   
   apex_apple_factory_exchange(pfactorymap);

   pfactorymap->create_factory < ::aura::posix::node, ::acme::node > ();
   pfactorymap->create_factory < ::aura::posix::shell, ::user::shell > ();

}



