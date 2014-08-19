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

#include "TrackReader.h"
#include "MetaMessage.h"
#include "SysExMessage.h"
#include "SysRealtimeMessage.h"
#include "Exception.h"

namespace Sanford { namespace Multimedia { namespace Midi {

	typedef TrackReaderClass cls;
	void cls::init() 
    {
        this->Track = Functor::New(this, &cls::get_Track);
        this->stream = StreamClass();
		this->trackData = bytebufferclass::null;
        this->trackIndex = 0;
        this->previousTicks = 0;
		this->ticks = 0;
		this->status = 0;
		this->runningStatus = 0;
    }

    TrackReaderClass::TrackReaderClass() :
		stream(StreamClass()), 
		trackData(bytebufferclass(0)),
		track(TrackClass::null), 
		newTrack(TrackClass::null), 
		cmBuilder(ChannelMessageBuilderClass()), 
		scBuilder(SysCommonMessageBuilderClass())
    {
		init();
        this->track = TrackClass();
        this->newTrack = TrackClass();
        this->cmBuilder = ChannelMessageBuilderClass();
        this->scBuilder = SysCommonMessageBuilderClass();
    }

    void TrackReaderClass::Read(Stream strm)
    { 
        stream = strm;     
        FindTrack();

        int trackLength = GetTrackLength();
        trackData = bytebufferclass(trackLength);

        int result = strm.Read(trackData, 0, trackLength);

        if(result < 0)
        {
            throw new MidiFileException("End of MIDI file unexpectedly reached.");
        }
            
        newTrack = TrackClass();

        ParseTrackData();

        track = newTrack;
    }

    void TrackReaderClass::FindTrack()
    {
        bool found = false;
        int result;

        while(!found)
        {
            result = stream.ReadByte();

            if(result == 'M')
            {
                result = stream.ReadByte();

                if(result == 'T')
                {
                    result = stream.ReadByte();

                    if(result == 'r')
                    {
                        result = stream.ReadByte();

                        if(result == 'k')
                        {
                            found = true;
                        }
                    }
                }
            }

            if(result < 0)
            {
                throw new MidiFileException("Unable to find track in MIDI file.");
            }
        }
    }

    int TrackReaderClass::GetTrackLength()
    {
        bytebuffer trackLength = bytebufferclass(4);

        int result = stream.Read(trackLength, 0, trackLength.Length);
            
        if(result < trackLength.Length)
        {
            throw new MidiFileException("End of MIDI file unexpectedly reached.");
        }

        if(BitConverter::IsLittleEndian())
        {
            trackLength.Reverse();
        }

        return BitConverter::ToInt32(trackLength, 0);
    }

    void TrackReaderClass::ParseTrackData()
    {
        trackIndex = ticks = runningStatus = 0;

        while(trackIndex < trackData.Length)
        {
            previousTicks = ticks;

            ticks += ReadVariableLengthValue();

            if((trackData[trackIndex] & 0x80) == 0x80)
            {
                status = trackData[trackIndex];
                trackIndex++;
            }
            else
            {
                status = runningStatus;
            }  
              
            ParseMessage();                
        }
    }

    void TrackReaderClass::ParseMessage()
    {
        // If this is a channel message.
        if(status >= (int)ChannelCommand::NoteOff && 
            status <= (int)ChannelCommand::PitchWheel + 
            ChannelMessageClass::MidiChannelMaxValue)
        {
            ParseChannelMessage();
        }
        // Else if this is a meta message.
        else if(status == 0xFF)
        {
            ParseMetaMessage();                
        }
        // Else if this is the start of a system exclusive message.
        else if(status == (int)SysExType::Start)
        {
            ParseSysExMessageStart();
        }
        // Else if this is a continuation of a system exclusive message.
        else if(status == (int)SysExType::Continuation)
        {
            ParseSysExMessageContinue();
        }
        // Else if this is a system common message.
        else if(status >= (int)SysCommonType::MidiTimeCode &&
            status <= (int)SysCommonType::TuneRequest)
        {
            ParseSysCommonMessage();
        }
        // Else if this is a system realtime message.
        else if(status >= (int)SysRealtimeType::Clock &&
            status <= (int)SysRealtimeType::Reset)
        {
            ParseSysRealtimeMessage();                
        }
    }

    void TrackReaderClass::ParseChannelMessage()
    {
        if(trackIndex >= trackData.Length)
        {
            throw new MidiFileException("End of track unexpectedly reached.");
        }

        cmBuilder.Command = ChannelMessageClass::UnpackCommand(status);
        cmBuilder.MidiChannel = ChannelMessageClass::UnpackMidiChannel(status);
        cmBuilder.Data1 = trackData[trackIndex];

        trackIndex++;

        if(ChannelMessageClass::DataBytesPerType(cmBuilder.Command) == 2)
        {
            if(trackIndex >= trackData.Length)
            {
                throw new MidiFileException("End of track unexpectedly reached.");
            }
                        
            cmBuilder.Data2 = trackData[trackIndex];

            trackIndex++;
        }  

        cmBuilder.Build();
        newTrack.Insert(ticks, cmBuilder.Result);
        runningStatus = status;
    }

