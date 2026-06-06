// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
//
// From innate_subsystem_macos by
// camilo on 2026-06-05 ~17:00 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/nano/graphics/brush.h"


namespace quartz2d
{

   namespace nano
   {

  
      namespace graphics
   {
      
      
   class CLASS_DECL_NANO_GRAPHICS_QUARTZ2D brush :
      virtual public ::nano::graphics::brush
   {
   public:
      
      
      ::pointer < ::core_graphics::cg_color > m_pcgcolor;

      brush();
      ~brush() override;
      
      
      void create_solid_brush(const ::color::color& color) override;



      //void * _HGDIOBJ() override;

   //protected:
      //void on_release() override;


//      void destroyGraphicsObject() override;

   // protected:
     //HBRUSH m_hbrush;
      //Gdiplus::Brush * m_pbrush;
      //::color::color m_color;
   //
   //    friend class Graphics;
   };
      
      } // namespace graphics
      } // namespace nano
      } // namespace quartz2d



