//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace aura
{


	namespace apple
	{


      class CLASS_DECL_AURA_APPLE node :
         virtual public ::aura::posix::node,
         virtual public ::apex::apple::node
      {
      public:

         
         node();
         virtual ~node();


         virtual ::e_status initialize(::object * pobject) override;


      };


   } // namespace apple


} // namespace aura



