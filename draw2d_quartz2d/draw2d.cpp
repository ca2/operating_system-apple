#include "framework.h"
#include "draw2d.h"
#include "aura/platform/system.h"


namespace draw2d_quartz2d
{


   draw2d::draw2d()
   {
      
   }


   draw2d::~draw2d()
   {

   }


   void draw2d::initialize(::object * pobject)
   {

      ::draw2d::draw2d::initialize(pobject);

   }


   string draw2d::write_text_get_default_library_name()
   {

      return "quartz2d";

   }

   
   CGFontRef draw2d::private_cgfontref(::acme::context * pcontext, const ::file::path & path)
   {
      
      auto & pprivatefont = m_mapPrivateFont[path];
      
      if(::is_set(pprivatefont))
      {
         
         return pprivatefont->m_cgfontref;
         
      }
      
      pprivatefont = __new(private_font);
      
      pprivatefont->m_cgfontref = nullptr;

      auto pmemory = m_psystem->m_paurasystem->draw2d()->write_text()->get_file_memory(pcontext, path);

      if(!pmemory || pmemory->is_empty())
      {
       
         return nullptr;
         
      }
   
      CFDataRef dataref = CFDataCreate(nullptr, pmemory->get_data(), pmemory->get_size());
   
      CGDataProviderRef dataproviderref = CGDataProviderCreateWithCFData(dataref);

      CFRelease(dataref);

      pprivatefont->m_cgfontref = CGFontCreateWithDataProvider(dataproviderref);

      CGDataProviderRelease(dataproviderref);
   
      return pprivatefont->m_cgfontref;
      
   }


} // namespace draw2d_quartz2d

