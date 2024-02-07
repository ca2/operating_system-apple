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
   NSString * m_strBasePath;
   
}

@property (nonatomic, strong) NSMetadataQueryHandler * metadata_query_handler_hold;
@property (nonatomic, strong) NSMetadataQuery * metadata_query;

-(id)init;

- (void)installCallback:(ns_metadata_query_callback *)pcallback;
- (void)uninstallCallback;

- (void)startMetadataQueryWithCallback:(ns_metadata_query_callback*) pcallback andAppCloudContainerIdentifier :(const char *) pszAppCloudContainerIdentifier;

- (void)metadataQueryDidFinishedGathering:(NSNotification *)notification;

-(void)metadataQueryDidUpdate:(NSNotification *)notification;

- (NSString *)calculateBasePathWithCallback:(ns_metadata_query_callback*) pcallback andAppCloudContainerIdentifier: (const char *) pszAppCloudContainerIdentifier;

@end
