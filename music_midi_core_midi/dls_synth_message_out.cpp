//
//  dls_synth_message_out.cpp
//  music_midi_core_midi
//
//  Created by Camilo Sasuke on 2021-06-09 03:56 BRT <3ThomasBorregaardSørensen__!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"
#include "app-veriwell/multimedia/music/midi/file.h"
#include "app-veriwell/multimedia/music/midi/sequence.h"
#include "app-veriwell/multimedia/music/midi/sequencer.h"
#include "app-veriwell/multimedia/music/midi/tracks.h"
#include "app-veriwell/multimedia/music/midi/message_out.h"
#include "dls_synth_message_out.h"
#include <AudioToolbox/AudioToolbox.h>
#include "operating_system-apple/media_apple/_.h"
#include "operating_system-apple/media_apple/media_apple.h"
#include "acme/platform/system.h"
CFURLRef xg_url();
char * ns_format_osstatus(OSStatus osstatus);
CFTypeRef get_a_soft_midi_synthesizer();
AudioUnit AVAudioUnitMIDIInstrument_audioUnit(CFTypeRef pAVAudioUnitMIDIInstrument);
void AVAudioUnitMIDIInstrument_sendMIDIEvent(CFTypeRef pinstrument, int event, int track, int b1);


void AVAudioUnitMIDIInstrument_sendMIDIEvent(CFTypeRef pinstrument, int event, int track, int b1, int b2);
void AVAudioUnitMIDIInstrument_startNote(CFTypeRef pAVAudioUnitMIDIInstrument, int note, int velocity, int channel);

void AVAudioUnitMIDIInstrument_stopNote(CFTypeRef pAVAudioUnitMIDIInstrument, int note, int channel);

void AVAudioUnitMIDIInstrument_sendProgramChange(CFTypeRef pAVAudioUnitMIDIInstrument, int program, int channel);
void music_midi_core_midi_start_audio_engine();
void music_midi_core_midi_instrument_set_callback(CFTypeRef pAVAudioUnitMIDIInstrument, AUDIO_UNIT_RENDER_CALLBACK_FUNCTION_POINTER callback, void * objectCallback );

