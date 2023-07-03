//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/operating_system/summary.h"
#include "acme/platform/system.h"


#include "acme/_operating_system.h"

#include "acme/primitive/primitive/memory.h"
#include "acme/operating_system/ansi/_pthread.h"
//#include "acme/primitive/primitive/payload.h"

#include <dispatch/dispatch.h>

int kern_max_proc();

::string apple_operating_system_store_release();
void apple_operating_system_release(::i32 & iMajor, ::i32 & iMinor, ::i32 & iPatch);


void ns_main_async(dispatch_block_t block);


void os_post_quit();


void ansios_sigchld_handler(int sig);


void apex_application_run(const char * pszAppName, const char * pszProgName);


bool ns_open_file(const char * psz);


namespace acme_apple
{


node::node()
{
   
   m_pAcmePosix = this;
   
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
   
   return acmesystem()->implementation_name("audio", "core_audio");
   
}


string node::multimedia_audio_mixer_get_default_implementation_name()
{
   
   return acmesystem()->implementation_name("audio_mixer", "core_audio");
   
}


string node::veriwell_multimedia_music_midi_get_default_implementation_name()
{
   
   return acmesystem()->implementation_name("music_midi", "core_midi");
   
}


void node::node_post(const ::procedure & routineParam)
{
   
   auto routine = routineParam;
   
   ns_main_async(^{
      
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
   
   psummary->m_strDistro = "macos";
   psummary->m_strDistroFamily = "macos";
   psummary->m_strDistroBranch = "macos";
   psummary->m_strDistroRelease = operating_system_store_release();
   
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

   psummary->m_strSlashedStore = "macos/" + psummary->m_strStoreRelease;
   
   psummary->m_strSlashedIntegration = "macos/" + psummary->m_strIntegrationRelease;

   return psummary;
   
}



::process_identifier_array node::processes_identifiers()
{

int  iDoubleKernMaxProc = kern_max_proc() * 2;

::memory memory;

memory.set_size(sizeof(pid_t) * iDoubleKernMaxProc);

pid_t * pids = (pid_t *) memory.data();

const int pidcount = proc_listallpids(pids, (int) memory.size());

process_identifier_array a;

a.set_size(pidcount);

for(int i = 0; i < pidcount; i++)
{
   
   a[i] = pids[i];
   
}

//  throw ::exception(error_not_implemented);;
return transfer(a);

   /*
    dwa.set_size(0);
    ::u32 cbNeeded = 0;
    while(cbNeeded == natural(dwa.get_count()))
    {
    dwa.set_size(dwa.get_count() + 1024);
    if(!EnumProcesses(
    dwa.get_data(),
    (::u32) (dwa.get_count() * sizeof(::u32)),
    &cbNeeded))
    {
    return;
    }
    dwa.set_size(cbNeeded / sizeof(::u32));
    }*/
}


} // namespace acme_darwin


} // namespace acme_apple


