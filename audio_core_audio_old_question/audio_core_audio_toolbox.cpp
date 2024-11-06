//
//  audio_core_audio_toolbox.cpp
//  audio_core_audio
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 11/10/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"


namespace multimedia
{


   namespace audio_core_audio
   {


      toolbox::toolbox(::object * pobject) :
         object(pobject),
         ::thread(pobject),
         wave_base(pobject)
      {

         __zero(m_dataformat);

         m_Queue           = nullptr;
         m_runloop         = nullptr;
         m_CurrentPacket   = 0;


      }


      toolbox::~toolbox()
      {

      }


      void toolbox::wave_allocate_buffer_data(::wave::buffer::item * pbuffer, memsize len, unsigned int uiAlign)
      {

         AudioQueueBufferRef buf = nullptr;

         if(0 != AudioQueueAllocateBuffer(m_Queue, (unsigned int) len, &buf))
            return;

         if(buf == nullptr)
            return;

         m_Buffers.add(buf);

         pbuffer->m_pData = buf->mAudioData;

      }


      void toolbox::wave_free_buffer_data(::wave::buffer::item * pbuffer)
      {

         for(int i = 0; i < m_Buffers.get_count(); i++)
         {


            if(m_Buffers[i]->mAudioData == pbuffer->m_pData)
            {

               AudioQueueFreeBuffer(m_Queue, m_Buffers[i]);

               m_Buffers.erase_at(i);

               break;

            }


         }


      }


      void toolbox::free_buffers()
      {

         for(int i = 0; i < m_Buffers.get_count(); i++)
         {


            AudioQueueFreeBuffer(m_Queue, m_Buffers[i]);

         }

         m_Buffers.erase_all();


      }


      AudioStreamBasicDescription * toolbox::wave_format()
      {

         return &m_dataformat;

      }


      AudioQueueBufferRef toolbox::audio_buffer(int iBuffer)
      {

         return m_Buffers[iBuffer];

      }

      bool toolbox::initialize_thread()
      {

         m_runloop = CFRunLoopGetCurrent();

         if(m_runloop != nullptr)
         {

            CFRetain(m_runloop);

         }

         m_runmode = kCFRunLoopDefaultMode;

         if(m_runmode != nullptr)
         {

            CFRetain(m_runmode);

         }

         return true;
      }


      int toolbox::exit_thread()
      {

         if(m_runmode != nullptr)
         {
            CFRelease(m_runmode);
            m_runmode = nullptr;
         }

         if(m_runloop != nullptr)
         {
            CFRelease(m_runloop);
            m_runloop = nullptr;
         }

         return 0;

      }



   } // namespace multimedia


} // namespace multimedia
