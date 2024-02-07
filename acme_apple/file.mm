//
//  file.m
//  acme_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 07/02/24.
//

#import <Foundation/Foundation.h>


char * apple_icloud_container_folder(const char * pszAppCloudContainerIdentifier)
{
   
   NSString * strContainerIdentifier = [[NSString alloc] initWithUTF8String:pszAppCloudContainerIdentifier];
   NSURL * purl =[ [ NSFileManager defaultManager ] URLForUbiquityContainerIdentifier: strContainerIdentifier ];
   
   if(!purl)
   {
      
      return nullptr;
      
   }
   NSString* path = [[purl absoluteURL] absoluteString];
   
   return strdup([path UTF8String]);

}



