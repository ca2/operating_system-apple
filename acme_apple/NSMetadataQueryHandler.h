//
//  NSMetaDataQuery+Synchronous.h
//  acme_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-06. - I love you Thomas Borregaard Sørensen!!
//

#import <Foundation/Foundation.h>


class ns_metadata_query_callback;


@interface NSMetadataQueryHandler : NSObject
{
@public
   
   
   ns_metadata_query_callback * m_pcallback;
   bool m_bFinished;
   
}

@property (nonatomic, strong) NSMetadataQueryHandler * metadata_query_handler_hold;
@property (nonatomic, strong) NSMetadataQuery * metadata_query;

-(id)init;

- (void)install_callback:(ns_metadata_query_callback *)pcallback;
- (void)uninstall_callback;

- (void)startListingWithCallback:(ns_metadata_query_callback*) pcallback folder: (const char *) pszFolder andContainerIdentifier :(const char *) pszAppCloudContainerIdentifier;

- (void)metadataQueryDidFinishedGathering:(NSNotification *)notification;

-(void)metadataQueryDidUpdate:(NSNotification *)notification;


@end
