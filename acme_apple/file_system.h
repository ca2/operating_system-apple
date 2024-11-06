//
//  file_system.hpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
// From windowing_ios by camilo on 2022-05-11 06:19 PM <3ThomasBorregaardSorensen!!
#pragma once


#include "acme_darwin/file_system.h"


namespace acme_apple
{


   class CLASS_DECL_ACME file_system :
      virtual public ::acme_darwin::file_system
   {
   public:
      
      
      
      file_system();
      ~file_system() override;

      
      ::file::path module() override;
      

   };


} // namespace acme_ios



