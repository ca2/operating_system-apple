#pragma once


namespace music
{


   namespace midi
   {


      namespace core_midi
      {


         class player_callback;


         class CLASS_DECL_MUSIC_MIDI_CORE_MIDI player :
            virtual public ::music::midi::player::player
         {
         public:


            player(::object * pobject);
            virtual ~player();



            void install_message_routing(::channel * pchannel) override;


            //bool PlayRate(double dRate = 0.0, unsigned int dwEllapse = 500) override;
            //bool Play(imedia_time tkStart, unsigned int dwEllapse = 500) override;

            virtual bool init_thread() override;
            virtual void term_thread() override;
            virtual void pre_translate_message(::message::message * pmessage) override;
            void OnMmsgDone(::music::midi::sequence *pSeq) override;
            DECLARE_MESSAGE_HANDLER(OnUserMessage);
            //virtual void SaveFile(memory & memory) override;
            void SetPosition(double dRate) override;
            void pause() override;
            //void close_file() override;
            //void SendReset();
            //virtual bool ExecuteCommand(enum_command ecommand, unsigned int dwEllapse) override;
            virtual void OnMidiOutDeviceChange() override;

            //virtual ::payload get_midi_out_device() override;
            //void PostNotifyEvent(e_notify_happening ehappening) override;

            //imedia_time RateToTicks(double dRate) override;

            bool SetTempoShift(int iTempoShift);

            //bool SetMidiOutDevice(unsigned int uiDevice) override;

            //virtual ::e_status     set_client(::music::midi::player_client * pclient) override;

            ::e_status     Initialize(::thread * pthread);

            bool IsPlaying() override;

            //void PostGMReset() override;
            //void PostTempoChange() override;
            //void SendTempoChange() override; // verificar


            //DECLARE_MESSAGE_HANDLER(OnNotifyEvent);
            DECLARE_MESSAGE_HANDLER(OnMultimediaMidiOutputMessageDone);
            //DECLARE_MESSAGE_HANDLER(OnMultimediaMidiOutputMessagePositionCB);

            // midi central listener
            virtual void on_attribute_change(::message::message * pmessage) override;


         };


      } // namespace core_midi


   } // namespace midi


} // namespace music



