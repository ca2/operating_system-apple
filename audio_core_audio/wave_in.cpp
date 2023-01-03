#include "framework.h"
#include "wave_in.h"
#include "translation.h"
#include "app-core/audio/decode/encoder.h"


namespace multimedia
{


   namespace audio_core_audio
   {


      in::in()
      {

         m_pencoder = nullptr;
         m_einstate = ::wave::e_in_state_initial;
         m_bResetting = false;

      }

   
      in::~in()
      {
         
      }


      void in::init_task()
      {

         TRACE("in::init_instance %X\n", get_itask());
         //SetMainWnd(nullptr);
         //ASSERT(GetMainWnd() == nullptr);
         ::parallelization::set_priority(::e_priority_highest);
         //m_evInitialized.SetEvent();

         ::wave::in::init_task();

//         if(!::wave::in::init_thread())
//            return false;

         toolbox::init_task();

//         if(!toolbox::init_thread())
//            return false;
//
//
//         return true;
      }


      void in::term_task()
      {

         m_eventExitInstance.SetEvent();

         thread::term_task();

      }

   
      void in::pre_translate_message(::message::message * pmessage)
      {
         //::pointer < ::user::message > pusermessage(pmessage);
         //ASSERT(GetMainWnd() == nullptr);
         /*         if(pusermessage->m_uiMessage == MM_WIM_OPEN ||
                     pusermessage->m_uiMessage == MM_WIM_CLOSE ||
                     pusermessage->m_uiMessage == MM_WIM_DATA)
                  {
                     translate_in_message(pusermessage);
                     if(pusermessage->m_bRet)
                        return;
                  }*/
         return thread::pre_translate_message(pmessage);
      }

   
      void in::in_open(i32 iBufferCount, i32 iBufferSampleCount)
      {

         if(m_Queue != nullptr && m_einstate != ::wave::e_in_state_initial)
         {
            
            in_initialize_encoder();
            
            return;
            
         }

         throw ::exception(error_failed);

//         single_lock sLock(mutex(), true);
//         ASSERT(m_Queue == nullptr);
//         ASSERT(m_einstate == ::wave::e_in_state_initial);
//
//         m_pwaveformat->wFormatTag = 0;
//         m_pwaveformat->nChannels = 2;
//         m_pwaveformat->nSamplesPerSec = 44100;
//         m_pwaveformat->wBitsPerSample = sizeof(::audio::WAVEBUFFERDATA) * 8;
//         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
//         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
//         m_pwaveformat->cbSize = 0;
//         ::pointer < ::audio::wave > audiowave = papplication->audiowave();
//         m_iBuffer = 0;
//
//         if(::success == (m_estatusWave  = translate(AudioQueueNewInput(                              // 1
//                                                          &m_dataformat,                          // 2
//                                                          &HandleInputBuffer,                            // 3
//                                                          this,                                      // 4
//                                                          nullptr,                                         // 5
//                                                          kCFRunLoopCommonModes,                        // 6
//                                                          0,                                            // 7
//                                                          &m_Queue                                // 8
//                                                          ))))
//            goto Opened;
//         m_pwaveformat->nSamplesPerSec = 22050;
//         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
//         if(::success == (m_estatusWave  = translate(AudioQueueNewInput(                              // 1
//                                                            &m_dataformat,                          // 2
//                                                            &HandleInputBuffer,                            // 3
//                                                            this,                                      // 4
//                                                            nullptr,                                         // 5
//                                                            kCFRunLoopCommonModes,                        // 6
//                                                            0,                                            // 7
//                                                            &m_Queue                                // 8
//                                                            ))))
//            goto Opened;
//         m_pwaveformat->nSamplesPerSec = 11025;
//         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
//         if(::success == (m_estatusWave  = translate(AudioQueueNewInput(                              // 1
//                                                            &m_dataformat,                          // 2
//                                                            &HandleInputBuffer,                            // 3
//                                                            this,                                      // 4
//                                                            nullptr,                                         // 5
//                                                            kCFRunLoopCommonModes,                        // 6
//                                                            0,                                            // 7
//                                                            &m_Queue                                // 8
//                                                            ))))
//            goto Opened;
//
//         return m_estatusWave;
//
//Opened:
//         u32 uiBufferSizeLog2;
//         u32 uiBufferSize;
//         u32 uiAnalysisSize;
//         u32 uiAllocationSize;
//         u32 uiInterestSize;
//         u32 uiSkippedSamplesCount;
//
//         if(m_pwaveformat->nSamplesPerSec == 44100)
//         {
//            uiBufferSizeLog2 = 16;
//            uiBufferSize = m_pwaveformat->nChannels * 2 * iBufferSampleCount; // 512 kbytes
//            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
//            if(iBufferCount > 0)
//            {
//               uiAllocationSize = iBufferCount * uiBufferSize;
//            }
//            else
//            {
//               uiAllocationSize = 8 * uiAnalysisSize;
//            }
//            uiInterestSize = 200;
//            uiSkippedSamplesCount = 2;
//         }
//         else if(m_pwaveformat->nSamplesPerSec == 22050)
//         {
//            uiBufferSizeLog2 = 9;
//            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
//            uiAnalysisSize = 16 * 1 << uiBufferSizeLog2;
//            uiAllocationSize = 4 * uiAnalysisSize;
//            uiInterestSize = 600;
//            uiSkippedSamplesCount = 1;
//         }
////         else if(m_pwaveformat->nSamplesPerSec == 11025)
//         else
//         {
//            uiBufferSizeLog2 = 9;
//            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
//            uiAnalysisSize = 8 * 1 << uiBufferSizeLog2;
//            uiAllocationSize = 4 * uiAnalysisSize;
//            uiInterestSize = 600;
//            uiSkippedSamplesCount = 1;
//         }
//         in_get_buffer()->FFTOpen(
//            uiAllocationSize,
//            uiBufferSize,
//            uiAnalysisSize,
//            uiInterestSize,
//            uiSkippedSamplesCount);
//
///*         i32 i, iSize;
//
//         iSize = (i32) in_get_buffer()->GetBufferCount();
//
//         for(i = 0; i < iSize; i++)
//         {
//
//            if(::success != (mmr =  waveInPrepareHeader(m_Queue, create_new_WAVEHDR(in_get_buffer(), i), sizeof(WAVEHDR))))
//            {
//               TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
//               return mmr;
//            }
//
//            in_add_buffer(i);
//
//         }*/
//
//         if(m_pencoder != nullptr && !in_initialize_encoder())
//         {
//
//            m_einstate = ::wave::e_in_state_opened;
//
//            in_close();
//
//            return (::e_status    ) -1;
//
//         }
//
//         m_einstate = ::wave::e_in_state_opened;
//
//         return ::success;

      }


