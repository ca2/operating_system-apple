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
      
      
      int get_object(int nCount, void * lpObject) const;
      //::u32 GetObjectType() const override;
      //bool CreateStockObject(int nIndex) override;
      //bool UnrealizeObject() override;
      
   };
   
   
} // namespace draw2d_quartz2d
