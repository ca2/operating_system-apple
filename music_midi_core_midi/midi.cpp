#include "framework.h"
//#include "app-veriwell/multimedia/music/midi/attribute_message.h"
#include "app-veriwell/multimedia/music/midi/sequence.h"
#include "app-veriwell/multimedia/music/midi/sequencer.h"
//#include "app-veriwell/multimedia/music/midi/midi_listener.h"
//#include "app-veriwell/multimedia/music/midi/midi_listener_set.h"
#include "app-veriwell/multimedia/music/midi/message_out.h"
#include "dls_synth_message_out.h"
#include "app-veriwell/multimedia/music/midi/message_in.h"
#include "input_base.h"
#include "message_in.h"
#include "app-veriwell/multimedia/music/midi/midi.h"
#include "midi.h"
#ifdef MACOS
#include <CoreServices/CoreServices.h>
#endif


namespace music
{


   namespace midi
   {
      
      
      namespace core_midi
      {

      void mach_init_timebase();

         CFStringRef ConnectedEndpointName(MIDIEndpointRef endpoint);

         ::u64 nano_to_absolute(::u64 nano);

         // The following is copied from: http://developer.apple.com/qa/qa2004/qa1374.html
         CFStringRef EndpointName(MIDIEndpointRef endpoint, bool isExternal);


         midi::midi()
         {
            
            mach_init_timebase();
            
            m_strName = "core_midi";

            //m_pmidiRealTime = music_midi_real_time_new_midi();
            
         }


         midi::~midi()
         {

         }

         
         bool midi::Initialize()
         {
            
            if(!::music::midi::midi::Initialize())
            {
               
               return false;
               
            }
            
            return true;

         }
      
      
         array < Endpoint > midi::get_source_endpoints()
         {

            array < Endpoint > sources;

            ItemCount iEndpointCount = MIDIGetNumberOfSources();

            printf("Found %i MIDI Sources\n", (int)iEndpointCount);

            for (int iEndpoint = 0; iEndpoint < (int) iEndpointCount; iEndpoint++)
            {

               MIDIEndpointRef endpoint = MIDIGetSource(iEndpoint);

               CFStringRef name = ConnectedEndpointName(endpoint);

               char szBuffer[256];

               CFStringGetCString(name, szBuffer, 256, kCFStringEncodingUTF8);

               CFRelease(name);

               WARNING("Source:" << ::as_string(iEndpoint) << " - '" << ::string(szBuffer) << "'");

               Endpoint source;

               source.m_endpoint = endpoint;

               source.m_strName = szBuffer;

               sources.add(source);

            }

            return sources;

         }

      
         array < Endpoint > midi::get_destination_endpoints()
         {
            
            array < Endpoint > destinations;
            
            ItemCount iEndpointCount = MIDIGetNumberOfDestinations();
            
            INFORMATION(iEndpointCount << " MIDI destinations");
            
            for (int iEndpoint =0; iEndpoint < (int) iEndpointCount; iEndpoint++)
            {
               
               MIDIEndpointRef endpoint = MIDIGetDestination(iEndpoint);
               
               CFStringRef name = ConnectedEndpointName(endpoint);
               
               char szBuffer[256];
               
               CFStringGetCString(name, szBuffer, 256, kCFStringEncodingUTF8);
               
               CFRelease(name);
               
               WARNING("Destination:" << ::as_string(iEndpoint) << " - '" << ::as_string(szBuffer) << "'");
               
               Endpoint destination;
               
               destination.m_endpoint = endpoint;
               
               destination.m_strName = szBuffer;
               
               destinations.add(destination);
               
            }
            
            return destinations;
            
         }

         
         void midi::enumerate_midi_out_devices()
         {
            
            ::output_debug_string("music::midi::core_midi::enumerate_midi_out_devices\n");
            
            add_midi_out_device("DLS Synth", "core_midi:DLS Synth");
            
            auto sources = get_destination_endpoints();
            
            for(auto & source : sources)
            {
               
               add_midi_out_device(source.m_strName, "core_midi");
               
            }

            ::music::midi::midi::enumerate_midi_out_devices();

         }

      
         void midi::enumerate_midi_in_devices()
         {
            
            ::output_debug_string("music::midi::core_midi::enumerate_midi_in_devices\n");
            
            auto sources = get_source_endpoints();
            
            for(auto & source : sources)
            {
               
               add_midi_in_device(source.m_strName, "core_midi");
               
            }
            
            ::music::midi::midi::enumerate_midi_in_devices();

         }


