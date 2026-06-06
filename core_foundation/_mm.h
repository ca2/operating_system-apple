//
//  Untitled.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/26.
//
#pragma once


#include "operating_system-apple/core_foundation/_struct.h"


#define CFSTRING(s) ((CFStringRef)(s).m_u)


using namespace core_foundation;


cf_string_t create_cf_string(const char * psz, int size);
void cf_release(cf_string_t & cfstring);


