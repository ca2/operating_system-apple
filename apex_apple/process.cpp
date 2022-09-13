#include "framework.h"
#include "acme_posix/pipe.h"
//#include "apex/platform/static_start.h"
#include "process.h"


#include <sys/wait.h>
#undef USE_MISC

#include <spawn.h>

#ifdef RASPBIAN
#include <sys/types.h>
#include <unistd.h>
#endif



struct chldstatus
{

   bool m_bRet;
   int  m_iExitCode;

};

critical_section * get_pid_cs();
void init_chldstatus(int iPid);
chldstatus get_chldstatus(int iPid);


CLASS_DECL_APEX void process_get_os_priority(i32 * piOsPolicy, sched_param * pparam, ::enum_priority epriority);


namespace apex_apple
{


   process::process()
   {

   }


   process::~process()
   {

   }


   bool process::create_child_process(const ::string & pszCmdLine,bool bPiped,const ::string & pszDir, ::enum_priority epriority)
   {

      if(!::operating_system::process::create_child_process(pszCmdLine, bPiped, pszDir, epriority))
      {

         return false;

      }

      string_array straParam;

      address_array < char * > argv;

      straParam.explode_command_line(pszCmdLine, &argv);

      posix_spawnattr_t attr;

      posix_spawnattr_init(&attr);

#ifndef __APPLE__

      if(epriority != ::priority_normal && epriority != ::priority_none)
      {

         i32 iPolicy = SCHED_OTHER;

         sched_param schedparam;

         schedparam.sched_priority = 0;

         process_get_os_priority(&iPolicy,&schedparam,epriority);
         
         posix_spawnattr_setschedpolicy(&attr,iPolicy);

         posix_spawnattr_setschedparam(&attr,&schedparam);
         
      }

#endif

      posix_spawn_file_actions_t actions;

      posix_spawn_file_actions_init(&actions);

      if(bPiped)
      {

         ::acme_posix::pipe * ppipeOut = m_pipe.m_ppipeOut.cast < ::acme_posix::pipe >();

         posix_spawn_file_actions_adddup2(&actions, ppipeOut->m_fd[1],STDOUT_FILENO);

         posix_spawn_file_actions_adddup2(&actions, ppipeOut->m_fd[1],STDERR_FILENO);

         ::acme_posix::pipe * ppipeIn = m_pipe.m_ppipeIn.cast < ::acme_posix::pipe >();

         posix_spawn_file_actions_adddup2(&actions, ppipeIn->m_fd[0],STDIN_FILENO);

      }

      address_array < char * > env;

      auto envp = m_psystem->m_envp;

      string strFallback;

      if(strFallback.begins_ci("/Users/"))
      {

         index i = 0;

         int iPrevious = -1;

         const char * psz;

         while((psz = envp[i]) != nullptr)
         {
            
            if(i <= iPrevious)
            {
               
               break;
               
            }

            env.add((char *) psz);

            iPrevious = (int) i;

            i++;

         }

         env.add(nullptr);

      }

      int status = 0;

      {

         critical_section_lock synchronouslock(get_pid_cs());

         status = posix_spawn(&m_iPid,argv[0],&actions,&attr,(char * const *)argv.get_data(),env.get_data());

         init_chldstatus(m_iPid);

      }

      return status == 0;

   }


   bool process::has_exited()
   {

      int iExitCode;

#if 0

      {

         int iPid;

         iPid = waitpid(m_iPid, &iExitCode,
                        WUNTRACED
#ifdef WNOHANG
                        | WNOHANG
#endif
#ifdef WCONTINUED
                        | WCONTINUED
#endif
                       );

         if(iPid == 0)
         {

            return false;

         }
         else if(iPid == -1)
         {

            return true;

         }

      }

#else

      {

         auto chldstatus = get_chldstatus(m_iPid);

         if(!chldstatus.m_bRet)
         {

            return false;

         }

         iExitCode = chldstatus.m_iExitCode;

      }

#endif

      if(WIFEXITED(iExitCode))
      {

         m_exitstatus.m_iExitCode = WEXITSTATUS(iExitCode);

         return true;

      }
      else if(WIFSIGNALED(iExitCode))
      {

         m_exitstatus.m_iExitSignal = WTERMSIG(iExitCode);

         m_exitstatus.m_iExitCode = 0x80000000;

         return true;

      }
      else if(WIFSTOPPED(iExitCode))
      {

         m_exitstatus.m_iExitStop = WSTOPSIG(iExitCode);

         m_exitstatus.m_iExitCode = 0x80000000;

         return true;

      }

#ifdef WIFCONTINUED

      else if(WIFCONTINUED(iExitCode))
      {

         return false;

      }

#endif

      return true;

   }


   bool process::synch_elevated(const ::string & pszCmdLineParam,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut)
   {

      string_array straParam;

      address_array < char * > argv;

      if (access("/usr/bin/gksu", X_OK) != 0)
      {

         m_exitstatus.m_iExitCode = -1;

         output_error_message("gksu is not installed, please install gksu.","Please, install gksu.",e_message_box_icon_information);

         return false;

      }

      string pszCmdLine = "/usr/bin/gksu " + string(pszCmdLineParam);

      straParam.explode_command_line(pszCmdLine, &argv);

      posix_spawnattr_t attr;

      posix_spawnattr_init(&attr);

      posix_spawn_file_actions_t actions;

      posix_spawn_file_actions_init(&actions);

      int status= 0;
      
      auto envp = m_psystem->m_envp;

      {

         critical_section_lock synchronouslock(get_pid_cs());

         status = posix_spawn(&m_iPid,argv[0],&actions,&attr,(char * const *)argv.get_data(),envp);

         init_chldstatus(m_iPid);

      }

      //int status = posix_spawn(&m_iPid,argv[0],nullptr,nullptr,(char * const *)argv.get_data(),environ);

      debug_print("synch_elevated : posix_spawn return status %d", status);

      auto tickStart = ::duration::now();

      while(!has_exited() && tickStart.elapsed() < durationTimeOut)
      {

         sleep(100_ms);

      }

      //::u32 dwExitCode = 0;

      if(!has_exited())
      {

         if(pbTimeOut != nullptr)
         {

            *pbTimeOut = true;

         }

      }

      return true;

   }


} // namespace apex_apple



