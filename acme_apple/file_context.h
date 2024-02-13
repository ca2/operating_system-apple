//
// Created by camilo on 26/04/2021. 00:02 BRT <3TBS_!!
//
#pragma once


#include "acme_darwin/file_context.h"


namespace acme_apple
{


   class CLASS_DECL_ACME_POSIX file_context :
      virtual public ::acme_darwin::file_context
   {
   public:


//      virtual ::payload length(const ::file::path & path, ::payload * pvarQuery) override;
      ::file_pointer defer_get_protocol_file(const ::scoped_string & scopedstrProtocol, const ::file::path & path, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception) override;


   };


} // namespace apex_apple



