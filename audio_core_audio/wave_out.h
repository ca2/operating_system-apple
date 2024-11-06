#pragma once


#include "toolbox.h"
#include "audio/audio/wave/out.h"


namespace multimedia
{


   namespace audio_core_audio
   {


      class  CLASS_DECL_AUDIO_CORE_AUDIO out :
         virtual public toolbox,
         virtual public ::wave::out
      {
      public:


         unsigned int                                    m_NumPacketsToRead;
         array < AudioStreamPacketDescription * >  m_PacketDescs;
         bool                                      m_bDone;
         iptr                                   m_iBufferCount;
         iptr                                   m_iBufferSampleCount;


         out();
         ~out() override;


         void install_message_routing(::channel * pchannel) override;

         //virtual imedia_time out_get_time() override;
         class ::time out_get_position() override;
         void out_filled(::collection::index iBuffer) override;

         void out_open_ex(::thread * pthreadCallback, unsigned int uiSamplesPerSec, unsigned int uiChannelCount, unsigned int uiBitsPerSample, ::wave::enum_purpose epurpose) override;
         void out_stop() override;
         void out_close() override;
         void out_pause() override;
         void out_restart() override;
         virtual void * get_os_data();
         AudioQueueRef out_get_safe_AudioQueueRef();

         virtual void _out_start();

         void out_start(const class ::time & time) override;


         virtual void out_on_playback_end() override;

         void init_task() override;
         void term_task() override;


         void AudioQueueBufferCallback(AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer);


         virtual bool on_run_step();

         
         double out_get_latency() override;

//         void OnOpen();

      };


   } // namespace audio_core_audio


} // namespace multimedia



