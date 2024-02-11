//
//  media_item.hpp
//  media_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 09/02/24.
//
#pragma once


#include "aqua/multimedia/media_item.h"


namespace media_apple
{


   class CLASS_DECL_MEDIA_APPLE media_item :
   virtual public ::aqua::media_item
   {
   public:
      
      
      media_item();
      ~media_item() override;
      
      ::aqua::enum_media_type get_media_type() override;

      void assign_media_player() override;
      
      
   };


} // namespace media_apple