namespace music
{
   
   
   namespace midi
   {
      
      
      namespace core_midi
      {

         
         dls_synth_message_out::dls_synth_message_out()
         {
             
             m_bMessageOutSequencesSequencer = true;
             m_audiograph = nullptr;
             m_iAddedEvents = 0;
            m_bUseEventList = false;

            
         }
         
         
         dls_synth_message_out::~dls_synth_message_out()
         {
            
            
         }
         
         
         void dls_synth_message_out::open()
         {
            m_bOpened = true;

#ifdef APPLE_IOS
            
            auto pfactory = system()->factory("media", "ios");
            
            pfactory->merge_to_global_factory();
            
#endif
            
            ::media_apple::media_apple::get(this);
            
            OSStatus result = noErr;
            
//            result = NewAUGraph(&m_audiograph);
//            
//            if (noErr != result)
//            {
//                               
//               throw ::exception(::error_failed);
//                               
//            }
//
//#ifdef MACOS
//            
//            AudioComponentDescription descriptionSynth ={};
//            descriptionSynth.componentType           = kAudioUnitType_MusicDevice;
//            descriptionSynth.componentSubType        = kAudioUnitSubType_DLSSynth;
//            descriptionSynth.componentManufacturer   = kAudioUnitManufacturer_Apple;
//            descriptionSynth.componentFlags          = 0;
//            descriptionSynth.componentFlagsMask      = 0;
//            
//#else
//            
//            AudioComponentDescription descriptionSynth ={};
//            descriptionSynth.componentType           = kAudioUnitType_MusicDevice;
//            descriptionSynth.componentSubType        = kAudioUnitSubType_MIDISynth;
//            descriptionSynth.componentManufacturer   = kAudioUnitManufacturer_Apple;
//            descriptionSynth.componentFlags          = 0;
//            descriptionSynth.componentFlagsMask      = 0;
//
//#endif
//            
//            result = AUGraphAddNode (m_audiograph, &descriptionSynth, &m_nodeSynth);
//
//            if (noErr != result)
//            {
//                               
//               throw ::exception(::error_failed);
//                               
//            }
//            
//#ifdef MACOS
//            
//            AudioComponentDescription descriptionOutput={};
//            descriptionOutput.componentType           = kAudioUnitType_Output;
//            descriptionOutput.componentSubType        = kAudioUnitSubType_DefaultOutput;
//            descriptionOutput.componentManufacturer   = kAudioUnitManufacturer_Apple;
//            descriptionOutput.componentFlags          = 0;
//            descriptionOutput.componentFlagsMask      = 0;
//            
//#else
//            
//            AudioComponentDescription descriptionOutput={};
//            descriptionOutput.componentType           = kAudioUnitType_Output;
////            descriptionOutput.componentSubType        = kAudioUnitSubType_GenericOutput;
//            descriptionOutput.componentSubType        = kAudioUnitSubType_RemoteIO;
//            descriptionOutput.componentManufacturer   = kAudioUnitManufacturer_Apple;
//            descriptionOutput.componentFlags          = 0;
//            descriptionOutput.componentFlagsMask      = 0;
//            
//#endif
//
//            result = AUGraphAddNode(m_audiograph, &descriptionOutput, &m_nodeOutput);
//            
//            if (noErr != result)
//            {
//                       
//               throw ::exception(::error_failed);
//                       
//            }
//            
//            // AUNode mixerNode;
//
//            // AudioComponentDescription mixerDescription = {0};
//            // mixerDescription.componentType = kAudioUnitType_Mixer;
//            // mixerDescription.componentSubType = kAudioUnitSubType_MultiChannelMixer;
//            // mixerDescription.componentManufacturer = kAudioUnitManufacturer_Apple;
//
//            // result = AUGraphAddNode(m_audiograph, &mixerDescription, &mixerNode);
//            
//            // if (noErr != result)
//            // {
//                       
//            //    throw ::exception(::error_failed, "Error adding Mixer mode to graph");
//                       
//            // }
//            
//            // 6.connect input->eq->output node
//            result = AUGraphConnectNodeInput(m_audiograph, m_nodeSynth, 0,m_nodeOutput, 0);
//            if (noErr != result)
//            {
//                       
//               throw ::exception(::error_failed);
//                       
//            }
//
//            
//            // result = AUGraphConnectNodeInput(m_audiograph, m_nodeMixer, 0, m_nodeOutput, 0),"AUGraphConnectModeInput");
//
//            // if (noErr != result)
//            // {
//                       
//            //    throw ::exception(::error_failed);
//                       
//            // }
//            
////            result = AUGraphUpdate (m_audiograph, NULL);
////            if (noErr != result)
////                   {
////                              
////                      throw ::exception(::error_failed);
////                              
////                   }
//
//            // 3.open augraphic
//            result = AUGraphOpen(m_audiograph);
//            if (noErr != result)
//            {
//               
//               throw ::exception(::error_failed);
//               
//            }
//
//            // 4.get audio unit instance from nodes
//            result = AUGraphNodeInfo(m_audiograph, m_nodeOutput, NULL, &m_unitOutput);
//            
//            if (noErr != result)
//            {
//                       
//               throw ::exception(::error_failed);
//                       
//            }
//            
            m_pAVAudioUnitMIDIInstrument = get_a_soft_midi_synthesizer();
            
            m_unitSynth = AVAudioUnitMIDIInstrument_audioUnit(m_pAVAudioUnitMIDIInstrument);
            
//            result = AUGraphNodeInfo(m_audiograph, m_nodeSynth, NULL, &m_unitSynth);
//            
//            if (noErr != result)
//            {
//                       
//               throw ::exception(::error_failed);
//                       
//            }
//            
//            
//            // 7. initialize graphic
//              result = AUGraphInitialize(m_audiograph);
//              if (noErr != result)
//              {
//                         
//                 throw ::exception(::error_failed);
//                         
//              }
              

            
            CFURLRef soundBankURL = xg_url();
            
                     result = AudioUnitSetProperty(
                         m_unitSynth,
                         kMusicDeviceProperty_SoundBankURL,
                         kAudioUnitScope_Global,
                         0,
                         (void *)&soundBankURL,
                                                   sizeof(soundBankURL));
            
            CFRelease(soundBankURL);
            if (noErr != result)
            {
                               
               throw ::exception(::error_failed);
                               
            }
             
             UInt32 sampleRateSize = sizeof(m_f64SamplingRate);
             AudioUnitGetProperty(m_unitSynth,
                                         kAudioUnitProperty_SampleRate,
                                  kAudioUnitScope_Output,
                                         0,
                                         &m_f64SamplingRate,
                                  &sampleRateSize);
            
//            ::u32 enabled = FALSE;
//            result = AudioUnitSetProperty(
//                m_unitSynth,
//                                          kAUMIDISynthProperty_EnablePreload,
//                                          kAudioUnitScope_Global,
//                0,
//                &enabled,
//                                          sizeof(enabled));
//            if (noErr != result)
//            {
//                               
//               throw ::exception(::error_failed);
//                               
//            }
//            
//
//            AUNode mixerNode;
//
//            AudioComponentDescription mixerDescription = {0};
//            mixerDescription.componentType = kAudioUnitType_Mixer;
//            mixerDescription.componentSubType = kAudioUnitSubType_MultiChannelMixer;
//            mixerDescription.componentManufacturer = kAudioUnitManufacturer_Apple;
//
//            result = AUGraphAddNode(m_audiograph, &mixerDescription, &mixerNode);
//
//            if (noErr != result)
//            {
//
//               throw ::exception(::error_failed, "Error adding Mixer mode to graph");
//
//            }
//
            // CheckError(AUGraphOpen(mGraph), "AUGraphOpen failed");

            // CheckError(AUGraphNodeInfo(mGraph, mixerNode, NULL, &mMixer), "Error loading mixer node info");
//
//            result = AudioUnitSetParameter(m_unitOutput, kHALOutputParam_Volume, kAudioUnitScope_Global, 0, 1.0f, 0);
//           if (noErr != result)
//            {
//                       
//               throw ::exception(::error_failed, "Error adding Mixer mode to graph");
//                       
//            }
//
            OSStatus status = AudioUnitAddRenderNotify(m_unitSynth, renderNotify, this);

            if (noErr != status)
              {
                         
                 throw ::exception(::error_failed);
                         
              }

             status = AudioUnitInitialize(m_unitSynth);
            
            
            if (noErr != status)
              {
                         
                 throw ::exception(::error_failed);
                         
              }

            //music_midi_core_midi_start_audio_engine();
            
//            AURenderCallbackStruct renderStruct;
//            renderStruct.inputProc = RenderCallback;
//            renderStruct.inputProcRefCon = this;
//            auto ret = AudioUnitSetProperty(m_unitSynth, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Global, 0, &renderStruct,
//                                       sizeof(renderStruct));
//            if (noErr != ret)
//            {
//                   
//               
////               auto psz = ns_format_osstatus(ret);
////
////               free(psz);
//               throw ::exception(::error_failed);
//                               
//            }
            
            
            //music_midi_core_midi_instrument_set_callback(m_pAVAudioUnitMIDIInstrument, &RenderCallback, this);
             
//                        result = AUGraphUpdate (m_audiograph, NULL);
//                        if (noErr != result)
//                               {
//            
//                                  throw ::exception(::error_failed);
//            
//                               }
//
//            CAShow(m_audiograph);
//           
            

            //return ::success;
         }
      
      
      void dls_synth_message_out::start()
      {
      //   ::parallelization::set_priority(e_priority_time_critical);
         
         //return;
          
          midi_message_step();
         
         m_bStarting = true;
          
         m_tkPosition = 0;
         
         m_iProgramChangeStreak = 0;
         
         m_iFrameProgramChangeStreak = 0;
         
         m_iFrame = 0;
         
         m_iFrameAbsolute = 0;
         
         m_f64DelaySeconds = 5.0;
         
         m_timePosition = 0_s;
         
         m_f64OutputSeconds = 0.;
          
         // Start the graph
         //auto result = AUGraphStart (m_audiograph);
         
         music_midi_core_midi_start_audio_engine();
           
//         if (noErr != result)
//         {
//                       
//            throw ::exception(::error_failed);
//                       
//         }
          
         informationf("AUGraphStart");
          
      }
      OSStatus dls_synth_message_out::RenderCallback(void* inRefCon, AudioUnitRenderActionFlags* ioActionFlags, const AudioTimeStamp* inTimeStamp,
                              UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList* ioData)
      {
         dls_synth_message_out * p = (dls_synth_message_out * ) inRefCon;
         
         return p->render_notify(ioActionFlags, inTimeStamp,
                                 inBusNumber,
                                 inNumberFrames,
                                 ioData);

      }
         
