//
//  m.m
//  music_midi_core_midi
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 03/Oct/22. 03:57
//  Copyright © 2022 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#import <Foundation/Foundation.h>

CFURLRef xg_url(void);


CFURLRef xg_url()
{
   
   NSBundle * bundleMain = [ NSBundle mainBundle ];
   
   NSURL * nsurlSoundBank =  [ bundleMain URLForResource : @"Yamaha_XG_Sound_Set" withExtension: @"sf2"];
   
   CFURLRef bankURL = (__bridge_retained CFURLRef) nsurlSoundBank;
   
   return bankURL;
   
}



