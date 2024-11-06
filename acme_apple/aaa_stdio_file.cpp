#include "framework.h"
#include "stdio_file.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include <fcntl.h>


namespace acme_apple
{


   stdio_file::stdio_file()
   {
      
      m_pStream = nullptr;
      
   }


   stdio_file::~stdio_file()
   {

      if (m_pStream != nullptr)
      {

         close();
         
      }
      
   }


   void stdio_file::open(const ::file::path & path, ::file::e_open eopen)
   {

      if ((eopen & ::file::e_open_defer_create_directory) && (eopen & ::file::e_open_write))
      {
         
         directory_system()->create(path.folder());
         
      }

      m_pStream = nullptr;
      //if (!::lnx::file::open(lpszFileName, (nOpenFlags & ~::file::e_open_text)))
      // return false;

      //   ASSERT(m_hFile != hFileNull);
      // ASSERT(m_bCloseOnDelete);

      char szMode[4]; // C-runtime open string
      int nMode = 0;

      // determine read/write mode depending on ::ca2::filesp mode
      if (eopen & ::file::e_open_create)
      {
         
         if (eopen & ::file::e_open_no_truncate)
         {
            
            szMode[nMode++] = 'a';
            
         }
         else
         {
          
            szMode[nMode++] = 'w';
            
         }
         
      }
      else if (eopen & ::file::e_open_write)
      {
         
         szMode[nMode++] = 'a';
         
      }
      else
      {
       
         szMode[nMode++] = 'r';
         
      }

      // add '+' if necessary (when read/write modes mismatched)
      if ((szMode[0] == 'r' && (eopen & ::file::e_open_read_write)) ||
            (szMode[0] != 'r' && !(eopen & ::file::e_open_write)))
      {
         // current szMode mismatched, need to add '+' to fix
         szMode[nMode++] = '+';
      }

      // will be inverted if not necessary
      int nFlags = O_RDONLY;
      if (eopen & (::file::e_open_write | ::file::e_open_read_write))
         nFlags ^= O_RDONLY;

      if (eopen & ::file::e_open_binary)
      {
         
         szMode[nMode++] = 'b'; // , nFlags ^= _O_TEXT;
         
      }
      else
      {
         
         szMode[nMode++] = 't';
         
      }
      
      szMode[nMode++] = '\0';

      // open a C-runtime low-level file handle
      //int nHandle = _open_osfhandle(m_hFile, nFlags);

      // open a C-runtime stream from that handle
      //if (nHandle != -1)
      m_pStream = fopen(path, szMode);


      if (m_pStream == nullptr)
      {
         
         auto cerrornumber = c_error_number();
         
         m_estatus = failed_errno_status(iErrNo);
         
         set_nok();
         
         if(!(eopen & ::file::e_open_no_exception_on_open))
         {
            
            throw ::exception(m_estatus);
            
         }
         
         //throw_
         //::file::exception * pe = get_Fileexception(::error_file, errno, m_path);
         // an error somewhere along the way...
         //if (pException != nullptr)
//         {
//            //         pException->m_lOsError = errno;
//            //         pException->m_cause = ::file::exception::OsErrorToException(errno);
//         }

         //::macos::file::Abort(); // close m_hFile

         //return ::error_failed;

      }

      m_path = path;

//      return ::success;
//
   }


   memsize stdio_file::read(void * lpBuf, memsize nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      if (nCount <= 0)
      {
         
         return 0;   // avoid Win32 "null-read"
         
      }

      //   ASSERT(fx_is_valid_address(lpBuf, nCount));

      size_t nRead = 0;

      nRead = fread(lpBuf, sizeof(unsigned char), nCount, m_pStream);
      
      if(nRead != nCount)
      {
         
         if(!feof(m_pStream))
         {
            
            if (ferror(m_pStream))
            {
               
               clearerr(m_pStream);
               
               int iErrNo = errno;
               
               auto errorcode = errno_error_code(iErrNo);
               
               auto estatus = cerrornumber.estatus();
               
               throw ::file::exception(estatus, errorcode, m_path, "fread(nCount) != nCount and ferror");
               
            }
            
         }
         
      }
            
      return nRead;
      
   }


