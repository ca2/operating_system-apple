// Create on 2021-03-21 20:00 <3ThomasBS_ // for Linux(question)
// Recreated on 2021-05-16 15:05 <3ThomasBS_ // for macOS
// From windowing_ios by camilo on 2022-05-11 06:20 PM <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme_directory.h"
#include "file_listing_handler.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/platform/context.h"


char * apple_icloud_container_folder(const char * psz_iCloudContainerIdentifier);


namespace acme_apple
{

   
   acme_directory::acme_directory()
   {

      //m_pplatformdir = this;

   }


   acme_directory::~acme_directory()
   {


   }


//   string acme_directory::dir_root()
//   {
//
//      return home() / ".config/ca2";
//
//   }
//
//
//   ::file::path acme_directory::get_memory_map_base_folder_path() 
//   {
//
//      return home() / ".config/ca2/memory_map";
//
//   }
//
//
////   ::file::path acme_directory::home()
////   {
////
////      return getenv("HOME");
////
////   }
//
//
//   ::file::path acme_directory::program_data()
//   {
//
//      return home() / "application";
//
//   }
//
//
//   ::file::path acme_directory::roaming()
//   {
//
//      return home() / "Library/Application Support";
//
//   }
//
//
//   ::file::path acme_directory::appdata()
//   {
//
//      return ca2roaming() / "appdata" / app_relative();
//
//   }
//
//
//   ::file::path acme_directory::public_system()
//   {
//
//      return public_root() / "system";
//
//   }
//
//
//   ::file::path acme_directory::system()
//   {
//
//      return ca2roaming() / "system";
//
//   }
//
//
//   ::file::path acme_directory::config()
//   {
//
//      return ca2roaming() / "config";
//
//   }
//
//
//   ::file::path acme_directory::local()
//   {
//
//      return ca2roaming() / "local";
//
//   }
//
//
//   ::file::path acme_directory::sensitive()
//   {
//
//   #ifdef LINUX
//
//      return "C:\\sensitive\\sensitive";
//
//   #else
//
//      return "/sensitive/sensitive";
//
//   #endif
//
//   }
//
//
//
//
//
//
//
//   string acme_directory::system_short_name()
//   {
//
//   #ifdef _UWP
//
//      return "metro";
//
//   #else
//
//      ::file::path pathSystemShortName = localconfig() / "system_short_name.txt";
//
//      return m_pacmefile->as_string(pathSystemShortName).trimmed();
//
//   #endif
//
//   }
//
//
//   ::file::path acme_directory::relative(::file::path path)
//   {
//
//      path.find_replace(":", "");
//
//      ::str::case_insensitive_ends_eat(path, ".exe");
//
//      return path;
//
//   }
//
//   #ifdef _UWP
//
//
//   ::file::path acme_directory::app_relative()
//   {
//
//      return "";
//
//   }
//
//
//   #else
//
//
//   ::file::path acme_directory::app_relative()
//   {
//
//      ::file::path path = m_psystem->m_pacmefile->module();
//
//      path = relative(path);
//
//      return path;
//
//   }
//
//
//   #endif
//
//
//
//   ::file::path acme_directory::inplace_install(string strAppId, string strPlatform, string strConfiguration)
//   {
//
//   #ifdef LINUX_DESKTOP
//
//      ::file::path path;
//
//      string strFolder;
//
//      strsize iFind = strAppId.find('/');
//
//      if (strPlatform.compare_ci("win32") == 0 || strPlatform.compare_ci("x86") == 0)
//      {
//
//         path = program_files_x86();
//
//      }
//      else
//      {
//         path = program_files_x86();
//
//
//         path = program_files();
//
//      }
//
//      if (iFind < 0)
//      {
//
//         path /= strAppId;
//
//      }
//      else
//      {
//
//         path /= strAppId.Left(iFind);
//
//         path /= strAppId.Mid(iFind + 1);
//
//      }
//
//      return path;
//
//   #elif defined(ANDROID)
//
//      return pacmedirectory->roaming();
//
//   #else
//
//      return m_psystem->m_pacmefile->module().folder(4);
//
//   #endif
//
//   }
//
//
//   ::file::path acme_directory::inplace_matter_install(string strAppId, string strPlatform, string strConfiguration)
//   {
//
//   #ifdef LINUX_DESKTOP
//
//      ::file::path path;
//
//      string strFolder;
//
//      strsize iFind = strAppId.find('/');
//
//      path = ca2roaming();
//
//      path /= "_matter";
//
//      return path;
//
//   #elif defined(ANDROID)
//
//      return pacmedirectory->roaming();
//
//   #else
//
//      return m_psystem->m_pacmefile->module().folder(4);
//
//   #endif
//
//
//   }
//
//
//   ::file::path acme_directory::install()
//   {
//
//      if (m_pathInstallFolder == nullptr || m_pathInstallFolder.is_empty())
//      {
//
//         return default_install();
//
//      }
//
//      return m_pathInstallFolder;
//
//   }
//
//
//   ::file::path acme_directory::default_install()
//   {
//
//   #ifdef ANDROID
//
//      return pacmedirectory->roaming();
//
//   #elif defined(__APPLE__)
//
//      return m_psystem->m_pacmefile->module().folder(3);
//
//   #else
//
//      return m_psystem->m_pacmepath->app_module().folder(4);
//
//   #endif
//
//   }
//
//
//   ::file::path acme_directory::beforeca2()
//   {
//
//      return file_path_folder(install());
//
//   }
//
//
//
//
//
//
//   #ifdef LINUX_DESKTOP
//
//
//   #include <Shlobj.h>
//
//
//   ::file::path acme_directory::program_files_x86()
//   {
//
//      wstring wstrModuleFolder(get_buffer, sizeof(unichar) * 8);
//
//      wstring wstrModuleFilePath(get_buffer, sizeof(unichar) * 8);
//
//      wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMFILES(X86)"));
//
//      if (wcslen(wstrModuleFilePath) == 0)
//      {
//
//         SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);
//
//      }
//
//      wstrModuleFilePath.trim_right(L"\\/");
//
//      wcscpy(wstrModuleFolder, wstrModuleFilePath);
//
//      return string(wstrModuleFolder);
//
//   }
//
//
//   ::file::path acme_directory::program_files()
//   {
//
//      wstring wstrModuleFolder(get_buffer, sizeof(unichar) * 8);
//
//      wstring wstrModuleFilePath(get_buffer, sizeof(unichar) * 8);
//
//      wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMW6432"));
//
//      if (wcslen(wstrModuleFilePath) == 0)
//      {
//
//         SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);
//
//      }
//
//      wstrModuleFilePath.trim_right(L"\\/");
//
//      wstrModuleFolder = wstrModuleFilePath;
//
//      return string(wstrModuleFolder);
//
//
//
//   }
//
//
//   #else
//
//
//   ::file::path acme_directory::program_files_x86()
//   {
//
//      ::file::path path("/opt/ca2");
//
//      return path;
//
//   }
//
//
//   ::file::path acme_directory::program_files()
//   {
//
//      ::file::path path("/opt/ca2");
//
//      return path;
//
//   }
//
//
//   #endif
//
//
//   ::file::path acme_directory::stage(string strAppId, string strPlatform, string strConfiguration)
//   {
//
//      return inplace_install(strAppId, strPlatform, strConfiguration) / "time" / time_binary_platform(strPlatform) / strConfiguration;
//
//   }
//
//
////   #ifdef LINUX
//
//
//   ::file::path acme_directory::home()
//   {
//
//      return getenv("HOME");
//
//   }
//
//
////   #endif
//
//
//   #if defined(_UWP) || defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
//
//
////   ::file::path acme_directory::bookmark()
////   {
////
////      auto psystem = m_psystem;
////
////      auto pacmedirectory = psystem->m_pacmedirectory;
////
////      return pacmedirectory->localconfig() / "bookmark";
////
////   }
//
//
//   #endif
//
//
//   #ifdef _UWP
//
//
//   ::file::path acme_directory::home()
//   {
//
//      return "";
//
//   }
//
//
//   #endif
//
//
//
//
//   void acme_directory::set_path_install_folder(const ::string & strPath)
//   {
//
//      m_pathInstallFolder = strPath;
//
//   }
//
//
//   ::file::path acme_directory::bookmark()
//   {
//
//      return localconfig() / "bookmark";
//
//   }
//
//
//
//
//
//   ::file::path acme_directory::sys_temp()
//   {
//
//      return appdata() / "time";
//
//   }
//
//
//   //::string acme_directory::dir_root()
//   //{
//
//   //   return "";
//
//   //}
//
//
//   //::file::path acme_directory::home()
//   //{
//
//   //   return "";
//
//   //}
//
//
//   //::file::path acme_directory::program_data()
//   //{
//
//   //   return "";
//
//   //}
//
//
//   ::file::path acme_directory::ca2appdata()
//   {
//
//      return ca2roaming() / "appdata";
//
//   }
//
//
//
//   ::file::path acme_directory::public_root()
//   {
//
//      return program_data() / "ca2";
//
//   }
//
//   ::file::path acme_directory::ca2roaming()
//   {
//
//      return roaming() / "ca2";
//
//   }
//
//
//   ::file::path acme_directory::localconfig()
//   {
//
//      return ca2roaming() / "localconfig";
//
//   }
//
//
//   ::file::path acme_directory::module()
//   {
//
//      return ::acme_directory::module();
//
//   }
//
//   //
//   //::file::path acme_directory::base_module()
//   //{
//   //
//   //   return "";
//   //
//   //}
//   //
//
//   //::file::path acme_directory::ca2_module()
//   //{
//   //
//   //   return "";
//   //
//   //}
//   //
//   ::file::path acme_directory::archive()
//   {
//
//      return "";
//
//   }
//
//
//
//   ::file::path acme_directory::tool()
//   {
//
//      return "";
//
//   }
//
//
//   //::file::path acme_directory::roaming()
//   //{
//
//   //   return "";
//
//   //}
//
//
//   ::file::path acme_directory::pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode)
//   {
//
//      ::file::path_array stra;
//
//      stra.add_tokens(pszEnv, ":", false);
//
//      string strCandidate;
//
//      for (i32 i = 0; i < stra.get_count(); i++)
//      {
//
//         strCandidate = stra[i] / pszTopic;
//
//         //if (m_pcontext->m_papexcontext->file().exists(strCandidate))
//         if (file_exists(strCandidate))
//         {
//
//            return strCandidate;
//
//         }
//
//      }
//
//      return "";
//
//   }
//
//
//   //::file::path acme_directory::get_memory_map_base_folder_path()
//   //{
//
//   //   return "";
//
//   //}
//
//
//   ::file::path acme_directory::user_appdata_local()
//   {
//
//      //return _shell_get_special_folder_path(CSIDL_LOCAL_APPDATA);
//
//      return home() / ".config";
//
//   }


