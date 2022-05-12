//
//  acme_file.cpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
// From windowing_ios by camilo on 2022-05-11 06:20 PM <3ThomasBorregaardSorensen!!


#include "framework.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme_file.h"


string apple_get_executable_path();


namespace acme_apple
{

   
   acme_file::acme_file()
   {

//      m_pplatformfile = this;

   }


   acme_file::~acme_file()
   {


   }


   ::file::path acme_file::module()
   {

      ::file::path path = apple_get_executable_path();

      return path;

   }


} // namespace acme_ios



