#include "framework.h"
#include "wave_in.h"
#include "translation.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/single_lock.h"
#include "audio/audio/decode/encoder.h"


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

         informationf("in::init_instance %llX\n", task_index());
         //SetMainWnd(nullptr);
         //ASSERT(GetMainWnd() == nullptr);
         ::parallelization::set_priority(::e_priority_highest);
         //m_evInitialized.set_happening();

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

         m_happeningExitInstance.set_happening();

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

   
      void in::in_open(int iBufferCount, int iBufferSampleCount)
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
//         unsigned int uiBufferSizeLog2;
//         unsigned int uiBufferSize;
//         unsigned int uiAnalysisSize;
//         unsigned int uiAllocationSize;
//         unsigned int uiInterestSize;
//         unsigned int uiSkippedSamplesCount;
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
///*         int i, iSize;
//
//         iSize = (int) in_get_buffer()->GetBufferCount();
//
//         for(i = 0; i < iSize; i++)
//         {
//
//            if(::success != (mmr =  waveInPrepareHeader(m_Queue, create_new_WAVEHDR(in_get_buffer(), i), sizeof(WAVEHDR))))
//            {
//               information("ERROR OPENING Preparing INPUT DEVICE buffer");
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

         single_lock sLock(this->synchronization(), true);

         //::e_status     mmr;

         if(m_einstate != ::wave::e_in_state_opened && m_einstate != ::wave::e_in_state_stopped)
         {
            
            return;
            
         }

         in_reset();


         free_buffers();

         /*         int i, iSize;

                  iSize = (int) in_get_buffer()->GetBufferCount();

                  for(i = 0; i < iSize; i++)
                  {

                     if(::success != (mmr = waveInUnprepareHeader(m_Queue, wave_hdr(i), sizeof(WAVEHDR))))
                     {
                        information("ERROR OPENING Unpreparing INPUT DEVICE buffer");
                        //return mmr;
                     }

                     delete wave_hdr(i);

                  }*/
         
         OSStatus osstatus = AudioQueueDispose(m_Queue, 1);

         m_estatusWave = os_status_status(osstatus);

         m_Queue = nullptr;

         m_einstate = ::wave::e_in_state_initial;

         //return mmr;

      }


      void in::in_start()
      {

         single_lock sLock(this->synchronization(), true);

         if(m_einstate == ::wave::e_in_state_recording)
         {
            
            return;
            
         }

         if(m_einstate != ::wave::e_in_state_opened && m_einstate != ::wave::e_in_state_stopped)
         {
            
            return;
            
         }
         
         auto ostatusStart = AudioQueueStart(m_Queue, nullptr);
         
         m_estatusWave = os_status_status(ostatusStart);

         if(m_estatusWave.failed())
         {

            informationf("ERROR starting INPUT DEVICE ");

            throw ::exception(m_estatusWave);

         }

         m_einstate = ::wave::e_in_state_recording;

         //return ::success;

      }


      void in::in_stop()
      {

         single_lock sLock(this->synchronization(), true);

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
               informationf("in::in_stop : ERROR OPENING stopping INPUT DEVICE ");
            }
         }
         catch(...)
         {
            informationf("in::in_stop : Exception OPENING stopping INPUT DEVICE ");
         }
         m_einstate = ::wave::e_in_state_stopped;

         m_happeningStopped.set_happening();

         //return ::success;

      }

      /*
            void CALLBACK in::in_proc(HWAVEIN hwi, unsigned int uMsg, unsigned int dwInstance, unsigned int dwParam1, unsigned int dwParam2)
            {

               UNREFERENCED_PARAMETER(hwi);
               UNREFERENCED_PARAMETER(dwInstance);
               UNREFERENCED_PARAMETER(dwParam1);
               UNREFERENCED_PARAMETER(dwParam2);
               if(uMsg == WIM_DATA)
               {
                  ASSERT(false);
                       unsigned int msSampleTime = timeGetTime();
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
         
         single_lock sLock(this->synchronization(), true);
         
         m_bResetting = true;
         
         if(m_Queue == nullptr)
         {
            
            throw ::exception(error_wrong_state);
            
         }

         if(m_einstate == ::wave::e_in_state_recording)
         {

            in_stop();
            
         }
         
         auto osstatusReset = AudioQueueReset(m_Queue);
         
         auto estatusReset = os_status_status(osstatusReset);
         
         if(estatusReset.failed())
         {
         
            errorf("in::Reset error resetting input device");
               
            throw ::exception(estatusReset, "in::Reset error resetting input device");
            
         }
         
         m_einstate = ::wave::e_in_state_opened;

         m_bResetting = false;

      }


      void in::in_add_buffer(int iBuffer)
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

         if(::is_null(this))
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
                                      unsigned int                               inNumPackets,
                                      const AudioStreamPacketDescription   *inPacketDesc)
      {

         in * pwavein = (in *) aqData;               // 1

         pwavein->HandleInputBuffer(inAQ, inBuffer, inStartTime, inNumPackets, inPacketDesc);

      }


      void in::HandleInputBuffer( AudioQueueRef                        inAQ,
                                       AudioQueueBufferRef                  inBuffer,
                                       const AudioTimeStamp                 *inStartTime,
                                       unsigned int                               inNumPackets,
                                       const AudioStreamPacketDescription   *inPacketDesc)
      {

         if(inNumPackets == 0 && m_pdataformat->mBytesPerPacket != 0)
            inNumPackets = inBuffer->mAudioDataByteSize / m_pdataformat->mBytesPerPacket;

         m_iBuffer--;

         auto tickSampleTime = ::time::now();

         int iBuffer = (int) m_Buffers.find_first(inBuffer);

         m_listenerset.in_data_proc(this, (unsigned int) (tickSampleTime.integral_millisecond() % 0x100000000ULL), iBuffer);

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






