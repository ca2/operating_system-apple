//
//  ns_metadata_query_callback.h
//  acme_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-06 <3ThomasBorregaardSorensen!!
//
#pragma once


class ns_metadata_query_callback
{
public:
   
   void * m_pNSMetadataQueryHandler;
   
   bool        m_bPublic;
   
   ns_metadata_query_callback();

   virtual void ns_metadata_query_callback_on_base_path(const char * pszBasePath);

   virtual void ns_metadata_query_callback_listing(::i64 ll, const char ** pszaFullPath, int * piaFlag);
   
   virtual void ns_metadata_query_callback_finished();
   
   virtual void ns_metadata_query_callback_uninstall();
   
};

   
