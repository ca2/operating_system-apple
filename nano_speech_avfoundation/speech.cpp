#include "framework.h"
#include "speech.h"

void ns_speak(const char * psz, const char * pszLang, enum_gender egender);


namespace avfoundation
{


   namespace nano
{
   
 namespace speech
   {
 
 speech::speech()
 {
    
 }
 speech::~speech() {}
 
 
#ifdef _DEBUG
 
 huge_integer speech::increment_reference_count() {}
 huge_integer speech::decrement_reference_count() {}
 huge_integer speech::release() {}
 
#endif
 
 void speech::on_initialize_particle() {}
 
 
 void speech::speak(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrLang, enum_gender egender) {
    
    ::string str(scopedstr);::string strLang(scopedstr);
    
    ns_speak(str, strLang, egender);
    
 }
 
 } // namespace speech
   
   } // namespace nano


} // namespace avfoundation



