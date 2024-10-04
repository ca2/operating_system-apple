// Created by camilo on 2024-09-12 22:34 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/dialog.h"
#include "window.h"


namespace innate_ui_appkit
{


   class CLASS_DECL_INNATE_UI_APPKIT dialog :
      virtual public ::innate_ui_appkit::window,
      virtual public ::innate_ui::dialog
   {
   public:


      //GtkWidget *       m_pgtkwidgetFixed;


      dialog();
      ~dialog() override;


      virtual void __create();
      void _create() override;
      //void _get_class(WNDCLASSEXW & wcex);
      //void set_text(const ::scoped_string & scopedstr) override;
   };


} // namespace innate_ui_appkit




