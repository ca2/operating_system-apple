// Created by camilo on 2024-09-13 00:36 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/still.h"
#include "__impact.h"
//#include <gtk/gtk.h>

namespace innate_ui_appkit
{

class icon;


   class CLASS_DECL_INNATE_UI_APPKIT still :
      virtual public ::innate_ui_appkit::__impact,
      virtual public ::innate_ui::still
   {
   public:

      //GtkWidget * m_pgtkwidget;

      bool m_bIcon;

      still();
      ~still() override;

      virtual void __create();

      void _create_child(window * pwindowParent) override;
      void create_icon_still(::innate_ui::window * pwindowParent) override;

      void set_icon(::innate_ui::icon * picon) override;
      //void set_text(const ::scoped_string & scopedstr) override;
      virtual void __set_icon(::innate_ui_appkit::icon * picon);
      void __set_text(const char * pszText) override;
      
      
   };


} // namespace innate_ui_appkit




