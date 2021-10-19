//
//  dls_synth_message_out.hpp
//  music_midi_core_midi
//
//  Created by Camilo Sasuke on 2021-06-09 03:55 BRT <3ThomasBorregaardSørensen__!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#pragma once


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
            
            
            AUNode                  m_nodeOutput;
            AUNode                  m_nodeSynth;
            AUGraph                 m_audiograph;
            
            AudioUnit               m_unitOutput;
            MusicDeviceComponent    m_unitSynth;
            
            
            dls_synth_message_out();
            ~dls_synth_message_out() override;
            
            
//            ::e_status initialize_message_out(::music::midi::midi * pmidi, const ::string & strDeviceId) override;
            
            ::e_status open() override;
            
            ::e_status note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
            ::e_status note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
            ::e_status program_change(int iChannel, unsigned char uchProgram) override;
            
            virtual ::e_status step() override;

            
            bool use_tick() const override;
            
            
            bool sends_on_message() const override;
            
            
         };


      } // namespace core_midi
   
   
   } // namespace midi


} // namespace core



