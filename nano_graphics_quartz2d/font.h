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
// From Pen.h by camilo on 2026-04-11 04:18 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/nano/graphics/font.h"
#include "operating_system-apple/core_graphics/ct_font.h"


namespace quartz2d
{

   namespace nano
   {

  
      namespace graphics
   {
      


   class CLASS_DECL_NANO_GRAPHICS_QUARTZ2D font :
virtual public ::nano::graphics::font
   {
   public:
      
      ::pointer < ::core_text::ct_font > m_pctfont;
//      ::string m_strFamily;
//      int m_iPixelHeight;
//      int m_iFontWeight;
//      bool m_bItalice;

      //public:
      //Pen(int type, int width, const ::color::color & color);
      font();
      ~font() override;

      
      void create_point_font(::nano::graphics::font_family * pfontfamily, ::f64 fPointSize, bool bBold = false, bool bItalic = false, bool bUnderline = false) override;
      void create_pixel_font(::nano::graphics::font_family * pfontfamily, ::f64 fPixelSize, bool bBold = false, bool bItalic = false, bool bUnderline = false) override;


//      //void * _HGDIOBJ() override;
//      virtual void initialize_pixel_font(const_char_pointer pszFamily, ::i32 iPixelHeight, ::i32 iFontWeight = 400, bool bItalic = false) override;
//      virtual void initialize_point_font(const_char_pointer pszFamily, ::i32 iPixelHeight, ::i32 iFontWeight = 400,
//                                         bool bItalic = false) override;

      //void destroyGraphicsObject() override;

      // protected:
      //    HPEN m_pen;
      //
      //    friend class Graphics;
      //Gdiplus::Font * m_pfont;
    
   };


      
      } // namespace graphics
      } // namespace nano
      } // namespace quartz2d



