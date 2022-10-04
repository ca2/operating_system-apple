//
//  music_midi_augraph_sequencer.cpp
//  music_midi_core_midi
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 19/05/19.
//  Copyright © 2019 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
//#include "app-veriwell/multimedia/music/midi/attribute_message.h"
//#include "app-veriwell/multimedia/music/midi/midi_listener.h"
//#include "app-veriwell/multimedia/music/midi/midi_listener.h"
//#include "app-veriwell/multimedia/music/midi/midi_listener_set.h"
#include "app-veriwell/multimedia/music/midi/sequence.h"
#include "app-veriwell/multimedia/music/midi/sequencer.h"
#include "sequencer.h"
#include "app-veriwell/multimedia/music/midi/midi.h"
#include "midi.h"
#include <AudioToolbox/MusicPlayer.h>


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace core_midi
      {
   
         
         
         void MyMIDIReadProc( const MIDIPacketList *list, void *procRef, void */*srcRef*/ )
         {
            
            
         }
         CFStringRef ConnectedEndpointName(MIDIEndpointRef endpoint);

         OSStatus LoadSMF(const char* data, int dataSize, MusicSequence& sequence, MusicSequenceLoadFlags loadFlags);
         
         
         // Get general midi notifications
         void MyMIDINotifyProc (const MIDINotification  *message, void *refCon)
         {
            printf("MIDI Notify, messageId=%d,", message->messageID);
         }
         
   
         sequencer::sequencer(::music::midi::sequence * psequence, const string & strDevice):
         ::music::midi::sequencer(psequence, strDevice)
         {
           
            m_pmidi = psequence->get_midi(strDevice);
            
            index iDevice = m_iDevice;
            
            if(iDevice < 0)
            {
               
               iDevice = 0;
               
            }
            
            auto pmessageout = m_pmidi->get_message_out(strDevice);
            
            m_pmessageout = pmessageout;

         }
      
      
         sequencer::~sequencer()
         {
            
         }
      
         
         void sequencer::preroll(player_command* pcommand)
         {
            
            
            
         }

      
      } // namespace audio_unit
   
   
   } // namespace midi


} // namespace music



//::music::midi::sequencer * music_midi_core_midi_new_play_thread(::music::midi::sequence * psequence, index iPort)
//{
//   
//   return new ::music::midi::core_midi::sequencer(psequence, iPort);
//   
//}

