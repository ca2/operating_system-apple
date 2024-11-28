#include "framework.h"
#include "display.h"
#include "window.h"
#include "windowing.h"
#include "host_interaction.h"


IMPLEMENT_FACTORY(acme_windowing_uikit)
{

   pfactory->add_factory_item < ::uikit::acme::windowing::windowing, ::acme::windowing::windowing >();
   pfactory->add_factory_item < ::uikit::acme::windowing::window, ::acme::windowing::window >();
   pfactory->add_factory_item < ::uikit::acme::windowing::display, ::acme::windowing::display >();
   pfactory->add_factory_item < ::uikit::acme::windowing::host_interaction, ::acme::sandbox_windowing::host_interaction >();

}


