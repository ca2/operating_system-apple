//
//  cf_string.cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 12:30
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "cf_string.h"
#include "_mm.h"



namespace core_foundation
{


   
   cf_string::cf_string()
   {
      
      
   }
   cf_string::~cf_string()
   {
      
      if(m_cfstring.is_set())
      {
         
         cf_release(m_cfstring);
         
      }
         
   }
      
   void cf_string::create_string(const ::scoped_string & scopedstr)
   {
         
      if(m_cfstring.is_set())
      {
         
         cf_release(m_cfstring);
         
      }
      m_cfstring = create_cf_string(scopedstr.c_str(), scopedstr.length());
   
   }


} // namespace core_foundation


