#ifndef TRACKREADER_H
#define TRACKREADER_H

//REGION(License)

/* Copyright (c) 2005 Leslie Sanford
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software. 
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 */

//ENDREGION()

//REGION(Contact)

/*
 * Leslie Sanford
 * Email: jabberdabber@hotmail.com
 */

//ENDREGION()

#include "Types.h"
#include "Buffer.h"
#include "Stream.h"
#include "Track.h"
#include "ChannelMessageBuilder.h"
#include "SysCommonMessageBuilder.h"

namespace Sanford { namespace Multimedia { namespace Midi {

    class TrackReaderClass;
    typedef TrackReaderClass& TrackReader;

    /// <summary>
    /// Reads a track from a stream.
    /// </summary>
    class TrackReaderClass
    {

    private:

        Track track;

        Track newTrack;

        ChannelMessageBuilder cmBuilder;

        SysCommonMessageBuilder scBuilder;

        Stream stream;

        bytebuffer trackData;

        int trackIndex;

        int previousTicks;

        int ticks;

        int status;

        int runningStatus;

    public:

        TrackReaderClass();

        void Read(Stream strm);
        
        void FindTrack();
     
        int GetTrackLength();

        void ParseTrackData();

        void ParseMessage();

	private:

		void ParseChannelMessage();

		void ParseMetaMessage();

		void ParseSysExMessageStart();

		void ParseSysExMessageContinue();

		void ParseSysCommonMessage();

		void ParseSysRealtimeMessage();

		int ReadVariableLengthValue();

	public:

        ReadOnlyProperty<Track> Track;

    private:
        void init();
		Midi::Track get_Track();

    };

}}}

#endif