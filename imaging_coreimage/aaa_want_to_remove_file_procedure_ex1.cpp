#include "framework.h"


unsigned int _stdcall ___Ex1File__WriteProc(void * buffer, unsigned int size, unsigned int count, fi_handle handle)
{

   file_pointer  pfile = (::file::file *) handle;

   try
   {

      pfile->write(buffer, count * size);

   }
   catch (...)
   {

      return --count;

   }

   return count;

}


int _stdcall ___Ex1File__SeekProc(fi_handle handle, long offset, int origin)
{

   file_pointer  pfile = (::file::file *) handle;

   if (origin == SEEK_SET)
   {

      origin = ::e_seek_set;

   }
   else if (origin == SEEK_CUR)
   {

      origin = ::e_seek_current;

   }
   else if (origin == SEEK_END)
   {

      origin = ::e_seek_from_end;

   }

   if (pfile->seek(offset, (::enum_seek) origin) == 0xFFFFFFFF)
   {

      return -1;

   }
   else
   {

      return 0;

   }

}


long _stdcall ___Ex1File__TellProc(fi_handle handle)
{

   file_pointer  pfile = (::file::file *) handle;

   return (long)pfile->get_position();

}




