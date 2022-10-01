// From acme_posix/exception_translator.h by camilo on 2022-09-30 19:48 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme_posix/exception_translator.h"


namespace acme_apple
{


   class CLASS_DECL_ACME exception_translator :
      virtual public ::acme_posix::exception_translator
   {
   public:

      exception_translator();
      ~exception_translator() override;


      
      bool attach() override;
      bool detach() override;

      
   };


} // namespace acme_apple



