//
//  m.m
//  music_midi_core_midi
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 03/Oct/22. 03:57
//  Copyright © 2022 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#include "music_midi_core_midi.h"
#include "music_midi_core_midi_instrument.h"
CFURLRef xg_url(void);


CFURLRef xg_url()
{
   
   NSBundle * bundleMain = [ NSBundle mainBundle ];
   
   NSURL * nsurlSoundBank =  [ bundleMain URLForResource : @"Yamaha_XG_Sound_Set" withExtension: @"sf2"];
   
   CFURLRef bankURL = (__bridge_retained CFURLRef) nsurlSoundBank;
   
   return bankURL;
   
}


//
//AVAudioEngine * av_audio_engine()
//{
// 
////   // Initialize the audio session
////   AVAudioSession *audioSession = [AVAudioSession sharedInstance];
////   NSError *error = nil;
////   [audioSession setCategory:AVAudioSessionCategoryPlayback error:&error];
////   if (error) {
////       NSLog(@"Error setting category: %@", error.localizedDescription);
////       return -1;
////   }
////   [audioSession setActive:YES error:&error];
////   if (error) {
////       NSLog(@"Error activating audio session: %@", error.localizedDescription);
////       return -1;
////   }
//
//   // Setup the audio engine
//   AVAudioEngine *audioEngine = [[AVAudioEngine alloc] init];
//   
//   return audioEngine;
//   
//}


// Helper function to set up AVAudioEngine and MIDI instrument
CFTypeRef get_a_soft_midi_synthesizer()
{
    AudioComponentDescription instrumentACD = {0};
    instrumentACD.componentType = kAudioUnitType_MusicDevice;
    
    //NSMutableArray<NSDictionary<NSString *, id> *> *instrumentComponents = [NSMutableArray array];
    
    AudioComponent instrumentComponent = NULL;
    while ((instrumentComponent = AudioComponentFindNext(instrumentComponent, &instrumentACD))) {
        CFStringRef name = NULL;
        AudioComponentCopyName(instrumentComponent, &name);
        
        NSString *nameString = (__bridge_transfer NSString *)name;
       
       auto psz = [nameString UTF8String];
       
       if(!strcmp(psz, "MakeMusic: SmartMusicSoftSynth")
          || !strcmp(psz, "Apple: AUMIDISynth")
          || !strcmp(psz, "Apple: DLSMusicDevice"))
       {
          
          AudioComponentDescription compDescr;
          
          AudioComponentGetDescription(instrumentComponent, &compDescr);
          
          music_midi_core_midi_instrument * instrumentAU = [[music_midi_core_midi_instrument alloc] initWithAudioComponentDescription:compDescr];
          
          AVAudioEngine *audioEngine = [music_midi_core_midi sharedAudioEngine];
          
          [audioEngine attachNode:instrumentAU];
          
          auto mainMixerNode = [ audioEngine mainMixerNode ];
          
          [audioEngine connect:instrumentAU to:mainMixerNode format:nil];
          
          //[ audioEngine startAndReturnError:nil];

          return CFBridgingRetain(instrumentAU);
          
       }
    }
   
   return {};
   
}


void music_midi_core_midi_start_audio_engine()
{
   
   AVAudioEngine *audioEngine = [music_midi_core_midi sharedAudioEngine];
   
   [ audioEngine startAndReturnError:nil];
   
}


void music_midi_core_midi_instrument_set_callback(CFTypeRef pAVAudioUnitMIDIInstrument, AUDIO_UNIT_RENDER_CALLBACK_FUNCTION_POINTER callback, void * objectCallback )
{
 
   music_midi_core_midi_instrument * pinstrument = (__bridge music_midi_core_midi_instrument *)pAVAudioUnitMIDIInstrument;

   [pinstrument setRenderCallback:callback withObject:objectCallback];
   
}

AudioUnit AVAudioUnitMIDIInstrument_audioUnit(CFTypeRef pAVAudioUnitMIDIInstrument)
{
   
   music_midi_core_midi_instrument * pinstrument = (__bridge music_midi_core_midi_instrument *)pAVAudioUnitMIDIInstrument;
   
   return [pinstrument audioUnit];
   
}

void AVAudioUnitMIDIInstrument_sendMIDIEvent(CFTypeRef pAVAudioUnitMIDIInstrument, int event, int track, int b1)
{
   
   music_midi_core_midi_instrument * pinstrument = (__bridge music_midi_core_midi_instrument *)pAVAudioUnitMIDIInstrument;
   
   [pinstrument sendMIDIEvent:track | event data1:b1];
   
}


void AVAudioUnitMIDIInstrument_startNote(CFTypeRef pAVAudioUnitMIDIInstrument, int note, int velocity, int channel)
{
   
   music_midi_core_midi_instrument * pinstrument = (__bridge music_midi_core_midi_instrument *)pAVAudioUnitMIDIInstrument;

   [pinstrument startNote: note withVelocity:velocity onChannel: channel];
   
}


void AVAudioUnitMIDIInstrument_stopNote(CFTypeRef pAVAudioUnitMIDIInstrument, int note, int channel)
{
   
   music_midi_core_midi_instrument * pinstrument = (__bridge music_midi_core_midi_instrument *)pAVAudioUnitMIDIInstrument;
   
   [pinstrument stopNote: note onChannel: channel];
   
}


void AVAudioUnitMIDIInstrument_sendMIDIEvent(CFTypeRef pAVAudioUnitMIDIInstrument, int event, int track, int b1, int b2)
{
   
   music_midi_core_midi_instrument * pinstrument = (__bridge music_midi_core_midi_instrument *)pAVAudioUnitMIDIInstrument;

   [pinstrument sendMIDIEvent:track | event data1:b1 data2:b2];
   
}


void AVAudioUnitMIDIInstrument_sendProgramChange(CFTypeRef pAVAudioUnitMIDIInstrument, int program, int channel)
{
   
   music_midi_core_midi_instrument * pinstrument = (__bridge music_midi_core_midi_instrument *)pAVAudioUnitMIDIInstrument;

   [pinstrument sendProgramChange:program onChannel:channel];
   
}



char * ns_format_osstatus(OSStatus osstatus)
{
   NSString* ErrMsg = (__bridge_transfer NSString *) SecCopyErrorMessageString(osstatus, NULL);
   
   if(!ErrMsg)
   {
    
      return nullptr;
      
   }
   return strdup([ErrMsg UTF8String]);
   
}
