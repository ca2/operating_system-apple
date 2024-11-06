#pragma once


#include "object.h"
#include "aura/graphics/draw2d/pen.h"


namespace draw2d_quartz2d
{
   
   
   class CLASS_DECL_DRAW2D_QUARTZ2D pen :
      virtual public ::draw2d_quartz2d::object,
      virtual public ::draw2d::pen
   {
   public:
      
      
      
      //int                  m_iStock;
      //int                  m_iStyle;
      //int                  m_iWidth;
      //color32_t             m_color;
      
      
      pen();
      ~pen() override;
      /*virtual void construct(int nPenStyle, double nWidth, color32_t crColor);
       virtual void construct(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const ::u32* lpStyle = nullptr);
       bool CreatePen(int nPenStyle, double nWidth, color32_t crColor);
       bool CreatePen(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const ::u32* lpStyle = nullptr);*/
      
      
      //      virtual void * get_os_data() const;
      
      //void dump(dump_context & dumpcontext) const override;
      
   };
   
   
} // namespace draw2d_quartz2d





