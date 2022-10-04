//
//  audio_core_aligned_pointer.h
//  audio_core_audio
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/11/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once


template < typename POINTER >
class aligned_pointer
{
public:

   POINTER * m_pp;

   aligned_pointer() { m_pp = (POINTER *) main_memory_allocate_heap::aligned_memory_allocate(sizeof(POINTER)); *m_pp = nullptr; }
   ~aligned_pointer() { memory_free(m_pp);}

   POINTER operator ->()
   {
      return *m_pp;
   }

   operator POINTER & ()
   {
      return *m_pp;
   }

   POINTER * operator & ()
   {
      return m_pp;
   }


   aligned_pointer & operator = (POINTER p)
   {

      *m_pp = p;

      return *this;

   }


};
