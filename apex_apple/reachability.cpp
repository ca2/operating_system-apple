/*
 Copyright (C) 2016 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 Basic demonstration of how to use the SystemConfiguration Reachablity APIs.
 */
#include "framework.h"
#include "reachability.h"
#include "node.h"
#include "acme/constant/id.h"
#include "acme/platform/application.h"
#include "acme/_operating_system.h"
#import <arpa/inet.h>
#import <ifaddrs.h>
#import <netdb.h>
#import <sys/socket.h>
#import <netinet/in.h>

//#import <CoreFoundation/CoreFoundation.h>


//#pragma mark IPv6 Support
//Reachability fully support IPv6.  For full details, see ReadMe.md.


//NSString *kReachabilityChangedNotification = @"kNetworkReachabilityChangedNotification";


//#pragma mark - Supporting functions

#define kShouldPrintReachabilityFlags 1

namespace apex_apple
{


reachability::reachability()
{
   
   m_runloopref = nullptr;
   m_networkreachabilityref = nullptr;
   
}



static void PrintReachabilityFlags(SCNetworkReachabilityFlags flags, const char* comment)
{
#if kShouldPrintReachabilityFlags
#ifdef APPLE_IOS
   printf("Reachability Flag Status: %c%c %c%c%c%c%c%c%c %s\n",

          (flags & kSCNetworkReachabilityFlagsIsWWAN)				? 'W' : '-',
          (flags & kSCNetworkReachabilityFlagsReachable)            ? 'R' : '-',
          
          (flags & kSCNetworkReachabilityFlagsTransientConnection)  ? 't' : '-',
          (flags & kSCNetworkReachabilityFlagsConnectionRequired)   ? 'c' : '-',
          (flags & kSCNetworkReachabilityFlagsConnectionOnTraffic)  ? 'C' : '-',
          (flags & kSCNetworkReachabilityFlagsInterventionRequired) ? 'i' : '-',
          (flags & kSCNetworkReachabilityFlagsConnectionOnDemand)   ? 'D' : '-',
          (flags & kSCNetworkReachabilityFlagsIsLocalAddress)       ? 'l' : '-',
          (flags & kSCNetworkReachabilityFlagsIsDirect)             ? 'd' : '-',
          comment
          );
#else
   printf("Reachability Flag Status: %c%c %c%c%c%c%c%c %s\n",

          (flags & kSCNetworkReachabilityFlagsReachable)            ? 'R' : '-',
          
          (flags & kSCNetworkReachabilityFlagsTransientConnection)  ? 't' : '-',
          (flags & kSCNetworkReachabilityFlagsConnectionRequired)   ? 'c' : '-',
          (flags & kSCNetworkReachabilityFlagsConnectionOnTraffic)  ? 'C' : '-',
          (flags & kSCNetworkReachabilityFlagsInterventionRequired) ? 'i' : '-',
          (flags & kSCNetworkReachabilityFlagsConnectionOnDemand)   ? 'D' : '-',
          (flags & kSCNetworkReachabilityFlagsIsLocalAddress)       ? 'l' : '-',
          (flags & kSCNetworkReachabilityFlagsIsDirect)             ? 'd' : '-',
          comment
          );
#endif
#endif
}


static void ReachabilityCallback(SCNetworkReachabilityRef target, SCNetworkReachabilityFlags flags, void* info)
{
#pragma unused (target, flags)
   //NSCAssert(info != NULL, @"info was NULL in ReachabilityCallback");
   //NSCAssert([(__bridge NSObject*) info isKindOfClass: [Reachability class]], @"info was wrong class in ReachabilityCallback");
   
   reachability * preachability = (reachability *)info;
   // Post a notification to notify the client that the network reachability changed.
   //[[NSNotificationCenter defaultCenter] postNotificationName: kReachabilityChangedNotification object: noteObject];
   preachability->notify_topic(id_network_reachability_status_change);
}


//#pragma mark - Reachability implementation
//
//@implementation Reachability
//{
//   
//}
::pointer < reachability >  node::__reachability(SCNetworkReachabilityRef networkreachabilityref)
{
   
   ::pointer < reachability > preachability;
   
   try
   {
      
      __construct_new(preachability);
      
      preachability->m_networkreachabilityref = networkreachabilityref;
      
   }
   catch (...)
   {
      
      CFRelease(networkreachabilityref);
      
   }
   
   return preachability;
   
}


::pointer < reachability> node::reachability_from_host_name(const ::scoped_string & scopedstrHostname)
{
   
   SCNetworkReachabilityRef networkreachabilityref = SCNetworkReachabilityCreateWithName(NULL, scopedstrHostname.c_str());
   
   if (networkreachabilityref == NULL)
   {
      
      return nullptr;
      
   }
   
   return __reachability(networkreachabilityref);
   
}


::pointer < reachability> node::reachability_from_address(const struct sockaddr *hostAddress)
{
   SCNetworkReachabilityRef networkreachabilityref = SCNetworkReachabilityCreateWithAddress(kCFAllocatorDefault, hostAddress);
   
   if (networkreachabilityref == NULL)
   {
      
      return nullptr;
      
   }
   
   return __reachability(networkreachabilityref);

}


::pointer < reachability> node::reachability_for_ip4_internet()
{
   struct sockaddr_in zeroAddress{};
   zeroAddress.sin_len = sizeof(zeroAddress);
   zeroAddress.sin_family = AF_INET;
   zeroAddress.sin_addr.s_addr = 0x08080808;
   
   return reachability_from_address((const struct sockaddr *) &zeroAddress);
}


::pointer < reachability> node::reachability_for_ip6_internet()
{
   struct sockaddr_in6 zeroAddress{};
   zeroAddress.sin6_len = sizeof(zeroAddress);
   zeroAddress.sin6_family = AF_INET6;
   zeroAddress.sin6_addr.__u6_addr.__u6_addr16[0]=0x2001; // Google Public DNS 1
   zeroAddress.sin6_addr.__u6_addr.__u6_addr16[1]=0x4860;
   zeroAddress.sin6_addr.__u6_addr.__u6_addr16[2]=0x4860;
   zeroAddress.sin6_addr.__u6_addr.__u6_addr16[7]=0x8888;
   
   return reachability_from_address((const struct sockaddr *) &zeroAddress);
}


//#pragma mark reachabilityForLocalWiFi
//reachabilityForLocalWiFi has been removed from the sample.  See ReadMe.md for more information.
//+ (instancetype)reachabilityForLocalWiFi



//#pragma mark - Start and stop notifier

bool reachability::start_notifier()
{
   SCNetworkReachabilityContext context = {0, this, NULL, NULL, NULL};
   
   if (!SCNetworkReachabilitySetCallback(m_networkreachabilityref, &ReachabilityCallback, &context))
   {
      
      return false;
      
   }

   application()->fork([this]()
                       {
      m_runloopref = CFRunLoopGetCurrent();

      SCNetworkReachabilityScheduleWithRunLoop(m_networkreachabilityref, m_runloopref, kCFRunLoopDefaultMode);
      
      CFRunLoopRun();
      
   });
   
   return true;
   
}

void reachability::stop_notifier()
{
   if (m_networkreachabilityref)
   {
      
      SCNetworkReachabilityUnscheduleFromRunLoop(m_networkreachabilityref, m_runloopref, kCFRunLoopDefaultMode);
      
      CFRunLoopStop(m_runloopref);
      
      m_runloopref = nullptr;
      
   }
}


reachability::~reachability()
{
   stop_notifier();
   if (m_networkreachabilityref)
   {
      CFRelease(m_networkreachabilityref);
      m_networkreachabilityref = nullptr;
   }
}


//#pragma mark - Network Flag Handling

enum_reachability ereachability_for_flags(SCNetworkReachabilityFlags flags)
{
   PrintReachabilityFlags(flags, "networkStatusForFlags");
   if ((flags & kSCNetworkReachabilityFlagsReachable) == 0)
   {
      // The target host is not reachable.
      return e_reachability_none;
   }
   
   enum_reachability returnValue = e_reachability_none;
   
   if ((flags & kSCNetworkReachabilityFlagsConnectionRequired) == 0)
   {
      /*
       If the target host is reachable and no connection is required then we'll assume (for now) that you're on Wi-Fi...
       */
      returnValue = e_reachability_wifi;
   }
   
   if ((((flags & kSCNetworkReachabilityFlagsConnectionOnDemand ) != 0) ||
        (flags & kSCNetworkReachabilityFlagsConnectionOnTraffic) != 0))
   {
      /*
       ... and the connection is on-demand (or on-traffic) if the calling application is using the CFSocketStream or higher APIs...
       */
      
      if ((flags & kSCNetworkReachabilityFlagsInterventionRequired) == 0)
      {
         /*
          ... and no [user] intervention is needed...
          */
         returnValue = e_reachability_wifi;
      }
   }
   
#ifdef APPLE_IOS
   if ((flags & kSCNetworkReachabilityFlagsIsWWAN) == kSCNetworkReachabilityFlagsIsWWAN)
   {
      /*
       ... but WWAN connections are OK if the calling application is using the CFNetwork APIs.
       */
      returnValue = e_reachability_wireless_wide_area_network;
   }
   
#endif
   
   return returnValue;
}


bool reachability::is_connection_required()
{
//   NSAssert(_reachabilityRef != NULL, @"connectionRequired called with NULL reachabilityRef");
   SCNetworkReachabilityFlags flags;
   
   if (SCNetworkReachabilityGetFlags(m_networkreachabilityref, &flags))
   {
      return (flags & kSCNetworkReachabilityFlagsConnectionRequired);
   }
   
   return false;
}


enum_reachability reachability::current_reachability()
{
   //NSAssert(_reachabilityRef != NULL, @"currentNetworkStatus called with NULL SCNetworkReachabilityRef");
   enum_reachability returnValue = e_reachability_none;
   SCNetworkReachabilityFlags flags;
   
   if (SCNetworkReachabilityGetFlags(m_networkreachabilityref, &flags))
   {
      returnValue = ereachability_for_flags(flags);
   }
   
   return returnValue;
}


//@end


} // namespace apex_apple
