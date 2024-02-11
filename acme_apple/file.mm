//
//  file.m
//  acme_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 07/02/24.
//

#import <Foundation/Foundation.h>


char * apple_icloud_container_folder(const char * psz_iCloudContainerIdentifier)
{
   
   NSString * strContainerIdentifier = [[NSString alloc] initWithUTF8String:psz_iCloudContainerIdentifier];
   NSURL * purl =[ [ NSFileManager defaultManager ] URLForUbiquityContainerIdentifier: strContainerIdentifier ];
   
   if(!purl)
   {
      
      return nullptr;
      
   }
   NSString* path = [[purl absoluteURL] absoluteString];
   
   return strdup([path UTF8String]);

}