         ::e_status midi::enumerate_midi_devices()
         {
            
            auto estatus = ::music::midi::midi::enumerate_midi_devices();
            
            if(!estatus)
            {
               
               return estatus;
               
            }

            return ::success;

         }


         ::e_status     midi::translate_os_result(string & strMessage, string & strOsMessage, ::music::midi::object * pobject, i64 iOsResult, const string & strContext, const string & strText)
         {

            ::e_status     estatus = iOsResult == 0 ? ::success : error_failed;

            if (estatus == ::success)
            {
               
               return ::success;
               
            }

            return estatus;

         }
      
         
         ::pointer < ::music::midi::sequencer > midi::create_midi_sequencer(::music::midi::sequence * psequence, const string& strDevice)
         {
            
            string strEngine = device_engine(strDevice);
            
            if (strEngine.is_empty() || strEngine.case_insensitive_equals(m_strName))
            {
               
               auto pmessageout = get_message_out(strDevice);
               
               return __new(::music::midi::sequencer(psequence, pmessageout));
               
            }
            
            return ::music::midi::midi::create_midi_sequencer(psequence, strDevice);
            
         }

         
         ::pointer < ::music::midi::message_out > midi::get_message_out(const string & strDevice)
         {
            
            if(strDevice == "core_midi:DLS Synth")
            {
               
               return __create_new<dls_synth_message_out>();
               
            }
            
            //auto iPort = get_midi_out_device_port(strDevice);
            
            //if (iPort >= 0 && iPort < m_cPortCount)
            {
               
               auto & pmessageout = m_mapMessageOut[strDevice];
               
               if (!pmessageout)
               {
                  
                  auto pmidiout = __create_new < message_out >();
                  
                  pmessageout = pmidiout;
                  
               }
               
               return pmessageout;
               
            }
            
            return nullptr;
            
         }

      
      ::pointer < ::music::midi::message_in > midi::get_message_in(const string & strDevice)
      {
         
//         if(strDevice == "core_midi:DLS Synth")
//         {
//            
//            return __create_new<my_message_in>();
//            
//         }
         
         auto iPort = get_midi_in_device_port(strDevice);
         
         if (iPort >= 0)
         {
            
            auto & pmessagein = m_mapMessageIn[strDevice];
            
            if (!pmessagein)
            {
               
               auto pmidiin = __new(message_in(this, maximum(0, (int) iPort)));
               
               pmessagein = pmidiin;
               
            }
            
            return pmessagein;
            
         }
         
         return nullptr;
         
      }

         
         ::pointer < ::music::midi::midi > midi::get_device_midi(const string & strDevice)
         {

            string strEngine = device_engine(strDevice);

            if (m_strName.case_insensitive_equals(strEngine))
            {

               return this;

            }

            return ::music::midi::midi::get_device_midi(strEngine);

         }

      
         // The following is copied from: http://developer.apple.com/qa/qa2004/qa1374.html
         CFStringRef EndpointName(MIDIEndpointRef endpoint, bool isExternal)
         {
            CFMutableStringRef result = CFStringCreateMutable(nullptr, 0);
            CFStringRef str;
            
            // begin with the endpoint's name
            str = nullptr;
            MIDIObjectGetStringProperty(endpoint, kMIDIPropertyName, &str);
            if (str != nullptr) {
               CFStringAppend(result, str);
               CFRelease(str);
            }
            
            MIDIEntityRef entity = 0;
            MIDIEndpointGetEntity(endpoint, &entity);
            if (entity == 0)
               // probably virtual
               return result;
            
            if (CFStringGetLength(result) == 0) {
               // endpoint name has zero length -- try the entity
               str = nullptr;
               MIDIObjectGetStringProperty(entity, kMIDIPropertyName, &str);
               if (str != nullptr) {
                  CFStringAppend(result, str);
                  CFRelease(str);
               }
            }
            // now consider the device's name
            MIDIDeviceRef device = 0;
            MIDIEntityGetDevice(entity, &device);
            if (device == 0)
               return result;
            
            str = nullptr;
            MIDIObjectGetStringProperty(device, kMIDIPropertyName, &str);
            if (str != nullptr) {
               // if an external device has only one entity, __throw( away
               // the endpoint name and just use the device name
               if (isExternal && MIDIDeviceGetNumberOfEntities(device) < 2) {
                  CFRelease(result);
                  return str;
               } else {
                  // does the entity name already start with the device name?
                  // (some drivers do this though they shouldn't)
                  // if so, do not prepend
                  if (CFStringCompareWithOptions(str /* device name */,
                                                 result /* endpoint name */,
                                                 CFRangeMake(0, CFStringGetLength(str)), 0) != kCFCompareEqualTo) {
                     // prepend the device name to the entity name
                     if (CFStringGetLength(result) > 0)
                        CFStringInsert(result, 0, CFSTR(" "));
                     CFStringInsert(result, 0, str);
                  }
                  CFRelease(str);
               }
            }
            return result;
         }


