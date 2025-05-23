//
//  media_player.cpp
//  media_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-10 22:21.
//
#include "framework.h"
#include "media_player.h"
#include "media_item.h"
#include "aqua/multimedia/media_player_command.h"

#include <dispatch/dispatch.h>


void ns_main_post(dispatch_block_t block);

void apple_play_media_item(void * pMPMediaItem);


namespace media_apple
{


   media_player::media_player()
   {
      
      
   }


   media_player::~media_player()
   {
      
      
   }


   void media_player::OnHappening(::aqua::enum_player_happening ehappening, ::aqua::media_player_command * pcommand)
   {
   
      switch(ehappening)
      {
//         case ::aqua::e_player_happening_:
//         {
//            
//            
//         }
//            break;
         case ::aqua::e_player_happening_play:
         {
//            apple_play_media_item(m_pmediaitem->m_pplatformmediaitem);
            
         }
            break;
         default:
            break;
      };
      
   }

void media_player::post_command(::aqua::media_player_command* pcommand)
{
   
   pcommand->increment_reference_count();
 ns_main_post(^()
               {
    
    player_command_procedure(pcommand);
    pcommand->release();
    
 });

}

} // namespace media_apple



