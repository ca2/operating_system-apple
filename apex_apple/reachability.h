/*
 Copyright (C) 2016 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 Basic demonstration of how to use the SystemConfiguration Reachablity APIs.
 */
#pragma once
//#include <Foundation/Foundation.h>
#include <SystemConfiguration/SystemConfiguration.h>
#include <netinet/in.h>

//#import "Reachability.h"
#include "acme/handler/source.h"

namespace apex_apple
{

enum enum_reachability
{
   e_reachability_none,
   e_reachability_wifi,
   e_reachability_wireless_wide_area_network,
} ;

//#pragma mark IPv6 Support
//Reachability fully support IPv6.  For full details, see ReadMe.md.


//extern NSString *kReachabilityChangedNotification;


class CLASS_DECL_APEX_APPLE reachability :
virtual public ::source
{
public:
   
   CFRunLoopRef m_runloopref;
   SCNetworkReachabilityRef      m_networkreachabilityref;
   
   reachability();
   ~reachability() override;
   
//#pragma mark reachabilityForLocalWiFi
   //reachabilityForLocalWiFi has been removed from the sample.  See ReadMe.md for more information.
   //+ (instancetype)reachabilityForLocalWiFi;
   
   /*!
    * Start listening for reachability notifications on the current run loop.
    */
   virtual bool start_notifier();
   virtual void stop_notifier();
   
   virtual enum_reachability current_reachability();
   
   /*!
    * WWAN may be available, but not active until a connection has been established. WiFi may require a connection for VPN on Demand.
    */
   virtual bool is_connection_required();
  
   //virtual void reachability_callback(SCNetworkReachabilityRef target, SCNetworkReachabilityFlags flags);
};


} // namespace apex_apple
