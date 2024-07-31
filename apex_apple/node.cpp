//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"


void os_post_quit();


void apex_application_run(const char * pszAppName, const char * pszProgName);


namespace apex_apple
{


      node::node()
      {

         //m_pGtkSettingsDefault = nullptr;

         m_pApexPosix = this;

      }


      node::~node()
      {

//      if(m_pGtkSettingsDefault)
//      {
//
//         g_object_unref(m_pGtkSettingsDefault);
//
//      }

      }


      int node::node_init_check(int * pi, char *** ppz)
      {

         //auto iResult = gtk_init_check(pi, ppz);

         //return iResult;

         return 0;

      }


////      ::e_status node::start_()
////      {
////
////
//////      if (psystem->m_bGtkApp)
//////      {
//////
//////         apex_application_run(psystem->m_XstrAppId, psystem->m_strProgName);
//////
//////      }
//////      else
//////      {
////         //
////         ////      g_set_application_name(psystem->m_XstrAppId);
////         ////
////         ////      g_set_prgname(psystem->m_strProgName);
////         ////
////         ////      //auto idle_source = g_idle_source_new();
////         ////
////         ////      //g_source_set_callback(idle_source, &linux_start_system, (::apex::system *) m_psystem, nullptr);
////         ////
////         ////      //g_source_attach(idle_source, g_main_context_default());
////         ////
////         ////      //int c = 2;
////         ////
////         ////      //const char * argv[]={"app", "--g-fatal-warnings"};
////         ////
////         ////#if !defined(__SANITIZE_ADDRESS__)
////         ////
////         ////      gtk_init_check(&psystem->m_argc, &psystem->m_argv);
////         ////
////         ////#endif
////
//////         node_fork([this]()
//////                   {
//////
//////                      //x11_add_idle_source();
//////
//////                      //x11_add_filter();
//////
//////                      auto pgtksettingsDefault = gtk_settings_get_default();
//////
//////                      if(pgtksettingsDefault)
//////                      {
//////
//////
//////                         m_pGtkSettingsDefault = G_OBJECT(pgtksettingsDefault);
//////
//////                         g_object_ref (m_pGtkSettingsDefault);
//////
//////                         gchar *theme_name = nullptr;
//////
//////                         g_object_get(m_pGtkSettingsDefault, "gtk-theme-name", &theme_name, NULL);
//////
//////                         m_strTheme = theme_name;
//////
//////                         g_free(theme_name);
//////
//////                         auto preturn = g_signal_connect_data(
//////                            m_pGtkSettingsDefault,
//////                            "notify::gtk-theme-name",
//////                            G_CALLBACK(gtk_settings_gtk_theme_name_callback),
//////                            this,
//////                            NULL,
//////                            G_CONNECT_AFTER);
//////
//////                         //g_object_ref(preturn);
//////
//////                         //printf("return %" PRIiPTR, preturn);
//////
//////                         //printf("return %" PRIiPTR, preturn);
//////
//////                      }
//////
//////
//////                   });
//////
//////
//////         //x11_add_filter();
//////
//////psystem->fork([]()
//////     {
//////
//////      x11_main();
//////
//////     });
//////
//////         gtk_main();
////
////         //x11_main();
////
////         //}
////         //
////         //::parallelization::post_quit_and_wait(get_context_system(), one_minute());
////
////         return ::success;
////
////      }
//
//
////      ::e_status node::initialize(::object * pobject)
////      {
////
////         //::node_gnome::g_defer_init();
////
////         return ::success;
////
////      }
//
//
////
////
////   string node::os_get_user_theme()
////   {
////
////      return m_strTheme;
////
////   }
////
////
////   bool node::os_set_user_theme(const ::string &strUserTheme)
////   {
////
////      // https://ubuntuforums.org/showthread.php?t=2140488
////      // gsettings set org.gnome.desktop.interface gtk-theme your_theme
////
////      // indirect wall-changer sourceforge.net contribution
////
////      auto edesktop = psystem->get_edesktop();
////
////      switch (edesktop)
////      {
////
////      case ::user::e_desktop_gnome:
////      case ::user::e_desktop_ubuntu_gnome:
////      case ::user::e_desktop_unity_gnome:
////      {
////
////      bool bOk1 = ::node_gnome::gsettings_set("org.gnome.desktop.interface", "gtk-theme", strUserTheme);
////
////      bool bOk2 = true;
////
////      //if(m_psystem->m_pacmedirectory->system_short_name().contains_ci("manjaro"))
////      {
////
////         bOk2 = ::node_gnome::gsettings_set("org.gnome.desktop.wm.preferences", "theme", strUserTheme);
////
////      }
////
////      sleep(300_ms);
////
////      ::node_gnome::gsettings_sync();
////
////      sleep(300_ms);
////
////      return
////      bOk1 &&bOk2;
////
////      }
////
////      case ::user::e_desktop_mate:
////
////      //return ::user::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);
////
////      case ::user::e_desktop_lxde:
////
////      //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);
////
////      break;
////
////      case ::user::e_desktop_xfce:
////      {
////      //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
////      //          if(entry.contains("image-path") || entry.contains("last-image")){
////      //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
////      //      }
////      //}
////
////      }
////
////      //break;
////
////      default:
////
////      output_debug_string("Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
////      return false;
////
////      }
////
////      return true;
////
////   }
////
////
////   void node::os_process_user_theme(string strTheme)
////   {
////
////      _os_process_user_theme(strTheme);
////
////   }
////
////
////   bool node::set_wallpaper(index iScreen, string strLocalImagePath)
////   {
////
////      // wall-changer sourceforge.net contribution
////
////      auto pnode = Node;
////
////      auto edesktop = psystem->get_edesktop();
////
////      switch (edesktop)
////      {
////
////         case ::user::e_desktop_gnome:
////         case ::user::e_desktop_ubuntu_gnome:
////         case ::user::e_desktop_unity_gnome:
////
////            return ::node_gnome::gsettings_set("org.gnome.desktop.background", "picture-uri", "file://" + strLocalImagePath);
////
////         case ::user::e_desktop_mate:
////
////            return ::node_gnome::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);
////
////         case ::user::e_desktop_lxde:
////
////            call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);
////
////            break;
////
////         case ::user::e_desktop_xfce:
////         {
////            //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
////            //          if(entry.contains("image-path") || entry.contains("last-image")){
////            //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
////            //      }
////            //}
////
////         }
////
////            //break;
////
////         default:
////
////            output_debug_string("Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
////            return false;
////
////      }
////
////      return true;
////
////   }
////
////
////   void node::enable_wallpaper_change_notification()
////   {
////
////      auto edesktop = psystem->get_edesktop();
////
////      switch (edesktop)
////      {
////
////         case ::user::e_desktop_gnome:
////         case ::user::e_desktop_ubuntu_gnome:
////         case ::user::e_desktop_unity_gnome:
////
////            ::node_gnome::g_enable_wallpaper_change_notification("org.gnome.desktop.background", "picture-uri");
////
////            break;
////
////         case ::user::e_desktop_mate:
////
////            ::node_gnome::g_enable_wallpaper_change_notification("org.mate.background", "picture-filename");
////
////            break;
////
////         case ::user::e_desktop_lxde:
////
////            //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);
////
////            break;
////
////         case ::user::e_desktop_xfce:
////         {
////            //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
////            //          if(entry.contains("image-path") || entry.contains("last-image")){
////            //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
////            //      }
////            //}
////
////         }
////
////         break;
////         default:
////
////            output_debug_string("Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
////            //return "";
////
////      }
////
////   }
////
////
////   string node::get_file_icon_path(const char * pszPath, int iSize)
////   {
////
////      return ::linux_g_direct_get_file_icon_path(pszPath, iSize);
////
////   }
////
////
////   string node::get_file_content_type(const char * pszPath)
////   {
////
////      return ::linux_g_direct_get_file_content_type(pszPath);
////
////   }
////
////
////   string node::get_wallpaper(index iScreen)
////   {
////
////      return "";
////
////   }
//
//
////   void node::node_fork(const ::procedure & procedure)
////   {
////
////      //gdk_branch(routine);
////
////   }
//
//
////   void node::node_post_quit()
////   {
////
////      os_post_quit();
////
////   }
//
//
////   ::linux::appindicator * node::appindicator_allocate()
////   {
////
////      return new ::node_gnome::appindicator();
////
////   }
////
////
////   void node::appindicator_destroy(::linux::appindicator * pappindicator)
////   {
////
////      //::linux::appindicator_destroy(pappindicator);
////
////      delete pappindicator;
////
////   }
////
////
////   void node::enum_display_monitors(::aura::session * psession)
////   {
////
////      node_fork(__routine([psession]
////                           {
////
////                              synchronous_lock sl(x11_mutex());
////
////                              xdisplay d(x11_get_display());
////
////                              GdkDisplay *pdisplay = gdk_display_get_default();
////
////                              if (pdisplay == nullptr)
////                              {
////
////                                 return;
////
////                              }
////
////                              synchronous_lock slSession(psession->mutex());
////
////                              ::collection::count iMonitorCount = gdk_display_get_n_monitors(pdisplay);
////
////                              psession->m_rectaWorkspace.set_size(iMonitorCount);
////
////                              psession->m_rectaMonitor.set_size(iMonitorCount);
////
////                              for (index iMonitor = 0; iMonitor < iMonitorCount; iMonitor++)
////                              {
////
////                                 GdkMonitor *pmonitor = gdk_display_get_monitor(pdisplay, iMonitor);
////
////                                 auto &rectWorkspace = psession->m_rectaWorkspace[iMonitor];
////
////                                 auto &rectMonitor = psession->m_rectaMonitor[iMonitor];
////
////                                 if (pmonitor == nullptr)
////                                 {
////
////                                    rectWorkspace.Null();
////
////                                    rectMonitor.Null();
////
////                                    continue;
////
////                                 }
////
////                                 GdkRectangle rect;
////
////                                 __zero(rect);
////
////                                 gdk_monitor_get_workarea(pmonitor, &rect);
////
////                                 copy(rectWorkspace, rect);
////
////                                 __zero(rect);
////
////                                 gdk_monitor_get_geometry(pmonitor, &rect);
////
////                                 copy(rectMonitor, rect);
////
////                              }
////
////                           }));
////
////   }
//
//
////   void node::os_post_quit()
////   {
////
////   }
//
//
////   void * node::node_wrap_window(void * pvoidDisplay, i64 window)
////   {
////
////      Display * pdisplay = (Display *) pvoidDisplay;
////
////      GdkDisplay * pd = gdk_x11_lookup_xdisplay (pdisplay);
////
////      auto pwindow = gdk_x11_window_foreign_new_for_display(GDK_DISPLAY(pd), (Window) window);
////
////      return pwindow;
////
////   }
//

////
////
////   bool node::launch_on_node(::subject::subject * psubject)
////   {
////
////      ::matter * pmatter = psubject;
////
////      node_fork([pmatter]()
////                {
////
////                   auto ret = g_timeout_add(300, (GSourceFunc) &node_gnome_source_func, pmatter);
////
////                   printf("ret %d", ret);
////
////                   printf("ret %d", ret);
////
//////      g_idle_add(&node_gnome_source_func, pmatter);
////
////                });
////
////   }
////
////
////} // namespace node_gnome
////
////
////gboolean node_gnome_source_func(gpointer pUserdata)
////{
////
////   ::matter * pmatter = (::matter *) pUserdata;
////
////   if(!pmatter->step())
////   {
////
////      return false;
////
////   }
////
////   return true;
////
////}


bool node::has_ip4_internet()
{
   
   if(!m_preachabilityIp4Internet)
   {
    
      m_preachabilityIp4Internet = reachability_for_ip4_internet();
      
   }
   
   return m_preachabilityIp4Internet->current_reachability() != e_reachability_none;
   
}

bool node::has_ip6_internet()
{
  
   if(!m_preachabilityIp6Internet)
   {
    
      m_preachabilityIp6Internet = reachability_for_ip6_internet();
      
   }
   
   return m_preachabilityIp6Internet->current_reachability() != e_reachability_none;
   
}


} // namespace apex_apple



