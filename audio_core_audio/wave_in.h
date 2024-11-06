#pragma once


#include "toolbox.h"
#include "audio/audio/wave/in.h"


namespace multimedia
{


   namespace audio_core_audio
   {


      class  CLASS_DECL_AUDIO_CORE_AUDIO in :
         virtual public toolbox,
         virtual public ::wave::in
      {
      public:


         bool                             m_bIsRunning;


         in();
         ~in() override;


         void in_initialize_encoder() override;


         void in_add_buffer(int iBuffer) override;


         virtual void * get_os_data();


         AudioQueueRef in_get_safe_AudioQueueRef();


         void in_open(int iBufferCount, int iBufferSampleCount) override;
         void in_close() override;
         void in_stop() override;
         void in_start() override;
         void in_reset() override;


         void init_task() override;
         void term_task() override;
         void pre_translate_message(::message::message * pmessage) override;


         static void HandleInputBuffer(void                                 *aqData,
                                       AudioQueueRef                        inAQ,
                                       AudioQueueBufferRef                  inBuffer,
                                       const AudioTimeStamp                 *inStartTime,
                                       unsigned int                               inNumPackets,
                                       const AudioStreamPacketDescription   *inPacketDesc);


         void HandleInputBuffer(AudioQueueRef                        inAQ,
                                AudioQueueBufferRef                  inBuffer,
                                const AudioTimeStamp                 *inStartTime,
                                unsigned int                               inNumPackets,
                                const AudioStreamPacketDescription   *inPacketDesc);


      };


   } // namespace audio_core_audio


} // namespace multimedia




