//
//  music_midi_core_midi.h
//  music_midi_core_midi
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 02/08/24.
//  Copyright © 2024 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <AVFoundation/AVFoundation.h>

@interface music_midi_core_midi : NSObject

@property (class, strong, readonly) AVAudioEngine *sharedAudioEngine;

- (id)init __attribute__((unavailable("Use +[Model sharedModel] instead")));
+ (id)new __attribute__((unavailable("Use +[Model sharedModel] instead")));

@end

