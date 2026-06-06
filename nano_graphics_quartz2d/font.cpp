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
// From Pen.cpp by camilo on 2026-04-11 04:21 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "font.h"
#include "acme/platform/node.h"
#include "acme/nano/graphics/font_family.h"
#include "operating_system-apple/core_graphics/cg_font.h"

//#include <crtdbg.h>

namespace quartz2d
{

   namespace nano
   {

  
      namespace graphics
   {
      
//Pen::Pen(int type, int width, const ::color::color & color)
   font::font()
//:   m_pfont(nullptr)
//: m_pen(NULL)
{
  // m_pen = CreatePen(type, width, color);
  //
  // ASSERT(m_pen != NULL);
}

font::~font()
{
      //destroyGraphicsObject();
  //DeleteObject(m_pen);
}

   // void * Pen::_HGDIOBJ()
   // {
   //    return m_pparticleThis->_HGDIOBJ();
   // }


      void font::create_pixel_font(::nano::graphics::font_family * pfontfamily, ::f64 fPixelHeight, bool bBold, bool bItalic, bool bUnderline)
   {
//destroyGraphicsObject();

      construct_newø(m_pctfont);
         
         m_pfontfamily = pfontfamily;
      
         ::string strFontFamilyName = pfontfamily->get_font_family_name();

         m_pctfont->create_font_with_name(strFontFamilyName, fPixelHeight, bBold, bItalic, bUnderline);
//
//      Gdiplus::REAL fontSize =(Gdiplus::REAL) iPixelHeight;
//      m_pfont = new Gdiplus::Font(::wstring(pszFamily), fontSize,
//         iFontWeight >= 500 ? (bItalic ? Gdiplus::FontStyleBoldItalic : Gdiplus::FontStyleBold) :
//         (bItalic ? Gdiplus::FontStyleItalic : Gdiplus::FontStyleRegular));

   }

      void font::create_point_font(::nano::graphics::font_family * pfontfamily, ::f64 fPointHeight, bool bBold, bool bItalic, bool bUnderline)
{
//destroyGraphicsObject();

   construct_newø(m_pctfont);
         
         ::string strFontFamilyName = pfontfamily->get_font_family_name();

   m_pctfont->create_font_with_name(strFontFamilyName, fPointHeight, bBold, bItalic, bUnderline);
//
//      Gdiplus::REAL fontSize =(Gdiplus::REAL) iPixelHeight;
//      m_pfont = new Gdiplus::Font(::wstring(pszFamily), fontSize,
//         iFontWeight >= 500 ? (bItalic ? Gdiplus::FontStyleBoldItalic : Gdiplus::FontStyleBold) :
//         (bItalic ? Gdiplus::FontStyleItalic : Gdiplus::FontStyleRegular));

}
//
//
//   void font::destroyGraphicsObject()
//   {
//
////      if (m_pfont)
////      {
////
////         delete m_pfont;
////         m_pfont = nullptr;
////
////      }
//
//   }


   //    ///: m_pen(NULL)
// {
//
//    m_pparticleThis->initialize_pen(epen, width, color);
// }
//    // m_pen = CreatePen(type, width, color);
//    //
//    // ASSERT(m_pen != NULL);


} // namespace graphics
} // namespace nano
} // namespace quartz2d



