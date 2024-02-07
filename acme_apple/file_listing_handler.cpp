//
//  file_listing.h
//  acme_ios
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-06 - I love yout Thomas Borregaard Sorensen!!
//
#include "framework.h"
#include "file_listing_handler.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/parallelization/synchronous_lock.h"


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

      listing.m_pathFinal = listing.m_pathUser;

   }

   if (listing.m_pathBasePath.is_empty())
   {

      listing.m_pathBasePath = listing.m_pathFinal;

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
      
      path.m_iDir = 0;
      
      listing.defer_add(path);
      
   }

   return true;

}


} // namespace acme_apple



