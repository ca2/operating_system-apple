//
//  AUOutputBL.hpp
//  music_midi_core_audio
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 9/8/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#pragma once


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace audio_unit
      {

         
         class AUOutputBL
         {
            public:
               
               // you CANNOT use one of these - it will crash!
               //										AUOutputBL ();
               
               // this is the constructor that you use
               // it can't be reset once you've constructed it
               AUOutputBL (const CAStreamBasicDescription &inDesc, unsigned int inDefaultNumFrames = 512);
               ~AUOutputBL();
               
               void 								Prepare ()
               {
                  Prepare (mFrames);
               }
               
               // this version can throw ::exception( if this is an allocted ABL and inNumFrames is > AllocatedFrames();
               // you can set the bool to true if you want a nullptr buffer list even if allocated
               // inNumFrames must be a valid number (will throw ::exception( if inNumFrames is 0);
               void 								Prepare (unsigned int inNumFrames, bool inWantNullBufferIfAllocated = false);
               
               AudioBufferList*					ABL() { return mBufferList; }
               
               // You only need to call this if you want to allocate a buffer list
               // if you want an empty buffer list, just call Prepare()
               // if you want to dispose previously allocted memory, pass in 0
               // then you either have an empty buffer list, or you can re-allocate
               // Memory is kept around if an Allocation request is less than what is currently allocated
               void								Allocate (unsigned int inNumberFrames);
               
               unsigned int								AllocatedFrames() const { return mFrames; }
               
               const CAStreamBasicDescription&		GetFormat() const { return mFormat; }
               
            #ifdef _DEBUG
               void								Print();
            #endif
               
            private:
               unsigned int						AllocatedBytes () const { return (mBufferSize * mNumberBuffers); }
               
               CAStreamBasicDescription	mFormat;
               Byte*						mBufferMemory;
               AudioBufferList* 			mBufferList;
               unsigned int						mNumberBuffers;
               unsigned int						mBufferSize;
               unsigned int						mFrames;
               
               // don't want to copy these.. can if you want, but more code to write!
               AUOutputBL () {}
               AUOutputBL (const AUOutputBL &c) {}
               AUOutputBL& operator= (const AUOutputBL& c) { return *this; }
            };

         
      } // namespace audio_unit
      
      
   } // namespace midi
   
   
} // namespace music




