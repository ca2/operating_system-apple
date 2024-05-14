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

#import "ns_speaker.h"



@implementation ns_speaker



+ (instancetype) shared
{
   
   static id s_pspeaker = nil;
   
   static dispatch_once_t s_dispatchonce;
   
   dispatch_once(&s_dispatchonce,
                 
                 ^{
//      [[AVAudioSession sharedInstance ] setCategory:AVAudioSessionCategoryPlayback]
      ns_speaker * pspeaker = [ ns_speaker alloc ];
      pspeaker.synthesizer=[[AVSpeechSynthesizer alloc] init];
      //pspeaker.voice = av_speech_get_voice("en-us", true);
      pspeaker.utterancea=[[NSMutableArray alloc]init];

      s_pspeaker = pspeaker;
                  }
                 
                 );
   
   return s_pspeaker;
   
}
   
- (void) speakText:(const char *_Nonnull)pszText withPreferredLanguage:(const char *_Nullable) pszLang andWithPreferredGender: (enum_gender) egender;
{
   
   NSString * strText=[[NSString alloc]initWithUTF8String:pszText];
   
   AVSpeechUtterance *utterance =
   [[AVSpeechUtterance alloc] initWithString:strText];
   
   AVSpeechSynthesisVoice * voice = [self getVoicePreferablyWithLanguage: pszLang withPreferredGender: egender ];
   
   utterance.voice = voice;
   
   [self.utterancea addObject:utterance];
   
   [self.synthesizer speakUtterance: utterance ];
   
}


- (AVSpeechSynthesisVoice * _Nullable) findVoiceWithLanguage: (const char *_Nullable) pszLang andWithGender: (enum_gender) egender
{
   
   NSString * strLang = [[NSString alloc] initWithUTF8String:pszLang];
   
   for (AVSpeechSynthesisVoice *voice in [AVSpeechSynthesisVoice speechVoices])
   {
      
      NSLog(@"Language: %@", voice.language);
      NSLog(@"Gender: %@", (voice.gender ==AVSpeechSynthesisVoiceGenderMale?@"male":@"(alien)"));
      
      if([voice.language caseInsensitiveCompare:strLang] == NSOrderedSame)
      {
         
         if(egender == e_gender_male)
         {
            
            if(voice.gender == AVSpeechSynthesisVoiceGenderMale)
            {
               
               return voice;
               
            }
            
         }
         else if(egender == e_gender_female)
         {
            
            if(voice.gender == AVSpeechSynthesisVoiceGenderFemale)
            {
               
               return voice;
               
            }
            
         }
         else
         {
            
            return voice;
            
         }
         
      }
      
   }
   
   return nil;
   
}


- (AVSpeechSynthesisVoice *) getVoicePreferablyWithLanguage: (const char *) pszLang withPreferredGender: (enum_gender) egender
   {
      
      AVSpeechSynthesisVoice * voice = [self findVoiceWithLanguage: pszLang andWithGender: egender];
      
      if(voice) return voice;
      
      voice = [self findVoiceWithLanguage: pszLang andWithGender: e_gender_none];
      
      if(voice) return voice;
      
      if(!stricmp(pszLang, "en-us")) return nil;

      voice = [self findVoiceWithLanguage: "en-us" andWithGender: egender];
      
      if(voice) return voice;
      
      voice = [self findVoiceWithLanguage: "en-us" andWithGender: e_gender_none];
      
      if(voice) return voice;
      
      return nil;

   }

@end


void ns_speak(const char * psz, const char * pszLang, enum_gender egender)
{
   
   [ [ ns_speaker shared ] speakText :psz  withPreferredLanguage:pszLang andWithPreferredGender: egender];
   

}



  
