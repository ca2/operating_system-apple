//
//  Untitled.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/26.
//
#pragma once


#include "operating_system-apple/core_graphics/_struct.h"
#include <CoreGraphics/CoreGraphics.h>

#define CGCONTEXT(s) ((CGContextRef)(s).m_u)
#define CGCOLOR(s) ((CGColorRef)(s).m_u)
#define CGIMAGE(s) ((CGImageRef)(s).m_u)
#define CTFONT(s) ((CTFontRef)(s).m_u)
#define CFSTRING(s) ((CFStringRef)(s).m_u)


using namespace core_foundation;
using namespace core_graphics;
using namespace core_text;

void cg_context_draw_line(cg_context_t cgcontext, CGFloat x1, CGFloat y1, CGFloat x2, CGFloat y2);
void cg_context_draw_rect(cg_context_t cgcontext, CGRect rect);
void cg_context_fill_rect(cg_context_t cgcontext, CGRect rect);
void cg_context_draw_ellipse(cg_context_t cgcontext, CGRect rect);
void cg_context_fill_ellipse(cg_context_t cgcontext, CGRect rect);
void cg_context_draw_image(cg_context_t cgcontext, cg_image_t nsimage, CGPoint poin, CGRect rect);
void cg_context_draw_image(cg_context_t cgcontext, cg_image_t nsimage, CGRect rect);
void cg_context_set_blend_mode_on(cg_context_t cgcontext, bool bSet);
void cg_context_set_anti_alias_on(cg_context_t cgcontext, bool bSet);
void cg_context_set_stroke_color_with_color(cg_context_t cgcontext, cg_color_t cgcolor);
void cg_context_set_fill_color_with_color(cg_context_t cgcontext, cg_color_t cgcolor);
void cg_context_set_line_width(cg_context_t cgcontext, CGFloat fLineWidth);



void cg_image_release(cg_image_t & cgimage);
CGSize cg_image_get_size(cg_image_t cgimage);


void ct_font_release(ct_font_t & ctfont);

cf_string_t create_cf_string(const char * psz, int size);
void cf_release(cf_string_t & cfstring);



