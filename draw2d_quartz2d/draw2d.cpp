#include "framework.h"
#include "draw2d.h"
#include "acme/prototype/prototype/memory.h"
#include "aura/platform/system.h"


namespace draw2d_quartz2d
{


   draw2d::draw2d()
   {
      
   }


   draw2d::~draw2d()
   {

   }


   void draw2d::initialize(::particle * pparticle)
   {

      ::draw2d::draw2d::initialize(pparticle);

   }


   string draw2d::write_text_get_default_implementation_name()
   {

      return system()->implementation_name("write_text", "quartz2d");

   }

   
   CGFontRef draw2d::private_cgfontref(::acme::context * pcontext, const ::file::path & path)
   {
      
      auto & pprivatefont = m_mapPrivateFont[path];
      
      if(::is_set(pprivatefont))
      {
         
         return pprivatefont->m_cgfontref;
         
      }
      
      pprivatefont = new private_font();
      
      pprivatefont->m_cgfontref = nullptr;

      auto pmemory = system()->m_paurasystem->draw2d()->write_text()->get_file_memory(pcontext, path);

      if(!pmemory || pmemory->is_empty())
      {
       
         return nullptr;
         
      }
   
      CFDataRef dataref = CFDataCreate(nullptr, pmemory->data(), pmemory->size());
   
      CGDataProviderRef dataproviderref = CGDataProviderCreateWithCFData(dataref);

      CFRelease(dataref);

      pprivatefont->m_cgfontref = CGFontCreateWithDataProvider(dataproviderref);

      CGDataProviderRelease(dataproviderref);
   
      return pprivatefont->m_cgfontref;
      
   }


} // namespace draw2d_quartz2d

