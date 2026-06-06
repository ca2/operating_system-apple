//
//  cf_string.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 12:30
//  <3ThomasBorregaardSørensen!!
//
#pragma once


namespace core_foundation
{


   class CLASS_DECL_CORE_FOUNDATION cf_string :
      virtual public ::particle
   {
      public:
     
      cf_string_t m_cfstring;
      
      
      cf_string();
      ~cf_string() override;
      
      virtual void create_string(const ::scoped_string & scopedstr);
   
   };


} // namespace core_foundation
