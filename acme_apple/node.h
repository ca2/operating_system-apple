//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace acme
{


   namespace apple
   {


      class CLASS_DECL_ACME node :
         virtual public ::acme::posix::node
      {
      public:

         
         __creatable_from_library(node, ::acme::node, "acme_apple");
         

         node();
         ~node() override;


         //virtual ::color::color get_system_color(enum_system_color esystemcolor) override;

         virtual int node_init_check(int * pi, char *** ppz) override;

         //virtual ::e_status start_node();

         //override;

         void initialize(::object * pobject) override;



         void install_sigchld_handler() override;


         string audio_get_default_library_name() override;
      
         string multimedia_audio_mixer_get_default_library_name() override;
      
         string veriwell_multimedia_music_midi_get_default_library_name() override;
         
         
         void node_post(const ::routine & routine) override;
         
         void shell_execute_async(const char * pszFile, const char * pszParams) override;
         

      };


   } // namespace apple


} // namespace acme



