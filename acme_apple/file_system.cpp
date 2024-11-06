//
//  file_system.cpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
// From windowing_ios by camilo on 2022-05-11 06:20 PM <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "file_system.h"


string apple_get_executable_path();


namespace acme_apple
{

   
   file_system::file_system()
   {

//      m_pplatformfile = this;

   }


   file_system::~file_system()
   {


   }


   ::file::path file_system::module()
   {

      ::file::path path = apple_get_executable_path();

      return path;

   }


} // namespace acme_ios



