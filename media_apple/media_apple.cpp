//
//  media_apple.cpp
//  media_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 10/02/24.
//
#include "framework.h"
#include "media_apple.h"
#include "acme/platform/application.h"


namespace media_apple
{


media_apple::media_apple()
{
   
}


media_apple::~media_apple()
{
   
   
}


media_apple * media_apple::get(::particle * pparticle)
{
   
   ::pointer < ::media_apple::media_apple > pmediaapple = pparticle->application()->payload("media_apple").cast < ::media_apple::media_apple >();
   
   if(pmediaapple)
   {
    
      return pmediaapple;
      
   }
   
   pparticle->__construct(pmediaapple);
   
   pparticle->application()->payload("media_apple") = pmediaapple;
   
   return pmediaapple;

}


} // namespace media_apple




