// Created on 2021-04-29 1:03 PM BRT <3TBS_!! Second celebration of Mummis Birthday 70!!
// From acme_posix/exception_translator.cpp by camilo on 2022-09-30 19:48 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "exception_translator.h"


void InstallUncaughtExceptionHandler();
void UninstallUncaughtExceptionHandler();


namespace acme_apple
{


   exception_translator::exception_translator()
   {


   }


   exception_translator::~exception_translator()
   {

      
   }


   bool exception_translator::attach()
   {

      if (m_bSet)
      {
       
         return true;
         
      }

      if(!::acme_posix::exception_translator::attach())
      {
         
         return false;
         
      }

      ::InstallUncaughtExceptionHandler();
      
      return true;

   }


   bool exception_translator::detach()
   {

      if (!m_bSet)
      {
         
         return false;
         
      }

      ::UninstallUncaughtExceptionHandler();
      
      ::acme_posix::exception_translator::detach();
      
      return true;

   }


} // namespace acme_translator