      OSStatus dls_synth_message_out::renderNotify(void                         * inRefCon,
                                   AudioUnitRenderActionFlags   * ioActionFlags,
                                   const AudioTimeStamp         * inTimeStamp,
                                   UInt32                       inBusNumber,
                                   UInt32                       inNumberFrames,
                                                   AudioBufferList              * ioData) {
          dls_synth_message_out * p = (dls_synth_message_out * ) inRefCon;
          
          return p->render_notify(ioActionFlags, inTimeStamp,
                                  inBusNumber,
                                  inNumberFrames,
                                  ioData);
          
      }
      
      
      OSStatus dls_synth_message_out::render_notify(
                  AudioUnitRenderActionFlags   * ioActionFlags,
                  const AudioTimeStamp         * inTimeStamp,
                  UInt32                       inBusNumber,
                  UInt32                       inNumberFrames,
                  AudioBufferList              * ioData)
      {

         if (*ioActionFlags & kAudioUnitRenderAction_PreRender)
         {
            
            auto f64LastSampleTime = m_f64LastSampleTime;
            auto i32LastFrameCount = m_i32LastFrameCount;
            
            double dDiff;
            
            if(m_bStarting)
            {
               
               m_bStarting = false;
               
               f64LastSampleTime = inTimeStamp->mSampleTime;
               
               m_f64StartSampleTime = inTimeStamp->mSampleTime;
               
               i32LastFrameCount = 0;
               
               dDiff = 0;
               
            }
            else
            {
               
               dDiff = inTimeStamp->mSampleTime - (m_f64LastSampleTime + m_i32LastFrameCount);
               
               if(dDiff < 0)
               {
                
                  return noErr;
                  
               }

            }
            
            double dDelayNow = 0.;
            
            int iFramesToQueue = inNumberFrames;
            
//            if(iFramesToQueue < 1024)
//            {
//             
//               iFramesToQueue *= 4;
//               
//            }
//            else if(iFramesToQueue < 2048)
//            {
//               
//               iFramesToQueue *= 2;
//               
//            }
            
            if(dDiff > 0)
            {

               dDelayNow = dDiff / m_f64SamplingRate;
               
               warningf("oVeRlOaD?!? dDiff = %0.1f   dDelayNow = %3.3f", dDiff, dDelayNow);
               
               m_f64DelaySeconds += dDelayNow;
               
            }
            
            m_f64LastSampleTime = inTimeStamp->mSampleTime;
            
            //m_i32LastFrameCount = inNumberFrames;
            
            m_i32LastFrameCount = iFramesToQueue;
            
            m_iAddedEvents = 0;
            
            while(true)
            {
                  
               if(m_pevent == nullptr)
               {
                     
                  auto tickMax = m_psequencer->m_psequence->m_tkEnd;

                  auto estatus = m_psequencer->m_psequence->m_pfile->WorkGetNextEvent(m_pevent, tickMax, true);
                     
                  if (::success != estatus)
                  {
                        
                     return -50;
                        
                  }
                     
                  auto tkPosition = m_psequencer->m_psequence->m_pfile->m_ptracks->m_tkPosition;
                     
                  if(tkPosition != m_tkPosition)
                  {
                        
                     m_tkPosition = tkPosition;
                        
                     m_timePosition = m_psequencer->m_psequence->m_pfile->tick_to_time(tkPosition);
                     
                      midi_message_step();
                      
                  }
                     
               }
               
               m_f64OutputSeconds = m_timePosition.floating_second() + m_f64DelaySeconds;
                  
               m_iFrameAbsolute = m_f64SamplingRate * m_f64OutputSeconds;
                      
               auto iFrame = m_iFrameAbsolute - (::i64) (inTimeStamp->mSampleTime - m_f64StartSampleTime);
                 
               if(iFrame < 0)
               {
                  
                  double d = (inTimeStamp->mSampleTime - m_f64StartSampleTime) / m_f64SamplingRate;
                  
                  warningf("event skipped %03.3fs %03.3fs %lld frames", d, m_timePosition.floating_second(), iFrame);
                      
                  m_pevent = nullptr;
                  
                  continue;
                      
               }
               
               if(iFrame >= iFramesToQueue)
               {
                  
                  if(m_iProgramChangeStreak >= 0)
                  {

                      midi_message_step();
                     
                     if(m_iFrameProgramChangeStreak < (inTimeStamp->mSampleTime - m_f64StartSampleTime))
                     {
                        
                        m_iFrameProgramChangeStreak = (inTimeStamp->mSampleTime - m_f64StartSampleTime);
                        
                     }
                     
                     for (;m_iProgramChangeStreak < 16 && m_iFrameProgramChangeStreak < (inTimeStamp->mSampleTime + inNumberFrames - m_f64StartSampleTime); m_iProgramChangeStreak++)
                     {
                           
                        int iTrack = m_iProgramChangeStreak;
                        
                        int iValue = m_psequencer->m_keyframe.rbProgram[iTrack];
                        
                        if(iValue != KF_EMPTY)
                        {
                           
                            program_change(iTrack, iValue);
                           
                        }
                         
                         midi_message_step();
                        
//                        if(iAddedEvents > 0)
//                        {
//                           
//                           m_iFrame = m_iFrameProgramChangeStreak - (::i64) inTimeStamp->mSampleTime;
//                           
//                           auto status = MusicDeviceMIDIEventList(m_unitSynth, (::i32)m_iFrame, &m_midieventlist);
//                           
//                           if(status != noErr)
//                           {
//                            
//                              warningf("error sending midi event listr");
//                              
//                              
//                           }
//                           
//                           m_pmidieventpacket = MIDIEventListInit(&m_midieventlist, kMIDIProtocol_1_0);
//                           
//                           iAddedEvents = 0;
//                           
//                           m_iFrameProgramChangeStreak += (int)(m_f64SamplingRate *0.040);
//                           
//                        }
                        
                     }
                        
                     for (;m_iProgramChangeStreak>= 16 && m_iProgramChangeStreak < 32 && m_iFrameProgramChangeStreak < (inTimeStamp->mSampleTime + inNumberFrames - m_f64StartSampleTime); m_iProgramChangeStreak++)
                     {
                        
                        int iTrack = m_iProgramChangeStreak - 16;
                        
                        for(int iControl = 0; iControl < 120; iControl++)
                        {
                           
                           int iValue = m_psequencer->m_keyframe.rbControl[iTrack][iControl];
                           
                           if(iValue != KF_EMPTY)
                           {
                               
                               control_change(iTrack, iControl, iValue);
                              
//                              auto message = MIDI1UPChannelVoiceMessage(0, ::music::midi::control_change >> 4, iTrack, iControl, iValue);
//                              
//                              m_pmidieventpacket = MIDIEventListAdd(&m_midieventlist, 65535, m_pmidieventpacket, 0, sizeof(message), &message);
//                              
//                              iAddedEvents++;
                              
                           }
                           
                        }
                        
                         midi_message_step();
//                        if(iAddedEvents > 0)
//                        {
//                           
//                           m_iFrame = m_iFrameProgramChangeStreak - (::i64) inTimeStamp->mSampleTime;
//                           
//                           MusicDeviceMIDIEventList(m_unitSynth, (::i32)m_iFrame, &m_midieventlist);
//                           
//                           m_pmidieventpacket = MIDIEventListInit(&m_midieventlist, kMIDIProtocol_1_0);
//                           
//                           iAddedEvents = 0;
//                           
//                           m_iFrameProgramChangeStreak += (int)(m_f64SamplingRate *0.020);
//
//                        }
                        
                     }
                     
                     if(m_iProgramChangeStreak >= 32)
                     {
                        
                        m_iProgramChangeStreak = -1;
                        
                     }
                     
                  }
                     
                  m_iFrame = 0;
                  
                  return noErr;
                      
               }
                  
               m_iFrame = iFrame;
               
//               MusicDeviceMIDIEventList(m_unitSynth,
//                                        iFrame, plist);
                  
               //on_event(m_pevent);
               
               if(m_pevent->GetType() == ::music::midi::note_on)
               {
                  
                   note_on(
                           m_pevent->GetTrack(), m_pevent->GetNotePitch(), m_pevent->GetNoteVelocity());
                  
               }
               else if(m_pevent->GetType() == ::music::midi::note_off)
               {

                   note_off(
                            m_pevent->GetTrack(),
                            m_pevent->GetNotePitch(),
                            m_pevent->GetNoteVelocity());
                  
               }
               else if(m_pevent->GetType() == ::music::midi::program_change)
               {
                   program_change(m_pevent->GetTrack(), m_pevent->GetProgram());
                   
                   
//                  auto message = MIDI1UPChannelVoiceMessage(0, ::music::midi::program_change >> 4, m_pevent->GetTrack(), m_pevent->GetProgram(), 0);
//                 
//                  m_pmidieventpacket = MIDIEventListAdd(&m_midieventlist, 65535, m_pmidieventpacket, 0, sizeof(message), &message);
//                  
//                  iAddedEvents++;
                  
               }
               else if(m_pevent->GetType() == ::music::midi::pitch_bend)
               {
                   
                   auto ushBend = (unsigned short)((unsigned short)(m_pevent->GetChB1() & 127) | ((unsigned short)((m_pevent->GetChB2() & 127) << 7)));
                   
                   pitch_bend(m_pevent->GetTrack(), ushBend);
                  
//                  auto message = MIDI1UPPitchBend(0, m_pevent->GetTrack(), m_pevent->GetChB1(), m_pevent->GetChB2());
//                 
//                  m_pmidieventpacket = MIDIEventListAdd(&m_midieventlist, 65535, m_pmidieventpacket, 0, sizeof(message), &message);
//                  
//                  m_iAddedEvents++;
                  
               }
                
               m_pevent = nullptr;

            }
              
          }

          return noErr;
          
      }
         
      
      void dls_synth_message_out::note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity)
         {
            
//            int noteOnCommand = ::u32(0x90 | iChannel);
//            
//            int iNote = uchNote;
//            
//            int iVelocity = uchVelocity;
            
//            if(iVelocity == 0)
//            {
//
//               information("iVelocity == 0");
//
//               // try to note off;
//
//               //return
//
//            }
            
         
//         AVAudioUnitMIDIInstrument_sendMIDIEvent(m_pAVAudioUnitMIDIInstrument,
//                                                 (int)::music::midi::note_on,
//                                                 iChannel,
//                                                 iNote,
//                                                 iVelocity);
          
          if (__builtin_available(macOS 12, iOS 15.0, *))
          {
              
              auto message = MIDI1UPNoteOn(0, iChannel, uchNote, uchVelocity);
             
              m_pmidieventpacket = MIDIEventListAdd(&m_midieventlist, 65535, m_pmidieventpacket, 0, sizeof(message), &message);
              
              m_iAddedEvents++;
             
          }
          else
          {
              
              auto status = MusicDeviceMIDIEvent(m_unitSynth, (::music::midi::note_on >> 4) | iChannel,
                                                 uchNote,
                                                 uchVelocity,
                                                 0);
              
              if(status != noErr)
              {
               
                  warningf("note on error");
                  
              }
              
          }
//         AVAudioUnitMIDIInstrument_startNote(m_pAVAudioUnitMIDIInstrument,
//                                                 iNote,
//                                                 iVelocity,
//                                             iChannel);

//            OSStatus result = MusicDeviceMIDIEvent(
//                                                   m_unitSynth,
//                                                   noteOnCommand,
//                                                   iNote,
//                                                   iVelocity, m_iFrame);
//            
////            if(iVelocity == 0)
////            {
////
////               information("(note_on command doesn't accept 0 velocity???)");
////
////               // try to note off;
////
////               //return
////
////            }
//            if (noErr != result)
//            {
//                       
//               throw ::exception(::error_failed);
//                       
//            }
            
         }
         
         
         void dls_synth_message_out::note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity)
         {
            
//            int noteOffCommand = ::u32(0x80 | iChannel);
//            
//            int iNote = uchNote;
            
//            if(iNote >= 127)
//            {
//
//               information("uchNote >= 127 (doesn't accept 127 note off???)");
//
//               return;
//
//            }
            
//            int iVelocity = uchVelocity;
//         
//            OSStatus result = MusicDeviceMIDIEvent (
//                                                    m_unitSynth,
//                                                    noteOffCommand,
//                                                    iNote,
//                                                    iVelocity,
//                                                    m_iFrame);
//                    
//            if (result != noErr)
//            {
//                                     
//               throw ::exception(::error_failed);
//                            
//            }
//            AVAudioUnitMIDIInstrument_sendMIDIEvent(m_pAVAudioUnitMIDIInstrument,
//                                                    ::music::midi::note_off,
//                                                    iChannel,
//                                                    iNote,
//                                                    uchVelocity);
             
             if (__builtin_available(macOS 12, iOS 15.0, *))
             {
                 
                 auto message = MIDI1UPNoteOff(0, iChannel, uchNote, uchVelocity);
                
                 m_pmidieventpacket = MIDIEventListAdd(&m_midieventlist, 65535, m_pmidieventpacket, 0, sizeof(message), &message);
                 
                 m_iAddedEvents++;

             }
             else
             {
                 
                 auto status = MusicDeviceMIDIEvent(m_unitSynth, (::music::midi::note_off >> 4) | iChannel,
                                                    uchNote,
                                                    uchVelocity,
                                                    0);
                 
                 if(status != noErr)
                 {
                  
                     warningf("note on error");
                     
                 }
                 

             }
//            AVAudioUnitMIDIInstrument_stopNote(m_pAVAudioUnitMIDIInstrument,
//                                                    iNote,
//                                                iChannel);

         }
         
         
         void dls_synth_message_out::program_change(int iChannel, unsigned char uchProgram)
         {
            
            
//            int programChangeCommand = ::u32(0xC0 | iChannel);
//                OSStatus result=    MusicDeviceMIDIEvent (m_unitSynth, programChangeCommand, uchProgram, 0, m_iFrame);
//                    
//                    if (noErr != result)
//                          {
//                                     
//                             //return ::error_failed;
//                             
//                             throw ::exception(::error_failed);
//                                     
//                          }
//                    //return ::success;
//            AVAudioUnitMIDIInstrument_sendMIDIEvent(m_pAVAudioUnitMIDIInstrument,
//                                                    ::music::midi::program_change,
//                                                    iChannel,
//                                                    uchProgram);
             if (__builtin_available(macOS 12, iOS 15.0, *))
             {
                 
                 auto message = MIDI1UPChannelVoiceMessage(0, ::music::midi::program_change >> 4, iChannel, uchProgram, 0);
                 
                 m_pmidieventpacket = MIDIEventListAdd(&m_midieventlist, 65535, m_pmidieventpacket, 0, sizeof(message), &message);
                 
                 m_iAddedEvents++;
                 
             }
             else
             {
                 
                 
                 
                 auto status = MusicDeviceMIDIEvent(m_unitSynth, (::music::midi::program_change >> 4) | iChannel,
                                                    uchProgram,
                                                    0,
                                                    0);
                 
                 if(status != noErr)
                 {
                  
                     warningf("note on error");
                     
                 }
                 

//
//                 AVAudioUnitMIDIInstrument_sendProgramChange(m_pAVAudioUnitMIDIInstrument,
//                                                             uchProgram,
//                                                             iChannel
//                                                             );
                 
             }

         }
         
