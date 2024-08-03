//
//  music_midi_core_midi_intrument.m
//  music_midi_core_midi
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 02/08/24.
//  Copyright © 2024 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "music_midi_core_midi_instrument.h"


@implementation music_midi_core_midi_instrument
    
-(void) setRenderCallback:(AUDIO_UNIT_RENDER_CALLBACK_FUNCTION_POINTER) callback withObject: (void*) objectCallback;
{
 
   m_callback = callback;
   m_objectCallback = objectCallback;
   
}

- (AUInternalRenderBlock)internalRenderBlock {
   
   
   return ^AUAudioUnitStatus(AudioUnitRenderActionFlags    *actionFlags,
                             const AudioTimeStamp       *timestamp,
                             AVAudioFrameCount          frameCount,
                             NSInteger             outputBusNumber,
                             AudioBufferList          *outputBufferListPtr,
                             const AURenderEvent       *realtimeEventListHead,
                             AURenderPullInputBlock       pullInputBlock ) {
   
      return self->m_callback(self->m_objectCallback, actionFlags, timestamp,(UInt32)(long)outputBusNumber, frameCount, outputBufferListPtr);
      
   };
   
   
}
       
@end
