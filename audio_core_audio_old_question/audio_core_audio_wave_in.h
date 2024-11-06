#pragma once


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


         in(::object * pobject);
         virtual ~in();


         virtual bool in_initialize_encoder() override;


         virtual ::e_status     in_add_buffer(int iBuffer) override;


         virtual void * get_os_data();


         AudioQueueRef in_get_safe_AudioQueueRef();


         ::e_status     in_open(int iBufferCount, int iBufferSampleCount) override;
         ::e_status     in_close() override;
         ::e_status     in_stop() override;
         ::e_status     in_start() override;
         ::e_status     in_reset() override;


         virtual bool initialize_thread() override;
         virtual int exit_thread() override;

         virtual void pre_translate_message(::message::message * pmessage) override;


         static void HandleInputBuffer(void                                 *aqData,
                                       AudioQueueRef                        inAQ,
                                       AudioQueueBufferRef                  inBuffer,
                                       const AudioTimeStamp                 *inStartTime,
                                       ::u32                               inNumPackets,
                                       const AudioStreamPacketDescription   *inPacketDesc);


         void HandleInputBuffer(AudioQueueRef                        inAQ,
                                AudioQueueBufferRef                  inBuffer,
                                const AudioTimeStamp                 *inStartTime,
                                ::u32                               inNumPackets,
                                const AudioStreamPacketDescription   *inPacketDesc);


      };


   } // namespace audio_core_audio


} // namespace multimedia




