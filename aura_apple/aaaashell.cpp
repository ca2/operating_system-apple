#include "framework.h"
#include "shell.h"





// const char * linux_g_direct_get_file_icon_path(const char * pszPath, int iSize);

// string linux_get_file_icon_path(string strPath, int iSize)
// {

//    return ::str::from_strdup(linux_g_direct_get_file_icon_path(strPath, iSize));

// }

// const char * linux_g_direct_get_file_content_type(const char * pszFile);

// string core_linux_get_file_content_type(string strPath)
// {

//    return ::str::from_strdup(linux_g_direct_get_file_content_type(strPath));

// }





namespace aura
{


   namespace posix
   {


      shell::shell()
      {

         //set_get_file_content_type_function(&core_linux_get_file_content_type);

         defer_create_mutex();
         //begin();

         //SHGetImageList(SHIL_SMALL, IID_IImageList, m_pilSmall);
         //SHGetImageList(SHIL_LARGE, IID_IImageList, m_pilLarge);
         //SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, m_pilExtraLarge);
         //SHGetImageList(SHIL_JUMBO, IID_IImageList, m_pilJumbo);
         /// SHGetMalloc(&m_pmalloc);

//         for (index i = 0; i < get_processor_count() * 2; i++)
//         {
//
//            m_threadaGetImage.add(fork([&]()
//            {
//
//               ::parallelization::set_priority(::priority_highest);
//
//               shell_run();
//
//            }));
//
//         }

      }


      shell::~shell()
      {

      }


      ::e_status shell::initialize(::object * pobject)
      {

         auto estatus = ::user::shell::initialize(pobject);

         if(!estatus)
         {

            return estatus;

         }

         estatus = __compose(m_pcontextimage);

         if(!estatus)
         {

            return estatus;

         }

         return estatus;

      }
//
//      void linux::initialize()
//      {
//
//
//      }

//      void linux::defer_start()
//      {
//
//
//      }

//      int linux::get_image_by_extension(per_fork * pfork, oswindow oswindow, image_key & key, color32_t crBk)
//      {
//
//         return 0x80000000;
//
//      }




//      int linux::get_file_extension_image(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk)
//      {
//
//         int iImage;
//
//         wstring wstrFilePath;
//
////         imagekey.m_strPath = "foo";
//
//         imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();
//
//         {
//
//            synchronous_lock synchronouslock(synchronization());
//
//            if (m_imagemap.lookup(imagekey, iImage))
//            {
//
//               return iImage;
//
//            }
//
//         }
//
////         if (imagekey.m_eattribute.has(file_attribute_directory))
////         {
////
////            SHGetFileInfoW(
////               L"foo",
////               FILE_ATTRIBUTE_DIRECTORY,
////               &shfi16,
////               sizeof(shfi16),
////               SHGFI_USEFILEATTRIBUTES
////               | SHGFI_ICON
////               | SHGFI_SMALLICON);
////
////            SHGetFileInfoW(
////               L"foo",
////               FILE_ATTRIBUTE_DIRECTORY,
////               &shfi48,
////               sizeof(shfi48),
////               SHGFI_USEFILEATTRIBUTES
////               | SHGFI_ICON
////               | SHGFI_LARGEICON);
////
////         }
////         else
////         {
////
////            wstrFilePath = wstring(L"foo.") + wstring(imagekey.m_pszExtension);
////
////            SHGetFileInfoW(
////               wstrFilePath,
////               FILE_ATTRIBUTE_NORMAL,
////               &shfi16,
////               sizeof(shfi16),
////               SHGFI_USEFILEATTRIBUTES
////               | SHGFI_ICON
////               | SHGFI_SMALLICON);
////
////            SHGetFileInfoW(
////               wstrFilePath,
////               FILE_ATTRIBUTE_NORMAL,
////               &shfi48,
////               sizeof(shfi48),
////               SHGFI_USEFILEATTRIBUTES
////               | SHGFI_ICON
////               | SHGFI_LARGEICON);
////
////         }
//         per_fork f(false);
//         if (pfork == nullptr)
//         {
//            f.init();
//            pfork = &f;
//
//         }
////
////         bool b16 = false;
////         bool b48 = false;
////         iImage = add_icon_set(pfork, &shfi16, &shfi48, crBk, b16, b48);
////         if (!b16 && shfi16.hIcon != nullptr)
////         {
////            ::DestroyIcon(shfi16.hIcon);
////         }
////         if (!b48 && shfi48.hIcon != nullptr)
////         {
////            ::DestroyIcon(shfi48.hIcon);
////         }         synchronous_lock synchronouslock(synchronization());
////
////         m_imagemap.set_at(imagekey, iImage);
////
//         return iImage;
//
//      }





