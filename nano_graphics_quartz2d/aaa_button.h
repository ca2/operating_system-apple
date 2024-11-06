// Created by camilo on 2024-09-13 00:36 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/button.h"
#include "__impact.h"
//#include <gtk/gtk.h>


#ifdef __OBJC__

@class ProcedureCaller;

#endif

namespace innate_ui_appkit
{


   class CLASS_DECL_INNATE_UI_APPKIT button :
    virtual public ::innate_ui_appkit::__impact,
      virtual public ::innate_ui::button
   {
   public:


     //GtkWidget * m_pgtkwidget;
#ifdef __OBJC__
      ProcedureCaller *m_pcaller;
#else
      void *m_pCaller;
#endif
      
      button();
      ~button() override;

      
      virtual void __create();

      void _create_child(window * pwindowParent) override;

      //bool _on_command() override;

      void set_icon(::innate_ui::icon * picon) override;
      void set_callback_on_click(const ::procedure & callbackOnClick) override;
      void __set_text(const char * pszText) override;
      void __set_callback();
      void    __button_release();
   };


} // namespace innate_ui_win32




