//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "aura_darwin/node.h"
#include "apex_apple/node.h"


namespace aura_apple
{


//	namespace apple
//	{
//

      class CLASS_DECL_AURA_APPLE node :
         virtual public ::aura_darwin::node,
         virtual public ::apex_apple::node
      {
      public:

         
         node();
         ~node() override;


         void initialize(::particle * pparticle) override;

         
         ::image_pointer get_file_image_by_type_identifier(int iSize, const ::scoped_string & scopedstrTypeIdentifier) override;

         ::image_pointer get_file_image(int iSize, const ::file::path & path) override;

         void on_start_system() override;
        
         
         
      };

//
//   } // namespace apple


} // namespace aura_apple



