//
//  av_speech_synthesis.m
//  acme_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-05-11 23:00
// <3ThomasBorregaardSorensen!!
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <AVFoundation/AVFoundation.h>

#import "av_speech.h"

@implementation av_speech

+ (instancetype) shared
{
   
   static id s_av_speech = nil;
   
   static dispatch_once_t s_dispatchonce;
   
   dispatch_once(&s_dispatchonce,
                 
                 ^{
//      [[AVAudioSession sharedInstance ] setCategory:AVAudioSessionCategoryPlayback]
      self.synthesis=[[AVSpeechSynthesizer alloc] init];
      self.voice = [AVSpeechSynthesisVoice voiceWithLanguage:@"en-us"];
      self.utterancea=[[NSMutableArray alloc]init];
                     s_av_speech = [[self alloc] init];
       
                  }
                 
                 );
   
   return s_av_speech;
   
}

@end


void av_speech_synthesizer_speak(const char * psz)
{
   
   auto psynthesizer = [ [ av_speech shared ] synthesizer ];
   
   NSString * str=[[NSString alloc]initWithUTF8String:psz];
   
   AVSpeechUtterance *utterance =
   [[AVSpeechUtterance alloc] initWithString:str];
   
   
   utterance.voice = voice;
   
   [ psynthesizer speakUtterance: utterance ];
   
}