      void in::in_close()
      {

         single_lock sLock(mutex(), true);

         ::e_status     mmr;

         if(m_einstate != ::wave::e_in_state_opened && m_einstate != ::wave::e_in_state_stopped)
         {
            
            return;
            
         }

         in_reset();


         free_buffers();

         /*         i32 i, iSize;

                  iSize = (i32) in_get_buffer()->GetBufferCount();

                  for(i = 0; i < iSize; i++)
                  {

                     if(::success != (mmr = waveInUnprepareHeader(m_Queue, wave_hdr(i), sizeof(WAVEHDR))))
                     {
                        TRACE("ERROR OPENING Unpreparing INPUT DEVICE buffer");
                        //return mmr;
                     }

                     delete wave_hdr(i);

                  }*/
         
         OSStatus status = AudioQueueDispose(m_Queue, 1);

         m_estatusWave = translate(status);

         m_Queue = nullptr;

         m_einstate = ::wave::e_in_state_initial;

         //return mmr;

      }


      void in::in_start()
      {

         single_lock sLock(mutex(), true);

         if(m_einstate == ::wave::e_in_state_recording)
         {
            
            return;
            
         }

         if(m_einstate != ::wave::e_in_state_opened && m_einstate != ::wave::e_in_state_stopped)
         {
            
            return;
            
         }
         
         int iStatus = AudioQueueStart(m_Queue, nullptr);
         
         m_estatusWave = translate(iStatus);

         if(m_estatusWave != ::success)
         {

            TRACE("ERROR starting INPUT DEVICE ");

            throw ::exception(m_estatusWave);

         }

         m_einstate = ::wave::e_in_state_recording;

         //return ::success;

      }


      void in::in_stop()
      {

         single_lock sLock(mutex(), true);

         if(m_einstate != ::wave::e_in_state_recording)
         {
          
            throw ::exception(error_wrong_state);
            
         }

         OSStatus status;

         m_einstate = ::wave::e_in_state_stopping;

         try
         {
            if(0 != (status = AudioQueueStop(m_Queue, 1)))
            {
               TRACE("in::in_stop : ERROR OPENING stopping INPUT DEVICE ");
            }
         }
         catch(...)
         {
            TRACE("in::in_stop : Exception OPENING stopping INPUT DEVICE ");
         }
         m_einstate = ::wave::e_in_state_stopped;

         m_eventStopped.SetEvent();

         //return ::success;

      }

