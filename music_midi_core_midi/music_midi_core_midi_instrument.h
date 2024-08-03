//
//  music_midi_core_midi_instrument.h
//  music_midi_core_midi
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 02/08/24.
//  Copyright © 2024 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#pragma once

#import <Foundation/Foundation.h>

#import <AVFoundation/AVFoundation.h>



typedef OSStatus AUDIO_UNIT_RENDER_CALLBACK(void* inRefCon, AudioUnitRenderActionFlags* ioActionFlags, const AudioTimeStamp* inTimeStamp,
                               UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList* ioData);

using AUDIO_UNIT_RENDER_CALLBACK_FUNCTION_POINTER = AUDIO_UNIT_RENDER_CALLBACK *;

@interface music_midi_core_midi_instrument : AVAudioUnitMIDIInstrument
{
   
   AUDIO_UNIT_RENDER_CALLBACK_FUNCTION_POINTER m_callback;
   void * m_objectCallback;
   
}

-(void) setRenderCallback:(AUDIO_UNIT_RENDER_CALLBACK_FUNCTION_POINTER) callback withObject: (void*) objectCallback;

@end


