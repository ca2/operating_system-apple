//
//  get_icloud_data.h
//  get_icloud_data
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-08-05 11:50
//  Copyright © 2024 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//  I love you Thomas Borregaard Sorensen!!
//
#pragma once


#import <Foundation/Foundation.h>

// https://stackoverflow.com/questions/13503194/cant-read-icloud-file-from-second-device-that-was-written-on-first-device
//      Well, I didn't give up and I now think I have an acceptable work around for this problem. The key to the solution is for the second device to be able to successfully detect the token file that was written to the ubiquity container by the first device, and not try to write the file itself.
//
//   Here are the steps that work for me:
//
//1.   Immediately try to read the token file from the container.
//2.   If successful, use the file and ignore the rest of the steps.
//3.   Otherwise, start a meta data query whose predicate will trigger on two specific file names (the token file you are trying to read and a "dummy" file).
//4.   Now write a file to the ubiquity container with the dummy file name.
//5.   As the results for the meta data query arrive, check the upload/download status for the files that it reports.
//6.   If the query ever reports seeing the token file, then this is NOT the first device and it should continue to try to read the file until successful. It may take a while, but it will eventually read it.
//7.   If the meta data query reports the dummy file as being completely uploaded and there is still no sign of the token file, then it's safe to assume this is the first device and it's now OK to write the token file.
//8.   I find it useful to wait until the status of the token file is completely uploaded before trying to use the token. Otherwise, if there are network issues, another device also starting this process may do the same thing and also think it's the first device.
//9.   It seems that the writing of the dummy file to the ubiquity container "kick starts" the meta data query enough to get it to report the existence of the token file on a second device. Without it, the meta data query never reports the existence of the token file on anything other than the first device.

//@class meta_data_query_result_item;


@interface get_icloud_data : NSObject
{
   
   NSFileManager *                                       m_filemanager;
   NSString *                                            m_strPath;
   NSString *                                            m_strContainerId;
   NSString *                                            m_strContainerIdForFileName;
   NSURL *                                               m_urlContainer;
   NSURL *                                               m_url;
   NSData *                                              m_data;
   BOOL                                                  m_iCloudURLsReady;
   NSOperationQueue *                                    m_operationqueue;
   //NSMutableArray < meta_data_query_result_item * > *    m_iCloudFiles;
   bool                                                  m_bIndexExists;
   bool                                                  m_bIndexHasConflicts;
   NSString *                                            m_strIndexDownloadStatus;
   NSError *                                             m_errorDownloadIndex;
   bool                                                  m_bDummyExists;
   bool                                                  m_bDummyHasConflicts;
   bool                                                  m_bDummyUploaded;
   bool                                                  m_bThisIsFirstDeviceAndCanWriteIndexFile;
   
   NSString *                                            m_strDummy;
   NSURL *                                               m_urlDummy;
   NSURL *                                               m_urlQueryIndex;
   NSURL *                                               m_urlQueryDummy;
   
}

@property (nonatomic, readonly) NSData * data;
@property (nonatomic, strong) NSMetadataQuery * metadataquery;
//@property (nonatomic, readonly) NSMetadataQuery * metaDataQuery;

-(e_status) getDataWithPath : (const char * ) pszPath andContainer : (const char *) pszContainerId;
-( ::e_status) _setDataAtPath : (const char *) psz withData: (const void *) p ofLength: (long) l;

@end