      void dls_synth_message_out::control_change(int iChannel, unsigned char uchController, unsigned char uchValue)
      {
          
          if (__builtin_available(macOS 12, iOS 15.0, *))
          {
              
              auto message = MIDI1UPChannelVoiceMessage(0, ::music::midi::control_change >> 4, iChannel, uchController, uchValue);
              
              m_pmidieventpacket = MIDIEventListAdd(&m_midieventlist, 65535, m_pmidieventpacket, 0, sizeof(message), &message);
              
              m_iAddedEvents++;
              
          }
          else
          {
              
              auto status = MusicDeviceMIDIEvent(m_unitSynth, (::music::midi::control_change >> 4) | iChannel,
                                                 uchController,
                                                 uchValue,
                                                 0);
              
              if(status != noErr)
              {
               
                  warningf("note on error");
                  
              }
              

          }
          
          
      }
      
      
      void dls_synth_message_out::pitch_bend(int iChannel, unsigned short ushBend)
      {
          
          if (__builtin_available(macOS 12, iOS 15.0, *))
          {
              
              auto message = MIDI1UPPitchBend(0, m_pevent->GetTrack(), m_pevent->GetChB1(), m_pevent->GetChB2());
              
              m_pmidieventpacket = MIDIEventListAdd(&m_midieventlist, 65535, m_pmidieventpacket, 0, sizeof(message), &message);
              
              m_iAddedEvents++;
                                
          }
          else
          {
              
              int c1 = (ushBend & 0x7F);
              
              int c2 = ((ushBend >> 7) & 0x7F);

              auto status = MusicDeviceMIDIEvent(m_unitSynth, (::music::midi::pitch_bend >> 4) | iChannel,
                                                 c1,
                                                 c2,
                                                 0);
              if(status != noErr)
              {
                  
                  warningf("MusicDeviceMIDIEventList failed...");
                  
              }
          }

          
      }
      
      
         bool dls_synth_message_out::midi_message_step()
        {
             
             if (__builtin_available(macOS 12, iOS 15.0, *))
             {
             
                 if(m_iAddedEvents > 0)
                 {
                     
                     auto status = MusicDeviceMIDIEventList(m_unitSynth, (::i32)m_iFrame, &m_midieventlist);
                     
                     if(status != noErr)
                     {
                         
                         warningf("MusicDeviceMIDIEventList failed...");
                         
                     }
                     
                     m_pmidieventpacket = nullptr;
                     
                     m_iAddedEvents = 0;

                 }
                 
                 if(!m_pmidieventpacket)
                 {
                     
                     m_pmidieventpacket = MIDIEventListInit(&m_midieventlist, kMIDIProtocol_1_0);
                     
                 }
                 
             }
             
             return true;
            
         }
      
      
         bool dls_synth_message_out::use_tick() const
         {
            
            return false;
            
         }
      
         
         bool dls_synth_message_out::sends_on_message() const
         {
      
            return true;
         
         }


      } // namespace core_midi


   } // namespace midi


} // namespace core



