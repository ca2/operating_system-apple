//
//  graphics_path.cpp
//  draw2d_quartz2d
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2023-06-05 10:48.
//  Copyright © 2023 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
#include "graphics.h"
#include "path.h"
#include "aura/graphics/write_text/text_out.h"
#include "aura/graphics/write_text/draw_text.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/primitive/geometry2d/_collection.h"
#include "acme/primitive/geometry2d/item.h"
#include "acme/primitive/geometry2d/_defer_item.h"
#include "aura/graphics/write_text/_defer_geometry2d_item.h"


namespace draw2d_quartz2d
{


   void graphics::_clip(::draw2d::region * pregion, bool bEO)
   {

      if(::is_null(pregion))
      {

         return;

      }
      
      auto pitem = pregion->m_pitem;

      if(::is_null(pitem))
      {

         return;

      }
      
      if(pitem->type() == ::draw2d::e_item_combine)
      {
         
         ::pointer < ::geometry2d::combine_item > pcombineitem = pitem;

         if(pcombineitem->m_ecombine == ::draw2d::e_combine_intersect)
         {
            
            auto pregion1 = defer_get_os_data(pcombineitem->m_pregion1);

            _clip(pregion1);

            _intersect_eo_clip();

            auto pregion2 = defer_get_os_data(pcombineitem->m_pregion2);

            _add_path(pregion2);

            _intersect_eo_clip();

         }
         else if(pcombineitem->m_ecombine == ::draw2d::e_combine_add)
         {

            auto pregion1 = defer_get_os_data(pcombineitem->m_pregion1);

            _clip(pregion1);

            _intersect_clip();;

            auto pregion2 = defer_get_os_data(pcombineitem->m_pregion2);

            _add_path(pregion2);

            _intersect_clip();;

         }
         
      }
      else if(pitem->type() == ::draw2d::e_item_rectangle)
      {
         
         ::pointer < ::geometry2d::rectangle_item > pitem = pregion->m_pitem;

         CGRect rectangle;
         
         copy(rectangle, pitem->m_item);

   //         rectangle.origin.x = pregion->m_x1;
   //         rectangle.origin.y = pregion->m_y1;
   //         rectangle.size.width = pregion->m_x2 - pregion->m_x1;
   //         rectangle.size.height = pregion->m_y2 - pregion->m_y1;
         
         CGContextAddRect (m_cgcontext, rectangle);

      }
      else if(pitem->type() == ::draw2d::e_item_polygon)
      {
         
         ::pointer < ::geometry2d::polygon_item > ppolygonitem = pitem;

         CGContextBeginPath (m_cgcontext);

         set_polygon(ppolygonitem->m_polygon.data(), ppolygonitem->m_polygon.size());

      }
      else if(pitem->type() == ::draw2d::e_item_ellipse)
      {

         ::pointer < ::geometry2d::ellipse_item > pellipseitem = pitem;
         
         CGRect rectangle;

         copy(rectangle, pellipseitem->m_item);

   //         rectangle.origin.x = pregion->m_x1;
   //         rectangle.origin.y = pregion->m_y1;
   //         rectangle.size.width = pregion->m_x2 - pregion->m_x1;
   //         rectangle.size.height = pregion->m_y2 - pregion->m_y1;

         CGContextAddEllipseInRect(m_cgcontext, rectangle);

      }

      if(bEO)
      {
         
         _intersect_eo_clip();
         
      }
      else
      {
         
         _intersect_clip();
         
      }

   }


   void graphics::_add_path(::draw2d::region * pregion)
   {

      if(::is_null(pregion))
      {

         return;

      }
      
      auto pitem = pregion->m_pitem;

      if(::is_null(pitem))
      {

         return;

      }
      
      if(pitem->type() == ::draw2d::e_item_rectangle)
      {

         ::pointer < ::geometry2d::rectangle_item > prectangleitem = pitem;

         CGRect rectangle;
         
         copy(rectangle, prectangleitem->m_item);

   //         rectangle.origin.x = pregion->m_x1;
   //         rectangle.origin.y = pregion->m_y1;
   //         rectangle.size.width = pregion->m_x2 - pregion->m_x1;
   //         rectangle.size.height = pregion->m_y2 - pregion->m_y1;

         CGContextAddRect (m_cgcontext, rectangle);

      }
      else if(pitem->type() == ::draw2d::e_item_polygon)
      {

         ::pointer < ::geometry2d::polygon_item > ppolygonitem = pitem;

         CGContextBeginPath (m_cgcontext);

         set_polygon(ppolygonitem->m_polygon.data(), ppolygonitem->m_polygon.size());

      }
      else if(pitem->type() == ::draw2d::e_item_ellipse)
      {

         ::pointer < ::geometry2d::ellipse_item > pellipseitem = pitem;

         CGRect rectangle;
         
         copy(rectangle, pellipseitem->m_item);

   //         rectangle.origin.x = pregion->m_x1;
   //         rectangle.origin.y = pregion->m_y1;
   //         rectangle.size.width = pregion->m_x2 - pregion->m_x1;
   //         rectangle.size.height = pregion->m_y2 - pregion->m_y1;

         CGContextAddEllipseInRect(m_cgcontext, rectangle);

      }
      else if(pitem->type() == ::draw2d::e_item_combine)
      {
         
         ::pointer < ::geometry2d::combine_item > pcombineitem = pitem;
         
         if(pcombineitem->m_ecombine == ::draw2d::e_combine_intersect)
         {

            auto pregion1 = defer_get_os_data(pcombineitem->m_pregion1);

            _add_path(pregion1);
            
            _intersect_eo_clip();
         
            auto pregion2 = defer_get_os_data(pcombineitem->m_pregion2);

            _add_path(pregion2);
            
            _intersect_eo_clip();

         }
         else if(pcombineitem->m_ecombine == ::draw2d::e_combine_add)
         {

            auto pregion1 = defer_get_os_data(pcombineitem->m_pregion1);

            _add_path(pregion1);
            
            _intersect_clip();
         
            auto pregion2 = defer_get_os_data(pcombineitem->m_pregion2);

            _add_path(pregion2);
            
            _intersect_clip();

         }

      }

   }


   void graphics::_draw_inline(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      for(auto & pitem : ppath->m_itema)
      {
         
         switch(pitem->type())
         {
            case ::draw2d::e_item_text_out:
         {

            _draw_inline(pitem->cast<::geometry2d::text_out_item>()->m_item, ppen);
         
         }
         break;
            case ::draw2d::e_item_draw_text:
         {

            _draw_inline(pitem->cast<::geometry2d::draw_text_item >()->m_item, ppen);
         
         }
         break;
            default:
               break;
         };

      }

   }


   void graphics::_fill_inline(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      for(auto & pitem : ppath->m_itema)
      {
         
         if(pitem->type() == ::draw2d::e_item_text_out)
         {

            _fill_inline(pitem->cast < ::geometry2d::text_out_item >()->m_item, pbrush);
            
         }
         else if(pitem->type() == ::draw2d::e_item_draw_text)
         {

            _fill_inline(pitem->cast < ::geometry2d::draw_text_item >()->m_item, pbrush);
            
         }

      }

   }



} // namespace draw2d_quartz2d



