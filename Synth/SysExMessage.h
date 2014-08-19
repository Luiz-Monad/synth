#ifndef SYSEXMESSAGE_H
#define SYSEXMESSAGE_H

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

	/// <summary>
    /// Defines constants representing various system exclusive message types.
    /// </summary>
    enum SysExType
    {
        /// <summary>
        /// Represents the start of system exclusive message type.
        /// </summary>
        Start = 0xF0,

        /// <summary>
        /// Represents the continuation of a system exclusive message.
        /// </summary>
        Continuation = 0xF7
    };

	class SysExMessageClass;
	typedef SysExMessageClass& SysExMessage;

	/// <summary>
	/// Represents MIDI system exclusive messages.
	/// </summary>
    class SysExMessageClass : public IMidiMessageIf
    {
        REGION(SysExEventMessage Members)

        REGION(Constants)

	public:

        /// <summary>
        /// Maximum value for system exclusive channels.
        /// </summary>
        static const int SysExChannelMaxValue = 127;

        ENDREGION()

        REGION(Fields)

	private:

        // The system exclusive data.
        bytebuffer data;

        ENDREGION()

        REGION(Construction)

	public:

        /// <summary>
        /// Initializes a new instance of the SysExMessageEventArgs class with the
        /// specified system exclusive data.
        /// </summary>
        /// <param name="data">
        /// The system exclusive data.
        /// </param>
        /// <remarks>
        /// The system exclusive data's status byte, the first byte in the 
        /// data, must have a value of 0xF0 or 0xF7.
        /// </remarks>
        SysExMessageClass(bytebuffer data);

        ENDREGION()

        REGION(Methods)

	public:

        bytebuffer GetBytes();

        void CopyTo(bytebuffer buffer, int index);

        /*override*/ bool Equals(IEquatable obj);

        /*override*/ int GetHashCode();

        ENDREGION()

        REGION(Properties)

	public:

        /// <summary>
        /// Gets the element at the specified index.
        /// </summary>
        /// <exception cref="ArgumentOutOfRangeException">
        /// If index is less than zero or greater than or equal to the length 
        /// of the message.
        /// </exception>
        const byte& operator[](int index);

        /// <summary>
        /// Gets the length of the system exclusive data.
        /// </summary>
        ReadOnlyProperty<int> Length;

        /// <summary>
        /// Gets the system exclusive type.
        /// </summary>
        ReadOnlyProperty<Midi::SysExType> SysExType;

        ENDREGION()

        ENDREGION()
		            
        REGION(IMidiMessage Members)

	public:

        /// <summary>
        /// Gets the status value.
        /// </summary>
        ReadOnlyProperty<int> Status;

        /// <summary>
        /// Gets the MessageType.
        /// </summary>
        ReadOnlyProperty<Midi::MessageType> MessageType;

		ENDREGION()

        REGION(IEnumerable Members)

	public:

        bytebufferclass::iterator GetIterator();

        ENDREGION()
			
    private:
        void init();
        int get_Length();
        Midi::SysExType get_SysExType();
        int get_Status();
        Midi::MessageType get_MessageType();

    };

}}}

#endif