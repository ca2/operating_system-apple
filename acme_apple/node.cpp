//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/operating_system/summary.h"
#include "acme/platform/system.h"


#include "acme/_operating_system.h"

#include "acme/prototype/prototype/memory.h"
#include "acme/operating_system/ansi/_pthread.h"
//#include "acme/prototype/prototype/payload.h"

#include <dispatch/dispatch.h>
//void ns_speak(const char * psz);
//#include <libproc.h>
int apple_node_process_identifier_modules_paths(int pid, void * p, void (*callback)(void *, const char *, int ));

static void callback_modules_paths(void * p, const char * pszPath, int size)
{
   ::string strPath(pszPath, size);
   ::file::path path(strPath);
   auto ppatha = (::file::path_array *) p;
   
   ppatha->add(path);
}
int kern_max_proc();

::string apple_operating_system_store_release();
::string apple_operating_system_application_version();
void apple_operating_system_release(int & iMajor, int & iMinor, int & iPatch);


void ns_main_post(dispatch_block_t block);


void os_post_quit();


void ansios_sigchld_handler(int sig);


void apex_application_run(const char * pszAppName, const char * pszProgName);


bool ns_open_file(const char * psz);


namespace acme_apple
{


   node::node()
   {
      
      //m_pAcmePosix = this;
      
   }


   node::~node()
   {
      
   }


   int node::node_init_check(int * pi, char *** ppz)
   {
      
      return 0;
      
   }


   void node::initialize(::particle * pparticle)
   {
      
      ::acme_darwin::node::initialize(pparticle);
      
   }


   void node::install_sigchld_handler()
   {
      
      
   }


   string node::audio_get_default_implementation_name()
   {
      
      return system()->implementation_name("audio", "core_audio");
      
   }


   string node::multimedia_audio_mixer_get_default_implementation_name()
   {
      
#if defined(MACOS)
      
      return system()->implementation_name("audio_mixer", "core_audio");
      
#else
      
      return {};
      
#endif
      
   }


   string node::veriwell_multimedia_music_midi_get_default_implementation_name()
   {
      
      return system()->implementation_name("music_midi", "core_midi");
      
   }


   void node::_user_post(const ::procedure & routineParam)
   {
      
      auto routine = routineParam;
      
      ns_main_post(^{
         
         try
         {
            
            routine();
            
         }
         catch (...)
         {
            
         }
         
      });
      
      //return ::success;
      
   }


   void node::shell_open(const ::file::path & path, const ::string & strParams, const ::file::path & pathFolder)
   {
      
      ns_open_file(path);
      
   }


   ::file::path node::library_file_name(const ::scoped_string & scopedstr)
   {
      
      return "lib" + scopedstr + ".dylib";
      
   }


   ::string node::operating_system_store_release()
   {
      
      return ::apple_operating_system_store_release();
      
   }


   ::pointer <::operating_system::summary > node::operating_system_summary()
   {
      
      auto psummary = __create_new < ::operating_system::summary >();
      
      psummary->m_strSystem = "macos";
      psummary->m_strSystemFamily = "macos";
      psummary->m_strSystemBranch = "macos";
      psummary->m_strSystemRelease = operating_system_store_release();
      
      apple_operating_system_release(psummary->m_iMajor, psummary->m_iMinor, psummary->m_iPatch);
      
      if(psummary->m_iMajor > 10 || (psummary->m_iMajor == 10 && psummary->m_iMinor >= 13))
      {

         psummary->m_strStoreRelease = "13";
         
      }
      else
      {
         
         psummary->m_strStoreRelease = "12";
         
      }

      if(psummary->m_iMajor == 13)
      {

         psummary->m_strIntegrationRelease= "13";
         
      }
      else
      {
         
         psummary->m_strIntegrationRelease = "12";
         
      }

      //psummary->m_strSlashedStore = "macos/" + psummary->m_strStoreRelease;
      
      //psummary->m_strSlashedIntegration = "macos/" + psummary->m_strIntegrationRelease;

      psummary->m_strSystemAmbientRelease = "macos";
      
      //psummary->m_strSlashedIntegration = "macos";

      return psummary;
      
   }




   ::string node::operating_system_application_version()
   {
   
      return apple_operating_system_application_version();
      
   }


::file::path_array node::process_identifier_modules_paths(::process_identifier processidentifier)
{
   ::file::path_array patha;

#if defined(FREEBSD)

   int iError = 0;
#else
   int iError = apple_node_process_identifier_modules_paths((int)processidentifier, &patha, &callback_modules_paths);
#endif
   if(iError != 0)
   {
      
      throw ::exception(error_failed);
      
   }
   
   
   return patha;

}
//void node::speak(const ::scoped_string &scopedstr)
//{
//   ::string str(scopedstr);
//   ns_speak(str);
//
//   
//}


::string node::default_component_implementation(const ::scoped_string & scopedstrComponentName)
{

   if(scopedstrComponentName == "nano_speech")
   {
    
      return "avfoundation";
      
   }
   else if(scopedstrComponentName == "nano_idn")
   {
    
      return "libidn";
      
   }

   return ::acme_darwin::node::default_component_implementation(scopedstrComponentName);

}


//void node::defer_create_windowing_application_delegate(::platform::application * papplication, ::application_menu * papplicationmenu, ::application_menu_callback * papplicationmenucallback)
//{
//
//   acme_defer_create_windowing_application_delegate(papplication, papplicationmenu, papplicationmenucallback);
//   
//}


} // namespace acme_apple



