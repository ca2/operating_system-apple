//
//  NSMetaDataQuery+Synchronous.m
//  acme_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-06. - I love you Thomas Borregaard Sørensen!!
//

#import "NSMetadataQueryHandler.h"
#include "ns_metadata_query_callback.h"
#include "acme/constant/status.h"

enum_status ns_defer_initialize_icloud_access();


@implementation NSMetadataQueryHandler

-(id)init
{
   
   self = [super init];

   m_bFinished = false;
   
   
   return self;
   
}


- (void)install_callback:(ns_metadata_query_callback *) pcallback
{
   
   m_pcallback = pcallback;
   
   void * p = (__bridge_retained void *) self;
   
   m_pcallback->m_pNSMetadataQueryHandler = (void *) p;
   
   NSMetadataQuery * pquery = self.metadata_query;
   
   [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(metadataQueryDidFinishedGathering:) name:NSMetadataQueryDidFinishGatheringNotification object:pquery];
   
   [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(metadataQueryDidUpdate:) name:NSMetadataQueryDidUpdateNotification object:pquery];

}


- (void)metadataQueryDidFinishedGathering:(NSNotification *)notification
{
   
   //[ self metadataQueryDidUpdate : notification ];
   
   //[self stopQuery];
   
   m_bFinished = true;
   
   NSLog(@"NSMetadataQueryWithCallback metadataQueryDidFinishedGathering!!!");
   NSLog(@"NSMetadataQueryWithCallback metadataQueryDidFinishedGathering!!");
   
}


-(void)uninstall_callback
{
   
   [[NSNotificationCenter defaultCenter] removeObserver:self name:NSMetadataQueryDidFinishGatheringNotification object:self.metadata_query];

   [[NSNotificationCenter defaultCenter] removeObserver:self name:NSMetadataQueryDidUpdateNotification object:self.metadata_query];
   
   m_pcallback->ns_metadata_query_callback_finished();
   
   self.metadata_query = nil;
   
   m_pcallback = nullptr;

}


-(void)metadataQueryDidUpdate:(NSNotification *)notification
{
   
   NSMetadataQuery * pquery = self.metadata_query;
   
    [pquery disableUpdates];

   NSLog(@"NSMetadataQueryWithCallback metadataQueryDidUpdate!!!");

    // Look at each element returned by the search
    // - note it returns the entire list each time this method is called, NOT just the changes
    long resultCount = [pquery resultCount];
    for (int i = 0; i < resultCount; i++) {
        NSMetadataItem *item = [pquery resultAtIndex:i];
        [self onMetadataItem:item];
    }

    [pquery enableUpdates];
   
}


- (void)onMetadataItem:(NSMetadataItem *)item
{
   
    NSNumber *isUbiquitous = [item valueForAttribute:NSMetadataItemIsUbiquitousKey];
    NSNumber *hasUnresolvedConflicts = [item valueForAttribute:NSMetadataUbiquitousItemHasUnresolvedConflictsKey];
    NSString *downloadingStatus = [item valueForAttribute:NSMetadataUbiquitousItemDownloadingStatusKey];
    NSNumber *isDownloading = [item valueForAttribute:NSMetadataUbiquitousItemIsDownloadingKey];
    NSNumber *isUploaded = [item valueForAttribute:NSMetadataUbiquitousItemIsUploadedKey];
    NSNumber *isUploading = [item valueForAttribute:NSMetadataUbiquitousItemIsUploadingKey];
    NSNumber *percentDownloaded = [item valueForAttribute:NSMetadataUbiquitousItemPercentDownloadedKey];
    NSNumber *percentUploaded = [item valueForAttribute:NSMetadataUbiquitousItemPercentUploadedKey];
    NSURL *url = [item valueForAttribute:NSMetadataItemURLKey];
   NSURL *path = [item valueForAttribute:NSMetadataItemPathKey];
   long lPathComponentsCount = path.pathComponents.count;

    BOOL documentExists = [[NSFileManager defaultManager] fileExistsAtPath:[url path]];

    NSLog(@"isUbiquitous:%@ hasUnresolvedConflicts:%@ downloadinStatus:%@ isDownloading:%@ isUploaded:%@ isUploading:%@ %%downloaded:%@ %%uploaded:%@ pathComponentsCount:%ld, documentExists:%i - %@", isUbiquitous, hasUnresolvedConflicts, downloadingStatus, isDownloading, isUploaded, isUploading, percentDownloaded, percentUploaded, lPathComponentsCount, documentExists, url);
   
   NSString * str = [url absoluteString];
   
   m_pcallback->ns_metadata_query_callback_on_item([str UTF8String]);
   
}


