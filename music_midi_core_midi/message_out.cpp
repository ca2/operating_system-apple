//
//  message_out.cpp
//  music_midi_core_audio
//
//  Created by Camilo Sasuke Tsumanuma on 9/8/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"
#include "app-veriwell/multimedia/music/midi/_.h"
#include "app-veriwell/multimedia/music/midi/attribute_message.h"
#include "app-veriwell/multimedia/music/midi/midi_listener.h"
#include "app-veriwell/multimedia/music/midi/midi_listener_set.h"
#include "app-veriwell/multimedia/music/midi/sequence.h"
#include "app-veriwell/multimedia/music/midi/sequencer.h"
#include "app-veriwell/multimedia/music/midi/message_out.h"
#include "output_base.h"
#include "message_out.h"
#include "app-veriwell/multimedia/music/midi/midi.h"
#include "midi.h"


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace core_midi
      {


      message_out::message_out()
         {
            
         }
         

         void message_out::initialize_message_out(::music::midi::midi * pmidi, const string & strDriver)
         {
            
            //auto estatus =
            
            ::music::midi::message_out::initialize_message_out(pmidi, strDriver);
//            if(!estatus)
//            {
//
//               return estatus;
//
//            }
//            if(!estatus)
//            {
//
//               throw ::exception(estatus);
//
//            }
//
//            m_pmidi = pmidi;
//
//            m_packetlist = nullptr;
//
//            m_port = 0;
//
//            OSStatus result = MIDIOutputPortCreate(m_client, CFSTR("music_midi_core_midi"), &m_port);
//
//            if (result != 0)
//            {
//
//               string str;
//
//               str.Format("MIDIOutputPortCreate failed with code %i\n", (int) result);
//
//               throw ::exception(error_resource, str);;
//
//            }
//
//            bool bFound = false;
//
////            __pointer(::music::midi::core_midi::midi) pmidi = pmultimedia->midi();
////
////            if(pmidi)
//            {
//
//               auto destinations  = m_pmidi->get_destination_endpoints();
//
//               for (unsigned int n = 0; n < destinations.size(); n++)
//               {
//
//                  if (destinations[n].m_strName == strDriver)
//                  {
//
//                     m_endpoint = destinations[n].m_endpoint;
//
//                     bFound = true;
//
//                     return ::success;
//
//                  }
//
//               }
//
//               if(!bFound)
//               {
//
//                  for (unsigned int n = 0; n < destinations.size(); n++)
//                  {
//
//                     if (destinations[n].m_strName == strDriver)
//                     {
//
//                        m_endpoint = destinations[n].m_endpoint;
//
//                        bFound = true;
//
//                        return ::success;
//
//                     }
//
//                  }
//
//               }
//
//            }
//
//            if (!bFound)
//            {
//
//               output_debug_string("Unknown MIDI Output port (1)");
//
//               m_endpoint = MIDIGetDestination(0);
//
//            }
//
//            if(!m_port || !m_endpoint)
//            {
//
//               throw ::exception(error_resource, "either no Output Port or no Destination Endpoint");;
//
//            }
//
            //return estatus;
            
         }

     
//         message_out::message_out(::music::midi::core_midi::midi * pmidi, int iPort)
//         {
//
//            auto estatus = initialize(pmidi);
//
//            if(!estatus)
//            {
//
//               throw :::exception(estatus);
//
//            }
//
//            m_pmidi = pmidi;
//
//            estatus = open();
//
//            if(!estatus)
//            {
//
//               throw ::exception::exception(estatus);
//
//            }
//
//         }
      
      
         void message_out::open()
         {
         
            m_packetlist = nullptr;
            
            auto iPort = m_pmidi->get_midi_out_device_port(m_strDeviceId);
            
            m_port = (MIDIPortRef) iPort;
            
            OSStatus result = MIDIOutputPortCreate(m_client, CFSTR("music_midi_core_midi"), &m_port);
            
            if (result != 0)
            {
               
               WARNING("MIDIOutputPortCreate failed with code " << __string((int)result));
               
               throw ::exception(::error_failed);
               
            }
            
            bool bFound = false;
            
//            __pointer(::music::midi::core_midi::midi) pmidi = pmultimedia->midi();
//
//            if(pmidi)
            {
            
               auto destinations  = m_pmidi->get_destination_endpoints();
            
               if(iPort >= 0 && iPort < destinations.size())
               {
                  
                  m_endpoint = destinations[iPort].m_endpoint;
                    
                  bFound = true;
                     
               }
               
            }
            
            if (!bFound)
            {
               
               output_debug_string("Unknown MIDI Output port (2)");
               
               m_endpoint = MIDIGetDestination(0);
               
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

         void message_out::reset_all_controllers()
         {

            ::music::midi::message_out::reset_all_controllers();
            
         }


         message_out::~message_out()
         {
            
            MIDIPortDispose (m_port);
            
         }


         void message_out::note_off(int channel, unsigned char note, unsigned char velocity)
         {
            
            Byte message[3];
            
            message[0] = (byte) (::music::midi::note_off) | channel;
            
            message[1] = (byte) (0x7f & note);
            
            message[2] = (byte) (0x7f & velocity);
            
            add_short_message(message, 3);
            
            //return ::success;
            
         }
         
         
         void message_out::note_on(int channel, unsigned char note, unsigned char volume)
         {

            Byte message[3];
            
            message[0] = (byte) (::music::midi::note_on) | channel;
            
            message[1] = (byte) (0x7f & note);
            
            message[2] = (byte) (0x7f & volume);
            
            add_short_message(message, 3);
            
            //return ::success;
            
         }


         void message_out::control_change(int channel, unsigned char controller, unsigned char value)
         {
            
            Byte message[3];
            
            message[0] = (byte) (::music::midi::control_change) | channel;
            
            message[1] = (byte) (0x7f & controller);
            
            message[2] = (byte) (0x7f & value);
            
            add_short_message(message, 3);
            
         }
         
         
         void message_out::program_change(int channel, unsigned char instrument)
         {
            
            Byte message[2];
            
            message[0] = (byte) (::music::midi::program_change) | channel;
            
            message[1] = (byte) (0x7f & instrument);
            
            add_short_message(message, 2);
            
            //return ::success;
            
         }
         
         
         void message_out::pitch_bend(int channel, unsigned short value)
         {
            
            int c1 = (value & 0x7F);
            
            int c2 = ((value >> 7) & 0x7F);
            
            Byte message[3];
            
            message[0] = (byte) (::music::midi::pitch_bend) | channel;
            
            message[1] = c1;
            
            message[2] = c2;
            
            add_short_message(message, 3);
            
         }
         
         
         void message_out::sysex(const ::block & block)
         {
            
#ifdef _DEBUG
            
            string strHex;
            
            strHex = ::hex::lower_from(block.get_data(), block.get_size());
            
            output_debug_string(strHex);
            
#endif
            
            m_memoryLongMessage.set_size(block.get_size() + 2);
            
            memcpy(&m_memoryLongMessage.get_data()[1], block.get_data(), block.get_size());
            
            m_memoryLongMessage[0] = 0xf0;
            
            m_memoryLongMessage[block.get_size() + 1] = 0xf7;
            
            add_long_message(m_memoryLongMessage.get_data(), (int) m_memoryLongMessage.get_size());
            
         }
         
         
         bool message_out::step()
         {
            
            if(m_packetlist)
            {
            
               OSStatus result = MIDISend(m_port, m_endpoint, m_packetlist);
               
               if (result != 0)
               {
                  
                  fprintf(stderr, "MIDISend failed!!\n");
                  
               }
               
               m_packetlist = nullptr;
               
            }
            
            //return ::success;
            
            return true;

         }


         void message_out::start()
         {

#ifdef MACOS2

            m_ui64Start = AudioGetCurrentHostTime();
         
#endif
            
            //return ::success;
            
         }
         
         
         void message_out::add_short_message(Byte * pmessage, int iSize)
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
            
               m_packetlist = (MIDIPacketList *) m_buffer;
            
               m_packet = MIDIPacketListInit(m_packetlist);
               
            }
            
            m_packet = MIDIPacketListAdd(m_packetlist, sizeof(m_buffer), m_packet, timestamp, iSize, pmessage);

         }

         
         void message_out::add_long_message(Byte * pmessage, int iSize)
         {
            
            step();
            
            add_short_message(pmessage, iSize);

         }
         

      } // namespace audio_unit
      
      
   } // namespace midi
   
   
} // namespace music



