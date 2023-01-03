//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "aura_posix/node.h"
#include "apex_apple/node.h"


namespace aura_apple
{


//	namespace apple
//	{
//

      class CLASS_DECL_AURA_APPLE node :
         virtual public ::aura_posix::node,
         virtual public ::apex_apple::node
      {
      public:

         
         node();
         ~node() override;


         void initialize(::particle * pparticle) override;


      };

//
//   } // namespace apple


} // namespace aura_apple



