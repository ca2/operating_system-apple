//
//  NSMetaDataQuery+Synchronous.h
//  acme_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-06. - I love you Thomas Borregaard Sørensen!!
//

#import <Foundation/Foundation.h>


class ns_metadata_query_callback;


@interface NSMetadataQueryWithCallback : NSMetadataQuery
{
@public
   
   
   ns_metadata_query_callback * m_pcallback;
   bool m_bFinished;
   
}



- (void)install_callback:(ns_metadata_query_callback *)pcallback;
- (void)uninstall_callback;

- (void)startListingWithCallback:(ns_metadata_query_callback*) pcallback folder: (const char *) pszFolder andContainerIdentifier :(const char *) pszAppCloudContainerIdentifier;

@property (nonatomic, strong) NSMetadataQuery * queryHold;

- (void)metadataQueryDidFinishedGathering:(NSNotification *)notification;

-(void)metadataQueryDidUpdate:(NSNotification *)notification;


@end
