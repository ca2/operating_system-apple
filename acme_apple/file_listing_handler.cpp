//
//  file_listing.h
//  acme_ios
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-06 - I love yout Thomas Borregaard Sorensen!!
//
#include "framework.h"
#include "file_listing_handler.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/time/_text_stream.h"


void ns_app_cloud_start_metadata_query(ns_metadata_query_callback * pcallback, const char * pszAppCloudContainerIdentifier);


namespace acme_apple
{


   file_listing_handler::file_listing_handler()
   {
      
      defer_create_synchronization();
      
      m_pfilelistinghandlerHold = this;
      
      m_manualresetevent.ResetEvent();
      
   }


   file_listing_handler::~file_listing_handler()
   {
 
      ns_metadata_query_callback_uninstall();
   
   }

   
   void file_listing_handler::start_populating(const char * pszAppCloudContainerIdentifier)
   {
      
      auto start = ::time::now();

      m_manualresetevent.ResetEvent();
      
      try
      {
         
         ns_app_cloud_start_metadata_query(this, pszAppCloudContainerIdentifier);
         
      }
      catch (const char * psz)
      {
         
         ::string str(psz);
         
         if(str == "failed container identifier")
         {
            
            throw ::exception(error_failed);
            
         }
         
      }
      
      m_manualresetevent.wait(1_minute);
      
      {
         
         _synchronous_lock _synchronouslock(this->synchronization());
         
         information() << "Got " << m_filelisting.size() << " items!!";
         
         for(auto & path : m_filelisting)
         {
            
            information() << "Got :" << path;
            
         }
         
         information() << "Got after certain time: " << start.elapsed();
         
      }

   }


void file_listing_handler::ns_metadata_query_callback_on_base_path(const char * pszBasePath)
{
   
   m_pathBase = pszBasePath;
   
}
   
   
void file_listing_handler::ns_metadata_query_callback_on_item(const char * pszFullPath)
{
   
   _synchronous_lock _synchronouslock(this->synchronization());
   
   m_filelisting.add_unique(pszFullPath);
   
   m_filelisting.order();
   
//   ::file::path path;
//   
//   ::file::path pathName;
//   
//   path = pathName.name();
//   
//   m_filelisting.m_eflag +=::file::e_flag_file;
//   
//   path.m_iDir = 0;
//   
//   m_filelisting.defer_add(path);
   
}

void file_listing_handler::ns_metadata_query_callback_finished()
{
 
   m_manualresetevent.SetEvent();
   
}


bool file_listing_handler::enumerate(::file::listing& listing)
{

   if (listing.m_pathFinal.is_empty())
   {
      
      ::string str = listing.m_pathUser;
      
      if(str.begins_eat(acmedirectory()->app_cloud_document()))
      {
         
         listing.m_pathFinal = m_pathBase / str;
         
      }
      else
      {
         
         listing.m_pathFinal = listing.m_pathUser;
         
      }

   }

   if (listing.m_pathBasePath.is_empty())
   {

      listing.m_pathBasePath = m_pathBase;

   }
   
   ::string strFolder(listing.m_pathFinal);
   
   strFolder += "/";
   
   _synchronous_lock _synchronouslock(this->synchronization());

   auto iStart = m_filelisting.find_first_begins(strFolder);
   
   if(iStart < 0)
   {

      return false;

   }

   if (!listing.on_start_enumerating(this))
   {

      return true;

   }
   
   ::index iEnd = iStart + 1;
   
   for(iEnd = iStart + 1; iEnd < m_filelisting.size(); iEnd++)
   {
      
      auto & path = m_filelisting[iEnd];
      
      if(!path.begins(strFolder))
      {
         
         break;
         
      }
      
      if(path.find_first('/', strFolder.length()))
      {
         
         break;
         
      }
      
      path.m_iSize = listing.m_pathFinal.length();
      
      path.m_iBasePathLength = m_pathBase.length();
      
      path.m_iDir = 0;
      
      listing.defer_add(path);
      
   }

   return true;

}


} // namespace acme_apple