      /*
            void CALLBACK in::in_proc(HWAVEIN hwi, ::u32 uMsg, ::u32 dwInstance, ::u32 dwParam1, ::u32 dwParam2)
            {

               UNREFERENCED_PARAMETER(hwi);
               UNREFERENCED_PARAMETER(dwInstance);
               UNREFERENCED_PARAMETER(dwParam1);
               UNREFERENCED_PARAMETER(dwParam2);
               if(uMsg == WIM_DATA)
               {
                  ASSERT(false);
                       u32 msSampleTime = timeGetTime();
                  thread * pthread = (thread *) dwInstance;
                  ASSERT(pthread != nullptr);
                  LPWAVEHDR lpWaveHdr = (LPWAVEHDR) dwParam1;
                  LPWAVEPROCDATAMESSAGE lpxfwm = new WAVEPROCDATAMESSAGE;
                  lpxfwm->bDelete = true;
                  lpxfwm->msSampleTime = msSampleTime;
                  //      lpxfwm->tkSamplePosition = tkPosition;
                  lpxfwm->lpWaveHdr = lpWaveHdr;
                  pthread->post_thread_message(
                  WM_USER,
                  (WPARAM) WAVM_WAVE_PROC_DATA,
                  (LPARAM) lpxfwm);
                  //      i++;
                  //      if( i > 2)
                  //         i = 0;
      //         }
        //    }*/

   
      void in::in_reset()
      {
         
         single_lock sLock(mutex(), true);
         
         m_bResetting = true;
         
         if(m_Queue == nullptr)
         {
            
            throw ::exception(error_wrong_state);
            
         }

         if(m_einstate == ::wave::e_in_state_recording)
         {

            in_stop();
            
         }
         
         OSStatus status = AudioQueueReset(m_Queue);
         
         auto estatus = translate(status);
         
         if(failed(estatus))
         {
         
            ERROR("in::Reset error resetting input device");
               
            throw ::exception(estatus, "in::Reset error resetting input device");
            
         }
         
         m_einstate = ::wave::e_in_state_opened;

         m_bResetting = false;

      }


      void in::in_add_buffer(i32 iBuffer)
      {

         AudioQueueBufferRef buf = audio_buffer(iBuffer);

         AudioQueueEnqueueBuffer(m_Queue, buf, 0, nullptr);

      }


      void in::in_initialize_encoder()
      {

//         if(m_pencoder == nullptr)
//         {
//
//            return false;
//
//         }

         ::wave::in::in_initialize_encoder();
//            return false;
//
//         return true;

      }


      AudioQueueRef in::in_get_safe_AudioQueueRef()
      {

         if(is_null(this))
         {

            return nullptr;

         }

         return m_Queue;

      }


      void * in::get_os_data()
      {

         return m_Queue;

      }


      void in::HandleInputBuffer(void                                 *aqData,
                                      AudioQueueRef                        inAQ,
                                      AudioQueueBufferRef                  inBuffer,
                                      const AudioTimeStamp                 *inStartTime,
                                      ::u32                               inNumPackets,
                                      const AudioStreamPacketDescription   *inPacketDesc)
      {

         in * pwavein = (in *) aqData;               // 1

         pwavein->HandleInputBuffer(inAQ, inBuffer, inStartTime, inNumPackets, inPacketDesc);

      }


      void in::HandleInputBuffer( AudioQueueRef                        inAQ,
                                       AudioQueueBufferRef                  inBuffer,
                                       const AudioTimeStamp                 *inStartTime,
                                       ::u32                               inNumPackets,
                                       const AudioStreamPacketDescription   *inPacketDesc)
      {

         if(inNumPackets == 0 && m_dataformat.mBytesPerPacket != 0)
            inNumPackets = inBuffer->mAudioDataByteSize / m_dataformat.mBytesPerPacket;

         m_iBuffer--;

         auto tickSampleTime = ::duration::now();

         int iBuffer = (int) m_Buffers.find_first(inBuffer);

         m_listenerset.in_data_proc(this, (u32) (tickSampleTime.integral_millisecond().m_i % 0x100000000ULL), iBuffer);

         if(m_pencoder != nullptr)
         {

            m_pencoder->EncoderWriteBuffer(inBuffer->mAudioData, inBuffer->mAudioDataByteSize);

         }

         if(!in_is_resetting() && in_is_recording())
         {

            in_add_buffer(iBuffer);

         }


         if (m_bIsRunning == 0)                                         // 5
            return;


      }


   } // namespace audio_core_audio


} // namespace multimedia