      //bool linux::get_icon(
      //   per_fork * pfork,
      //   oswindow oswindow,
      //   IShellFolder * lpsf,
      //   LPITEMIDLIST lpiidlAbsolute,
      //   LPITEMIDLIST lpiidlChild,
      //   const unichar * lpcszExtra,
      //   e_icon eicon,
      //   HICON * phicon16,
      //   HICON * phicon48)
      //{

      //   single_lock synchronouslock(mutex(), true);

      //   if (lpsf == nullptr)
      //      return false;
      //   int iType;
      //   switch (eicon)
      //   {
      //   case icon_normal:
      //      iType = 0;
      //      break;
      //   case icon_open:
      //      iType = GIL_OPENICON;
      //      break;
      //   default:
      //      // unexpected icon type
      //      ASSERT(false);
      //      return false;
      //   }


      //   WCHAR szFilePath[_MAX_PATH * 10];
      //   SHGetPathFromIDListW(
      //      lpiidlAbsolute,
      //      szFilePath);
      //   string strFilePath(szFilePath);

      //   //   WCHAR wszFilePath[_MAX_PATH * 10];
      //   SHGetPathFromIDListW(
      //      lpiidlAbsolute,
      //      szFilePath);

      //   char szPath[_MAX_PATH * 10];
      //   string strPath;
      //   //   int iImage = 0x80000000;

      //   HICON hicon16 = nullptr;
      //   HICON hicon48 = nullptr;
      //   HRESULT hrIconLocation;
      //   HRESULT hrExtract;
      //   image_key imagekey;


      //   string strPathEx(strFilePath);
      //   string strExtra;

      //   ::str::international::unicode_to_utf8(strExtra, lpcszExtra);

      //   if (strExtra.get_length() > 0)
      //   {
      //      strPathEx += ":" + strExtra;
      //   }



      //   int iIcon = 0x80000000;
      //   unsigned int uFlags = 0;

      //   SHFILEINFO shfi16;
      //   SHFILEINFO shfi48;

      //   ::linux::comptr< IExtractIcon > lpiextracticon;

      //   if (SUCCEEDED(lpsf->GetUIObjectOf(
      //      oswindow,
      //      1,
      //      (LPCITEMIDLIST *)&lpiidlChild,
      //      IID_IExtractIcon,
      //      nullptr,
      //      lpiextracticon)))
      //   {
      //      if (SUCCEEDED(hrIconLocation = lpiextracticon->GetIconLocation(
      //         iType,
      //         szPath,
      //         sizeof(szPath),
      //         &iIcon,
      //         &uFlags)))
      //      {
      //         strPath = szPath;
      //         if (strPath == "*")
      //         {
      //            character_count iFind = strFilePath.reverse_find('.');

