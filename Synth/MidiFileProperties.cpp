//REGION(License)

/* Copyright (c) 2006 Leslie Sanford
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

#include "MidiFileProperties.h"
#include "PpqnClock.h"
#include "Exception.h"

namespace Sanford { namespace Multimedia { namespace Midi {

	static int midiFileHeaderSize = 8;
    static byte midiFileHeader[] =
        {
            (byte)'M',
            (byte)'T',
            (byte)'h',
            (byte)'d',
            0, 
            0, 
            0,
            6
        };
		   
    typedef MidiFilePropertiesClass cls;
    void cls::init() 
    {
        this->Format = Functor::New(this, &cls::get_Format, &cls::set_Format);
        this->TrackCount = Functor::New(this, &cls::get_TrackCount, &cls::set_TrackCount);
        this->Division = Functor::New(this, &cls::get_Division, &cls::set_Division);
        this->SequenceType = Functor::New(this, &cls::get_SequenceType, &cls::set_SequenceType);
        this->MidiFileHeader = bytebufferclass(midiFileHeaderSize, midiFileHeader);
        this->format = 1;
        this->trackCount = 0;
        this->division = PpqnClockClass::PpqnMinValue;
        this->sequenceType = SequenceType::Ppqn;
    }
        
	MidiFilePropertiesClass::MidiFilePropertiesClass()
	{
		init();
	}

    void MidiFilePropertiesClass::Read(Stream strm)
    {
        REGION(Require)

        if(StreamClass::IsNull(strm))
        {
            throw new ArgumentNullException("strm");
        }

        ENDREGION()

        format = trackCount = division = 0;

        FindHeader(strm);
        Format = (int)ReadProperty(strm);
        TrackCount = (int)ReadProperty(strm);
        Division = (int)ReadProperty(strm);

        REGION(Invariant)

        AssertValid();

        ENDREGION()
    }

    void MidiFilePropertiesClass::FindHeader(Stream stream)
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

                    if(result == 'h')
                    {
                        result = stream.ReadByte();

                        if(result == 'd')
                        {
                            found = true;
                        }
                    }
                }
            }

            if(result < 0)
            {
                throw new MidiFileException("Unable to find MIDI file header.");
            }
        }

        // Eat the header length.
        for(int i = 0; i < 4; i++)
        {
            if(stream.ReadByte() < 0)
            {
                throw new MidiFileException("Unable to find MIDI file header.");
            }
        }
    }

    ushort MidiFilePropertiesClass::ReadProperty(Stream strm)
    {
        bytebuffer data = bytebufferclass(PropertyLength);

        int result = strm.Read(data, 0, data.Length);

        if(result != data.Length)
        {
            throw new MidiFileException("End of MIDI file unexpectedly reached.");
        }

        if(BitConverter::IsLittleEndian())
        {
            data.Reverse();
        }

        return BitConverter::ToUInt16(data, 0);
    }

    void MidiFilePropertiesClass::Write(Stream strm)
    {
        REGION(Require)

        if(StreamClass::IsNull(strm))
        {
            throw new ArgumentNullException("strm");
        }

        ENDREGION()

        strm.Write(MidiFileHeader, 0, MidiFileHeader.Length);
        WriteProperty(strm, (ushort)Format);
        WriteProperty(strm, (ushort)TrackCount);
        WriteProperty(strm, (ushort)Division);
    }

    void MidiFilePropertiesClass::WriteProperty(Stream strm, ushort prop)
    {
        bytebuffer data = BitConverter::GetBytes(prop);

        if(BitConverter::IsLittleEndian())
        {
            data.Reverse();
        }

        strm.Write(data, 0, PropertyLength);
    }

    bool MidiFilePropertiesClass::IsSmpte(int division)
    {
        bool result;
        bytebuffer data = BitConverter::GetBytes((short)division);
            
        if(BitConverter::IsLittleEndian())
        {
            data.Reverse();
        }

        if((sbyte)data[0] < 0)
        {
            result = true;
        }
        else
        {
            result = false;
        }

        return result;
    }

    #if(DEBUG)
    void MidiFilePropertiesClass::AssertValid()
    {
        if(trackCount > 1)
        {
            Assert(Format == 1 || Format == 2);
        }

        if(IsSmpte(Division))
        {
            Assert(SequenceType == SequenceType.Smpte);
        }
        else
        {
            Assert(SequenceType == SequenceType.Ppqn);
            Assert(Division % PpqnClock.PpqnMinValue == 0);
        }
    }
	#else
	void MidiFilePropertiesClass::AssertValid() { }
    #endif

    int MidiFilePropertiesClass::get_Format()
    {
        return format;
    }
    void MidiFilePropertiesClass::set_Format(int value)
    {
        REGION(Require)

        if(value < 0 || value > 3)
        {
            throw new ArgumentOutOfRangeException("Format", value,
                "MIDI file format out of range.");
        }
        else if(value == 0 && trackCount > 1)
        {
            throw new ArgumentException(
                "MIDI file format invalid for this track count.");
        }

        ENDREGION()

        format = value;

        REGION(Invariant)

        AssertValid();

        ENDREGION()
    }

    int MidiFilePropertiesClass::get_TrackCount()
    {
        return trackCount;
    }
    void MidiFilePropertiesClass::set_TrackCount(int value)
    {
        REGION(Require)

        if(value < 0)
        {
            throw new ArgumentOutOfRangeException("TrackCount", value,
                "Track count out of range.");
        }
        else if(value > 1 && Format == 0)
        {
            throw new ArgumentException(
                "Track count invalid for this format.");
        }

        ENDREGION()

        trackCount = value;

        REGION(Invariant)

        AssertValid();

        ENDREGION()
    }

    int MidiFilePropertiesClass::get_Division()
    {
        return division;
    }
    void MidiFilePropertiesClass::set_Division(int value)
    {
        if(IsSmpte(value))
        {
            bytebuffer data = BitConverter::GetBytes((short)value); 

            if(BitConverter::IsLittleEndian())
            {
                data.Reverse();
            }

            if((sbyte)data[0] != -(int)SmpteFrameRate::Smpte24 &&                        
                (sbyte)data[0] != -(int)SmpteFrameRate::Smpte25 &&
                (sbyte)data[0] != -(int)SmpteFrameRate::Smpte30 &&
                (sbyte)data[0] != -(int)SmpteFrameRate::Smpte30Drop)
            {
                throw new ArgumentException("Invalid SMPTE frame rate.");
            }
            else
            {
                sequenceType = SequenceType::Smpte;
            }
        }
        else 
        {
            if(value % PpqnClockClass::PpqnMinValue != 0)
            {
                throw new ArgumentException(
                    "Invalid pulses per quarter note value.");
            }
            else
            {
                sequenceType = SequenceType::Ppqn;
            }
        }

        division = value;

        REGION(Invariant)

        AssertValid();

        ENDREGION()
    }

    SequenceType MidiFilePropertiesClass::get_SequenceType()
    {
        return sequenceType;
    }

}}}