- (NSURL *)create_a_nice_url_for_me_with_callback:(ns_metadata_query_callback*) pcallback folder:(const char *) pszFolder andContainerIdentifier: (const char *) pszAppCloudContainerIdentifier
{
   
   NSString * strContainerIdentifier = [ [ NSString alloc ] initWithUTF8String : pszAppCloudContainerIdentifier ];
   
   NSURL * urlContainer = [ [ NSFileManager defaultManager ] URLForUbiquityContainerIdentifier: strContainerIdentifier ];
   
   if(!urlContainer)
   {
      
      throw "failed container identifier";
      
      return nil;
      
   }
   
   NSString * strFolder = [ [ NSString alloc ] initWithUTF8String : pszFolder ];

   NSURL * urlBase;
   
   if(pcallback->m_bPublic)
   {
      
      urlBase = [urlContainer URLByAppendingPathComponent:@"Documents"];
      
   }
   else{
    
      urlBase = urlContainer;
      
   }

   NSURL * url;
   
   if([strFolder length] > 0)
   {
      
     url = [urlBase URLByAppendingPathComponent:strFolder];

   }
   else
   {
   
      url = urlBase;
   
   }

   return url;
   
}




 -(void)startListingWithCallback:(ns_metadata_query_callback*) pcallback folder: (const char *) pszFolder andContainerIdentifier: (const char *) pszAppCloudContainerIdentifier
{

   //NSURL *url = [self create_a_nice_url_for_me_with_callback : pcallback folder:pszFolder andContainerIdentifier:pszAppCloudContainerIdentifier];
   //long lPathComponentsCount = [ [ url pathComponents ] count ];
      
   //NSString * strPath = [ url path ];

   
   //   // Add a predicate for finding the documents
   //   NSString* filePattern = [ NSString stringWithFormat : @"*.%@", @"*" ];
      
//      
//      NSMetadataQueryWithCallback * metadataQuery = [ [ NSMetadataQueryWithCallback alloc ] init ];
//      
   
   // Before starting to query, it is required to set the search scope.
   //arrayWithObject:NSMetadataQueryUbiquitousDataScope]];
   
   //   NSString * predicateFormat = @"((%K BEGINSWITH[cd] 'h') AND (%K BEGINSWITH %@)) AND (%K.pathComponents.@count == %d)"
   //NSString * predicateFormat = @"(%K BEGINSWITH[cd] 'h') AND (%K BEGINSWITH %@) AND (%K.pathComponents.@count == %d)";

   self.metadata_query_handler_hold = self;
   
   ns_main_async(^()
   {
      
      
      
      {
         
         id token = [[NSFileManager defaultManager] ubiquityIdentityToken];
         
         if (token == nil)
         {
            NSLog(@"ICloud Is not LogIn");
            throw "failed icloud is not login";
            
            return;
         }
         
      }
      

      NSMetadataQuery * pquery = [[NSMetadataQuery alloc] init];
      
      self.metadata_query = pquery;

      self->m_bFinished = false;
   

      NSString * predicateFormat = @"(%K like '2*.txt')";
      
      // Control the directory depth through the number of pathComponents
         
         
   //      NSPredicate * predicate = [ NSPredicate predicateWithFormat : predicateFormat,
   //                                 NSMetadataItemFSNameKey,
   //                                 NSMetadataItemPathKey,
   //                                 strPath,
   //                                 NSMetadataItemPathKey,
   //                                 lPathComponentsCount + 1 ];
      NSPredicate * predicate = [ NSPredicate predicateWithFormat : predicateFormat,
                                 NSMetadataItemFSNameKey ];

      [pquery setPredicate:predicate];
         //NSArray *dirs = [[NSArray alloc] initWithObjects:urlContainer, nil] ;

        NSArray * searchScopes = [NSArray arrayWithObject:NSMetadataQueryUbiquitousDocumentsScope];
   //   NSArray * searchScopes = [NSArray arrayWithObject:url];

         [pquery setSearchScopes:searchScopes];
      
      //[self setSearchScopes:NSMetadataQueryUbiquitousDataScope];

         NSString * sPred = [predicate predicateFormat];
         
         NSLog(@"MetaDataQuery predicateFormat %@", sPred);
         
      
      

      [ self install_callback: pcallback];
         
      if([pquery startQuery])
      {
         
         NSLog(@"MetaDataQuery seems ok");
         while( !self->m_bFinished )
          {
            [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:30]];
          }
         NSLog(@"MetaDataQuery query finished?!?");

         //CFRunLoopRun();
         
      }
      else{
         
         NSLog(@"MetaDataQuery seems nok");

      }
      
      
   });
   
}

@end


void ns_metadata_query_callback::ns_metadata_query_callback_uninstall()
{
   
   auto p = (__bridge_transfer NSMetadataQueryHandler *) m_pNSMetadataQueryHandler;
   
   [ p uninstall_callback ];
   
   
}




void ns_app_cloud_start_listing(ns_metadata_query_callback * pcallback, const char * pszFolder, const char * pszAppCloudContainerIdentifier)
{
   
   NSMetadataQueryHandler * queryhandler =
   [[NSMetadataQueryHandler alloc] init];
   
   [queryhandler startListingWithCallback:pcallback folder:pszFolder andContainerIdentifier:pszAppCloudContainerIdentifier];
   
}
