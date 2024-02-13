// Created by camilo on 2024-02-06 02:17 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/memory_file.h"


namespace acme_apple
{


   ///////////////////////////////////////////////////////////////
   //
   //  File - memory backed file synchronized to iCloud on close
   //


   class CLASS_DECL_ACME icloud_file :
      virtual public ::memory_file
   {
   public:

      
      ::file::path      m_pathName;
      ::string          m_str_iCloudContainerIdentifier;


      icloud_file();
      ~icloud_file() override;

//
//      void assert_ok() const override;
//      void dump(dump_context & dumpcontext) const override;

      //virtual bool has_write_mode() override;

//      virtual filesize get_position() const override;
//      ::file::file_status get_status() const override;
//      ::file::path get_file_path() const override;
//      void set_file_path(const ::file::path & path) override;
////
////      void open(const ::file::path & path, ::file::e_open eopen) override;
//
//  
//      
//      void open(const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception = nullptr) override;
//      
//      //filesize translate(filesize uiCount, ::enum_seek eseek) override;
//      
//      void translate(filesize offset, ::enum_seek eseek) override;
//     void set_size(filesize uiCount) override;
//      filesize size() const override;
//
//      memsize read(void * pbuffer, memsize uiCount) override;
//      void write(const void * pbuffer, memsize uiCount) override;
//
//      void lock(filesize pos, filesize uiCount) override;
//      void unlock(filesize pos, filesize uiCount) override;
//
      void close() override;
      void flush() override;
//
//      bool is_opened() const override;


   };


//   namespace file_exception
//   {
//
//
//      void os_error_to_exception(::i32 lOsError);
//      void err_no_to_exception(i32 nErrno);
//      void throw_os_error(::object * pobject, ::i32 lOsError, const char * lpszFileName = nullptr);
//      void throw_err_no(::object * pobject, i32 nErrno, const char * lpszFileName = nullptr);
//
//
//   }  // namespace file_exception
//
//
} // namespace acme_apple
