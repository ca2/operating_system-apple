//
//  media_player.hpp
//  media_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-10 22:21.
//
#pragma once


#include "aqua/multimedia/media_player.h"


namespace media_apple
{

      
   class CLASS_DECL_MEDIA_APPLE media_player :
   virtual public ::aqua::media_player
   {
   public:
      
      
      media_player();
      ~media_player();
      
      
      void OnEvent(::aqua::enum_player_event eevent, ::aqua::media_player_command * pcommand) override;
      
      void post_command(::aqua::media_player_command* pcommand) override;

   };


} // namespace media_apple
