//
// Created by camilo on 2024-05-12 02:00 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/speech/speech.h"
//
//
//class nano_window_bridge;

namespace avfoundation
{


   namespace nano
{
   
   
   namespace speech
   {
   
   class CLASS_DECL_NANO_SPEECH_AVFOUNDATION speech :
   virtual public ::nano::speech::speech
   {
   public:
      
      
      speech();
      ~speech() override;
      
      
#ifdef _DEBUG
      
      virtual huge_integer increment_reference_count() override;
      virtual huge_integer decrement_reference_count() override;
      virtual huge_integer release() override;
      
#endif
      
      void on_initialize_particle() override;
      
      
      void speak(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrLang = "en-us", enum_gender egender = e_gender_none) override;
      
   };
   
   
   } // namespace speech
   
   
   } // namespace nano


} // namespace avfoundation



