//
//  music_midi_core_midi.m
//  music_midi_core_midi
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 02/08/24.
//  Copyright © 2024 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "music_midi_core_midi.h"



@implementation music_midi_core_midi


// Class method to access the shared instance
+ (AVAudioEngine *)sharedAudioEngine {
   
   static id s_sharedAudioEngine = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
       s_sharedAudioEngine = [[AVAudioEngine alloc] init];
       
       ///[ s_sharedAudioEngine setup
    });
    return s_sharedAudioEngine;
}

@end