      //            imagekey.m_iIcon = 0x80000000;
      //            imagekey.m_pszExtension = (char*)&strFilePath[iFind];
      //            imagekey.m_strPath = "";
      //         }
      //         else
      //         {
      //            imagekey.m_strPath = (char *)strPath.c_str();
      //            imagekey.m_iIcon = iIcon;
      //            imagekey.m_pszExtension = nullptr;
      //         }
      //      }
      //   }
      //   if (papplication->dir().is(::str::international::unicode_to_utf8(szFilePath)))
      //   {
      //      if (imagekey.m_iIcon == 0x80000000)
      //      {
      //         SHGetFileInfo(
      //            "foo",
      //            FILE_ATTRIBUTE_DIRECTORY,
      //            &shfi16,
      //            sizeof(shfi16),
      //            SHGFI_USEFILEATTRIBUTES
      //            | SHGFI_ICON
      //            | SHGFI_SMALLICON);
      //         SHGetFileInfo(
      //            "foo",
      //            FILE_ATTRIBUTE_DIRECTORY,
      //            &shfi48,
      //            sizeof(shfi48),
      //            SHGFI_USEFILEATTRIBUTES
      //            | SHGFI_ICON
      //            | SHGFI_LARGEICON);
      //      }
      //      else
      //      {
      //         strPath = "foo." + string(imagekey.m_pszExtension);
      //         SHGetFileInfo(
      //            strPath,
      //            FILE_ATTRIBUTE_NORMAL,
      //            &shfi16,
      //            sizeof(shfi16),
      //            SHGFI_USEFILEATTRIBUTES
      //            | SHGFI_ICON
      //            | SHGFI_SMALLICON);
      //         SHGetFileInfo(
      //            strPath,
      //            FILE_ATTRIBUTE_NORMAL,
      //            &shfi48,
      //            sizeof(shfi48),
      //            SHGFI_USEFILEATTRIBUTES
      //            | SHGFI_ICON
      //            | SHGFI_LARGEICON);
      //      }
      //      *phicon16 = shfi16.hIcon;
      //      *phicon48 = shfi48.hIcon;
      //   }
      //   else
      //   {
      //      try
      //      {
      //         hicon16 = nullptr;
      //         strPath.Truncate(0);
      //         strPath.free_extra();
      //         strPath = imagekey.m_strPath;
      //         iIcon = imagekey.m_iIcon;
      //         bool bExtract = false;
      //         //HGLOBAL hglobal = ::GlobalAlloc(GPTR, strPath.get_length() + 1);
      //         //char * lpsz = (char *) ::GlobalLock(hglobal);
      //         //strcpy(lpsz, strPath);
      //         try
      //         {
      //            if ((hrIconLocation == S_OK && !(uFlags & GIL_NOTFILENAME))
      //               && lpiextracticon.is_null()
      //               && (NOERROR == (hrExtract = lpiextracticon->Extract(
      //                  strPath,
      //                  iIcon,
      //                  &hicon48,
      //                  &hicon16,
      //                  0x00100030)))
      //               )
      //            {
      //               bExtract = true;
      //               *phicon16 = hicon16;
      //               *phicon48 = hicon48;
      //            }
      //         }
      //         catch (...)
      //         {
      //         }
      //         //::GlobalUnlock(hglobal);
      //         //::GlobalFree(hglobal);
      //         if (!bExtract)
      //         {
      //            if (strlen(imagekey.m_strPath) <= 0)
      //            {
      //               SHGetFileInfo(
      //                  (const char *)lpiidlAbsolute,
      //                  FILE_ATTRIBUTE_NORMAL,
      //                  &shfi16,
      //                  sizeof(shfi16),
      //                  SHGFI_PIDL
      //                  | SHGFI_ICON
      //                  | SHGFI_SMALLICON);
      //               hicon16 = shfi16.hIcon;
      //               SHGetFileInfo(
      //                  (const char *)lpiidlAbsolute,
      //                  FILE_ATTRIBUTE_NORMAL,
      //                  &shfi48,
      //                  sizeof(shfi48),
      //                  SHGFI_PIDL
      //                  | SHGFI_ICON
      //                  | SHGFI_LARGEICON);
      //               hicon16 = shfi16.hIcon;
      //               hicon48 = shfi48.hIcon;
      //            }
      //            else
      //            {
      //               ExtractIconEx(
      //                  imagekey.m_strPath,
      //                  imagekey.m_iIcon,
      //                  &hicon48,
      //                  &hicon16,
      //                  1);
      //            }
      //            if (hicon16 == nullptr)
      //            {
      //               SHGetFileInfo(
      //                  "foo",
      //                  FILE_ATTRIBUTE_NORMAL,
      //                  &shfi16,
      //                  sizeof(shfi16),
      //                  SHGFI_USEFILEATTRIBUTES
      //                  | SHGFI_ICON
      //                  | SHGFI_SMALLICON);
      //               hicon16 = shfi16.hIcon;
      //            }
      //            if (hicon48 == nullptr)
      //            {
      //               SHGetFileInfo(
      //                  "foo",
      //                  FILE_ATTRIBUTE_NORMAL,
      //                  &shfi48,
      //                  sizeof(shfi48),
      //                  SHGFI_USEFILEATTRIBUTES
      //                  | SHGFI_ICON
      //                  | SHGFI_LARGEICON);
      //               hicon48 = shfi48.hIcon;
      //            }
      //            *phicon16 = hicon16;
      //            *phicon48 = hicon48;
      //         }
      //      }
      //      catch (...)
      //      {
      //      }
      //   }

