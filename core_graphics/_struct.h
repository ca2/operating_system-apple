//
//  _struct.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 11:21
//  <3ThomasBorregaardSørensen!!
//
#pragma once


#include "operating_system-apple/core_foundation/_struct.h"


namespace core_graphics
{

   struct cg_context;
   struct cg_image;

   using cg_float = double;


   struct cg_context_t : public ::core_foundation::cf_type { };
   struct cg_path_t : public ::core_foundation::cf_type { };
   struct cg_color_t : public ::core_foundation::cf_type { };
   struct cg_image_t : public ::core_foundation::cf_type { };
   struct cg_font_t : public ::core_foundation::cf_type { };


   struct cg_point { cg_float x; cg_float y;};
   struct cg_size { cg_float w; cg_float h;};
   struct cg_rect { cg_point origin; cg_size size;};

   struct cg_affine_transform_t;

   struct cg_dib_t
   {
      
      void *                     m_p = nullptr;
      cg_size                    m_cgsize = {};
      int                        m_iBytesPerRow = 0;
      
      ::pointer < cg_context >   m_pcgcontext;
      ::pointer < cg_image >     m_pcgimage;
      
      bool is_ok() const
      {
         
         return ::is_set(m_p) & (m_cgsize.w > 0) && (m_cgsize.h > 0) && (m_iBytesPerRow > 0);
         
      }
      
      bool is_null() const
      {
         
         return !is_ok();
         
      }
      
   };

} // namespace core_graphics



namespace core_text
{

   class ct_font;

   class ct_line;

   struct ct_font_t : public ::core_foundation::cf_type { };
   struct ct_line_t : public ::core_foundation::cf_type { };

} // namespace core_text






using namespace core_foundation;
using namespace core_graphics;
using namespace core_text;


void cg_context_save_g_state(cg_context_t cgcontext);
void cg_context_restore_g_state(cg_context_t cgcontext);


void cg_context_scale_ctm(cg_context_t cgcontext, cg_float x, cg_float y);
void cg_context_translate_ctm(cg_context_t cgcontext, cg_float x, cg_float y);


void cg_context_release(cg_context_t & cgcontext);
void cg_context_draw_line(cg_context_t cgcontext, cg_point point1, cg_point point2);
void cg_context_stroke_rect(cg_context_t cgcontext, cg_rect rect);
void cg_context_fill_rect(cg_context_t cgcontext, cg_rect rect);
void cg_context_fill_ellipse(cg_context_t cgcontext, cg_rect rect);
void cg_context_stroke_ellipse(cg_context_t cgcontext, cg_rect rect);
void cg_context_draw_image(cg_context_t cgcontext, cg_image_t nsimage, cg_point point, cg_rect rect);
void cg_context_draw_image(cg_context_t cgcontext, cg_image_t nsimage, cg_rect rect);
void cg_context_set_blend_mode_on(cg_context_t cgcontext, bool bSet);
void cg_context_set_anti_alias_on(cg_context_t cgcontext, bool bSet);
void cg_context_set_stroke_color_with_color(cg_context_t cgcontext, cg_color_t cgcolor);
void cg_context_set_fill_color_with_color(cg_context_t cgcontext, cg_color_t cgcolor);
void cg_context_set_line_width(cg_context_t cgcontext, cg_float fLineWidth);

void cg_context_draw_text(
      cg_context_t cgcontext,
      const char * text,
      int cchText,
      cg_rect cgrect,
      cg_color_t cgcolor,
      cg_font_t ctfont,
      unsigned int format,
      enum_align ealign);

void cg_context_set_text_position(cg_context_t cgcontext, cg_float x, cg_float y);

void cg_context_draw_dib(cg_context_t cgcontext, cg_dib_t * pdib);

void cg_path_release(cg_path_t & cgpath);
cg_path_t cg_mutable_path_create();
void cg_path_add_arc(cg_path_t cgpath,
                     const cg_affine_transform_t * ptransfrom,
                     cg_float x, cg_float y, cg_float radius, cg_float startAngle, cg_float endAngle,
                     bool clockwise);
void cg_path_close_subpath(cg_path_t cgpath);

void cg_color_release(cg_color_t & cgcolor);
cg_color_t cg_color_create(cg_float rgba[4]);


cg_image_t cg_image_create(cg_size size);
void cg_image_from_cg_bitmap_context(cg_image_t & cgimage, cg_context_t cgcontext);
void cg_image_release(cg_image_t & cgimage);
cg_size cg_image_get_size(cg_image_t cgimage);


cf_string_t create_cf_string(const char * psz, int size);
void cf_release(cf_string_t & cfstring);


void cg_dib_release(cg_dib_t & cgdib);
bool cg_dib_create_from_cg_image(cg_dib_t & cgdib, cg_image_t sourceImage);
bool cg_dib_create(cg_dib_t & cgdib, cg_size size);


void cg_font_release(cg_font_t & cgfont);

void ct_font_release(ct_font_t & ctfont);
ct_font_t ct_font_create_with_name_and_attributes_1(cf_string_t cfstring, cg_float fPointSize, int iFontWeight, bool bItalic, bool bUnderline);

void ct_line_release(ct_line_t & ctline);
ct_line_t ct_line_create_from_text_and_font(cf_string_t cfstrint, ct_font_t ctfont);
cg_float ct_line_get_typographic_founds(ct_line_t ctline, cg_float * pascent, cg_float * pdescent, cg_float * pleading);
void ct_line_draw(ct_line_t ctline, cg_context_t cgcontext);



