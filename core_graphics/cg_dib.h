//
//  cg_dib.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026 May
//
#pragma once


namespace core_graphics
{


   class CLASS_DECL_CORE_GRAPHICS cg_dib :
      virtual public ::particle
   {
   public:
      
      cg_dib_t       m_cgdib;
//      void *       m_p;
//      ::i32_size   m_size;
//      int          m_iBytesPerRow;
//
//      ::pointer < cg_context > m_pcgcontext;
//      ::pointer < cg_image > m_pcgimage;
      
      
      cg_dib();
      ~cg_dib();
      
      //virtual void draw_image(cg_image * pimage);
      
      virtual void initialize_dib(const ::i32_size & size);
      
      virtual void initialize_from_cg_image(cg_image * pcgimage);
      
      virtual void update_image();
      
      virtual ::i32_size get_size();
      
      virtual void * get_buffer();
      
   };

} // namespace core_graphics