      //   return true;

      //}



      //int linux::get_image(per_fork * pfork, oswindow oswindow, image_key imagekey, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, color32_t crBk)
      //{

      //   int iImage = get_image(pfork, oswindow, imagekey, lpiidlAbsolute, lpiidlChild, lpcszExtra, crBk);

      //   _017ItemIDListFree(pfork, lpiidlChild);

      //   return iImage;

      //}





//      bool linux::get_icon( oswindow oswindow, const char * psz, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48)
//      {
//
//         single_lock synchronouslock(mutex(), true);
//
//         per_fork fork;
//         LPITEMIDLIST lpiidlAbsolute;
//         _017ItemIDListParsePath(oswindow, &lpiidlAbsolute, psz);
//         bool bGet = get_icon(oswindow, lpiidlAbsolute, lpcszExtra, eicon, phicon16, phicon48);
//         _017ItemIDListFree(&fork, lpiidlAbsolute);
//         return bGet;
//
//      }
//
//      bool linux::get_icon(per_fork * pfork, oswindow oswindow, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48)
//      {
//
//         single_lock synchronouslock(mutex(), true);
//
//         wstring wstr;
//
////         ::linux::comptr < IShellFolder > lpsf = _017GetShellFolder(wstr, lpiidlAbsolute);
//         ::linux::comptr < IShellFolder > lpsf = _017GetShellFolder(lpiidlAbsolute);
//
//
//         LPITEMIDLIST lpiidlChild = _017ItemIDListGetLast(pfork, lpiidlAbsolute);
//         bool bGet = get_icon(
//            oswindow,
//            lpsf,
//            lpiidlAbsolute,
//            lpiidlChild,
//            lpcszExtra,
//            eicon,
//            phicon16,
//            phicon48);
//
//         _017ItemIDListFree(pfork, lpiidlChild);
//
//         return bGet;
//      }
//


      shell::e_folder shell::get_folder_type(::object * pobject, const char * lpcsz)
      {

         return get_folder_type(pobject, ::str::international::utf8_to_unicode(lpcsz));

      }


      shell::e_folder shell::get_folder_type(::object * pobject, const widechar * lpcszPath)
      {

         string strPath;

         ::str::international::unicode_to_utf8(strPath, lpcszPath);

         if (dir::is(strPath))
         {

            return folder_file_system;

         }
         else
         {

            return folder_none;

         }

      }


      void shell::on_update_sizes_interest()
      {

         synchronous_lock synchronouslock(synchronization());

         m_iaSize.erase_all();

         m_iaSize.add(16);

         m_iaSize.add(48);

         ::user::shell::shell::on_update_sizes_interest();

      }


