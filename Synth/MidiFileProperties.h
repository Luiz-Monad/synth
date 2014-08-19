#ifndef MIDIFILEPROPERTIES_H
#define MIDIFILEPROPERTIES_H

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

#include "Types.h"
#include "Buffer.h"
#include "Stream.h"

namespace Sanford { namespace Multimedia { namespace Midi {

	/// <summary>
    /// Defintes constants representing SMPTE frame rates.
    /// </summary>
    enum SmpteFrameRate
    {
        Smpte24     = 24,
        Smpte25     = 25,
        Smpte30Drop = 29,
        Smpte30     = 30
    };

    /// <summary>
    /// The different types of sequences.
    /// </summary>
    enum SequenceType
    {
        Ppqn,
        Smpte
    };

	class MidiFilePropertiesClass;
	typedef MidiFilePropertiesClass& MidiFileProperties;

	/// <summary>
	/// Represents MIDI file properties.
	/// </summary>
	class MidiFilePropertiesClass
	{

	private:
		
		static const int PropertyLength = 2;

        static const bytebuffer MidiFileHeader;

        int format;

        int trackCount;

        int division;

        SequenceType sequenceType;

	public:

		MidiFilePropertiesClass();

        void Read(Stream strm);

        void Write(Stream strm);

	private:

		void FindHeader(Stream stream);

        ushort ReadProperty(Stream strm);
	
		void WriteProperty(Stream strm, ushort prop);

        static bool IsSmpte(int division);

	private:

        void AssertValid();

	public:

        Property<int> Format;

        Property<int> TrackCount;

        Property<int> Division;

        Property<Midi::SequenceType> SequenceType;

	private:
		void init();
		int get_Format();
		void set_Format(int value);
		int get_TrackCount();
		void set_TrackCount(int value);
		int get_Division();
		void set_Division(int value);
		Midi::SequenceType get_SequenceType();
		void set_SequenceType(Midi::SequenceType value);

	};
	
}}}

#endif