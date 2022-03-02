#pragma once


#include "aura/graphics/draw2d/object.h"


namespace draw2d_quartz2d
{
   
   
   class CLASS_DECL_DRAW2D_QUARTZ2D object :
   virtual public ::draw2d::object
   {
   public:
      
      
      object();
      ~object() override;
      
      
      //virtual void * get_os_data() const;
      
      
      bool delete_object();
      
      
      i32 get_object(i32 nCount, void * lpObject) const;
      ::u32 GetObjectType() const override;
      bool CreateStockObject(i32 nIndex) override;
      bool UnrealizeObject() override;
      
   };
   
   
} // namespace draw2d_quartz2d
