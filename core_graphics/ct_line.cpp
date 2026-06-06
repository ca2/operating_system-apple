//
//  ct_line.cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/06/26 20:36
//  <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#include "framework.h"
#include "ct_font.h"
#include "ct_line.h"
#include "cg_context.h"
#include "operating_system-apple/core_foundation/cf_string.h"


namespace core_text
{


ct_line::ct_line()
{
   
}


ct_line::~ct_line()
{
   
   ct_line_release(m_ctline);
   
}

void ct_line::create_with_text_and_font(::core_foundation::cf_string * pcfstring, ::core_text::ct_font * pctfont)
{
   
   m_ctline = ct_line_create_from_text_and_font(pcfstring->m_cfstring, pctfont->m_ctfont);
   
}

::f64 ct_line::get_typographic_bounds(cg_float * pascent, cg_float * pdescent, cg_float * pleading)
{
   
   return ct_line_get_typographic_bounds(m_ctline, pascent, pdescent, pleading);
   
}


void ct_line::draw(::core_graphics::cg_context * pcgcontext)
{
   
   ct_line_draw(m_ctline, pcgcontext->m_cgcontext);
   
}

} // namespace core_text
