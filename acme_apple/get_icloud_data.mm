//
//  get_icloud_data.m
//  get_icloud_data
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-08-05 11:57
//  Copyright © 2024 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//  <3ThomasBorregaardSorensen!!
//

#include "get_icloud_data.h"
#include "meta_data_query_result_item.h"
NSString * ns_random_string_of_length(int len);
void ns_defer_create_folder_at_path(NSString * strFolderPath);
//::e_status ns_cloud_set_data_with_container_id(const char * psz, const char * psz_iCloudContainerIdentifier, const void * p, long l);
NSString * ns_get_folder_name(NSString * strPath, int iEatenCount = 1);

::e_status ns_defer_initialize_icloud_container_access();


@implementation get_icloud_data
    

@synthesize data = m_data;

-(id) init
{
 
   self = [ super init];
   
   m_filemanager = nil;
   
   m_strPath = nil;
   
   m_strContainerId = nil;
   
   m_iCloudURLsReady = false;
   
   m_data = nil;
   
   m_urlContainer = nil;
   
   m_url = nil;
   
   m_strDummy = nil;
   
   m_urlDummy = nil;

   m_urlQueryIndex = nil;
   
   m_urlQueryDummy = nil;
   
   m_bIndexExists = false;
   
   m_bIndexHasConflicts = false;
   
   m_strIndexDownloadStatus = nil;
   
   m_errorDownloadIndex = nil;
   
   m_bDummyExists = false;
   
   m_bDummyHasConflicts = false;
   
   m_bDummyUploaded = false;
   
   m_bThisIsFirstDeviceAndCanWriteIndexFile = false;
   
   return self;
   
}


-(e_status) getDataWithPath : (const char * ) pszPath andContainer : (const char *) pszContainerId
{
   
   m_iCloudURLsReady = FALSE;
   
   m_strPath = [ [ NSString alloc ] initWithUTF8String : pszPath ];
   
   m_strContainerId = [ [ NSString alloc ] initWithUTF8String : pszContainerId ];
   
   auto estatus = ns_defer_initialize_icloud_container_access();
   
   if(estatus.failed())
   {
      
      return estatus;
      
   }
   
   //--------------------------Get data back from iCloud -----------------------------//
   
   m_filemanager = [ [ NSFileManager alloc ] init ];
   
   id token = [ m_filemanager ubiquityIdentityToken];
   
   if (token == nil)
   {
      
      NSLog(@"ICloud Is not LogIn");
      
      return ::error_failed;
      
   }
   
   NSLog(@"ICloud Is LogIn");
   
   m_urlContainer = [ m_filemanager URLForUbiquityContainerIdentifier : m_strContainerId];
   
   m_url = [ m_urlContainer URLByAppendingPathComponent : m_strPath];
   
   // (1.)
   m_data = [ NSData dataWithContentsOfURL : m_url ];
   
   if(m_data)
   {
      
      // (2.)
      return ::success;
      
   }
   
   m_strContainerIdForFileName = [ m_strContainerId stringByReplacingOccurrencesOfString: @"." withString: @"~" ];
   
   m_strDummy = [NSString stringWithFormat:@"%@-%@.txt", m_strContainerIdForFileName, ns_random_string_of_length(64)];
   
   m_urlDummy = [ m_urlContainer URLByAppendingPathComponent : m_strDummy ];
   
   const char * szData = "Dummy File";
   
   //ns_cloud_set_data_with_container_id([m_strDummy UTF8String], pszContainerId, szData, strlen(szData));
   
   [ self _setDataAtPath : [ m_strDummy UTF8String] withData : szData ofLength: strlen(szData) ];
   
//   NSString * filePattern = [NSString stringWithFormat:@"%@-*.txt", m_strContainerIdForFileName ];
   
   self.metadataquery = [ [ NSMetadataQuery alloc] init ];

   // Before starting to query, it is required to set the search scope.
   [ self.metadataquery setSearchScopes:[NSArray arrayWithObject:NSMetadataQueryUbiquitousDataScope]];
   //[ m_metadataquery setSearchScopes:[NSArray arrayWithObject:m_urlContainer]];
   
   //auto format = @"%K LIKE %@";
   
   auto format = @"%K LIKE '*'";

   //NSPredicate * predicate = [NSPredicate predicateWithFormat: format, NSMetadataItemFSNameKey, filePattern ];
   
   NSPredicate * predicate = [NSPredicate predicateWithFormat: format, NSMetadataItemFSNameKey ];
   
   // It is also required to set a search predicate.
   [ self.metadataquery setPredicate: predicate];
   
   
   
   [ self startQuery ];
   
   while(true)
   {
    
      [NSThread sleepForTimeInterval: 1.0f];
      
      if(m_bThisIsFirstDeviceAndCanWriteIndexFile)
      {
       
         return success_none;
         
      }
      
      if([m_strIndexDownloadStatus isEqual:@"current"])
      {
         
         m_data = [ NSData dataWithContentsOfURL : m_url ];
         
         return ::success;
         
      }
      
   }
   
   return error_failed;

}

