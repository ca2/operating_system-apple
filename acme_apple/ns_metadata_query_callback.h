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
   
   virtual void ns_metadata_query_callback_on_item(const char * pszName);
   
   virtual void ns_metadata_query_callback_finished();
   
   virtual void ns_metadata_query_callback_uninstall();
   
};

   
