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


namespace core_graphics
{

   struct cg_context;
   struct cg_image;

   using cg_float = double;


   struct cg_context_t : public ::core_foundation::cf_type { };
   struct cg_color_t : public ::core_foundation::cf_type { };
   struct cg_image_t : public ::core_foundation::cf_type { };

   struct cg_point { cg_float x; cg_float y;};
   struct cg_size { cg_float w; cg_float h;};
   struct cg_rect { cg_point origin; cg_size size;};

   struct cg_dib_t
   {
      
      void *                     m_p = nullptr;
      cg_size                    m_cgsize = {};
      int                        m_iBytesPerRow = 0;
      
      ::pointer < cg_context >   m_pcgcontext;
      ::pointer < cg_image >     m_pcgimage;
      
      bool is_ok() const
      {
         
         return ::is_set(m_p) & (m_cgsize.w > 0) && (m_cgsize.h > 0) && (m_iBytesPerRow > 0);
         
      }
      
      bool is_null() const
      {
         
         return !is_ok();
         
      }
      
   };

} // namespace core_graphics



namespace core_text
{

   struct ct_font_t : public ::core_foundation::cf_type { };

} // namespace core_text




::core_foundation::cf_string_t create_cf_string(const ::scoped_string & scopedstr);
