//
// Created by camilo on 19/01/2021. <33TBS!!
//
//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "apex_posix/node.h"
#include "acme_apple/node.h"


namespace apex_apple
{


   class CLASS_DECL_APEX_APPLE node :
      virtual public ::apex_posix::node,
      virtual public ::acme_apple::node
   {
   public:


      node();
      ~node() override;

      
      int node_init_check(int * pi, char *** ppz) override;


   };


} // namespace apex_apple



