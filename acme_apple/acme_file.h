//
//  acme_file.hpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
// From windowing_ios by camilo on 2022-05-11 06:19 PM <3ThomasBorregaardSorensen!!
#pragma once


namespace acme_apple
{


   class CLASS_DECL_ACME acme_file :
      virtual public ::acme_posix::acme_file
   {
   public:
      
      
      
      acme_file();
      ~acme_file() override;

      
      ::file::path module() override;
      

   };


} // namespace acme_ios



