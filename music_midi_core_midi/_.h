//
//  _.h
//  music_midi_core_audio
//
//  Created by Camilo Sasuke on 2021-06-07 21:37 BRT <3ThomasBorregaardSørensen__!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#pragma once


#include "app-veriwell/multimedia/_.h"
#include <CoreMIDI/MIDIServices.h>
#define __MACOSX_CORE__


#if defined(_MUSIC_MIDI_CORE_MIDI_LIBRARY)
   #define CLASS_DECL_MUSIC_MIDI_CORE_MIDI  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_MUSIC_MIDI_CORE_MIDI  CLASS_DECL_IMPORT
#endif


namespace music
{


   namespace midi
   {

   
      namespace core_midi
      {
      
      
         class midi;
      
      
      } // namespace core_midi
   
   
   } // namespace midi


} // namespace music



