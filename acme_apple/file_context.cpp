//
// Created by camilo on 26/04/2021. 00:02 BRT <3TBS_!!
//
#include "framework.h"
#include "file_context.h"
#include "icloud_file.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/file_system_options.h"
#include "acme/platform/application.h"


enum_status ns_defer_initialize_icloud_container_access();


namespace acme_apple
{
//
//
//   ::payload file_context::length(const ::file::path &path, ::payload *pvarQuery)
//   {
//
//      if (path.m_iSize != -1)
//      {
//
//         return maximum(0, path.m_iSize);
//
//      }
//
//      ::payload payloadLength;
//
//   //#ifdef WINDOWS
//   //
//   //   WIN32_FILE_ATTRIBUTE_DATA data;
//   //
//   //   if (!GetFileAttributesExW(::str::international::utf8_to_unicode(path), GetFileExInfoStandard, &data))
//   //   {
//   //
//   //      varRet.set_type(::e_type_null);
//   //
//   //      ((::file::path &) path).m_iSize = -2;
//   //
//   //   }
//   //   else
//   //   {
//   //
//   //      varRet = (((unsigned long long) data.nFileSizeHigh) << 32) | (unsigned long long) data.nFileSizeLow;
//   //
//   //      ((::file::path &) path).m_iSize = varRet.m_hi;
//   //
//   //   }
//   //
//   //#else
//   //
//      struct stat stat;
//
//      if (::stat(path, &stat) == -1)
//      {
//
//         payloadLength.set_type(::e_type_null);
//
//         ((::file::path &) path).m_iSize = -2;
//
//      }
//      else
//      {
//
//         payloadLength = (iptr)stat.st_size;
//
//         ((::file::path &)path).m_iSize = payloadLength.m_hi;
//
//      }
//
//   //#endif
//
//      return payloadLength;
//
//   }
//

// C++ string at STL

// STL - Standard Template Library

// ::std::string


// Qt is a C++ framework

// Qt string is called QString


// MFC is Microsoft Foundation Classes (for C++)

// MFC string is called CString

// MFC wide string is called CStringW


// ATL is Microsoft Active Template Library (for C++)

// ATL string is called ATLString


// ca2 is a C++ Framework

// ca2 string is called string


   ::file_pointer file_context::defer_get_protocol_file(const ::scoped_string & scopedstrProtocol, const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception)
   {
      
      if(scopedstrProtocol == "icloud")
      {
         
         auto pfilesystemoptions = application()->m_pfilesystemoptions.get();
         
         if(pfilesystemoptions->m_b_iCloudContainer)
         {
            
            auto estatus = ns_defer_initialize_icloud_container_access();
            
            if(estatus == error_icloud_not_available)
            {
               
               application()->application_on_status(estatus);
               
               throw ::exception(estatus);
               
               return nullptr;
               
            }
            
            auto pfile = __create_new < ::acme_apple::icloud_file >();
            
            ::string strName;
            
            ::string str_iCloudContainerIdentifier;
            
            path_system()->defer_get_icloud_container_path_name(strName, str_iCloudContainerIdentifier, path);
            
            //pfile->m_pathName = "Documents";
            
            pfile->m_pathName /= strName;
            
            pfile->m_str_iCloudContainerIdentifier = str_iCloudContainerIdentifier;
            
            pfile->m_eopen = eopen;
            
            if(eopen & ::file::e_open_read)
            {
               
               auto memory = file_system()->get_app_cloud_data(pfile->m_pathName, nullptr);
               
               pfile->get_memory()->assign(memory);
               
            }
            
            return pfile;
            
         }
         else{
          
            auto pathParse = path;
            
            if(pathParse.begins_eat("icloud://Documents/"))
            {

               auto pfile = __create_new < ::acme_apple::icloud_file >();
               
               ::string strName;
               
               pfile->m_pathName = pathParse;
               
               pfile->m_str_iCloudContainerIdentifier = "Documents";
               
               pfile->m_eopen = eopen;
               
               if(eopen & ::file::e_open_read)
               {
                  
                  try {
                     
                     auto memory = file_system()->get_documents_cloud_data(pfile->m_pathName);
                     
                     pfile->get_memory()->assign(memory);
                     
                  }
                  catch(...)
                  {
                     
                  }
                  
               }
               
               return pfile;

            }
            
         }
      
      }
    
      return ::acme_posix::file_context::defer_get_protocol_file(scopedstrProtocol, path, eopen, pfileexception);
      
   }

} // namespace acme_apple




//
//::enum_status ns_defer_initialize_icloud_container_access()
//{
//   
//   __block enum_status estatus;
//   
//   ns_main_send(^{
//      
//      ::platform::get()->node()->defer_initialize_icloud_container_access();
//      iosApp * papp = (iosApp *) [[UIApplication sharedApplication] delegate];
//
//      estatus = [ papp deferInitializeiCloudContainerAccess ];
//
//   });
//   
//   return estatus;
//   
//}
