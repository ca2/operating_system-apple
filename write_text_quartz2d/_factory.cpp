#include "framework.h"


__FACTORY_EXPORT void write_text_quartz2d_factory(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::write_text_quartz2d::fonts, ::write_text::fonts >();
   pfactorymap->create_factory < ::write_text_quartz2d::write_text, ::write_text::write_text >();
   pfactorymap->create_factory < ::write_text_quartz2d::font_enumeration, ::write_text::font_enumeration >();

}
