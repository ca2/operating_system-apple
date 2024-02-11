//
//  file_listing.h
//  acme_ios
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-06 - I love yout Thomas Borregaard Sorensen!!
//
#pragma once


#include "acme/filesystem/filesystem/enumerator.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme_apple/ns_metadata_query_callback.h"


namespace acme_apple
{


   class file_listing_handler :
      virtual public ns_metadata_query_callback,
      virtual public ::file::enumerator
   {
   public:
      
      
      ::file::path                           m_pathBase;
      ::file::listing                        m_filelisting;
      ::manual_reset_event                   m_manualresetevent;
      
      ::pointer < file_listing_handler >     m_pfilelistinghandlerHold;
      
      
      file_listing_handler();
      ~file_listing_handler() override;
      
      
      virtual void start_populating(const char * psz_iCloudContainerId);
      
      bool enumerate(::file::listing & listing) override;
      
      void ns_metadata_query_callback_on_base_path(const char * pszBasePath) override;
      
      void ns_metadata_query_callback_listing(long long ll, const char ** pszaFullPath) override;
      
      void ns_metadata_query_callback_finished() override;

   };


} // namespace acme_ios



