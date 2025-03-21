//
//  apple.cpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 21/07/17.
//
//

#include "framework.h"
#include "main.h"
//#include "apex/os/_.h"
//#include "apex/os/_os.h"
#include "acme/update.h"
//char * ns_realpath(const char * pszPath);
char * mm_ca2_command_line();


// ThomasBS-LiveEdu.TV(LiveCoding.TV)

//void * ()
//CreateDispatchQueue
//{
//
//   return dispatch_queue_create (nullptr, nullptr);
//
//}


//void CancelDispatchSource(void * p)
//{
//
//   dispatch_source_cancel((dispatch_source_t) p);
//
//}


//void * CreateDispatchTimer(unsigned long long interval, unsigned long long leeway, void * queue, void (*pfnTimer)(void * p), void * p)
//{
//
//   dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, (dispatch_queue_t) queue);
//
//   if (timer)
//   {
//
//      dispatch_source_set_timer(timer, dispatch_walltime(DISPATCH_TIME_NOW, interval * NSEC_PER_MSEC), DISPATCH_TIME_FOREVER, leeway * NSEC_PER_MSEC);
//
//      dispatch_source_set_event_handler(timer, ^() { pfnTimer(p); });
//
//      dispatch_resume(timer);
//
//   }
//
//   return timer;
//
//}
//
//
//void * ResetDispatchTimer(void * timerParam, unsigned long long interval, unsigned long long leeway)
//{
//
//   dispatch_source_t timer = (dispatch_source_t) timerParam;
//
//   if (timer)
//   {
//
//      dispatch_source_set_timer(timer, dispatch_walltime(DISPATCH_TIME_NOW, interval * NSEC_PER_MSEC), DISPATCH_TIME_FOREVER, leeway * NSEC_PER_MSEC);
//
//      //dispatch_resume(timer);
//
//   }
//
//   return timer;
//
//}
//
//
//void ReleaseDispatch(void * p)
//{
//
//   dispatch_release((dispatch_object_t) p);
//
//}


static bool g_bRunSystem = false;


int defer_run_system()
{

   if(g_bRunSystem)
   {

      return 0;

   }

   g_bRunSystem = true;

   //return __start_system_with_file(nullptr);
   
   return 0;

}

//
//int defer_run_system(const char * pszFileName)
//{
//
//   return __start_system_with_file(pszFileName);
//
//}
//
//
//int defer_run_system(char ** pszaFileName, int iFileCount)
//{
//
//   return __start_system_with_file((const char **) pszaFileName, iFileCount);
//
//}
//




void apple_on_new_file()
{

   ::apex::get_system()->on_open_file(::e_type_empty, "");

}

// iMillisDelay default 500ms good
void apple_accumulate_on_open_file(const char ** psza, int iCount, const char * pszExtra)
{

   string_array stra;

   stra.c_add((char **) psza, iCount, false);

   for(index i = 0; i < stra.get_count(); i++)
   {

      if(::str::case_insensitive_begins_eat(stra[i], "file://"))
      {

         if(!::str::begins(stra[i], "/"))
         {

            stra[i] = "/" + stra[i];

         }

         stra[i] = ::apex::get_system()->url().url_decode(stra[i]);

      }

   }

   ::apex::get_system()->defer_accumulate_on_open_file(stra, pszExtra);

}



void apple_on_open_file(const char ** psza, int iCount, const char * pszExtra)
{

   if(iCount <= 0)
   {

      apple_on_new_file();

   }
   else if(iCount == 1)
   {

      ::apex::get_system()->on_open_file(psza[0], pszExtra);

      ::free((void *) psza[0]);

      ::free(psza);

   }
   else
   {

      string_array stra;

      stra.c_add((char **) psza, iCount, false);

      ::apex::get_system()->on_open_file(stra, pszExtra);

   }

}




string ca2_command_line()
{

   return ::str::from_strdup(mm_ca2_command_line());

}



//void copy(CGPoint & pointTarget, const INT_POINT & pointSource)
//{
//
//   ppointTarget->x      = ppointSource->x;
//   ppointTarget->y      = ppointSource->y;
//
//}
//
//
//void copy(INT_POINT & pointTarget, const CGPoint & pointSource)
//{
//
//   ppointTarget->x      = ppointSource->x;
//   ppointTarget->y      = ppointSource->y;
//
//}
//
//void copy(CGPoint & pointTarget, const DOUBLE_POINT & pointSource)
//{
//
//   ppointTarget->x      = ppointSource->x;
//   ppointTarget->y      = ppointSource->y;
//
//}
//
//
//void copy(DOUBLE_POINT & pointTarget, const CGPoint & pointSource)
//{
//
//   ppointTarget->x      = ppointSource->x;
//   ppointTarget->y      = ppointSource->y;
//
//}


bool __node_further_file_is_equal(file::path const & path1, file::path const & path2)
{

   return __node_full_file_path(path1).compare_ci(__node_full_file_path(path2)) == 0;

}


::file::path __node_full_file_path(file::path path)
{

   if(path.is_empty())
   {

      return path;

   }

   //return ::str::from_strdup(ns_realpath(path));

   char sz[4096];

   __zero(sz);

   return realpath(path, sz);

}



long long oswindow_id(oswindow w)
{

   return (long long) (w);

}


//int is_window(oswindow window)
//{
//   return (window == nullptr) ? false : (window->get_user_interaction() != nullptr);
//}
//


//
//int show_window(oswindow oswindow, int iShow)
//{
//   
//   if(::is_null(oswindow))
//   {
//    
//      return false;
//      
//   }
// 
//   if(::is_null(oswindow->m_pimpl))
//   {
//      
//      return false;
//      
//   }
//   
//   return oswindow->m_pimpl->ShowWindow(iShow);
//   
//}
