//
//  Untitled.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/26.
//
#pragma once

#include "operating_system-apple/core_foundation/_mm.h"
#include "operating_system-apple/core_graphics/_struct.h"


#define CGCONTEXT(s) ((CGContextRef)(s).m_u)
#define CGCOLOR(s) ((CGColorRef)(s).m_u)
#define CGIMAGE(s) ((CGImageRef)(s).m_u)
#define CGPATH(s) ((CGPathRef)(s).m_u)
#define CGFONT(s) ((CGFontRef)(s).m_u)


#define CTFONT(s) ((CTFontRef)(s).m_u)
#define CTLINE(s) ((CTLineRef)(s).m_u)



