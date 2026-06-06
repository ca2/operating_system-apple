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
// camilo on 2026-06-05 17:24 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/nano/graphics/pen.h"
//#include "subsystem_macos/_common_header.h"
//#include <Gdiplus.h>

namespace quartz2d
{

   namespace nano
   {

  
      namespace graphics
   {
      

   class pen :
      virtual public ::nano::graphics::pen
   {
   public:
      // const static int SOLID_TYPE = PS_SOLID;
      // const static int DASH_TYPE = PS_DASH;
      // const static int NULL_TYPE = PS_NULL;
      //
   //public:
      ///Pen(int type, int width, COLORREF color);
      
      // protected:
          //HPEN m_hpen;
         //Gdiplus::Pen * m_ppen;
         //::nano::graphics::enum_pen m_epen;
         //int m_iWidth;
         //::color::color m_color;
      //::nano::graphics::enum_line_cap m_elinecapStart;
      //::nano::graphics::enum_line_cap m_elinecapEnd;
         ::pointer < ::core_graphics::cg_color > m_pcgcolor;
      //
      //    friend class Graphics;
      pen();
      ~pen() override;


      //void * _HGDIOBJ() override;
      virtual void create_pen(::nano::graphics::enum_pen epen, ::f64 fWidth, const ::color::color &color);

      virtual void set_start_cap(::nano::graphics::enum_line_cap elinecap);
      virtual void set_end_cap(::nano::graphics::enum_line_cap elinecap);



//      void initialize_pen(innate_subsystem::enum_pen epen, ::f32 width, const color::color& color) override;
//
//
//      void setStartCap(::innate_subsystem::enum_line_cap elinecap) override;
//      void setEndCap(::innate_subsystem::enum_line_cap elinecap) override;

      //void destroyGraphicsObject() override;

  
   };

      
      } // namespace graphics
      } // namespace nano
      } // namespace quartz2d

