//
//  ProcedureCaller.h
//  innate_ui_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-09-20 20:26
//
#pragma once


#include <AppKit/AppKit.h>



@interface ProcedureCaller: NSObject
{
 
   ::procedure m_procedure;
   
};

-(void) callProcedure;
- (id)initWithProcedure:(const ::procedure &) procedure;
@end

