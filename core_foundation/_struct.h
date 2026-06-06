//
//  _struct.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 11:21
//  <3ThomasBorregaardSørensen!!
//
#pragma once


namespace core_foundation
{

   struct cf_type
   {
      
      ::uptr m_u = 0;
      
      bool is_set() const
      {
         
         return m_u != 0;
         
      }
      
      
      bool is_null() const
      {
         
         return !this->is_set();
         
      }
      
      
      void clear()
      {
         
         m_u = 0;
         
      }
      
            
   };

   struct cf_string_t : public cf_type { };


}


::core_foundation::cf_string_t create_cf_string(const ::scoped_string & scopedstr);