- (void) stopQuery
{

   if (self.metadataquery)
   {
     
      [ self.metadataquery disableUpdates];
      
      [ self.metadataquery stopQuery];
      
      [ [ NSNotificationCenter defaultCenter ] removeObserver : self name : NSMetadataQueryDidFinishGatheringNotification object : nil];
      
      [ [ NSNotificationCenter defaultCenter ] removeObserver : self name : NSMetadataQueryDidUpdateNotification object : nil];
      
    }
   
}

- (void)startQuery 
{
   
    //[ m_metadataquery stopQuery ];
    
    m_iCloudURLsReady = NO;
   
    //[ m_iCloudFiles removeAllObjects ];
//
//    
//    
//    _query = [self documentQuery];
    
    [ [ NSNotificationCenter defaultCenter ] addObserver:self
                                             selector:@selector(queryDidFinishGathering:)
                                                 name:NSMetadataQueryDidFinishGatheringNotification
                                               object:nil];
    
    [ [ NSNotificationCenter defaultCenter ] addObserver:self
                                             selector:@selector(queryDidUpdate:)
                                                 name:NSMetadataQueryDidUpdateNotification
                                               object:nil];
    
   [ self.metadataquery enableUpdates];
   
   m_operationqueue = [ NSOperationQueue new ];
   
   m_operationqueue.maxConcurrentOperationCount = 1;
   
   self.metadataquery.operationQueue = m_operationqueue;
   
   [ m_operationqueue addOperationWithBlock:
   ^{
      
      //[ self installCallback : pcallback];
      
      [ self.metadataquery enableUpdates ];
      
      if([ self.metadataquery startQuery])
      {
          
         NSLog(@"MetaDataQuery seems ok");
         NSLog(@"MetaDataQuery query finished?!?");

      }
      else
      {
         
         NSLog(@"MetaDataQuery failed");

      }
      
   }];
      
//   [[NSOperationQueue mainQueue] addOperationWithBlock:^{
//
//   }];
//    
   
}

- (void) queryDidUpdate: (NSNotification *) notification
{
    
   NSLog(@"in queryDidUpdate:");
    
   [ self.metadataquery disableUpdates ];
   
   [ self processResult ];
   
   [ self.metadataquery enableUpdates ];
   
}


- (void) queryDidFinishGathering: (NSNotification *) notification
{
    
   NSLog(@"in queryDidFinishGathering:");

   [ self stopQuery ];
    
   [ self processResult ];
   
   if(!m_bDummyExists || !m_bDummyUploaded)
   {
      
      [ NSThread sleepForTimeInterval: 5.0f];
    
      [ self startQuery ];
      
   }
   
}


