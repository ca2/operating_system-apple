#pragma once
//
//
//#define  VERSION_MINOR              0x00
//#define  VERSION_MAJOR              0x04
//#define  SEQ_VERSION                ((uint32_t)(WORD)((BYTE)VERSION_MINOR | (((WORD)(BYTE)VERSION_MAJOR) << 8)))
//
//#define MMSG_DONE                   (WM_USER+20)
//
//
//namespace music
//{
//
//   
//   namespace midi
//   {
//      
//      
//      namespace core_audio
//      {
//      
//
//      class buffer;
//      class sequence;
//      class sequence_thread;
//
//
//      class CLASS_DECL_VERIWELL_MULTIMEDIA midi_callback_data
//      {
//      public:
//
//
//         sequence *          m_psequence;
//
//
//      };
//
//
//      class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI sequence :
//         virtual public ::music::midi::sequence
//      {
//      public:
//
//         class buffer_array;
//         
//         enum e_message
//         {
//            
//            message_run = WM_APP + 1050,
//            
//         };
//         
//         
//         class buffer
//         {
//         public:
//            
//            
//            MIDIHDR              m_midihdr;
//            memory               m_storage;
//            bool                 m_bPrepared;
//
//            
//            bool IsPrepared();
//            void Reset();
//            void Initialize(int32_t iSize, uint32_t dwUser);
//            
//            inline LPMIDIHDR GetMidiHdr() { return &m_midihdr; }
//            
//            void SetNextMidiHdr(LPMIDIHDR lpNext);
//            
//            
//         };
//         
//         
//         class buffer_array :
//         public array < buffer, buffer >
//         {
//         public:
//            
//            
//            void Reset();
//            void Initialize(int32_t iCount, int32_t iSize, uint32_t dwUser);
//            
//            
//         };
//         
//         class event :
//         public ::music::midi::sequence::happening
//         {
//         public:
//            
//            
//            LPMIDIHDR                     m_lpmh;
//            
//            
//         };
//         
//         buffer_array                        m_buffera;
//
//         MIDIPortRef                         m_port;
//         MIDIClientRef                       m_client;
//
//         midi_callback_data                  m_midicallbackdata;
//         int64_array                         m_iaBuffered;
//
//         array < ::music::midi::event * >    m_evptra;
//         int                                 m_iBuffered;
//         imedia_time                     m_tkPosition;
//         thread *                            m_pthreadPlay;
//
//         sequence(::aura::application * papp);
//         virtual ~sequence();
//
//         
//         
//         void SetSpecialModeV001Flag(bool bSet = true);
//         
//         void MuteAll(bool bMute = true, int32_t iExcludeTrack = -1);
//         void MuteTrack(int32_t iIndex, bool bMute = true);
//         
//         
//         virtual int32_t GetDefaultCodePage();
//         
////         void Prepare(::ikaraoke::data & data);
////         void Prepare(int32_t iTrack, ::ikaraoke::data & data);
////         void Prepare(
////                      string2a & str2a,
////                      imedia_time_2darray & tka2DTokensTicks,
////                      int32_t iMelodyTrack,
////                      int2a & ia2TokenLine,
////                      ::ikaraoke::data & data);
//         
//         //imedia_time GetPositionTicks();
//         void SetLevelMeter(int32_t iLevel);
//         ::multimedia::e_result CloseStream();
//         bool SetMidiOutDevice(uint32_t uiDevice);
//         int32_t SetKeyShift(int32_t iKeyShift);
//         int32_t GetKeyShift();
//         
//         void OnMidiPlaybackEnd(::music::midi::sequence::happening * pevent);
//         int32_t SetTempoShift(int32_t iTempoShift);
//         
//         void OnPositionCB(LPMIDIHDR lpmidihdr);
////         void OnDone(seq_context_t * hmidistream, LPMIDIHDR lpmidihdr);
//         virtual void GetTimeLength(imedia_time & time);
//         virtual void GetPositionLength(imedia_time & position);
//         
//         using ::ikaraoke::karaoke::TimeToPosition;
//         using ::ikaraoke::karaoke::PositionToTime;
//         
//         virtual imedia_time TimeToPosition(imedia_time time);
//         virtual imedia_time PositionToTime(imedia_time position);
//         
//         virtual bool IsOpened();
//         
//         virtual bool IsNull();
//         virtual void SetTempoChangeFlag(bool bSet = true);
//         virtual bool IsChangingTempo();
//         
//         virtual double GetTempoShift();
//         virtual bool IsInSpecialModeV001();
//         virtual bool WasInSpecialModeV001();
//         
//         virtual void OnEvent(::music::midi::sequence::happening * pevent);
//         
//         
////         ::multimedia::e_result AllocBuffers();
////
////         VOID FreeBuffers();
//         
////         ::music::e_result OpenFile(::music::midi::sequence & sequence, int32_t iOpenMode);
////         ::music::e_result OpenFile(::file::file * pfile, int32_t openMode);
////         ::music::e_result OpenFile(const char * lpFileName, int32_t openMode);
////         ::music::e_result OpenFile(memory * pmemorystorage, int32_t openMode, ::music::e_storage estorage);
//         
////         ::music::e_result CloseFile();
////         ::music::e_result SaveFile(const char * lpFileName);
////         ::music::e_result SaveFile();
////         ::music::e_result SaveFile(::file::file * *pfile);
//         ::multimedia::e_result Preroll(::thread * pthread, ::music::midi::LPPREROLL lpPreroll, bool bThrow);
//         ::multimedia::e_result Start();
//         
//         ::multimedia::e_result Pause();
//         
//         ::multimedia::e_result Restart();
//         
//         //::multimedia::e_result Stop(uint32_t dwEllapse);
//         ::multimedia::e_result Stop();
//         
//         void GetPosition(imedia_time  & time);
//         void get_time(imedia_time  & time);
//         
//         ::multimedia::e_result get_ticks(imedia_time & time);
//         ::multimedia::e_result get_millis(imedia_time & time);
//         
//         
//         imedia_time MillisecsToTicks(imedia_time msOffset);
//         
//         imedia_time TicksToMillisecs(imedia_time tkOffset);
//         
//         bool IsPlaying();
//         
//         //         static void CALLBACK MidiOutProc(HMIDIOUT hmo, uint32_t wMsg, uint32_t dwInstance, uint32_t dwParam1, uint32_t dwParam2);
//         
//         
//         
//         bool IsSettingPosition();
//         void SetSettingPositionFlag(bool bSet = TRUE);
//         
//         imedia_time GetQuarterNote();
//         
//         
//         inline sp(::music::midi::port::buffer) file()
//         {
//            return get_file();
//         }
//         
//         inline sp(::music::midi::port::sequence_thread) thread()
//         {
//            return m_pthread;
//         }
//         
//         using ::music::midi::sequence::create_new_event;
//         virtual ::music::midi::sequence::happening * create_new_event(::music::midi::sequence::e_happening ehappening, LPMIDIHDR lpmidihdr);
//         
//         int seq_dump();
//         ::music::midi::event * seq_get_next_event();
//         int seq_play(::music::midi::event * pevent);
//         ::multimedia::e_result seq_start();
//
//      };
//
//      } // namespace core_audio
//
//
//   } // namespace midi
//
//
//} // namespace music
//
//
//
//
//
//
//
