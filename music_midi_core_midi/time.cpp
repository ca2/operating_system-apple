//
//  time.cpp
//  music_midi_core_midi
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 10/08/20.
//  Copyright © 2020 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"

#include <mach/mach_time.h>

namespace music
{


   namespace midi
   {
      
      
      namespace core_midi
      {

      
         static mach_timebase_info_data_t sTimebaseInfo;

      
         void mach_init_timebase()
         {
      
            mach_timebase_info(&sTimebaseInfo);
            
         }

         unsigned long long nano_to_absolute(unsigned long long nano)
         {
            
            return nano * sTimebaseInfo.denom / sTimebaseInfo.numer;
            
         }

   
      }
 
   
   } // namespace midi


} // namespace music



