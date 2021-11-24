#include "framework.h"


__FACTORY_EXPORT void aura_posix_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void apex_apple_factory(::factory::factory * pfactory);



__FACTORY_EXPORT void aura_apple_factory(::factory::factory * pfactory)
{
   
   aura_posix_factory(pfactory);
   
   apex_apple_factory(pfactory);

   pfactory->add_factory_item < ::aura::posix::node, ::acme::node > ();
   pfactory->add_factory_item < ::aura::posix::shell, ::user::shell > ();

}



