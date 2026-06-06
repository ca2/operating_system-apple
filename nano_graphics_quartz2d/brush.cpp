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
#include "framework.h"
#include "brush.h"


namespace quartz2d
{

   namespace nano
   {

  
      namespace graphics
   {
      
   brush::brush()
//   : m_hbrush(nullptr)
   //: m_pbrush(nullptr)
   {
   }

   brush::~brush()
   {

      //destroyGraphicsObject();

   }


   // void *Brush::_HGDIOBJ()
   // {
   //
   //    return m_hbrush;
   //
   // }
//
//
//   void brush::destroyGraphicsObject()
//   {
//      // if (m_hbrush) {
//      //    ::DeleteObject(m_hbrush);
//      //    m_hbrush = nullptr;
//      // }
////      if (m_pbrush)
////      {
////         delete m_pbrush;
////         m_pbrush = nullptr;
////
////      }
//   }
      
      } // namespace graphics
      } // namespace nano
      } // namespace quartz2d



