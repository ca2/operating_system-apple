#include "framework.h"
#include "wave_out.h"
#include "translation.h"
#include "acme/constant/message.h"
#include "acme/operating_system/apple/_apple.h"
#include "acme/parallelization/synchronous_lock.h"


#include "acme/_operating_system.h"


void WaveOutAudioQueueBufferCallback(void * inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer);


namespace multimedia
{


   namespace audio_core_audio
   {


      out::out()
      {

         m_eoutstate          = ::wave::e_out_state_initial;
         m_pthreadCallback    = nullptr;
         m_estatusWave        = ::success;
         m_bDone              = false;

      }

   
      out::~out()
      {

      }
   

      void out::install_message_routing(::channel * pchannel)
      {

         ::wave::out::install_message_routing(pchannel);

      }


      void out::init_task()
      {

         //if(!
         ::wave::out::init_task();
//
//         {
//
//            return false;
//
//         }

         //if(!
            
         toolbox::init_task();
         
//         {
//            
//            return false;
//            
//         }
//
//         return true;

      }
   

      void out::term_task()
      {

         ::wave::out::term_task();

         toolbox::term_task();

         thread::term_task();

      }


      void out::out_open_ex(thread * pthreadCallback, u32 uiSamplesPerSec, u32 uiChannelCount, u32 uiBitsPerSample, ::wave::enum_purpose epurpose)
      {

         synchronous_lock synchronouslock(synchronization());

         if(m_Queue != nullptr && m_eoutstate != ::wave::e_out_state_initial)
         {

            return;

         }

         m_pthreadCallback = pthreadCallback;

         ASSERT(m_Queue == nullptr);

         ASSERT(m_eoutstate == ::wave::e_out_state_initial);

         m_pwaveformat->m_waveformat.wFormatTag        = 0;
         m_pwaveformat->m_waveformat.nChannels         = (::u16) uiChannelCount;
         m_pwaveformat->m_waveformat.nSamplesPerSec    = uiSamplesPerSec;
         m_pwaveformat->m_waveformat.wBitsPerSample    = (::u16) uiBitsPerSample;
         m_pwaveformat->m_waveformat.nBlockAlign       = m_pwaveformat->m_waveformat.wBitsPerSample * m_pwaveformat->m_waveformat.nChannels / 8;
         m_pwaveformat->m_waveformat.nAvgBytesPerSec   = m_pwaveformat->m_waveformat.nSamplesPerSec * m_pwaveformat->m_waveformat.nBlockAlign;
         //m_pwaveformat->m_waveformat.cbSize            = 0;

         ::zero(m_dataformat);

         translate(m_dataformat, m_pwaveformat);

         int iBufferCount = 8;

         int iBufferSampleCount = 8192;

         if(epurpose == ::wave::e_purpose_playground)
         {

            iBufferCount = 2;

            iBufferSampleCount = uiSamplesPerSec / 20;

         }
         else if(epurpose == ::wave::e_purpose_playback)
         {

            iBufferCount = 8;

            iBufferSampleCount = uiSamplesPerSec / 20;

         }
         else if(epurpose == ::wave::e_purpose_live)
         {

            iBufferCount = 4;

            iBufferSampleCount = uiSamplesPerSec / 40;

         }

         m_epurpose = epurpose;
         m_iBufferCount = iBufferCount;
         m_iBufferSampleCount = iBufferSampleCount;

         m_estatusWave = error_failed;
         
//         try
//         {
//
            OSStatus osstatus = AudioQueueNewOutput(&m_dataformat, WaveOutAudioQueueBufferCallback, this, nullptr, nullptr, 0, &m_Queue);
            
            m_estatusWave = translate(osstatus);

//         }
//         catch(...)
//         {

         if(failed(m_estatusWave))
         {
            
            m_estatusWave = error_failed;

            throw ::exception(m_estatusWave);

         }

         int iFrameSize = m_pwaveformat->m_waveformat.wBitsPerSample * m_pwaveformat->m_waveformat.nChannels / 8;

         int iBufferSize = iBufferSampleCount * iFrameSize;

         out_get_buffer()->PCMOutOpen(this, iBufferSize, iBufferCount, 64, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open( m_pwaveformat->m_waveformat.nChannels, iBufferCount, iBufferSampleCount);

         m_eoutstate = ::wave::e_out_state_opened;

         //return m_estatusWave;

      }


      void out::out_close()
      {

         if(m_eoutstate == ::wave::e_out_state_playing)
         {

            out_stop();

         }

         if(m_eoutstate != ::wave::e_out_state_opened)
         {

            return;

         }

         m_eoutstate = ::wave::e_out_state_closing;

         OSStatus status;

         int i = 0;

         ::u32 property_running;

         ::u32 size;

         while(i < 50)
         {

            property_running = 0;

            size = sizeof(property_running);

            {
               
               synchronous_lock synchronouslock(synchronization());

               status = AudioQueueGetProperty(m_Queue, kAudioQueueProperty_IsRunning, &property_running, &size);
               
            }

            if(status != 0)
            {

               break;

            }

            if(!property_running)
            {

               break;

            }

            i++;

            sleep(100_ms);

         }

         free_buffers();
         
         {
         
            synchronous_lock synchronouslock(synchronization());

            status = AudioQueueDispose(m_Queue, false);
            
         }

         m_Queue = nullptr;

         m_eoutstate = ::wave::e_out_state_initial;

         //return ::success;

      }


      void out::out_filled(index iBuffer)
      {

         if(out_get_state() != ::wave::e_out_state_playing)
         {

            TRACE("ERROR out::BufferReady while out_get_state() != ::wave::e_out_state_playing");

            return;

         }

         synchronous_lock synchronouslock(synchronization());

         AudioQueueBufferRef buffer = audio_buffer(iBuffer);

         OSStatus status;

         buffer->mAudioDataByteSize = (::u32) out_get_buffer_size();

         status = AudioQueueEnqueueBuffer(m_Queue, buffer, 0, nullptr);

         if(status == 0)
         {

            m_iBufferedCount++;

         }

      }

   
      void out::out_stop()
      {

         synchronous_lock synchronouslock(synchronization());

         if(m_eoutstate != ::wave::e_out_state_playing && m_eoutstate != ::wave::e_out_state_paused)
         {

            throw ::exception(error_failed);

         }

         m_eoutstate = ::wave::e_out_state_stopping;
         
         OSStatus status = AudioQueueStop(m_Queue, false);

         m_estatusWave = translate(status);

         if(m_estatusWave == ::success)
         {

            m_eoutstate = ::wave::e_out_state_opened;

         }
         
         if(failed(m_estatusWave))
         {

            throw ::exception(m_estatusWave);
            
         }

      }


      void out::out_pause()
      {

         synchronous_lock synchronouslock(synchronization());

         ASSERT(m_eoutstate == ::wave::e_out_state_playing);

         if(m_eoutstate != ::wave::e_out_state_playing)
         {

            throw ::exception(error_failed);

         }

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_core_audio output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         OSStatus status = AudioQueuePause(m_Queue);
         
         m_estatusWave = translate(status);

         ASSERT(m_estatusWave == ::success);

         if(m_estatusWave == ::success)
         {

            m_eoutstate = ::wave::e_out_state_paused;

         }

         if(failed(m_estatusWave))
         {
            
            throw ::exception(m_estatusWave);
            
         }

      }


      void out::out_restart()
      {

         synchronous_lock synchronouslock(synchronization());

         ASSERT(m_eoutstate == ::wave::e_out_state_paused);

         if(m_eoutstate != ::wave::e_out_state_paused)
         {

            m_estatusWave = error_failed;

            throw ::exception(m_estatusWave);

         }

         //m_estatusWave =
         
         _out_start();

         //return m_estatusWave;

      }


      void out::_out_start()
      {

         synchronous_lock synchronouslock(synchronization());

         OSStatus statusPrime = AudioQueuePrime(m_Queue, 0, nullptr);

         m_estatusWave = translate(statusPrime);

         if(failed(m_estatusWave))
         {
            
            throw ::exception(m_estatusWave);
            
         }

         OSStatus statusStart = AudioQueueStart(m_Queue, nullptr);

         string strErrorString = apple_error_string(statusStart);

         string strErrorDescription = apple_error_description(statusStart);

         m_estatusWave = translate(statusStart);

         if(failed(m_estatusWave))
         {
            
            throw ::exception(m_estatusWave);
            
         }

         if(m_estatusWave == ::success)
         {

            m_eoutstate = ::wave::e_out_state_playing;

         }

         //return m_estatusWave;

      }


//      imedia_time out::out_get_time()
//      {
//
//         single_lock sLock(mutex(), true);
//
//         OSStatus                status;
//
//         AudioTimeStamp          stamp;
//
//         if(m_Queue != nullptr)
//         {
//
//
//            AudioQueueTimelineRef timeLine;
//
//            status = AudioQueueCreateTimeline(m_Queue, &timeLine);
//            if(status != noErr)
//               return 0;
//
//            status = AudioQueueGetCurrentTime(m_Queue, timeLine, &stamp, nullptr);
//
//            if(status != 0)
//               return 0;
//
//
//
//
//            if(!(stamp.mFlags & kAudioTimeStampSampleTimeValid))
//               return 0;
//
//            imedia_time iTime = (imedia_time) stamp.mSampleTime * 1000 / m_pwaveformat->m_waveformat.nSamplesPerSec;
//
//            return iTime;
//
//         }
//         else
//            return 0;
//
//
//      }


      class ::time out::out_get_position()
      {

         single_lock sLock(this->synchronization(), true);

         OSStatus                status;

         AudioTimeStamp          stamp;

         if(m_Queue != nullptr)
         {

            AudioQueueTimelineRef timeLine;

            status = AudioQueueCreateTimeline(m_Queue, &timeLine);
            if(status != noErr)
               return e_zero;

            status = AudioQueueGetCurrentTime(m_Queue, timeLine, &stamp, nullptr);

            if(status != 0)
               return e_zero;


            if(!(stamp.mFlags & kAudioTimeStampSampleTimeValid))
               return e_zero;

            return (double)stamp.mSampleTime/(double)m_pwaveformat->m_waveformat.nSamplesPerSec;

         }
         else
            return e_zero;


      }

      void out::out_on_playback_end()
      {

         ::wave::out::out_on_playback_end();

      }


      void * out::get_os_data()
      {

         return m_Queue;

      }



      void out::AudioQueueBufferCallback(AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer)
      {

         if(m_bDone)
         {

            return;

         }

         index iBuffer = m_Buffers.find_first(inCompleteAQBuffer);

         if(iBuffer < 0)
         {

            return;

         }

         m_psynthtask->on_free(iBuffer);

      }


      AudioQueueRef out::out_get_safe_AudioQueueRef()
      {

         return m_Queue;

      }


      bool out::on_run_step()
      {

         if(m_eoutstate == ::wave::e_out_state_playing)
         {

            CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.25, false);

         }

         return true;

      }


      void out::out_start(const class ::time & position)
      {

         ::wave::out::out_start(position);

//         if(failed(estatus))
//         {
//
//            return estatus;
//
//         }

         //m_estatusWave =
         
         _out_start();

         //if(return m_estatusWave;

      }


   } // namespace audio_core_audio


} // namespace multimedia




void WaveOutAudioQueueBufferCallback(void * inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inCompleteAQBuffer)
{

   ::multimedia::audio_core_audio::out * pwaveout = (::multimedia::audio_core_audio::out *) inUserData;

   if(pwaveout == nullptr)
   {

      return;

   }

   try
   {

      pwaveout->AudioQueueBufferCallback(inAQ, inCompleteAQBuffer);

   }
   catch(...)
   {

   }

}



