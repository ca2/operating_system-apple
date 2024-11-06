#include "framework.h"
#include "node.h"


__FACTORY_EXPORT void aura_darwin_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void apex_apple_factory(::factory::factory * pfactory);



__FACTORY_EXPORT void aura_apple_factory(::factory::factory * pfactory)
{
   
   aura_darwin_factory(pfactory);
   
   apex_apple_factory(pfactory);

   pfactory->add_factory_item < ::aura_apple::node, ::platform::node > ();
   //pfactory->add_factory_item < ::aura_posix::shell, ::user::shell > ();

}



