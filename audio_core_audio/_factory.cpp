#include "framework.h"
#include "wave_in.h"
#include "wave_out.h"


//namespace multimedia
//{
//
//
//   namespace audio_core_audio
//   {
//
//
//      factory_exchange::factory_exchange()
//      {
//
//         create_factory < in, ::wave::in >();
//         create_factory < out, ::wave::out >();
//
//      }
//
//
//      factory_exchange::~factory_exchange()
//      {
//      }
//
//
//   } // namespace audio_core_audio
//
//
//} // namespace multimedia


__FACTORY_EXPORT void audio_core_audio_factory(::factory::factory * pfactory)
{

   //::multimedia::audio_core_audio::factory_exchange factoryexchange();
   pfactory->add_factory_item < ::multimedia::audio_core_audio::in, ::wave::in >();
   pfactory->add_factory_item < ::multimedia::audio_core_audio::out, ::wave::out >();
   
}








