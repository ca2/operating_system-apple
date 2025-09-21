//
//  media_item.cpp
//  media_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 09/02/24.
//
#include "framework.h"
#include "media_item.h"
#include "media_player.h"


namespace media_apple
{


   media_item::media_item()
   {
      
   }


   media_item::~media_item()
   {
      
   }


   ::aqua::enum_media_type media_item::get_media_type()
   {
      
      return ::aqua::e_media_type_opaque_audio;
      
   }


   void media_item::assign_media_player()
{
      
      m_pmediaplayer = øallocate ::media_apple::media_player();
      
      m_pmediaplayer->initialize(this);
      
   }

} //namespace media_apple

