//
//  media_apple.hpp
//  media_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 10/02/24.
//
#pragma once


namespace media_apple
{

   
   class CLASS_DECL_MEDIA_APPLE media_apple :
      virtual public ::particle
   {
   public:
      
     
      media_apple();
      ~media_apple() override;
      
      
      static media_apple * get(::particle * pparticle);
      
   
   };


} // namespace media_apple



