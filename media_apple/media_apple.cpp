//
//  media_apple.cpp
//  media_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 10/02/24.
//
#include "framework.h"
#include "media_apple.h"
#include "acme/platform/application.h"


//void ns_av_session_initialize();


namespace media_apple
{


media_apple::media_apple()
{
   
}


media_apple::~media_apple()
{
   
   
}


void media_apple::on_initialize_particle()
{
   
   ::particle::on_initialize_particle();
   
   //ns_av_session_initialize();
   
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




