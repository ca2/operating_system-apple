//
//  draw2d_quartzd_mm.m
//  draw2d_quartz2d
//
//  Created by Camilo Sasuke Tsumanuma on 27/10/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>


CGMutablePathRef cg_mutable_path_from_ns_bezier_path(NSBezierPath * path)
{
   
   long i, numElements;

   // Need to begin a path here.
   // Then draw the path elements.
   numElements = [path elementCount];

   if (numElements <= 0)
   {

      return nullptr;

   }
   
   CGMutablePathRef mutablepath = CGPathCreateMutable();

   NSPoint             points[3];
   BOOL                didClosePath = YES;

   for (i = 0; i < numElements; i++)
   {
      
      switch ([path elementAtIndex:i associatedPoints:points])
      {
         case NSBezierPathElementMoveTo:
         CGPathMoveToPoint(mutablepath, NULL, points[0].x, points[0].y);
         break;

         case NSBezierPathElementLineTo:
         CGPathAddLineToPoint(mutablepath, NULL, points[0].x, points[0].y);
         didClosePath = NO;
         break;

         case NSBezierPathElementCurveTo:
         CGPathAddCurveToPoint(mutablepath, NULL, points[0].x, points[0].y,
                         points[1].x, points[1].y,
                         points[2].x, points[2].y);
         didClosePath = NO;
         break;

         case NSBezierPathElementClosePath:
         CGPathCloseSubpath(mutablepath);
         didClosePath = YES;
         break;
         case NSBezierPathElementQuadraticCurveTo:
            CGPathAddQuadCurveToPoint(mutablepath, NULL, points[0].x, points[0].y,
                            points[1].x, points[1].y);
            didClosePath = NO;
            break;
      }
      
   }

   // Be sure the path is closed or Quartz may not do valid hit detection.
   if (!didClosePath)
   {
      
      CGPathCloseSubpath(mutablepath);
      
   }

   //immutablePath = CGPathCreateCopy(path);
   //CGPathRelease(path);
   //   }

   return mutablepath;
   
}


CGMutablePathRef ns_rounded_rect_path(CGRect r, double rx, double ry)
{
   
   //https://stackoverflow.com/questions/11971866/rounded-corner-gradient-background-of-window-in-cocoa
   //https://stackoverflow.com/users/247203/radex
   NSBezierPath *path = [NSBezierPath bezierPathWithRoundedRect:r xRadius:rx yRadius:ry];
 
   // Get the CGPathRef and create a mutable version.
   CGMutablePathRef cgmutablePath = cg_mutable_path_from_ns_bezier_path(path);
   
   return cgmutablePath;
   
}



