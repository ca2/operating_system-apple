#include "framework.h"


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace port
      {
      
      namespace player
      {
         
         
         player::player(::aura::application * papp) :
            ::object(papp),
            thread(papp),
            ::music::midi::player::player(papp)
         {
            
            m_psequencethread = dynamic_cast < ::music::midi::port::sequence_thread * > (__begin_thread < sequence_thread >(papp, ::multithreading::priority_normal, 0, CREATE_SUSPENDED));
            
            m_puie               = NULL;
            
            //m_psection = NULL;
            //m_pmidiplayer = NULL;

            
         }
         
         player::~player()
         {
            
         }
         
         bool player::init_thread()
         {
            
            m_psequencethread->ResumeThread();
            
            information("player::initialize_instance %X\n", get_os_int());
            //SetMainWnd(NULL);
            //ASSERT(GetMainWnd() == NULL);
            
            set_thread_priority(::multithreading::priority_normal);
            
            m_evInitialized.set_happening();
            
            return true;
         }
         
         void player::term_thread()
         {
            // TODO:  perform any per-thread cleanup here
            //   if(!get_sequence()->IsNull())
            //   {
            //      delete get_sequence();
            //   }
            //    if(m_pmidicallbackdata != NULL)
            //  {
            //    delete m_pmidicallbackdata;
            ///  m_pmidicallbackdata = NULL;
            //}
            thread::term_thread();
            
         }
         
         
         void player::install_message_routing(::message::sender * pinterface)
         {
            
            ::music::midi::player::player::install_message_routing(pinterface);
            //IGUI_WIN_MSG_LINK(MM_MOM_DONE, pinterface, this, &player::OnMultimediaMidiOutputMessageDone);
            //IGUI_WIN_MSG_LINK(MM_MOM_POSITIONCB, pinterface, this, &player::OnMultimediaMidiOutputMessagePositionCB);
         }
         
         bool player::Play(imedia_time tkStart, uint32_t dwEllapse)
         {
            
            ::music::midi::player::command * pcommand = new ::music::midi::player::command(get_app());
            
            pcommand->m_ecommand = ::music::midi::player::command_play;
            pcommand->m_dwEllapse = dwEllapse;
            pcommand->m_flags.signalize(::music::midi::player::command::flag_ticks);
            pcommand->m_ticks = tkStart;
            
            m_psequencethread->ExecuteCommand(pcommand);
            
            bool bFinished = pcommand->wait_ready();
            
            pcommand->release();
            
            return bFinished;
         }
         
         bool player::PlayRate(double dRate, uint32_t dwEllapse)
         {
            
            ::music::midi::player::command * pcommand = new ::music::midi::player::command(get_app());
            
            pcommand->m_ecommand = ::music::midi::player::command_play;
            pcommand->m_dwEllapse = dwEllapse;
            pcommand->m_flags.signalize(::music::midi::player::command::flag_dRate);
            pcommand->m_dRate = dRate;
            
            m_psequencethread->ExecuteCommand(pcommand);
            
            bool bFinished = pcommand->wait_ready();
            
            pcommand->release();
            
            return bFinished;
            
         }
         
         imedia_time player::RateToTicks(double dRate)
         {
            ASSERT(dRate >= 0.0);
            ASSERT(dRate <= 1.0);
            return (imedia_time) (int32_t) (get_sequence()->m_tkLength * dRate);
         }
         
         
         
         bool player::IsPlaying()
         {
            ASSERT(!get_sequence()->IsNull());
            return (bool) get_sequence()->IsPlaying();
            
         }
         
         bool player::ExecuteCommand(::music::midi::player::e_command ecommand, uint32_t dwEllapse)
         {
            
            ::music::midi::player::command * pcommand = new ::music::midi::player::command(get_app());
            
            pcommand->m_ecommand = ecommand;
            pcommand->m_dwEllapse = dwEllapse;
            
            m_psequencethread->ExecuteCommand(pcommand);
            
            bool bFinished = pcommand->wait_ready();
            
            pcommand->release();
            
            return bFinished;
         }
         
         
         void player::close_file()
         {
            
            ::music::e_result            mmrc;
            
            if(::music::failed(mmrc = get_sequence()->close_file()) &&
               mmrc != ::music::EFunctionNotSupported)
            {
               
               throw new exception(get_app(), EMidiPlayerClose);
               
            }
            
         }
         
         
         void player::pause()
         {
            
            if (get_sequence()->get_status() == ::music::midi::sequence::status_paused)
            {
               
               get_sequence()->Restart();
               
            }
            else
            {
               
               get_sequence()->Pause();
               
            }
            
         }
         
         void player::SetPosition(double dRate)
         {
            if (::music::midi::sequence::status_playing != get_sequence()->get_status() &&
                ::music::midi::sequence::status_stopping != get_sequence()->get_status() &&
                ::music::midi::sequence::status_opened != get_sequence()->get_status())
               return;
            
            if(get_sequence()->IsPlaying())
            {
               
               ::music::midi::sequence::PlayerLink & link = get_sequence()->GetPlayerLink();
               
               link() |= ::music::midi::sequence::FlagSettingPos;
               
               link.m_tkRestart = RateToTicks(dRate);
               
               get_sequence()->Stop();
               
            }
            
         }
         
         void player::OnMmsgDone(::music::midi::sequence * pSeq)
         {
            ASSERT(FALSE);
            ASSERT(FALSE);
            ASSERT(FALSE);
            ASSERT(FALSE);
            ASSERT(FALSE);
            ASSERT(FALSE);
            ASSERT(FALSE);
            ASSERT(FALSE);
            ASSERT(pSeq == get_sequence());
            if(pSeq->IsSettingPosition())
            {
               get_sequence()->SetSettingPositionFlag(FALSE);
               try
               {
                  //         PrerollAndWait(m_dNextPositionRate);
               }
               catch(exception *pe)
               {
                  //SendMmsgDone(pSeq, NULL);
                  pe->Delete();
                  return;
               }
               
               get_sequence()->Start();
               
            }
            else
            {
               
            }
            
         }
         
         
         void player::pre_translate_message(::message::message * pobj)
         {
            SCAST_PTR(::message::base, pbase, pobj);
            //ASSERT(GetMainWnd() == NULL);
            //   if(pMsg->message == MM_MOM_DONE ||
            //      pMsg->message == MM_MOM_POSITIONCB ||
            //      pMsg->message == MM_MOM_OPEN ||
            //      pMsg->message == MM_MOM_OPEN)
            //   {
            //      OnMidiOutMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
            //      return TRUE;
            //   }
            if(pbase->m_pwnd == NULL)
            {
               switch(pbase->m_id)
               {
                  case WM_USER + 100:
                  {
                     LPDOUBLESTRUCT lpds = (LPDOUBLESTRUCT) pbase->m_wparam;
                     SetPosition(lpds->d);
                     delete lpds;
                  }
                     return;
               }
            }
            if(pbase->m_id == MMSG_DONE)
            {
               OnMmsgDone((::music::midi::sequence *) pbase->m_wparam);
               pbase->m_bRet = true;
               return;
            }
            else if(pbase->m_id == WM_USER)
            {
               //      OnUserMessage(pMsg->wParam, pMsg->lParam);
            }
            return thread::pre_translate_message(pobj);
         }
         
         void player::SaveFile(const char * lpszPathName)
         {
            ::music::e_result            mmrc;
            if(::music::failed(mmrc = get_sequence()->SaveFile(lpszPathName)) )
            {
               throw new exception(get_app(), ::music::EMidiPlayerSave);
            }
            
         }
         
         
         void player::OnUserMessage(::message::message * pobj)
         {
            SCAST_PTR(::message::base, pbase, pobj);
            if(pbase->m_wparam == 3377)
            {
               m_puie->send_message(WM_USER, pbase->m_wparam, pbase->m_lparam);
            }
            
         }
         
         
         void player::PostGMReset()
         {
            m_psequencethread->PostGMReset();
         }
         
         void player::PostTempoChange()
         {
            m_psequencethread->PostTempoChange();
         }
         
         void player::SendTempoChange()
         {
            m_psequencethread->SendTempoChange();
         }
         
         
//         ::multimedia::e_result player::Initialize(thread * pthread)
//         {
//            UNREFERENCED_PARAMETER(pthread);
//            return ::multimedia::result_success;
//         }
//
         //void player::SetView(CXfplayerView *pview)
         //{
         //    m_pView = pview;
         //}
         
//         ::multimedia::e_result player::SetInterface(player_interface * pinterface)
//         {
//            m_pinterface = pinterface;
//            get_sequence()->m_pthread   = m_psequencethread;
//            m_psequencethread->m_psequence = get_sequence();
//            m_psequencethread->m_pplayer = this;
//            PostNotifyEvent(::music::midi::player::notify_event_set_sequence);
//            return ::multimedia::result_success;
//         }
         
         
         bool player::SetMidiOutDevice(uint32_t uiDevice)
         {
            UNREFERENCED_PARAMETER(uiDevice);
            OnMidiOutDeviceChange();
            return true;
         }
         
         
         
         bool player::SetTempoShift(int32_t iTempoShift)
         {
            //   if(IsPlaying())
            {/*
              get_sequence()->SetTempoChangeFlag();
              ::music::midi::sequence::PlayerLink & link = get_sequence()->GetPlayerLink();
              link.ModifyFlag(
              ::music::midi::sequence::FlagTempoChange,
              ::music::midi::sequence::FlagNull);
              imedia_time tk = get_sequence()->GetPositionTicks();
              get_sequence()->m_evMmsgDone.reset_happening();
              link.m_tkRestart = tk + get_sequence()->m_tkBase;
              //m_bChangingTempo = true;
              get_sequence()->Stop();
              //get_sequence()->m_evMmsgDone.lock();
              */
               
               bool bPlay = IsPlaying();
               
               imedia_time ticks = 0;
               
               if(bPlay)
               {
                  
                  get_sequence()->get_position(ticks);
                  
                  get_sequence()->Stop();
                  
               }
               
               if(!get_sequence()->SetTempoShift(iTempoShift))
               {
                  
                  return false;
                  
               }
               
               if(bPlay)
               {
               
                  get_sequence()->m_pthread->PrerollAndWait(ticks);
                  
                  get_sequence()->Start();
                  
               }
               
            }
            
            return true;
            
         }
         
         
         void player::PostNotifyEvent(::music::midi::player::enum_notify_event eevent)
         {
            if(m_puie != NULL)
            {
               ::music::midi::player::notify_event * pdata = new ::music::midi::player::notify_event;
               pdata->m_pplayer = this;
               pdata->m_enotifyevent = eevent;
               m_puie->post_message(::music::midi::player::message_notify_event, 0 , (LPARAM) pdata);
            }
         }
         
//         void player::SendMmsgDone(::music::midi::sequence *pSeq, ::music::midi::LPMIDIDONEDATA lpmdd)
//         {
//            if(m_puie != NULL)
//            {
//               m_puie->post_message(MMSG_DONE, (WPARAM) pSeq, (LPARAM) lpmdd);
//            }
//            
//         }
//         
         uint32_t player::GetMidiOutDevice()
         {
            
            return Application.midi()->GetMidiOutDevice();
         }
         
//         void player::SetCallbackWindow(::user::interaction * puie)
//         {
//            m_puie = puie;
//         }
//         
         void player::on_attribute_change(::message::message * pobj)
         {
            SCAST_PTR(::music::midi::attribute_message, pchange, pobj);
            
            switch(pchange->m_eattribute)
            {
               case ::music::midi::attribute_midi_out_device:
                  OnMidiOutDeviceChange();
                  break;
            }
            
         }
         
         void player::OnMidiOutDeviceChange()
         {
            get_sequence()->SetMidiOutDevice(GetMidiOutDevice());
            if(get_sequence()->IsPlaying())
            {
               
               imedia_time tkPosition = 0;
               
               get_sequence()->get_position(tkPosition);
               
               ::music::midi::sequence::PlayerLink & link = get_sequence()->GetPlayerLink();
               
               link() |= ::music::midi::sequence::FlagTempoChange;
               
               link.m_tkRestart = tkPosition;
               
               get_sequence()->Stop();
               
            }
            
         }
         
         
         void player::OnMultimediaMidiOutputMessageDone(::message::message * pobj)
         {
  
            UNREFERENCED_PARAMETER(pobj);
//            SCAST_PTR(::message::base, pbase, pobj);
            
            /*seq_context_t * pseq = (seq_context_t *) pbase->m_wparam;
             
             LPMIDIHDR lpmidihdr = (LPMIDIHDR) pbase->m_lparam.m_lparam;
             
             sp(sequence) sequence = get_sequence();
             
             ASSERT(sequence->m_pseq == pseq);
             
             sequence->OnDone(pseq, lpmidihdr);*/
            
         }
         
         void player::OnMultimediaMidiOutputMessagePositionCB(::message::message * pobj)
         {
         UNREFERENCED_PARAMETER(pobj);
//            SCAST_PTR(::message::base, pbase, pobj);
            /*            LPMIDIHDR lpmidihdr = (LPMIDIHDR) pbase->m_wparam;
             //          get_sequence()->OnPositionCB(lpmidihdr);
             
             sp(sequence) sequence = get_sequence();
             
             //            ASSERT(sequence->m_hstream == hmidistream);
             
             sequence->OnPositionCB(lpmidihdr);*/
         }
         
         
         
         
         void player::OnNotifyEvent(::message::message * pobj)
         {
            SCAST_PTR(::message::base, pbase, pobj);
            ::music::midi::player::notify_event * pdata = (::music::midi::player::notify_event *) pbase->m_lparam.m_lparam;
            pdata->m_pplayer = this;
            if(m_puie != NULL)
            {
               m_puie->post_message(::music::midi::player::message_notify_event, 0 , (LPARAM) pdata);
            }
            else
            {
               delete pdata;
            }
         }
         
         
         
         
         void player::SendReset()
         {
            /*            HMIDIOUT hmidiout = NULL;
             ::multimedia::e_result mmrc;
             uint32_t uDeviceID = 0;
             mmrc = midiOutOpen(&hmidiout, uDeviceID,  0, 0, CALLBACK_NULL);
             if(mmrc != ::multimedia::result_success)
             return;
             Sleep(284);
             const uchar gmModeOn[] = {
             //        0x00, 0x00, 0x00, 0x00,
             //        0x00, 0x00, 0x00, 0x00,
             //        0x1b, 0x8a, 0x06, MEVT_TEMPO,
             0x00, 0x00, 0x00, 0x00,
             0x00, 0x00, 0x00, 0x00,
             0x06, 0x00, 0x00, MEVT_LONGMSG,
             0xf0, 0x7e, 0x7f, 0x09,
             0x01, 0xf7, 0x00, 0x00};
             //        0x70, 0x01, 0x00, 0x00,
             //      0x00, 0x00, 0x00, 0x00 };
             //      0x09, 0x00, 0x00, MEVT_LONGMSG,
             //      0x43, 0x10, 0x4c,
             //    0x00, 0x00, 0x7e, 0x00,
             //  0xf7, 0x00, 0x00, 0x00,};
             MIDIHDR mh;
             LPMIDIHDR lpmh = &mh;
             lpmh->lpData = (char *) gmModeOn;
             lpmh->dwBufferLength = sizeof(gmModeOn);
             lpmh->dwBytesRecorded = 0;
             lpmh->dwFlags = 0;
             mmrc = midiOutPrepareHeader( hmidiout, lpmh, sizeof(MIDIHDR));
             if(mmrc != ::multimedia::result_success)
             goto End;
             lpmh->dwBytesRecorded = sizeof(gmModeOn);
             if(mmrc != ::multimedia::result_success)
             goto End;
             mmrc = midiOutLongMsg( hmidiout, lpmh, sizeof(MIDIHDR));
             Sleep(284);
             mmrc = midiOutUnprepareHeader( hmidiout, lpmh, sizeof(MIDIHDR));
             if(mmrc != ::multimedia::result_success)
             goto End;
             End:
             midiOutClose( hmidiout);
             */
         }
         

//         bool player::Initialize(::music::midi::midi * pcentral)
//         {
//            
////            if(!initialize())
////               return false;
////
////            m_psection = pcentral;
//            
//            return true;
//            
//         }
//         
//         
//         bool player_interface::Finalize()
//         {
//            
//            if(!finalize())
//               return false;
//            
//            return true;
//            
//         }
         
         
//         bool player::OpenMidiPlayer()
//         {
//            
//            try
//            {
//               m_pmidiplayer = dynamic_cast < ::music::midi::player::player * > (__begin_thread < player >(
//                                                                                                           get_app(),
//                                                                                                           ::core::scheduling_priority_normal,
//                                                                                                           0,
//                                                                                                           CREATE_SUSPENDED));
//            }
//            catch(memory_exception *pe)
//            {
//               System.simple_message_box(NULL, _T("No primitive::memory to perform this operation." ));
//               pe->Delete();
//               return false;
//            }
//            
//            m_pmidiplayer->SetMidiCentral(m_psection);
//            
//            //            m_pmidiplayer->SetCallbackWindow(&m_wnd);
//            if(::multimedia::failed(m_pmidiplayer->Initialize(
//                                                              GetMidiPlayerCallbackThread())))
//            {
//               return false;
//            }
//            
//            
//            
//            if(!OnOpenMidiPlayer())
//            {
//               return false;
//            }
//            m_pmidiplayer->ResumeThread();
//            m_pmidiplayer->m_evInitialized.wait();
//            return true;
//         }
//         
//         
//         bool player::OnOpenMidiPlayer()
//         {
//            GetMidiPlayer()->SetInterface(this);
//            //            m_wnd.set_callback(m_composite);
//            return true;
//         }
//         
//         
//         // Event handling
//         void player::OnMidiPlayerNotifyEvent(::music::midi::player::notify_event * pdata)
//         {
//            callback::OnMidiPlayerNotifyEvent(pdata);
//            //          switch(pdata->m_enotifyevent)
//            //        {
//            //      case music::midi::player::notify_event_set_sequence:
//            //       //      pdata->m_pplayer->get_sequence()->m_midicallbackdata.lpThreadV1 = GetMidiPlayerCallbackThread();
//            //     break;
//            //}
//            
//         }

         
         
      } // namespace player
      
      } // namespace port
      
   } // namespace midi_core_midi
   
   
} // namespace music









