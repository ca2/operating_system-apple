//
//  music_midi_augraph_play_thread.hpp
//  music_midi_core_midi
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 19/05/19.
//  Copyright © 2019 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#pragma once


class output;


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace core_midi
      {
         
      
         class sequencer :
            virtual public ::music::midi::sequencer
         {
         public:
            
            
            ::pointer < ::music::midi::core_midi::midi > m_pmidi;
            
            
            sequencer(::music::midi::sequence * psequence, const string & strDevice);
            ~sequencer() override;
            
            
            virtual void preroll(player_command* pcommand) override;

            
         };

         
      } // namespace audio_unit
      
      
   } // namespace midi
   
   
} // namespace music



