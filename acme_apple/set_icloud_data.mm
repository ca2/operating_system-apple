//
//  set_icloud_data.mm from get_icloud_data.mm
//  set_icloud_data
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-08-05 11:57
//  Copied by Camilo Sasuke Thomas Borregaard Sørensen on 2024-08-05 22:14
//  Copyright © 2024 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//  <3ThomasBorregaardSorensen!!
//

#include "set_icloud_data.h"
NSString * ns_random_string_of_length(int len);
void ns_defer_create_folder_at_path(NSString * strFolderPath);
//::e_status ns_cloud_set_data_with_container_id(const char * psz, const char * psz_iCloudContainerIdentifier, const void * p, long l);
NSString * ns_get_folder_name(NSString * strPath, int iEatenCount = 1);

::e_status ns_defer_initialize_icloud_container_access();


@implementation set_icloud_data
    

-(id) init
{
 
   self = [ super init];
   
   return self;
   
}


-(e_status) setDataWithPath : (const char * ) pszPath andContainer : (const char *) pszContainerId data : (const void * ) p length : (unsigned long) len
{
   
   auto estatus = [ self getDataWithPath : pszPath andContainer : pszContainerId ];
   
   if(estatus.failed())
   {
    
      return estatus;
      
   }
   
   [ self _setDataAtPath : pszPath withData : p ofLength : len ];

   return ::success;

}

@end