   bool acme_directory::has_icloud_container(const char * psz_iCloudContainerIdentifier)
   {
      
      ::string str_iCloudContainerIdentifier;
      
      str_iCloudContainerIdentifier = acmepath()->icloud_container_identifier(psz_iCloudContainerIdentifier);
      
      auto p = apple_icloud_container_folder(str_iCloudContainerIdentifier);
      
      if(::is_set(p))
      {
         
         ::free(p);
         
         return true;
         
      }
      
      return false;
   //   if(acmedirectory()->has_icloud_container())
   //   {
   //
   //      ::file::path & path = listing.insert_at(0, "icloud://");
   //
   //      path.m_iDir = 1;
   //
   //      listing.m_straTitle.insert_at(0, unitext("iCloud"));
   //
   //   }

      
   }


   bool acme_directory::defer_enumerate_protocol(::file::listing& listing)
   {
      
      ::file::path pathFinal = listing.m_pathFinal;
      
      if(pathFinal.is_empty())
      {
         
         pathFinal = m_pcontext->defer_process_path(listing.m_pathUser);
         
      }
      
      if(pathFinal.begins_eat("icloud://"))
      {
         
         if(has_icloud_container())
         {
         
            const char * pend = nullptr;
         
            auto pathServer = pathFinal.get_word("/", &pend);
         
            if(pathServer.is_empty())
            {
               
               
               ::file::path path;
               
               listing.m_pathUser = icloud_container2();
               
               if(listing.m_eflag == 0)
               {
                  
                  listing.m_eflag = ::file::e_flag_file_or_folder;
                  
               }
               
               listing.m_pathUser.m_iDir = 1;
               
               ::string str_iCloudContainerIdentifier;
               
               acmepath()->icloud_container_identifier(str_iCloudContainerIdentifier);

               listing.m_pathFinal = ::apple_icloud_container_folder(str_iCloudContainerIdentifier);
               
               listing.m_pathFinal.m_iDir = 1;

               path = listing.m_pathFinal;
               
               path.m_iDir = 1;
               
               listing.defer_add(path);
               
            }
            else
            {
               
               auto strPath = pathServer;
               
               if(strPath.begins_eat(pathServer))
               {
                  
                  strPath.trim_left("/");
                  
                  if(!m_pfilelistinghandler_iCloudContainer)
                  {
                     
                     auto pfilelistinghandler = __create_new < ::acme_apple::file_listing_handler >();
                     
                     ::string str_iCloudContainerIdentifier;
                     
                     str_iCloudContainerIdentifier = pathServer;
                     
                     ::string strFolder;
                     
                     pfilelistinghandler->start_populating(str_iCloudContainerIdentifier);
                     
                     m_pfilelistinghandler_iCloudContainer = pfilelistinghandler;
                     
                  }
                  
                  return m_pfilelistinghandler_iCloudContainer->enumerate(listing);
//                  strFolder = strPath;
//                  
//                  
//                  //            ::string_array stra;
//                  //
//                  //            stra.c_add(ppsza);
//                  //
//                  //            for(auto & str:stra)
//                  //            {
//                  //
//                  //               ::file::path path;
//                  //
//                  //               path = str;
//                  //               listing.defer_add(path);
//                  //
//                  //            }
                  
               }
               
            }
            
         }
         
      }
      
      return ::acme_directory::defer_enumerate_protocol(listing);
      
   }




} // namespace acme_app



   
