//
//  CoreMIDIOutput.hpp
//  music_midi_core_audio
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 9/8/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

/*
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License along
 with this program; if not, write to the Free Software Foundation, Inc.,
 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#pragma once


#include "acme/prototype/prototype/memory.h"


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace core_midi
      {

         /**
          * @ingroup midi
          *
          * An OS X MIDI output port that uses CoreMIDI. This output device is used to send output
          * to external devices, not for playing with the built-in software synthesizer.
          */
         class message_in :
            virtual public input_base
         {
         public:
            
            
            ::pointer < ::music::midi::core_midi::midi > m_pmidi;

            unsigned long long                m_ui64Start;

            MIDIEndpointRef m_endpoint;
            
            MIDIPortRef m_port;
            
            memory m_buffer;
            
            memory            m_memoryLongMessage;
            
            MIDIPacketList * m_packetlist;

            MIDIPacket * m_packet;


            message_in(::music::midi::core_midi::midi * pmidi, const string & strDriver);
            message_in(::music::midi::core_midi::midi * pmidi, int iPort);
            
            void common_construct();
            
            
            //message_in();
            //message_in(::object * pobject, string driver);
            //message_in(::object * pobject, int iPort);
            ~message_in() override;
            
            void open(int iPort) override;
            
            void start() override;
            void stop() override;
            void close() override;
            
            
            void note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
            void note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
            void program_change(int iChannel, unsigned char uchProgram) override;
            void control_change(int iChannel, unsigned char uchController, unsigned char uchValue) override;
            void pitch_bend(int iChannel, unsigned short ushBend) override;
            void sysex(const ::block & block) override;
            
            bool midi_message_step() override;
            
            void reset_all_controllers() override;
            
            virtual void add_short_message(Byte * pmessage, int iSize);
            virtual void add_long_message(Byte * pmessage, int iSize);
            
            static void MIDIReadProc(const MIDIPacketList *pktlist, void *readProcRefCon, void *srcConnRefCon);

            void midi_read_proc(const MIDIPacketList *pktlist, void *srcConnRefCon);

         };
         
         
         
         CFStringRef ConnectedEndpointName(MIDIEndpointRef endpoint);

      } // namespace audio_unit
      
      
   } // namespace midi
   
   
} // namespace music




