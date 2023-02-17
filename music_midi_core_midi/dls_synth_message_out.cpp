//
//  dls_synth_message_out.cpp
//  music_midi_core_midi
//
//  Created by Camilo Sasuke on 2021-06-09 03:56 BRT <3ThomasBorregaardSørensen__!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"
#include "app-veriwell/multimedia/music/midi/sequence.h"
#include "app-veriwell/multimedia/music/midi/sequencer.h"
#include "app-veriwell/multimedia/music/midi/message_out.h"
#include "dls_synth_message_out.h"
#include <AudioToolbox/AudioToolbox.h>

CFURLRef xg_url();
namespace music
{
   
   
   namespace midi
   {
      
      
      namespace core_midi
      {

         
         dls_synth_message_out::dls_synth_message_out()
         {
            
            open();
            
         }
         
         
         dls_synth_message_out::~dls_synth_message_out()
         {
            
            
         }
         
         
         void dls_synth_message_out::open()
         {
            
            OSStatus result = noErr;
            
            result = NewAUGraph(&m_audiograph);
            
            if (noErr != result)
            {
                               
               throw ::exception(::error_failed);
                               
            }

#ifdef MACOS
            
            AudioComponentDescription descriptionSynth ={};
            descriptionSynth.componentType           = kAudioUnitType_MusicDevice;
            descriptionSynth.componentSubType        = kAudioUnitSubType_DLSSynth;
            descriptionSynth.componentManufacturer   = kAudioUnitManufacturer_Apple;
            descriptionSynth.componentFlags          = 0;
            descriptionSynth.componentFlagsMask      = 0;
            
#else
            
            AudioComponentDescription descriptionSynth ={};
            descriptionSynth.componentType           = kAudioUnitType_MusicDevice;
            descriptionSynth.componentSubType        = kAudioUnitSubType_MIDISynth;
            descriptionSynth.componentManufacturer   = kAudioUnitManufacturer_Apple;
            descriptionSynth.componentFlags          = 0;
            descriptionSynth.componentFlagsMask      = 0;

#endif
            
            result = AUGraphAddNode (m_audiograph, &descriptionSynth, &m_nodeSynth);

            if (noErr != result)
            {
                               
               throw ::exception(::error_failed);
                               
            }
            
#ifdef MACOS
            
            AudioComponentDescription descriptionOutput={};
            descriptionOutput.componentType           = kAudioUnitType_Output;
            descriptionOutput.componentSubType        = kAudioUnitSubType_DefaultOutput;
            descriptionOutput.componentManufacturer   = kAudioUnitManufacturer_Apple;
            descriptionOutput.componentFlags          = 0;
            descriptionOutput.componentFlagsMask      = 0;
            
#else
            
            AudioComponentDescription descriptionOutput={};
            descriptionOutput.componentType           = kAudioUnitType_Output;
//            descriptionOutput.componentSubType        = kAudioUnitSubType_GenericOutput;
            descriptionOutput.componentSubType        = kAudioUnitSubType_RemoteIO;
            descriptionOutput.componentManufacturer   = kAudioUnitManufacturer_Apple;
            descriptionOutput.componentFlags          = 0;
            descriptionOutput.componentFlagsMask      = 0;
            
#endif

            result = AUGraphAddNode(m_audiograph, &descriptionOutput, &m_nodeOutput);
            
            if (noErr != result)
            {
                       
               throw ::exception(::error_failed);
                       
            }
            
            // AUNode mixerNode;

            // AudioComponentDescription mixerDescription = {0};
            // mixerDescription.componentType = kAudioUnitType_Mixer;
            // mixerDescription.componentSubType = kAudioUnitSubType_MultiChannelMixer;
            // mixerDescription.componentManufacturer = kAudioUnitManufacturer_Apple;

            // result = AUGraphAddNode(m_audiograph, &mixerDescription, &mixerNode);
            
            // if (noErr != result)
            // {
                       
            //    throw ::exception(::error_failed, "Error adding Mixer mode to graph");
                       
            // }
            
            // 6.connect input->eq->output node
            result = AUGraphConnectNodeInput(m_audiograph, m_nodeSynth, 0,m_nodeOutput, 0);
            if (noErr != result)
            {
                       
               throw ::exception(::error_failed);
                       
            }

            
            // result = AUGraphConnectNodeInput(m_audiograph, m_nodeMixer, 0, m_nodeOutput, 0),"AUGraphConnectModeInput");

            // if (noErr != result)
            // {
                       
            //    throw ::exception(::error_failed);
                       
            // }
            
            result = AUGraphUpdate (m_audiograph, NULL);
            if (noErr != result)
                   {
                              
                      throw ::exception(::error_failed);
                              
                   }

            // 3.open augraphic
            result = AUGraphOpen(m_audiograph);
            if (noErr != result)
            {
               
               throw ::exception(::error_failed);
               
            }

            // 4.get audio unit instance from nodes
            result = AUGraphNodeInfo(m_audiograph, m_nodeOutput, NULL, &m_unitOutput);
            
            if (noErr != result)
            {
                       
               throw ::exception(::error_failed);
                       
            }
            
            // 7. initialize graphic
              result = AUGraphInitialize(m_audiograph);
              if (noErr != result)
              {
                         
                 throw ::exception(::error_failed);
                         
              }
              

            result = AUGraphNodeInfo(m_audiograph, m_nodeSynth, NULL, &m_unitSynth);
            
            if (noErr != result)
            {
                       
               throw ::exception(::error_failed);
                       
            }
            
            
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

            result = AudioUnitSetParameter(m_unitOutput, kHALOutputParam_Volume, kAudioUnitScope_Global, 0, 1.0f, 0);
           if (noErr != result)
            {
                       
               throw ::exception(::error_failed, "Error adding Mixer mode to graph");
                       
            }

             CAShow(m_audiograph);
            
             
            // Start the graph
            result = AUGraphStart (m_audiograph);
             
            if (noErr != result)
              {
                         
                 throw ::exception(::error_failed);
                         
              }
            
            INFORMATION("AUGraphStart");
            
            //return ::success;
         }
         
         
         void dls_synth_message_out::note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity)
         {
            
            int noteOnCommand = ::u32(0x90 | iChannel);
            
            int iNote = uchNote;
            
            int iVelocity = uchVelocity;
            
//            if(iVelocity == 0)
//            {
//
//               INFORMATION("iVelocity == 0");
//
//               // try to note off;
//
//               //return
//
//            }
            
            OSStatus result = MusicDeviceMIDIEvent(
                                                   m_unitSynth,
                                                   noteOnCommand,
                                                   iNote,
                                                   iVelocity, 0);
            
//            if(iVelocity == 0)
//            {
//
//               INFORMATION("(note_on command doesn't accept 0 velocity???)");
//
//               // try to note off;
//
//               //return
//
//            }
            if (noErr != result)
            {
                       
               throw ::exception(::error_failed);
                       
            }
            
         }
         
         
         void dls_synth_message_out::note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity)
         {
            
            int noteOffCommand = ::u32(0x80 | iChannel);
            
            int iNote = uchNote;
            
//            if(iNote >= 127)
//            {
//
//               INFORMATION("uchNote >= 127 (doesn't accept 127 note off???)");
//
//               return;
//
//            }
            
            int iVelocity = uchVelocity;
         
            OSStatus result = MusicDeviceMIDIEvent (
                                                    m_unitSynth,
                                                    noteOffCommand,
                                                    iNote,
                                                    iVelocity,
                                                    0);
                    
            if (result != noErr)
            {
                                     
               throw ::exception(::error_failed);
                            
            }
            
         }
         
         
         void dls_synth_message_out::program_change(int iChannel, unsigned char uchProgram)
         {
            
            
            int programChangeCommand = ::u32(0xC0 | iChannel);
                OSStatus result=    MusicDeviceMIDIEvent (m_unitSynth, programChangeCommand, uchProgram, 0, 0);
                    
                    if (noErr != result)
                          {
                                     
                             //return ::error_failed;
                             
                             throw ::exception(::error_failed);
                                     
                          }
                    //return ::success;

         }
         
      
         bool dls_synth_message_out::step()
         {
            
            //return ::success;
            
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



