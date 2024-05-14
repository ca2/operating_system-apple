//
//  av_speech_synthesis.h
//  acme_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-05-11 23:46 <3ThomasBorregaardSorensen!!
//

//  Model.h


#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#include "acme/constant/gender.h"


@interface ns_speaker : NSObject


- (void) speakText:(const char *_Nonnull)pszText withPreferredLanguage:(const char *_Nullable) pszLang andWithPreferredGender: (enum_gender) egender;



- (AVSpeechSynthesisVoice * _Nullable) findVoiceWithLanguage: (const char *_Nullable) pszLang andWithGender: (enum_gender) egender;

- (AVSpeechSynthesisVoice *_Nullable) getVoicePreferablyWithLanguage: (const char *_Nullable) pszLang withPreferredGender: (enum_gender) egender;




- (id _Nonnull )init __attribute__((unavailable("Use +[av_speech shared] instead")));
+ (id _Nonnull )new __attribute__((unavailable("Use +[av_speech shared] instead")));

@property (class, strong, readonly) ns_speaker * _Nonnull shared;
@property (nonatomic, retain,nullable) AVSpeechSynthesizer *synthesizer;
//@property (nonatomic, retain, nullable) AVSpeechSynthesisVoice *voice;
@property (nonatomic, retain, nullable) NSMutableArray *utterancea;

@end

