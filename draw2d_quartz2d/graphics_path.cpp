//
//  graphics_path.cpp
//  draw2d_quartz2d
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2023-06-05 ~10:45.
//  Copyright © 2023 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
#include "graphics.h"
#include "path.h"
#include "aura/graphics/draw2d/path_simple_optimization.h"


namespace draw2d_quartz2d
{


   void graphics::fill(::draw2d::path * ppath)
   {
      
      if(!ppath->m_bPersistent)
      {
         
         if(ppath->m_ppathoptimization.is_null())
         {
            
             ppath->m_ppathoptimization = __initialize_new ::draw2d::path_simple_optimization(ppath);
            
         }

         if(ppath->m_ppathoptimization->fill(this, nullptr))
         {
            
            return;
            
         }

      }

      auto path = ppath->template get_os_data < CGMutablePathRef >(this);
      
      CGContextAddPath(m_cgcontext, path);

      _fill();

      _fill_inline(ppath, m_pbrush);

   }


   void graphics::draw(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {
      
      if(!ppath->m_bPersistent)
      {
         
         if(ppath->m_ppathoptimization.is_null())
         {
            
            ppath->m_ppathoptimization = __initialize_new ::draw2d::path_simple_optimization(ppath);
            
         }

         if(ppath->m_ppathoptimization->draw(this, ppen))
         {
            
            return;
            
         }

      }

      auto path = ppath->template get_os_data < CGMutablePathRef >(this);
      
      CGContextAddPath(m_cgcontext, path);

      _draw(ppen);

      _draw_inline(ppath, ppen);
      
   }


   void graphics::fill(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {
      
      if(!ppath->m_bPersistent)
      {
         
         if(ppath->m_ppathoptimization.is_null())
         {
            
            ppath->m_ppathoptimization = __initialize_new ::draw2d::path_simple_optimization(ppath);
            
         }
         
         if(ppath->m_ppathoptimization->fill(this, pbrush))
         {
            
            return;
            
         }

      }

      auto path = ppath->template get_os_data < CGMutablePathRef >(this);
      
      CGContextAddPath(m_cgcontext, path);

      _fill(pbrush);

      _fill_inline(ppath, pbrush);

   }


   void graphics::draw(::draw2d::path * ppath)
   {

      if(!ppath->m_bPersistent)
      {
         
         if(ppath->m_ppathoptimization.is_null())
         {
            
            ppath->m_ppathoptimization = __initialize_new ::draw2d::path_simple_optimization(ppath);
            
         }
         
         if(ppath->m_ppathoptimization->draw(this, nullptr))
         {
            
            return;
            
         }

      }

      auto path = ppath->template get_os_data < CGMutablePathRef >(this);
      
      CGContextAddPath(m_cgcontext, path);

      _draw();

      _draw_inline(ppath, m_ppen);

   }


   void graphics::intersect_clip(::draw2d::path * ppath)
   {

      if(!ppath->m_bPersistent)
      {
         
         if(ppath->m_ppathoptimization.is_null())
         {
            
            ppath->m_ppathoptimization = __initialize_new ::draw2d::path_simple_optimization(ppath);
            
         }
         
         if(ppath->m_ppathoptimization->intersect_clip(this))
         {
            
            return;
            
         }

      }

      auto path = ppath->template get_os_data < CGMutablePathRef >(this);
      
      CGContextAddPath(m_cgcontext, path);
      
      _intersect_clip();

//      _fill(pbrush);

//      _fill_inline(ppath, pbrush);

   }


} // namespace draw2d_quartz2d



