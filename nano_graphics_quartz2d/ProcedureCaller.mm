//
//  ProcedureCaller.mm
//  innate_ui_appkit
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-09-20 20:25
//
#include "framework.h"
#include "ProcedureCaller.h"




@implementation ProcedureCaller

-(void)dealloc
{
   
   NSLog(@"ProcedureCaller::dealloc");
}
-(void) callProcedure
{
 
   m_procedure();
   
}

- (id)initWithProcedure:(const ::procedure &) procedure
{
 
   m_procedure = procedure;
   
   return self;
   
}
@end
