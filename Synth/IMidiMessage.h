#ifndef MIDIMESSAGE_H
#define MIDIMESSAGE_H

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

namespace Sanford { namespace Multimedia { namespace Midi {

    /// <summary>
    /// Defines constants representing MIDI message types.
    /// </summary>
    enum MessageType
    {
        Channel,

        SystemExclusive,

        SystemCommon,

        SystemRealtime,

        Meta
    };

    class IMidiMessageIf;
    typedef IMidiMessageIf& IMidiMessage;

    /// <summary>
    /// Represents the basic functionality for all MIDI messages.
    /// </summary>
    class IMidiMessageIf : public IEquatableIf
    {
    
    public: 

        /// <summary>
        /// Gets a byte array representation of the MIDI message.
        /// </summary>
        /// <returns>
        /// A byte array representation of the MIDI message.
        /// </returns>
        virtual bytebuffer GetBytes() = 0;

        /// <summary>
        /// Gets the MIDI message's status value.
        /// </summary>virt
        ReadOnlyProperty<int> Status;

        /// <summary>
        /// Gets the MIDI event's type.
        /// </summary>
        ReadOnlyProperty<MessageType> MessageType;

    private:
        virtual int get_Status() = 0;
        virtual Midi::MessageType get_MessageType() = 0;

    public:
        bool operator == (IMidiMessage other) { return Equals(other); }

    };

}}}

#endif