      int shell::impl_get_file_image(const image_key & imagekeyParam)
      {

         image_key imagekey(imagekeyParam);

         int iImage = 0x80000000;

         if (::str::case_insensitive_begins(imagekey.m_strPath, "uifs:"))
         {

            auto papplication = application();

            ::file::path path = papplication->dir().matter("cloud.ico");

            for (auto iSize : m_iaSize)
            {


//               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

               //             iImage = add_icon(iSize, hicon, crBk);

            }

            single_lock synchronouslock(mutex(), true);

            m_imagemap.set_at(imagekey, iImage);

            return iImage;

         }
         else if (::str::case_insensitive_begins(imagekey.m_strPath, "fs:"))
         {

            auto papplication = application();

            ::file::path path = papplication->dir().matter("remote.ico");

            for (auto iSize : m_iaSize)
            {


//               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

               //             iImage = add_icon(iSize, hicon, crBk);

            }

            single_lock synchronouslock(mutex(), true);

            m_imagemap.set_at(imagekey, iImage);

            return iImage;

         }
         else if (::str::case_insensitive_begins(imagekey.m_strPath, "ftp:"))
         {

            auto papplication = application();

            ::file::path path = papplication->dir().matter("ftp.ico");

            for (auto iSize : m_iaSize)
            {


               //HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

               //iImage = add_icon(iSize, hicon, crBk);

            }

            single_lock synchronouslock(mutex(), true);

            m_imagemap.set_at(imagekey, iImage);

            return iImage;

         }





         if (::str::case_insensitive_ends(imagekey.m_strPath, ".aura"))
         {

            auto papplication = application();

            string str = papplication->file().as_string(imagekey.m_strPath);

            if (::str::case_insensitive_begins_eat(str, "ca2prompt\r\n"))
            {
               str.trim();
               /*HICON hicon16 = (HICON) ::LoadImage(nullptr, papplication->dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
               HICON hicon48 = (HICON) ::LoadImage(nullptr, papplication->dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 48, 48, LR_LOADFROMFILE);
               synchronous_lock sl1(m_pil48Hover->mutex());
               synchronous_lock sl2(m_pil48->mutex());
               iImage = m_pil16->add_icon_os_data(hicon16);
               m_pil48Hover->add_icon_os_data(hicon48);

               if (crBk == 0)
               {
                  psystem->imaging().Createcolor_blend_ImageList(
                     m_pil48,
                     m_pil48Hover,
                     rgb(255, 255, 240),
                     64);
               }
               else
               {
                  *m_pil48 = *m_pil48Hover;
               }*/

            }
            return iImage;
         }
         // try to find "uifs:// http:// ftp:// like addresses"
         // then should show icon by extension or if is folder
         character_count iFind = imagekey.m_strPath.find_ci("://");
         character_count iFind2 = imagekey.m_strPath.find_ci(":");
         if (iFind >= 0 || iFind2 >= 2)
         {
            string strProtocol = string(imagekey.m_strPath).Left(maximum(iFind, iFind2));
            int i = 0;

            while (i < strProtocol.get_length() && ansi_char_is_alphanumeric(strProtocol[i]))
            {

               i++;

            }

            if (i > 0 && i == strProtocol.get_length())
            {

               // heuristically valid protocol
               return get_image_by_file_extension(imagekey);

            }

            if (imagekey.m_eattribute.has(file_attribute_directory))
            {

               return get_image_by_file_extension(imagekey);

            }

         }

         string strExtension;

         if (::str::case_insensitive_ends(imagekey.m_strPath, ".sln"))
         {

            // output_debug_string("test .sln");

         }


         string strIcon48;

         string strIcon16;

         if (::str::case_insensitive_ends(imagekey.m_strPath, ".desktop"))
         {

            auto papplication = application();

            string str = papplication->file().as_string(imagekey.m_strPath);

            string_array stra;

            stra.add_lines(str);

            stra.filter_begins_ci("icon=");

            if (stra.get_size() <= 0)
            {

               return -1;

            }

            string strIcon = stra[0];

            ::str::case_insensitive_begins_eat(strIcon, "icon=");

            strIcon48 = strIcon;

            strIcon16 = strIcon;

         }
         else
         {

            auto psystem = m_psystem->m_paurasystem;

            auto pnode = psystem->node();

            strIcon48 = pnode->get_file_icon_path(imagekey.m_strPath, 48);

            strIcon16 = pnode->get_file_icon_path(imagekey.m_strPath, 16);

         }

         if (strIcon48.has_character())
         {


            ::image_pointer pimage1 = m_pcontextimage->load_image(strIcon16);

            if (!::is_ok(pimage1))
            {

               return -1;

            }

            auto papplication = application();

            auto pcontextimage = pcontext->context_image();

            ::image_pointer pimage = pcontextimage->load_image(strIcon48);

            if (!::is_ok(pimage))
            {

               return -1;

            }

            ::image_pointer image16 = create_image({16, 16});

            if (!::is_ok(image16))
            {

               return -1;

            }

            ::image_pointer image48 = create_image({48, 48});

            if (!::is_ok(image48))
            {

               return -1;

            }

            pimage->get_graphics()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

            pimage->get_graphics()->stretch(::int_size(16, 16), pimage1->get_graphics(), pimage1->rectangle());

            pimage->get_graphics()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

            pimage->get_graphics()->stretch(::int_size(48, 48), pimage->get_graphics(), pimage->rectangle());

            synchronous_lock sl1(m_pilHover[48]->mutex());

            synchronous_lock sl2(m_pil[48]->mutex());

            iImage = m_pil[16]->add_image(image16, 0, 0);

            m_pilHover[48]->add_image(image48, 0, 0);

            if (imagekey.m_cr == 0)
            {

//               auto psystem = m_psystem->m_paurasystem;
//
//               auto pdraw2d = psystem->draw2d();
//
//               auto pimaging = pdraw2d->imaging();
//
               m_pil[48]->color_blend(m_pilHover[48], rgb(255, 255, 240), 64);

            }
            else
            {

               *m_pil[48] = *m_pilHover[48];

            }

            return iImage;

         }


         string str(imagekey.m_strPath);


         //iImage = GetImageByExtension(oswindow, imagekey.m_strPath, imagekey.m_eicon, imagekey.m_eattribute, crBk);

         return iImage;

      }



//      linux::per_fork::per_fork(bool bInit)
//      {
//         if (bInit)
//         {
//
//            init();
//
//         }
//
//      }
//
//
//      linux::per_fork::~per_fork()
//      {
//
//      }
//
//
//      void linux::per_fork::init()
//      {
//
//
//
//      }
//
//      int linux::shell_run()
//      {
//
//         per_fork fork;
//
//
//
//
//         synchronous_lock synchronouslock(&m_mutexQueue);
//
//         while (task_get_run())
//         {
//
//            if(m_keyptra.is_empty())
//            {
//
//               synchronouslock.unlock();
//
//               sleep(100_ms);
//
//            }
//            else
//            {
//
//               image_key * pkey = m_keyptra.first();
//
//               m_keyptra.erase_at(0);
//
//               synchronouslock.unlock();
//
//               int iImage = get_image(&fork, pkey->m_oswindow, *pkey, nullptr, pkey->m_cr);
//
//               {
//
//                  synchronous_lock s(mutex());
//
//                  m_imagemap.set_at(*pkey, iImage);
//
//               }
//
//               delete pkey;
//
//            }
//
//            synchronouslock.lock();
//
//         }
//
//         return 0;
//
//      }
//


//      int linux::get_image(oswindow oswindow, const string & strPath, e_file_attribute eattribute, e_icon eicon, color32_t crBk)
//      {
//
//         int iImage = 0x80000000;
//
//         {
//            if (colorref_get_a_value(crBk) != 255)
//            {
//
//               crBk = 0;
//
//            }
//
//
//
//            image_key imagekey;
//
//            imagekey.set_path(strPath);
//
//            imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();
//
//            imagekey.m_eattribute = eattribute;
//
//            imagekey.m_eicon = eicon;
//
//            imagekey.m_iIcon = 0;
//
//            imagekey.m_oswindow = oswindow;
//
//            imagekey.m_cr = crBk;
//
//            {
//
//               synchronous_lock synchronouslock(synchronization());
//
//               if (m_imagemap.lookup(imagekey, iImage))
//               {
//
//                  return iImage;
//
//               }
//
//            }
//
//            image_key * pstore = new image_key(imagekey);
//
//            {
//
//               synchronous_lock synchronouslock(&m_mutexQueue);
//
//               m_keyptra.add(pstore);
//
//            }
//
//            imagekey.set_path("foo");
//
//            iImage = get_foo_image(nullptr, oswindow, imagekey, imagekey.m_cr);
//
//            synchronous_lock synchronouslock(synchronization());
//
//            m_imagemap.set_at(imagekey, iImage);
//
//         }
//
//         return iImage;
//
//
//      }
//
//


