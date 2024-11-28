//
// Created by camilo on 09/04/2022.
// Modified 2023-10-05 23:50
//
#pragma once


#include "acme_posix/_.h"


#if defined(_acme_windowing_kit_project)
#define CLASS_DECL_ACME_WINDOWING_KIT CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACME_WINDOWING_KIT CLASS_DECL_IMPORT
#endif



