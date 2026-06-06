#include "framework.h"
//#include "dialog.h"
#include "icon.h"
//#include "window.h"
//#include "button.h"
//#include "still.h"
//#include "innate_ui.h"
#include "brush.h"
#include "dib.h"
#include "font.h"
#include "image.h"
#include "path.h"
#include "pen.h"
#include "acme/nano/graphics/font_family.h"
#include "acme/nano/graphics/graphics.h"
#include "context.h"


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
   pfactory->add_factory_item < ::nano::graphics::font_family >();
   pfactory->add_factory_item < ::quartz2d::nano::graphics::font, ::nano::graphics::font >();
   pfactory->add_factory_item < ::quartz2d::nano::graphics::brush, ::nano::graphics::brush >();
   pfactory->add_factory_item < ::quartz2d::nano::graphics::path, ::nano::graphics::path >();
   pfactory->add_factory_item < ::quartz2d::nano::graphics::pen, ::nano::graphics::pen >();
   pfactory->add_factory_item < ::quartz2d::nano::graphics::image, ::nano::graphics::image >();
   pfactory->add_factory_item < ::quartz2d::nano::graphics::dib, ::nano::graphics::dib >();
   pfactory->add_factory_item < ::quartz2d::nano::graphics::context, ::nano::graphics::context >();

}



