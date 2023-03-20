#pragma once


#include "acme/filesystem/file/text_file.h"


namespace acme_apple
{


   class stdio_file :
      virtual public ::file::text_file
   {
   public:


      //__creatable_from_library(stdio_file, ::file::text_file, "acme_macos");


      FILE * m_pStream;
      

      stdio_file();
      ~stdio_file() override;
      

      void write_string(const ::scoped_string & scopedstr) override;
      virtual char * read_string(char * lpsz, ::u32 nMax);
      bool read_string(string & rString) override;

//      void dump(dump_context & dumpcontext) const override;

      filesize get_position() const override;
      void open(const ::file::path & lpszFileName, const ::file::e_open & eopen) override;
      memsize read(void * lpBuf, memsize nCount) override;
      void write(const void * lpBuf, memsize nCount) override;
      virtual filesize seek(filesize lOff, ::enum_seek nFrom);
      virtual void Abort();
      virtual void Flush();
      void close() override;
      virtual filesize get_length() const;

      // Unsupported APIs
      virtual ::pointer <  ::file::file > Duplicate() const;
      virtual void LockRange(filesize dwPos, filesize dwCount);
      virtual void UnlockRange(filesize dwPos, filesize dwCount);


   };


} // namespace acme_apple



