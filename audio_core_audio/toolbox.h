//
//  audio_core_audio_toolbox.h
//  audio_core_audio
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 11/10/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#pragma once


#include "audio/audio/wave/base.h"


namespace multimedia
{
   
   
   namespace audio_core_audio
   {
      
      
      class  CLASS_DECL_AUDIO_CORE_AUDIO toolbox :
         virtual public ::wave::base
      {
      public:
   
         
//         aligned < AudioStreamBasicDescription >             m_pdataformat;
//         aligned_pointer < AudioQueueRef >                   m_Queue;
         AudioStreamBasicDescription                           m_dataformat;
         AudioQueueRef                                         m_Queue;
         comparable_raw_array < AudioQueueBufferRef >          m_Buffers;
         SInt64                                                m_CurrentPacket;
         CFRunLoopRef                                          m_runloop;
         CFStringRef                                           m_runmode;
   
         
         
         toolbox();
         ~toolbox() override;
         

         void allocate_buffer_data(::wave::buffer::item * pbuffer, memsize uiBufferSize, memsize uiAlign) override;
         
         void free_buffer_data(::wave::buffer::item * pbuffer) override;

         
         
         void init_task() override;
         void term_task() override;
         
         
         virtual void free_buffers();
         
         
         AudioStreamBasicDescription * wave_format();
         AudioQueueBufferRef audio_buffer(index iBuffer);
         
         
      } ;
      
   
   } // namespace multimedia
   
   
} // namespace multimedia