   void stdio_file::write(const void * lpBuf, memsize nCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);
      //   ASSERT(fx_is_valid_address(lpBuf, nCount, false));

      if (fwrite(lpBuf, sizeof(unsigned char), nCount, m_pStream) != nCount)
      {
         
         int iErrNo = errno;
         
         auto errorcode = errno_error_code(iErrNo);
         
         auto estatus = cerrornumber.estatus();
         
         throw ::file::exception(estatus, errorcode, m_path, "fwrite != nCount");
         
      }
      
   }


   void stdio_file::write_string(const ::scoped_string & scopedstr)
   {
      
      ASSERT(m_pStream != nullptr);

      if (fwrite(scopedstr.begin(), 1, scopedstr.size(), m_pStream) == EOF)
      {

         int iErrNo = errno;
         
         auto errorcode = errno_error_code(iErrNo);
         
         auto estatus = cerrornumber.estatus();
         
         throw ::file::exception(estatus, errorcode, m_path, "fwrite == EOF");

      }
      
   }


   char * stdio_file::read_string(char * lpsz, unsigned int nMax)
   {
      ASSERT(lpsz != nullptr);
      //   ASSERT(fx_is_valid_address(lpsz, nMax));
      ASSERT(m_pStream != nullptr);

      char * lpszResult = fgets(lpsz, nMax, m_pStream);
      if (lpszResult == nullptr && !feof(m_pStream))
      {
         
         clearerr(m_pStream);
         
         int iErrNo = errno;
         
         auto errorcode = errno_error_code(iErrNo);
         
         auto estatus = cerrornumber.estatus();
         
         throw ::file::exception(estatus, errorcode, m_path, "!fgets and !feof");
         
      }

      return lpszResult;
      
   }


   bool stdio_file::read_string(string & rString)
   {

      ASSERT_VALID(this);

      //rString = &afxWchNil;    // is_empty string without deallocating
      rString.empty();
      const int nMaxSize = 128;
      char * lpsz = rString.get_buffer(nMaxSize);
      char * lpszResult;
      strsize nLen = 0;
      for (;;)
      {
         
         lpszResult = fgets(lpsz, nMaxSize+1, m_pStream);
         
         rString.release_buffer();

         // handle error/eof case
         if (lpszResult == nullptr && !feof(m_pStream))
         {
            
            clearerr(m_pStream);
            
            int iErrNo = errno;
            
            auto errorcode = errno_error_code(iErrNo);
            
            auto estatus = cerrornumber.estatus();
            
            throw ::file::exception(estatus, errorcode, m_path, "!fgets and !feof");
            
         }

         // if string is read completely or EOF
         if (lpszResult == nullptr ||
               (nLen = strlen(lpsz)) < nMaxSize ||
               lpsz[nLen-1] == '\n')
            break;

         nLen = rString.length();
         
         lpsz = rString.get_buffer(nMaxSize + nLen) + nLen;
         
      }

      // remov '\n' from end of string if present
      lpsz = rString.get_buffer(0);
      
      nLen = rString.length();
      
      if (nLen != 0 && lpsz[nLen-1] == '\n')
      {
         
         rString.get_buffer(nLen-1);
         
      }

      return lpszResult != nullptr;
      
   }


   filesize stdio_file::seek(filesize lOff, ::enum_seek eseek)
   {
      ASSERT_VALID(this);
      ASSERT(eseek == ::e_seek_set || eseek== ::e_seek_from_end || eseek== ::e_seek_current);
      ASSERT(m_pStream != nullptr);

      int nFrom;
      switch(eseek)
      {
      case ::e_seek_set:
         nFrom = SEEK_SET;
         break;
      case ::e_seek_from_end:
         nFrom = SEEK_END;
         break;
      case ::e_seek_current:
         nFrom = SEEK_CUR;
         break;
      default:
            throw ::file::exception(error_bad_seek, {}, m_path, "eseek unknown");
      }

      if (fseek(m_pStream, lOff, nFrom) != 0)
      {
         
         int iErrNo = errno;
         
         auto errorcode = errno_error_code(iErrNo);
         
         auto estatus = cerrornumber.estatus();
         
         throw ::file::exception(estatus, errorcode, m_path, "fseek != 0");
         
      }

      long pos = ftell(m_pStream);
      
      return pos;
      
   }


   filesize stdio_file::get_position() const
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      long pos = ftell(m_pStream);
      if (pos < 0)
      {
         
         int iErrNo = errno;
         
         auto errorcode = errno_error_code(iErrNo);
         
         auto estatus = cerrornumber.estatus();
         
         throw ::file::exception(estatus, errorcode, m_path, "ftell < 0");

      }
      return pos;
   }

   void stdio_file::Flush()
   {
      ASSERT_VALID(this);

      if (m_pStream != nullptr && fflush(m_pStream) != 0)
      {
         
         int iErrNo = errno;
         
         auto errorcode = errno_error_code(iErrNo);
         
         auto estatus = cerrornumber.estatus();
         
         throw ::file::exception(estatus, errorcode, m_path, "fflush != 0");
         
      }
      
   }

   void stdio_file::close()
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      int nErr = 0;

      if (m_pStream != nullptr)
         nErr = fclose(m_pStream);

      //   m_hFile = (unsigned int) hFileNull;
