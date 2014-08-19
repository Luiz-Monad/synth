#ifndef SHORTMESSAGE_H
#define SHORTMESSAGE_H

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

    class ShortMessageClass;
    typedef ShortMessageClass& ShortMessage;

    /// <summary>
    /// Represents the basic class for all MIDI short messages.
    /// </summary>
    /// <remarks>
    /// MIDI short messages represent all MIDI messages except meta messages
    /// and system exclusive messages. This includes channel messages, system
    /// realtime messages, and system common messages.
    /// </remarks>
    class ShortMessageClass : public IMidiMessageIf
    {
        REGION(ShortMessage Members)

        REGION(Constants)
            
    public: 
        
        static const int DataMaxValue = 127;
        
        static const int StatusMaxValue = 255;
        
        //
        // Bit manipulation constants.
        //

    protected: 

        static const int StatusMask = ~255;
        static const int DataMask = ~StatusMask;
        static const int Data1Mask = ~65280;
        static const int Data2Mask = ~Data1Mask + DataMask;
        static const int Shift = 8;
        
        ENDREGION()

    protected: 
        
        int msg;
            
        REGION(Methods)
        
    public:

        bytebuffer GetBytes();

        static int PackStatus(int message, int status);

        static int PackData1(int message, int data1);

        static int PackData2(int message, int data2);

        static int UnpackStatus(int message);

        static int UnpackData1(int message);

        static int UnpackData2(int message);

        ENDREGION()

        REGION(Properties)

    public:

        /// <summary>
        /// Gets the short message as a packed integer.
        /// </summary>
        /// <remarks>
        /// The message is packed into an integer value with the low-order byte
        /// of the low-word representing the status value. The high-order byte
        /// of the low-word represents the first data value, and the low-order
        /// byte of the high-word represents the second data value.
        /// </remarks>
        ReadOnlyProperty<int> Message;

        /// <summary>
        /// Gets the messages's status value.
        /// </summary>
        ReadOnlyProperty<int> Status;

        /*abstract*/ ReadOnlyProperty<Midi::MessageType> MessageType;
        
        ENDREGION()

        ENDREGION()

    protected:
        void init();

    private:
        int get_Message();
        int get_Status();
        virtual Midi::MessageType get_MessageType() = 0;

    };

}}}

#endif
