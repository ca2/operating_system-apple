#include "framework.h"
#include "image.h"
#include "graphics.h"
#include "bitmap.h"
#include "pen.h"
#include "brush.h"
#include "palette.h"
#include "region.h"
#include "font.h"
#include "path.h"
#include "draw2d.h"


__FACTORY_EXPORT void draw2d_quartz2d_factory(::factory::factory * pfactory)
{

   
   pfactory->add_factory_item < ::draw2d_quartz2d::image        , ::image::image >();
   pfactory->add_factory_item < ::draw2d_quartz2d::graphics     , ::draw2d::graphics > ();
   pfactory->add_factory_item < ::draw2d_quartz2d::bitmap       , ::draw2d::bitmap > ();
   pfactory->add_factory_item < ::draw2d_quartz2d::pen          , ::draw2d::pen > ();
   pfactory->add_factory_item < ::draw2d_quartz2d::brush        , ::draw2d::brush > ();
   pfactory->add_factory_item < ::draw2d_quartz2d::palette      , ::draw2d::palette > ();
   pfactory->add_factory_item < ::draw2d_quartz2d::region       , ::draw2d::region > ();
   pfactory->add_factory_item < ::draw2d_quartz2d::font         , ::write_text::font > ();
   pfactory->add_factory_item < ::draw2d_quartz2d::path         , ::draw2d::path > ();


   pfactory->add_factory_item < ::draw2d_quartz2d::draw2d        , ::draw2d::draw2d >();

   
}



