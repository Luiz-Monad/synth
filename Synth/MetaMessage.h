#ifndef METAMESSAGE_H
#define METAMESSAGE_H

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
#include "IMidiMessage.h"

namespace Sanford { namespace Multimedia { namespace Midi {

    REGION(Meta Message Types)

    /// <summary>
    /// Represents MetaMessage types.
    /// </summary>
    enum MetaType
    {
        /// <summary>
        /// Represents sequencer number type.
        /// </summary>
        SequenceNumber,

        /// <summary>
        /// Represents the text type.
        /// </summary>
        Text,

        /// <summary>
        /// Represents the copyright type.
        /// </summary>
        Copyright,

        /// <summary>
        /// Represents the track name type.
        /// </summary>
        TrackName,

        /// <summary>
        /// Represents the instrument name type.
        /// </summary>
        InstrumentName,

        /// <summary>
        /// Represents the lyric type.
        /// </summary>
        Lyric,

        /// <summary>
        /// Represents the marker type.
        /// </summary>
        Marker,

        /// <summary>
        /// Represents the cue point type.
        /// </summary>
        CuePoint,

        /// <summary>
        /// Represents the program name type.
        /// </summary>
        ProgramName,

        /// <summary>
        /// Represents the device name type.
        /// </summary>
        DeviceName,

        /// <summary>
        /// Represents then end of track type.
        /// </summary>
        EndOfTrack = 0x2F,

        /// <summary>
        /// Represents the tempo type.
        /// </summary>
        Tempo = 0x51,

        /// <summary>
        /// Represents the Smpte offset type.
        /// </summary>
        SmpteOffset = 0x54,

        /// <summary>
        /// Represents the time signature type.
        /// </summary>
        TimeSignature = 0x58,

        /// <summary>
        /// Represents the key signature type.
        /// </summary>
        KeySignature,

        /// <summary>
        /// Represents the proprietary event type.
        /// </summary>
        ProprietaryEvent = 0x7F
    };

    ENDREGION()
        
    class MetaMessageClass;
    typedef MetaMessageClass& MetaMessage;

    /// <summary>
    /// Represents MIDI meta messages.
    /// </summary>
    /// <remarks>
    /// Meta messages are MIDI messages that are stored in MIDI files. These
    /// messages are not sent or received via MIDI but are read and 
    /// interpretted from MIDI files. They provide information that describes 
    /// a MIDI file's properties. For example, tempo changes are implemented
    /// using meta messages.
    /// </remarks>
    class MetaMessageClass : public IMidiMessageIf
    {
        REGION(MetaMessage Members)

        REGION(Constants)

    private:

        /// <summary>
        /// The amount to shift data bytes when calculating the hash code.
        /// </summary>
        static const int Shift = 7;

        //
        // Meta message length constants.
        //

    public:

        /// <summary>
        /// Length in bytes for tempo meta message data.
        /// </summary>
        static const int TempoLength = 3;

        /// <summary>
        /// Length in bytes for SMPTE offset meta message data.
        /// </summary>
        static const int SmpteOffsetLength = 5;

        /// <summary>
        /// Length in bytes for time signature meta message data.
        /// </summary>
        static const int TimeSigLength = 4;

        /// <summary>
        /// Length in bytes for key signature meta message data.
        /// </summary>
        static const int KeySigLength = 2;

        ENDREGION()

        REGION(Class Fields)

    public:

        /// <summary>
        /// End of track meta message.
        /// </summary>
        static const MetaMessage EndOfTrackMessage;

        ENDREGION()

        REGION(Fields)

    private:

        // The meta message type.
        MetaType type;

        // The meta message data.
        bytebuffer data;

        // The hash code value.
        int hashCode;

        ENDREGION()

        REGION(Construction)

    public:

        /// <summary>
        /// Initializes a new instance of the MetaMessage class.
        /// </summary>
        /// <param name="type">
        /// The type of MetaMessage.
        /// </param>
        /// <param name="data">
        /// The MetaMessage data.
        /// </param>
        /// <exception cref="ArgumentException">
        /// The length of the MetaMessage is not valid for the MetaMessage type.
        /// </exception>
        /// <remarks>
        /// Each MetaMessage has type and length properties. For certain 
        /// types, the length of the message data must be a specific value. For
        /// example, tempo messages must have a data length of exactly three. 
        /// Some MetaMessage types can have any data length. Text messages are
        /// an example of a MetaMessage that can have a variable data length.
        /// When a MetaMessage is created, the length of the data is checked
        /// to make sure that it is valid for the specified type. If it is not,
        /// an exception is thrown. 
        /// </remarks>
        MetaMessageClass(MetaType type, bytebuffer data);

        ENDREGION()

        REGION(Methods)

    public:
        
        /// <summary>
        /// Gets a copy of the data bytes for this meta message.
        /// </summary>
        /// <returns>
        /// A copy of the data bytes for this meta message.
        /// </returns>
        bytebuffer GetBytes();

        /// <summary>
        /// Returns a value for the current MetaMessage suitable for use in 
        /// hashing algorithms.
        /// </summary>
        /// <returns>
        /// A hash code for the current MetaMessage.
        /// </returns>
        /*override*/ int GetHashCode();

        /// <summary>
        /// Determines whether two MetaMessage instances are equal.
        /// </summary>
        /// <param name="obj">
        /// The MetaMessage to compare with the current MetaMessage.
        /// </param>
        /// <returns>
        /// <b>true</b> if the specified MetaMessage is equal to the current 
        /// MetaMessage; otherwise, <b>false</b>.
        /// </returns>
        /*override*/ bool Equals(IEquatable obj);

    private:

        // Calculates the hash code.
        void CalculateHashCode();

        /// <summary>
        /// Validates data length.
        /// </summary>
        /// <param name="type">
        /// The MetaMessage type.
        /// </param>
        /// <param name="length">
        /// The length of the MetaMessage data.
        /// </param>
        /// <returns>
        /// <b>true</b> if the data length is valid for this type of 
        /// MetaMessage; otherwise, <b>false</b>.
        /// </returns>
        bool ValidateDataLength(MetaType type, int length);

        ENDREGION()

        REGION(Properties)

    public:

        /// <summary>
        /// Gets the element at the specified index.
        /// </summary>
        /// <exception cref="ArgumentOutOfRangeException">
        /// index is less than zero or greater than or equal to Length.
        /// </exception>
        const byte& operator[](int index);

        /// <summary>
        /// Gets the length of the meta message.
        /// </summary>
        ReadOnlyProperty<int> Length;
        
        /// <summary>
        /// Gets the type of meta message.
        /// </summary>
        ReadOnlyProperty<Midi::MetaType> MetaType;

        ENDREGION()        

        ENDREGION()
            
        REGION(IMidiMessage Members)

	public:

        /// <summary>
        /// Gets the status value.
        /// </summary>
        ReadOnlyProperty<int> Status;

        /// <summary>
        /// Gets the MetaMessage's MessageType.
        /// </summary>
        ReadOnlyProperty<Midi::MessageType> MessageType;
        
        ENDREGION()

    private:
        void init();
        int get_Length();
        Midi::MetaType get_MetaType();
        int get_Message();
        int get_Status();
        Midi::MessageType get_MessageType();

    };

}}}

#endif