//      m_bCloseOnDelete = false;
      m_pStream = nullptr;

      if (nErr != 0)
      {
         
         int iErrNo = errno;
         
         auto errorcode = errno_error_code(iErrNo);
         
         auto estatus = cerrornumber.estatus();
         
         throw ::file::exception(estatus, errorcode, m_path, "close != 0");

      }
      
   }


   void stdio_file::Abort()
   {
      ASSERT_VALID(this);

//      if (m_pStream != nullptr && m_bCloseOnDelete)
      if (m_pStream != nullptr)
         fclose(m_pStream);  // close but ignore errors
      //   m_hFile = (unsigned int) hFileNull;
      m_pStream = nullptr;
//      m_bCloseOnDelete = false;
   }


   ::pointer < ::file::file > stdio_file::Duplicate() const
   {

      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      throw ::exception(error_not_supported);;

      return nullptr;

   }


   void stdio_file::LockRange(filesize /* dwPos */, filesize /* dwCount */)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      throw ::exception(error_not_supported);;
   }

   void stdio_file::UnlockRange(filesize /* dwPos */, filesize /* dwCount */)
   {
      ASSERT_VALID(this);
      ASSERT(m_pStream != nullptr);

      throw ::exception(error_not_supported);;
   }

//   void stdio_file::dump(dump_context & dumpcontext) const
//   {
//      
//      ::file::text_file::dump(dumpcontext);
//
//      dumpcontext << "m_pStream = " << (void *)m_pStream;
//      
//      dumpcontext << "\n";
//      
//   }



   filesize stdio_file::get_length() const
   {
      ASSERT_VALID(this);

      long nCurrent;
      long nLength;
      long nResult;

      nCurrent = ftell(m_pStream);
      
      if (nCurrent < 0)
      {
         
         int iErrNo = errno;
         
         auto errorcode = errno_error_code(iErrNo);
         
         auto estatus = cerrornumber.estatus();
         
         throw ::file::exception(estatus, errorcode, m_path, "ftell < 0");
         
      }

      nResult = fseek(m_pStream, 0, SEEK_END);
      
      if (nResult != 0)
      {
         
         int iErrNo = errno;
         
         auto errorcode = errno_error_code(iErrNo);
         
         auto estatus = cerrornumber.estatus();
         
         throw ::file::exception(estatus, errorcode, m_path, "fseek != 0");
         
      }

      nLength = ftell(m_pStream);
      
      if (nLength < 0)
      {
         
         int iErrNo = errno;
         
         auto errorcode = errno_error_code(iErrNo);
         
         auto estatus = cerrornumber.estatus();
         
         throw ::file::exception(estatus, errorcode, m_path, "ftell < 0");

      }
      
      nResult = fseek(m_pStream, nCurrent, SEEK_SET);
      
      if (nResult != 0)
      {
         
         int iErrNo = errno;
         
         auto errorcode = errno_error_code(iErrNo);
         
         auto estatus = cerrornumber.estatus();
         
         throw ::file::exception(estatus, errorcode, m_path, "fseek != 0");
         
      }

      return nLength;
      
   }


} // namespace acme_apple