      int shell::get_image_by_file_extension(image_key & imagekey)
      //int linux::get_image_foo(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk)
      {

         int iImage = 0x80000000;

         {

            if (colorref_get_a_value(imagekey.m_cr) != 255)
            {

               imagekey.m_cr = 0;

            }


            image_key imagekey;

            imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();

            imagekey.set_extension(imagekey.m_strPath);

            imagekey.m_strPath = "foo";

//            imagekey.m_eattribute = eattribute;

//            imagekey.m_eicon = eicon;

            imagekey.m_iIcon = 0;

            {

               synchronous_lock synchronouslock(synchronization());

               if (m_imagemap.lookup(imagekey, iImage))
               {

                  return iImage;

               }

            }

            iImage = get_file_image(imagekey);

            synchronous_lock synchronouslock(synchronization());

            m_imagemap.set_at(imagekey, iImage);

         }

         return iImage;

      }


//      int shell::add_hover_image(int iSize, int iImage, color32_t crBk)
//      {
//
//         if (crBk == 0)
//         {
//
//            return m_pilHover[iSize]->predicate_add_image([&](auto pimage)
//            {
//
//               psystem->imaging().color_blend(pimage, rgb(255, 255, 240), 64);
//
//            }
//            , m_pil[iSize], iImage);
//
//         }
//         else
//         {
//
//            iImage = m_pilHover[iSize]->add_image(m_pil[iSize], iImage);
//
//            {
//
//               ::image_pointer pimage;
//               pimage = create_image({iSize,  iSize});
//               pimage->fill(255, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk));
//               pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//               m_pilHover[iSize]->draw(pimage->get_graphics(), iImage, ::int_point(), 0);
//               m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);
//               m_pilHover[iSize]->m_pimage->g()->BitBlt(iImage * 48, 0, 48, 48, pimage->get_graphics());
//               m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//            }
//
//            {
//               auto & d = m_pilHover[iSize]->m_pimage;
//               int_size s = m_pil[iSize]->m_pimage->get_size();
//               ::image_pointer pimage;
//               pimage = __create_image(d->size());
//               pimage->fill(255, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk));
//               pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
//               pimage->get_graphics()->draw(::int_point(), d->size(), d->get_graphics());
//               pimage->get_graphics()->fill_rectangle(int_rectangle(d->size()), argb(123, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk)));
//               m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);
//               m_pil[iSize]->m_pimage->g()->draw(::int_point(), d->size(), pimage->get_graphics());
//               m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//            }
//
//            return iImage;
//
//         }
//
//      }

   //} // namespace shell


//      ::e_status user::create_user_shell()
//      {
//
//         ::e_status estatus = ::success;
//
//         if (!m_pshell)
//         {
//
//            estatus = __compose(m_pshell, __new(::linux::shell));
//
//            if (!estatus)
//            {
//
//               return estatus;
//
//            }
//
//         }
//
//         if (!m_pshell)
//         {
//
//            return ::error_failed;
//
//         }
//
//         return ::success;
//
//      }


   } // namespace posix


} // namespace aura
