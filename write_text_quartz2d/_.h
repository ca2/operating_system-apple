// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


#include "aura/_.h"


#ifdef _WRITE_TEXT_QUARTZ2D_STATIC
#define CLASS_DECL_WRITE_TEXT_QUARTZ2D
#elif defined(_write_text_quartz2d_project)
#define CLASS_DECL_WRITE_TEXT_QUARTZ2D  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_WRITE_TEXT_QUARTZ2D  CLASS_DECL_IMPORT
#endif



