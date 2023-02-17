//
//  message_in.cpp
//  music_midi_core_audio
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 9/8/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
//#include "app-veriwell/multimedia/music/midi/attribute_message.h"
//#include "app-veriwell/multimedia/music/midi/midi_listener.h"
//#include "app-veriwell/multimedia/music/midi/midi_listener_set.h"
#include "acme/primitive/string/hex.h"
#include "app-veriwell/multimedia/music/midi/sequence.h"
#include "app-veriwell/multimedia/music/midi/sequencer.h"
#include "app-veriwell/multimedia/music/midi/message_in.h"
#include "input_base.h"
#include "message_in.h"
#include "app-veriwell/multimedia/music/midi/midi.h"
#include "midi.h"


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace core_midi
      {

         
//         message_in::message_in()
//         {
//
//         }


      message_in::message_in(::music::midi::core_midi::midi * pmidi, const string & strDriver)
         {
         
         
         common_construct();
            
            //auto estatus =
         
         input_base::initialize(pmidi);
//
//            if(!estatus)
//            {
//
//               throw ::exception(estatus);
//
//            }

            m_pmidi = pmidi;

            m_packetlist = nullptr;
            
            m_port = 0;
            
            OSStatus result = MIDIInputPortCreate(m_client, CFSTR("music_midi_core_midi"),
               &message_in::MIDIReadProc,
               this,
               &m_port);

            if (result != 0)
            {
               
               string str;
               
               str.format("MIDIOutputPortCreate failed with code %i\n", (int) result);
               
               throw ::exception(error_resource, str);;
               
            }

            bool bFound = false;
            
//            ::pointer < ::music::midi::core_midi::midi > pmidi = pmultimedia->midi();
            
            //if(pmidi)
            {
            
               auto sources = m_pmidi->get_source_endpoints();
            
               for (unsigned int n = 0; n < sources.size(); n++)
               {
                  
                  if (sources[n].m_strName == strDriver)
                  {
                     
                     m_endpoint = sources[n].m_endpoint;
                     
                     bFound = true;
                     
                     return;
                     
                  }
                  
               }
            
               if(!bFound)
               {
               
                  for (unsigned int n = 0; n < sources.size(); n++)
                  {
                     
                     if (sources[n].m_strName == strDriver)
                     {
                     
                        m_endpoint = sources[n].m_endpoint;
                     
                        bFound = true;
                     
                        return;
                  
                     }
                     
                  }
                  
               }
               
            }

            if (!bFound)
            {
               
               //wxMessageBox(_("Unknown MIDI port : ") + driver);
               
               m_endpoint = MIDIGetSource(0);
               
            }
            
         }

     
         message_in::message_in(::music::midi::core_midi::midi * pmidi, int iPort)
         {
            
            common_construct();
         
            //auto estatus =
            
            initialize(pmidi);
         
//            if(!estatus)
//            {
//
//               throw ::exception(estatus);
//
//            }
            
            m_pmidi = pmidi;
            
            //estatus =
            
            open(iPort);

//            if(!estatus)
//            {
//
//               throw ::exception(estatus);
//
//            }
                   
         }
      
      
      void message_in::common_construct()
      {
         
         m_buffer.set_size(65535);
         
      }
      
      
         void message_in::open(int iPort)
         {
         
            m_packetlist = nullptr;
            
            m_port = (MIDIPortRef) iPort;
            
            OSStatus result = MIDIInputPortCreate(m_client, CFSTR("music_midi_core_midi"),
               &message_in::MIDIReadProc,
               this,
               &m_port);

            if (result != 0)
            {
               
               string str;
               
               WARNING("MIDIOutputPortCreate failed with code " << ::as_string((int)result) );
               
               throw ::exception(::error_failed);
               
            }
            
            bool bFound = false;
            
//            ::pointer < ::music::midi::core_midi::midi > pmidi = pmultimedia->midi();
//
//            if(pmidi)
            {
            
               auto sources  = m_pmidi->get_source_endpoints();
            
               if(iPort >= 0 && iPort < sources.size())
               {
                  
                  m_endpoint = sources[iPort].m_endpoint;
                     
                  bFound = true;
                     
               }
               
               if (!bFound)
               {
                  
                  output_debug_string("Unknown MIDI In port");
                  
                  m_endpoint = MIDIGetSource(0);
                  
               }
               
            }
            
            //return ::success;
            
         }
         
         
         void message_in::start()
         {
            
            OSStatus result = MIDIPortConnectSource(m_port, m_endpoint, this);
            
            if(result != 0)
            {
               
               string str;
               
               WARNING("MIDIPortConnectSource failed with code " << ::as_string((int)result));
               
               throw ::exception(::error_failed);
               
            }
            
            //return ::success;
            
            //return;
            
         }

      
         void message_in::stop()
         {
            
            OSStatus result = MIDIPortDisconnectSource(m_port, m_endpoint);
            
            if(result != 0)
            {
              
               string str;
              
               WARNING("MIDIPortDisconnectSource failed with code "<< ::as_string((int)result));
              
               throw ::exception(::error_failed);
              
            }
                 
            //return ::success;
            
         }

      
         void message_in::close()
         {
            
            OSStatus result = MIDIPortDispose(m_port);

            if(result != 0)
            {
              
               string str;
              
               WARNING("MIDIPortDispose (for MIDI Input) failed with code " << ::as_string((int)result));
              
               throw ::exception(::error_failed);
              
            }

            //return ::success;
            
         }

         /*
         
         1. GM Reset (understood by every GM-compatible instrument)
         Sys-Ex String: F0 7E 7F 09 01 F7
         
         2. Roland GS Reset (Understood by all Roland GS instruments)
         Sys-Ex String: F0 41 10 42 12 40 00 7F 00 41 F7
         
         3. Yamaha XG reset (Understood by all Yamaha XG instruments)
         Sys-Ex String: F0 43 10 4C 00 00 7E 00 F7

         */

         void message_in::reset_all_controllers()
         {

            ::music::midi::message_in::reset_all_controllers();
            
         }


         message_in::~message_in()
         {
            
            MIDIPortDispose (m_port);
            
         }


         void message_in::note_off(int channel, unsigned char note, unsigned char velocity)
         {
            
            //return
            ::music::midi::message_in::note_off(channel, note, velocity);
            
         }
         
         
         void message_in::note_on(int channel, unsigned char note, unsigned char volume)
         {

            //return
            
            ::music::midi::message_in::note_on(channel, note, volume);
            
         }


         void message_in::control_change(int channel, unsigned char controller, unsigned char value)
         {
            
            Byte message[3];
            
            message[0] = (byte) (::music::midi::control_change) | channel;
            
            message[1] = (byte) (0x7f & controller);
            
            message[2] = (byte) (0x7f & value);
            
            add_short_message(message, 3);
            
         }
         
         
         void message_in::program_change(int channel, unsigned char instrument)
         {
            
            Byte message[2];
            
            message[0] = (byte) (::music::midi::program_change) | channel;
            
            message[1] = (byte) (0x7f & instrument);
            
            add_short_message(message, 2);
            
            //return ::success;
            
         }
         
         
         void message_in::pitch_bend(int channel, unsigned short value)
         {
            
            int c1 = (value & 0x7F);
            
            int c2 = ((value >> 7) & 0x7F);
            
            Byte message[3];
            
            message[0] = (byte) (::music::midi::pitch_bend) | channel;
            
            message[1] = c1;
            
            message[2] = c2;
            
            add_short_message(message, 3);
            
         }
         
         
         void message_in::sysex(const ::block & block)
         {
            
#ifdef _DEBUG
            
            string strHex;
            
            strHex = ::hex::lower_case_from(block.data(), block.size());
            
            output_debug_string(strHex);
            
#endif
            
            m_memoryLongMessage.set_size(block.size() + 2);
            
            memcpy(&m_memoryLongMessage.data()[1], block.data(), block.size());
            
            m_memoryLongMessage[0] = 0xf0;
            
            m_memoryLongMessage[block.size() + 1] = 0xf7;
            
            add_long_message(m_memoryLongMessage.data(), (int) m_memoryLongMessage.size());
            
         }
         
         
         bool message_in::step()
         {
            
//            if(m_packetlist)
//            {
//
//               OSStatus result = MIDISend(m_port, m_endpoint, m_packetlist);
//
//               if (result != 0)
//               {
//
//                  fprintf(stderr, "MIDISend failed!!\n");
//
//               }
//
//               m_packetlist = nullptr;
//
//            }
            
            return ::success;

         }


//         void message_in::start()
//         {
//
//            
//#ifdef MACOS2
//
//            m_ui64Start =AudioGetCurrentHostTime();
//         
//#endif
//            
//         }
//         
         
         void message_in::add_short_message(Byte * pmessage, int iSize)
         {
            
            if(iSize <= 0)
            {
               
               return;
               
            }
            
         #ifdef sysex
            MIDITimeStamp timestamp = m_ui64Start + nano_to_absolute((m_ps->m_timeFile - m_ps->m_timeFileStart + 100.0) * 1000000.0);
         #else
            MIDITimeStamp timestamp = 0;
         #endif
            
            if(m_packetlist == nullptr)
            {
            
               m_packetlist = (MIDIPacketList *) m_buffer.data();
            
               m_packet = MIDIPacketListInit(m_packetlist);
               
            }
            
            m_packet = MIDIPacketListAdd(m_packetlist, sizeof(m_buffer), m_packet, timestamp, iSize, pmessage);

         }

         
         void message_in::add_long_message(Byte * pmessage, int iSize)
         {
            
            step();
            
            add_short_message(pmessage, iSize);

         }
      
         
         void message_in::MIDIReadProc(const MIDIPacketList *pktlist, void *readProcRefCon, void *srcConnRefCon)
         {
         
            message_in * pin = (message_in *) readProcRefCon;
            
            pin->midi_read_proc(pktlist, srcConnRefCon);
         
         }

      
         void message_in::midi_read_proc(const MIDIPacketList *pktlist, void *srcConnRefCon)
         {
            
            for(int i = 0; i < pktlist->numPackets; i++)
            {
               
               const MIDIPacket & packet = pktlist->packet[i];
            
               byte b =packet.data[0];
               byte b1 =packet.data[1];
               byte b2 =packet.data[2];
               
               on_os_message(b, b1, b2);
               
//               if((b & 0x90) == 0x90)
//               {
//
//                  if(b2 == 0)
//                  {
//
//                     note_off(b, b1, b2);
//
//                  }
//                  else
//                  {
//
//                     note_on(b, b1, b2);
//
//                  }
//
//               }
//               else
//               {
//
//                  note_off(b, b1, b2);
//
//               }
//
            }
            
         }
         

      } // namespace audio_unit
      
      
   } // namespace midi
   
   
} // namespace music



