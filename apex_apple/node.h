//
// Created by camilo on 19/01/2021. <33TBS!!
//
//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "apex_darwin/node.h"
#include "acme_apple/node.h"
#include "reachability.h"


namespace apex_apple
{


   class CLASS_DECL_APEX_APPLE node :
      virtual public ::apex_darwin::node,
      virtual public ::acme_apple::node
   {
   public:

      
      ::pointer < reachability > m_preachabilityIp4Internet;
      ::pointer < reachability > m_preachabilityIp6Internet;


      node();
      ~node() override;

      
      int node_init_check(int * pi, char *** ppz) override;
      
      ::pointer < reachability >  __reachability(SCNetworkReachabilityRef networkreachabilityref);
      /*!
       * Use to check the reachability of a given host name.
       */
      ::pointer < reachability > reachability_from_host_name(const ::scoped_string & scopedstrHostname);

      /*!
       * Use to check the reachability of a given IP address.
       */
         ::pointer < reachability > reachability_from_address(const struct sockaddr * psockaddrHost);

      /*!
       * Checks whether the default route is available. Should be used by applications that do not connect to a particular host.
       */
         ::pointer < reachability > reachability_for_ip4_internet();
         
         ::pointer < reachability > reachability_for_ip6_internet();

      bool has_ip4_internet() override;
      bool has_ip6_internet() override;

   };


} // namespace apex_apple