- (void) processResult
{
   
   auto results = [ self.metadataquery results ];
   
   auto resultCount = [ results count ];
    
   NSLog(@"in processResult:");
   
   for (unsigned long ulResult = 0; ulResult < resultCount; ulResult++)
   {

      //    [self logAllCloudStorageKeysForMetadataItem:result];
      
      NSMetadataItem * result = [ results objectAtIndex: ulResult ];
      
      NSNumber * hidden = nil;
      NSURL * fileURL = [result valueForAttribute:NSMetadataItemURLKey];
      BOOL success = [fileURL getResourceValue:&hidden forKey:NSURLIsHiddenKey error:nil];
      BOOL isHidden = (success && [hidden boolValue]);
        
      NSNumber *isDirectory;
      success = [fileURL getResourceValue:&isDirectory forKey:NSURLIsDirectoryKey error:nil];
      BOOL isDir = (success && [isDirectory boolValue]);
        
      if (!isHidden && !isDir)
      {

         NSString * strName= [ fileURL lastPathComponent ];
          
         NSString* prefix = [ NSString stringWithFormat:@"%@-", m_strContainerIdForFileName ];

         if([ strName hasPrefix : prefix ])
         {
             
            auto strSuffix = [ strName substringFromIndex : prefix.length ];
             
            if([ strSuffix isEqual : m_strPath ])
            {
                
               m_urlQueryIndex = fileURL;
                
               m_bIndexExists = true;
                
               id downloadStatus = [ result valueForAttribute : NSMetadataUbiquitousItemDownloadingStatusKey ];
                
               NSString * strDownloadStatus = downloadStatus != nil ? [downloadStatus stringValue] : nil;
                
               if(!strDownloadStatus)
               {
                   
                  m_strIndexDownloadStatus = nil;
                   
               }
               else if([ strDownloadStatus isEqual : NSMetadataUbiquitousItemDownloadingStatusNotDownloaded ])
               {
                   
                  m_strIndexDownloadStatus = @"not_downloaded";
                   
                  NSError * error = nil;
                   
                  [ m_filemanager startDownloadingUbiquitousItemAtURL:m_url error:&error];
                   
                  m_errorDownloadIndex = error;
                   
               }
               else if([ strDownloadStatus isEqual : NSMetadataUbiquitousItemDownloadingStatusDownloaded ])
               {
                   
                  m_strIndexDownloadStatus = @"downloaded";
                   
               }
               else if([ strDownloadStatus isEqual : NSMetadataUbiquitousItemDownloadingStatusCurrent ])
               {
                   
                  m_strIndexDownloadStatus = @"current";
                   
               }
                
               NSNumber * hasConflicts = [ result valueForAttribute : NSMetadataUbiquitousItemHasUnresolvedConflictsKey ];
                
               m_bIndexHasConflicts = hasConflicts != nil ? [ hasConflicts boolValue ] : NO;
                
            }
            else if([ strName isEqual: m_strDummy ])
            {
                
               m_urlQueryDummy = fileURL;
                
               m_bDummyExists = true;
                
               id uploaded = [ result valueForAttribute : NSMetadataUbiquitousItemIsUploadedKey ];
                
               BOOL isUploaded = uploaded != nil ? [uploaded boolValue] : NO;
                
               m_bDummyUploaded = isUploaded != NO;
                
               NSNumber * hasConflicts = [ result valueForAttribute : NSMetadataUbiquitousItemHasUnresolvedConflictsKey ];
                
               m_bDummyHasConflicts = hasConflicts != nil ? [ hasConflicts boolValue ] : NO;
                
               if(!m_bDummyHasConflicts && m_bDummyUploaded)
               {
                 
                  if(!m_bIndexExists)
                  {
                      
                     m_bThisIsFirstDeviceAndCanWriteIndexFile = true;
                      
                  }
                   
               }
                
            }

         }
            
      }
       
   }
    
   m_iCloudURLsReady = YES;
    
}

     
//Method writes a string to a text file
-(void) writeToTextFile{
        //get the documents directory:
        NSArray *paths = NSSearchPathForDirectoriesInDomains
            (NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];

        //make a file name to write the data to using the documents directory:
        NSString *fileName = [NSString stringWithFormat:@"%@/textfile.txt",
                                                      documentsDirectory];
        //create content - four lines of text
        NSString *content = @"One\nTwo\nThree\nFour\nFive";
        //save content to the documents directory
        [content writeToFile:fileName
                         atomically:NO
                               encoding:NSUTF8StringEncoding
                                      error:nil];

}


