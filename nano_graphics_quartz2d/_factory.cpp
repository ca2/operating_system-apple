#include "framework.h"
//#include "dialog.h"
#include "icon.h"
//#include "window.h"
//#include "button.h"
//#include "still.h"
//#include "innate_ui.h"
#include "acme/nano/graphics/brush.h"
#include "acme/nano/graphics/pen.h"
#include "acme/nano/graphics/font.h"
#include "acme/nano/graphics/graphics.h"
#include "device.h"


IMPLEMENT_FACTORY(nano_graphics_quartz2d)
{

//   pfactory->add_factory_item < ::innate_ui_appkit::window, ::innate_ui::window >();
//   pfactory->add_factory_item < ::innate_ui_appkit::dialog, ::innate_ui::dialog >();
//   
//   
//   pfactory->add_factory_item < ::innate_ui_appkit::button, ::innate_ui::button >();
//   pfactory->add_factory_item < ::innate_ui_appkit::still, ::innate_ui::still >();
//
//
   pfactory->add_factory_item < ::quartz2d::nano::graphics::icon, ::nano::graphics::icon >();
//
//
//   pfactory->add_factory_item < ::innate_ui_appkit::innate_ui, ::innate_ui::innate_ui >();
   pfactory->add_factory_item < ::nano::graphics::graphics >();
   pfactory->add_factory_item < ::nano::graphics::font >();
   pfactory->add_factory_item < ::nano::graphics::brush >();
   pfactory->add_factory_item < ::nano::graphics::pen >();
   pfactory->add_factory_item < ::quartz2d::nano::graphics::device, ::nano::graphics::device >();

}



