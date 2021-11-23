#include "framework.h"


__FACTORY_EXPORT void aura_posix_factory(::factory_map * pfactorymap);


__FACTORY_EXPORT void apex_apple_factory(::factory_map * pfactorymap);



__FACTORY_EXPORT void aura_apple_factory(::factory_map * pfactorymap)
{
   
   aura_posix_factory(pfactorymap);
   
   apex_apple_factory(pfactorymap);

   pfactorymap->create_factory < ::aura::posix::node, ::acme::node > ();
   pfactorymap->create_factory < ::aura::posix::shell, ::user::shell > ();

}