//Method retrieves content from documents directory and
//displays it in an alert
-(void) displayContent{
        //get the documents directory:
        //NSArray *paths = NSSearchPathForDirectoriesInDomains
                        //(NSDocumentDirectory, NSUserDomainMask, YES);
        //NSString *documentsDirectory = [paths objectAtIndex:0];

        //make a file name to write the data to using the documents directory:
//        NSString *fileName = [NSString stringWithFormat:@"%@/textfile.txt",
//                                                      documentsDirectory];
//        NSString *content = [[NSString alloc] initWithContentsOfFile:fileName
                                                      //usedEncoding:nil
                                                             //error:nil];
        //use simple alert from my library (see previous post for details)

}


-( ::e_status) _setDataAtPath : (const char *) psz withData: (const void *) p ofLength: (long) l
{
   
   auto estatus = ns_defer_initialize_icloud_container_access();
   
   if(estatus < 0)
   {
      
      return estatus;
      
   }
   
    //Doc dir
//    NSString *documentsDirectory = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
//    NSString *filePath = [documentsDirectory stringByAppendingPathComponent:@"SampleData.zip"];
//    NSURL *u = [[NSURL alloc] initFileURLWithPath:filePath];
   
   //NSString * strContainerIdentifier = [[NSString alloc] initWithUTF8String:psz_iCloudContainerIdentifier];
   
   auto pszDataInspect = (const char *) p;
   
   NSData * data = [ [ NSData alloc ] initWithBytes : pszDataInspect length : l ];
   
   NSString * str = [ [ NSString alloc ] initWithUTF8String : psz ];
   
   //Get iCloud container URL
   //    NSURL *ubiq = [m[NSFileManager defaultManager]URLForUbiquityContainerIdentifier:strContainerIdentifier];// in place of nil you can add your container name
   //Create Document dir in iCloud container and upload/sync SampleData.zip
   
   NSURL * ubiquitousPackage = [ m_urlContainer URLByAppendingPathComponent : str ];
   
   //Mydoc = [[MyDo alloc] initWithFileURL:ubiquitousPackage];
   //Mydoc.zipDataContent = data;
   
   auto strUbiquitousPackageFolderPath = ns_get_folder_name([ubiquitousPackage path]);
   
   ns_defer_create_folder_at_path(strUbiquitousPackageFolderPath);
  
   //get the documents directory:
   NSArray * paths = NSSearchPathForDirectoriesInDomains
       (NSDocumentDirectory, NSUserDomainMask, YES);
   
   NSString * documentsDirectory = [ paths objectAtIndex : 0 ];

   //make a file name to write the data to using the documents directory:
   NSString * fileName = [NSString stringWithFormat : @"%@/%@",
                                                 documentsDirectory, str ];
   
   auto documentsFolderPath = ns_get_folder_name(fileName);
   
   ns_defer_create_folder_at_path(documentsFolderPath);

   //create content - four lines of text
   //NSString *content = @"One\nTwo\nThree\nFour\nFive";
   //save content to the documents directory
   if(![ data writeToFile : fileName atomically : NO ])
   {
    
      return error_failed;
      
   }
   
   NSURL * urlLocal = [ [ NSURL alloc ] initFileURLWithPath : fileName ];
   
   NSError * error = nil;
   
   NSError * errorErase = nil;
   
   [ m_filemanager removeItemAtURL: ubiquitousPackage error : & errorErase ];
   
   [ m_filemanager setUbiquitous : YES itemAtURL:urlLocal destinationURL:ubiquitousPackage error:&error];
   
//   [ data writeToURL : ubiquitousPackage options:  0 error: &perror ];
//   
//   NSString * strUbiquitousPackage = [ [ ubiquitousPackage absoluteURL ] absoluteString ];
//   
//   NSLog(@"Called [ NSData writeToURL ] ubiquitousPackage : %@", strUbiquitousPackage);
//   NSLog(@"Called [ NSData writeToURL ] ubiquitousPackage : %@", strUbiquitousPackage);
//
//   
////    [Mydoc saveToURL:[Mydoc fileURL] forSaveOperation:UIDocumentSaveForCreating completionHandler:^(BOOL success)
////     {
////         if (success)
////         {
////             NSLog(@"SampleData.zip: Synced with icloud");
////         }
////         else
////             NSLog(@"SampleData.zip: Syncing FAILED with icloud");
////
////     }];
//   
   return ::success;
   
}



@end



