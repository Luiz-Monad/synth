#ifndef SYSCOMMONMESSAGEHEADER_H
#define SYSCOMMONMESSAGEHEADER_H

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
#include "ShortMessage.h"

namespace Sanford { namespace Multimedia { namespace Midi {

    REGION(System Common Message Types)
    
    /// <summary>
    /// Defines constants representing the various system common message types.
    /// </summary>
    enum SysCommonType
    {
        /// <summary>
        /// Represents the MTC system common message type.
        /// </summary>
        MidiTimeCode = 0xF1,

        /// <summary>
        /// Represents the song position pointer type.
        /// </summary>
        SongPositionPointer,

        /// <summary>
        /// Represents the song select type.
        /// </summary>
        SongSelect,

        /// <summary>
        /// Represents the tune request type.
        /// </summary>
        TuneRequest = 0xF6
    };
    
    ENDREGION()

    class SysCommonMessageClass;
    typedef SysCommonMessageClass& SysCommonMessage;

    /// <summary>
    /// Represents MIDI system common messages.
    /// </summary>
    class SysCommonMessageClass : public ShortMessageClass
    {
        REGION(SysCommonMessage Members)

        REGION(Construction)

    public:

        /// <summary>
        /// Initializes a new instance of the SysCommonMessage class with the
        /// specified type.
        /// </summary>
        /// <param name="type">
        /// The type of SysCommonMessage.
        /// </param>
        SysCommonMessageClass(SysCommonType type);

        /// <summary>
        /// Initializes a new instance of the SysCommonMessage class with the 
        /// specified type and the first data value.
        /// </summary>
        /// <param name="type">
        /// The type of SysCommonMessage.
        /// </param>
        /// <param name="data1">
        /// The first data value.
        /// </param>
        /// <exception cref="ArgumentOutOfRangeException">
        /// If data1 is less than zero or greater than 127.
        /// </exception>
        SysCommonMessageClass(SysCommonType type, int data1);

        /// <summary>
        /// Initializes a new instance of the SysCommonMessage class with the 
        /// specified type, first data value, and second data value.
        /// </summary>
        /// <param name="type">
        /// The type of SysCommonMessage.
        /// </param>
        /// <param name="data1">
        /// The first data value.
        /// </param>
        /// <param name="data2">
        /// The second data value.
        /// </param>
        /// <exception cref="ArgumentOutOfRangeException">
        /// If data1 or data2 is less than zero or greater than 127.
        /// </exception>
        SysCommonMessageClass(SysCommonType type, int data1, int data2);
 
        SysCommonMessageClass(int message);
        
        ENDREGION()

        REGION(Methods)

    public:

        /// <summary>
        /// Returns a value for the current SysCommonMessage suitable for use 
        /// in hashing algorithms.
        /// </summary>
        /// <returns>
        /// A hash code for the current SysCommonMessage.
        /// </returns>
        /*override*/ int GetHashCode();

        /// <summary>
        /// Determines whether two SysCommonMessage instances are equal.
        /// </summary>
        /// <param name="obj">
        /// The SysCommonMessage to compare with the current SysCommonMessage.
        /// </param>
        /// <returns>
        /// <b>true</b> if the specified SysCommonMessage is equal to the 
        /// current SysCommonMessage; otherwise, <b>false</b>.
        /// </returns>
        /*override*/ bool Equals(IEquatable obj);
        
        ENDREGION()

        REGION(Properties)

    public:
        
        /// <summary>
        /// Gets the SysCommonType.
        /// </summary>
        ReadOnlyProperty<Midi::SysCommonType> SysCommonType;
        
        /// <summary>
        /// Gets the first data value.
        /// </summary>
        ReadOnlyProperty<int> Data1;

        /// <summary>
        /// Gets the second data value.
        /// </summary>
        ReadOnlyProperty<int> Data2;

        /// <summary>
        /// Gets the MessageType.
        /// </summary>
        ReadOnlyProperty<Midi::MessageType> MessageType;
        
        ENDREGION()

        ENDREGION()

    private:
        void init();
        Midi::SysCommonType get_SysCommonType();
        int get_Data1();
        int get_Data2();
        Midi::MessageType get_MessageType();
            
    public:
        static const SysCommonMessage null;

    };

}}}

#endif
