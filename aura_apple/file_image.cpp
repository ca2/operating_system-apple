//
//  file_image.cpp
//  aura_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 22/08/21.
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
#include "aura/graphics/image/image.h"


bool apple_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * pszFilePath);
bool apple_get_file_image_by_type_identifier(unsigned int * pcr, int cx, int cy, int iScan, const char * pszTypeIdentifier);


//bool apple_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * pszFilePath)
//{
//
//
//   return mm1_get_file_image(pcr, cx, cy, iScan, pszFilePath);
//
//
//}


//bool macos1_get_file_image_by_type_identifier(unsigned int * pcr, int cx, int cy, int iScan, const char * pszTypeIdentifier)
//{
//
//   return mm1_get_file_image_by_type_identifier(pcr, cx, cy, iScan, pszTypeIdentifier);
//
//}


bool apple_get_file_image(::image::image * pimage, const char * pszFilePath)
{

   pimage->map();

   if(!apple_get_file_image(&pimage->get_data()->m_ui, pimage->width(), pimage->height(), pimage->scan_size(), pszFilePath))
   {

      return false;

   }

   return true;

}


bool apple_get_file_image_by_type_identifier(::image::image * pimage, const char * pszTypeIdentifier)
{

   pimage->map();

   if(!apple_get_file_image_by_type_identifier(&pimage->get_data()->m_ui, pimage->width(), pimage->height(), pimage->scan_size(), pszTypeIdentifier))
   {

      return false;

   }

   return true;

}

