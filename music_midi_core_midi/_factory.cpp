#include "framework.h"
#include "app-veriwell/multimedia/music/midi/attribute_message.h"
#include "app-veriwell/multimedia/music/midi/sequence.h"
#include "app-veriwell/multimedia/music/midi/sequencer.h"
#include "app-veriwell/multimedia/music/midi/midi_listener.h"
#include "app-veriwell/multimedia/music/midi/midi_listener_set.h"
#include "app-veriwell/multimedia/music/midi/midi.h"
#include "midi.h"
//
//
//namespace music
//{
//
//
//   namespace midi
//   {
//
//      namespace port
//      {
//
//
//      factory_exchange::factory_exchange(::aura::application * papp) :
//      ::object(papp)
//      {
//
//         System.factory().cloneable_large < sequence               >  (System.type_info < ::music::midi::sequence                  > ());
//         System.factory().cloneable_large < buffer              >  (System.type_info < ::music::midi::file::buffer                 > ());
//         System.factory().cloneable_large < sequence_thread              >  (System.type_info < ::music::midi::sequence_thread                 > ());
//         System.factory().cloneable_large < ::music::midi::port::player::player              >  (System.type_info < ::music::midi::player::player                 > ());
//         System.factory().cloneable_large < ::music::midi::port::player:: player              >  (System.type_info < ::music::midi::player::player                 > ());
//         System.factory().cloneable_large < ::music::midi::port::midi              >  (System.type_info < ::music::midi::midi               > ());
//
//      }
//
//
//      factory_exchange::~factory_exchange()
//      {
//      }
//
//      } // namespace port
//
//   } // namespace midi
//
//
//} // namespace music


__FACTORY_EXPORT void music_midi_core_midi_factory(::factory::factory * pfactory)
{

   //::music::midi::port::factory_exchange factoryexchange(papp);
   
//   pfactory->add_factory_item< ::music::midi::core_midi::sequence              , ::music::midi::sequence                  > ();
   pfactory->add_factory_item< ::music::midi::core_midi::midi              , ::music::midi::midi                  > ();
//   System.factory().cloneable_large < buffer              >  (System.type_info < ::music::midi::file::buffer                 > ());
//   System.factory().cloneable_large < sequence_thread              >  (System.type_info < ::music::midi::sequence_thread                 > ());
//   System.factory().cloneable_large < ::music::midi::port::player::player              >  (System.type_info < ::music::midi::player::player                 > ());
//   System.factory().cloneable_large < ::music::midi::port::player:: player              >  (System.type_info < ::music::midi::player::player                 > ());
//   System.factory().cloneable_large < ::music::midi::port::midi              >  (System.type_info < ::music::midi::midi               > ());


}









