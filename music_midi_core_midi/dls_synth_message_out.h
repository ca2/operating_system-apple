//
//  dls_synth_message_out.hpp
//  music_midi_core_midi
//
//  Created by Camilo Sasuke on 2021-06-09 03:55 BRT <3ThomasBorregaardSørensen__!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
// Accelerating Build 2022-08-22 21:03 <3ThomasBorregaardSorensen!!
//
#pragma once


#include <AudioToolbox/AUGraph.h>
#include <AudioUnit/AudioUnit.h>
#include <CoreMidi/MIDIMessages.h>
#include <CoreMidi/MIDIServices.h>

typedef OSStatus AUDIO_UNIT_RENDER_CALLBACK(void* inRefCon, AudioUnitRenderActionFlags* ioActionFlags, const AudioTimeStamp* inTimeStamp,
                               UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList* ioData);

using AUDIO_UNIT_RENDER_CALLBACK_FUNCTION_POINTER = AUDIO_UNIT_RENDER_CALLBACK *;

namespace music
{
   
   
   namespace midi
   {
      
      
      namespace core_midi
      {


         class dls_synth_message_out:
            public ::music::midi::message_out
         {
         public:
            
            //bool                    m_bUseEventList;
            AUNode                  m_nodeOutput;
            AUNode                  m_nodeSynth;
            AUGraph                 m_audiograph;
            
            AudioUnit               m_unitOutput;
            AudioUnit               m_unitSynth;
            CFTypeRef               m_pAVAudioUnitMIDIInstrument = nullptr;
            
            AudioUnit               m_unitMixer;
            ::music::midi::event *  m_pevent = nullptr;
            ::i64                   m_iPositionFrame;
            musical_tick            m_tkPosition;
            class ::time            m_timePosition;
            ::f64                   m_f64OutputSeconds;
            ::f64                   m_f64DelaySeconds;
            ::f64                   m_f64StartSampleTime;
            ::f64                   m_f64LastSampleTime;
            int                   m_i32LastFrameCount;
            bool                    m_bStarting;
            MIDIEventList           m_midieventlist;
            MIDIEventPacket *       m_pmidieventpacket = nullptr;
            int                     m_iProgramChangeStreak = -1;
            ::i64                   m_iFrameProgramChangeStreak = -1;
             
             int                  m_iAddedEvents;
            bool                    m_bInRenderMode;

            dls_synth_message_out();
            ~dls_synth_message_out() override;
            
             OSStatus render_notify(AudioUnitRenderActionFlags   * ioActionFlags,
                                                           const AudioTimeStamp         * inTimeStamp,
                                                           UInt32                       inBusNumber,
                                                           UInt32                       inNumberFrames,
                                    AudioBufferList              * ioData);
             
//            ::e_status initialize_message_out(::music::midi::midi * pmidi, const ::string & strDeviceId) override;
            
             static OSStatus renderNotify(void                         * inRefCon,
                                          AudioUnitRenderActionFlags   * ioActionFlags,
                                          const AudioTimeStamp         * inTimeStamp,
                                          UInt32                       inBusNumber,
                                          UInt32                       inNumberFrames,
                                          AudioBufferList              * ioData) ;
            static OSStatus RenderCallback(void* inRefCon, AudioUnitRenderActionFlags* ioActionFlags, const AudioTimeStamp* inTimeStamp,
                                           UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList* ioData);

            void open(bool bForSequencing) override;
            
            void note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
            void note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
            void program_change(int iChannel, unsigned char uchProgram) override;
            void control_change(int iChannel, unsigned char uchController, unsigned char uchValue) override;
            void pitch_bend(int iChannel, unsigned short ushBend) override;

            bool midi_message_step() override;

             void start() override;
            
            bool use_tick() const override;
            
            
            bool sends_on_message() const override;
            
            
         };


      } // namespace core_midi
   
   
   } // namespace midi


} // namespace core