         CFStringRef ConnectedEndpointName(MIDIEndpointRef endpoint)
         {
            CFMutableStringRef result = CFStringCreateMutable(nullptr, 0);
            CFStringRef str;
            OSStatus err;
            int i = 0;
            
            // Does the endpoint have connections?
            CFDataRef connections = nullptr;
            int nConnected = 0;
            bool anyStrings = false;
            err = MIDIObjectGetDataProperty(endpoint, kMIDIPropertyConnectionUniqueID, &connections);
            if (connections != nullptr) {
               // It has connections, follow them
               // Concatenate the names of all connected devices
               nConnected = (int) (CFDataGetLength(connections) / sizeof(MIDIUniqueID));
               if (nConnected) {
                  const SInt32 *pid = (SInt32*) CFDataGetBytePtr(connections);
                  for (i = 0; i < nConnected; ++i, ++pid) {
         #ifdef MACOS
                     MIDIUniqueID id = EndianS32_BtoN(*pid);
         #else
                     
               MIDIUniqueID id = *pid;
         #endif
                     MIDIObjectRef connObject;
                     MIDIObjectType connObjectType;
                     err = MIDIObjectFindByUniqueID(id, &connObject, &connObjectType);
                     if (err == noErr) {
                        if (connObjectType == kMIDIObjectType_ExternalSource  ||
                            connObjectType == kMIDIObjectType_ExternalDestination) {
                           // Connected to an external device's endpoint (10.3 and later).
                           str = EndpointName((MIDIEndpointRef)(connObject), true);
                           //str = EndpointName(connObject, true);
                        } else {
                           // Connected to an external device (10.2) (or something else, catch-all)
                           str = nullptr;
                           MIDIObjectGetStringProperty(connObject, kMIDIPropertyName, &str);
                        }
                        if (str != nullptr) {
                           if (anyStrings)
                              CFStringAppend(result, CFSTR(", "));
                           else anyStrings = true;
                           CFStringAppend(result, str);
                           CFRelease(str);
                        }
                     }
                  }
               }
               CFRelease(connections);
            }
            if (anyStrings)
            {

               return result;
               
            }
            
            // Here, either the endpoint had no connections, or we failed to obtain names for any of them.
            return EndpointName(endpoint, false);
         }

               
      } // namespace core_midi
   
   
   } // namespace midi


} // namespace music



