#include "framework.h"

#ifdef WITH_X11
#include "gnome_gnome.h"
//#include "apex/os/linux/appindicator.h"



//
//namespace linux
//{
//
//
//   void appindicator_destroy(appindicator * pindicator)
//   {
//
//      delete pindicator;
//
//   }
//
//} // namespace linux

namespace os
{

   string os_get_user_theme()
   {

      // https://ubuntuforums.org/showthread.php?t=2140488
      // gsettings set org.gnome.desktop.interface gtk-theme your_theme

      // indirect wall-changer sourceforge.net contribution

      string strTheme;

      bool bOk = false;

      auto edesktop = System.get_eoperating_ambient();

      switch (edesktop)
      {

      case ::user::desktop_gnome:
      case ::user::desktop_ubuntu_gnome:
      case ::user::desktop_unity_gnome:

         bOk = ::user::gsettings_get(strTheme, "org.gnome.desktop.interface", "gtk-theme");

         break;

      case ::user::desktop_mate:

         bOk = ::user::gsettings_get(strTheme, "org.mate.background", "picture-filename");

         break;

      case ::user::desktop_lxde:

         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

         break;

      case ::user::desktop_xfce:
      {
         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
         //          if(entry.contains("image-path") || entry.contains("last-image")){
         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
         //      }
         //}

      }

      //break;

      default:

         output_debug_string("Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
         //return "";

      }

      return strTheme;

   }


   string get_wallpaper(::collection::index iIndex)
   {

      // wall-changer sourceforge.net contribution

      bool bOk = false;

      string strWallpaper;

      auto edesktop = System.get_eoperating_ambient();

      switch (edesktop)
      {

      case ::user::desktop_gnome:
      case ::user::desktop_ubuntu_gnome:
      case ::user::desktop_unity_gnome:

         bOk = ::user::gsettings_get(strWallpaper, "org.gnome.desktop.background", "picture-uri");

         break;

      case ::user::desktop_mate:

         bOk = ::user::gsettings_get(strWallpaper, "org.mate.background", "picture-filename");

         break;

      case ::user::desktop_lxde:

         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

         break;

      case ::user::desktop_xfce:
      {
         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
         //          if(entry.contains("image-path") || entry.contains("last-image")){
         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
         //      }
         //}

      }

      //break;

      default:

         output_debug_string("Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
         //return "";

      }

      ::str::case_insensitive_begins_eat(strWallpaper, "file://");

      return strWallpaper;

   }



} // namespace os

#endif // define(WITH_X11)