    void TrackReaderClass::ParseMetaMessage()
    {
        if(trackIndex >= trackData.Length)
        {
            throw new MidiFileException("End of track unexpectedly reached.");
        }

        MetaType type = (MetaType)trackData[trackIndex];

        trackIndex++;

        if(trackIndex >= trackData.Length)
        {
            throw new MidiFileException("End of track unexpectedly reached.");
        }

        if(type == MetaType::EndOfTrack)
        {
            newTrack.EndOfTrackOffset = ticks - previousTicks;

            trackIndex++;
        }
        else
        {
            bytebuffer data = bytebufferclass(ReadVariableLengthValue());
			trackData.Offset(trackIndex).CopyTo(data, 0, data.Length);
            newTrack.Insert(ticks, MetaMessageClass(type, data));                   

            trackIndex += data.Length;
        }
    }

    void TrackReaderClass::ParseSysExMessageStart()
    {
        // System exclusive cancels running status.
        runningStatus = 0;

        bytebuffer data = bytebufferclass(ReadVariableLengthValue() + 1);
        data[0] = (byte)SysExType::Start;

		trackData.Offset(trackIndex).CopyTo(data, 1, data.Length - 1);
        newTrack.Insert(ticks, SysExMessageClass(data));

        trackIndex += data.Length - 1;
    }

    void TrackReaderClass::ParseSysExMessageContinue()
    {
        trackIndex++;

        if(trackIndex >= trackData.Length)
        {
            throw new MidiFileException("End of track unexpectedly reached.");
        }

        // System exclusive cancels running status.
        runningStatus = 0;
           
        // If this is an escaped message rather than a system exclusive 
        // continuation message.
        if((trackData[trackIndex] & 0x80) == 0x80)
        {
            status = trackData[trackIndex];
            trackIndex++;

            ParseMessage();
        }
        else
        {
            bytebuffer data = bytebufferclass(ReadVariableLengthValue() + 1);
            data[0] = (byte)SysExType::Continuation;

			trackData.Offset(trackIndex).CopyTo(data, 1, data.Length - 1);
            newTrack.Insert(ticks, SysExMessageClass(data));

            trackIndex += data.Length - 1;
        }
    }

    void TrackReaderClass::ParseSysCommonMessage()
    {
        if(trackIndex >= trackData.Length)
        {
            throw new MidiFileException("End of track unexpectedly reached.");
        }

        // System common cancels running status.
        runningStatus = 0;

        scBuilder.Type = (SysCommonType)status;

        switch((SysCommonType)status)
        {
			case SysCommonType::MidiTimeCode:
                scBuilder.Data1 = trackData[trackIndex];
                trackIndex++;
                break;

			case SysCommonType::SongPositionPointer:
                scBuilder.Data1 = trackData[trackIndex];
                trackIndex++;

                if(trackIndex >= trackData.Length)
                {
                    throw new MidiFileException("End of track unexpectedly reached.");
                }

                scBuilder.Data2 = trackData[trackIndex];
                trackIndex++;
                break;

			case SysCommonType::SongSelect:
                scBuilder.Data1 = trackData[trackIndex];
                trackIndex++;
                break;

			case SysCommonType::TuneRequest:
                // Nothing to do here.
                break;
        }

        scBuilder.Build();

        newTrack.Insert(ticks, scBuilder.Result);
    }

    void TrackReaderClass::ParseSysRealtimeMessage()
    {
        SysRealtimeMessage e = SysRealtimeMessageClass::null;

        switch((SysRealtimeType)status)
        {
			case SysRealtimeType::ActiveSense:
                e = SysRealtimeMessageClass::ActiveSenseMessage;
                break;

			case SysRealtimeType::Clock:
                e = SysRealtimeMessageClass::ClockMessage;
                break;

			case SysRealtimeType::Continue:
                e = SysRealtimeMessageClass::ContinueMessage;
                break;

			case SysRealtimeType::Reset:
                e = SysRealtimeMessageClass::ResetMessage;
                break;

			case SysRealtimeType::StartRealtime:
                e = SysRealtimeMessageClass::StartMessage;
                break;

			case SysRealtimeType::StopRealtime:
                e = SysRealtimeMessageClass::StopMessage;
                break;

			case SysRealtimeType::Tick:
                e = SysRealtimeMessageClass::TickMessage;
                break;
        }

        newTrack.Insert(ticks, e);
    }

    int TrackReaderClass::ReadVariableLengthValue()
    {
        if(trackIndex >= trackData.Length)
        {
            throw new MidiFileException("End of track unexpectedly reached.");
        }

        int result = 0;

        result = trackData[trackIndex];

        trackIndex++;

        if((result & 0x80) == 0x80)
        {
            result &= 0x7F;

            int temp;

            do
            {
                if(trackIndex >= trackData.Length)
                {
                    throw new MidiFileException("End of track unexpectedly reached.");
                }

                temp = trackData[trackIndex];
                trackIndex++;
                result <<= 7;
                result |= temp & 0x7F;
            }while((temp & 0x80) == 0x80);
        }

        return result;            
    }

    Track TrackReaderClass::get_Track()
    {
        return track;
    }

}}}


