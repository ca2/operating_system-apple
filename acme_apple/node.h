//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


#include "acme_darwin/node.h"


namespace acme_apple
{


   class CLASS_DECL_ACME node :
      virtual public ::acme_darwin::node
   {
   public:

      
      //__creatable_from_library(node, ::platform::node, "acme_apple");
      

      node();
      ~node() override;


      //virtual ::color::color get_system_color(enum_system_color esystemcolor) override;

      virtual int node_init_check(int * pi, char *** ppz) override;


      void initialize(::particle * pparticle) override;


      void install_sigchld_handler() override;


      string audio_get_default_implementation_name() override;
   
      string multimedia_audio_mixer_get_default_implementation_name() override;
   
      string veriwell_multimedia_music_midi_get_default_implementation_name() override;
      
      
      void _user_post(const ::procedure & procedure) override;
      
      
      void shell_open(const ::file::path & path, const ::string & strParams = "", const ::file::path & pathFolder = "") override;
      
      ::file::path library_file_name(const ::scoped_string & scopedstr) override;

      ::string operating_system_store_release() override;
      
      ::pointer <::operating_system::summary > operating_system_summary() override;
      
      
      
      ::string operating_system_application_version() override;

      ::file::path_array process_identifier_modules_paths(::process_identifier processidentifier) override;
      //void speak(const ::scoped_string & scopedstr) override;

      ::string default_component_implementation(const ::scoped_string & scopedstrComponentName) override;
      
      
   };


} // namespace acme_apple



