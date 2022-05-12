//
//  resource.cpp
//  acme_apple
//
//  Created by Camilo Sasuke on 2021-05-13 20:45 BRT <3ThomasBS_!!
//

#include "framework.h"


string apple_get_bundle_identifier();

string executable_get_app_id()
{

   return apple_get_bundle_identifier();

}


char * ns_get_bundle_identifier();


#ifdef __APPLE__


string apple_get_bundle_identifier()
{

   return ::string_from_strdup(ns_get_bundle_identifier());

}


#endif

