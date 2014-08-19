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

#include "ShortMessage.h"
#include "Exception.h"

namespace Sanford { namespace Multimedia { namespace Midi {

    typedef ShortMessageClass cls;
    void cls::init() 
    {
        this->Message = Functor::New(this, &cls::get_Message);
        this->Status = Functor::New(this, &cls::get_Status);
        this->MessageType = Functor::New(this, &cls::get_MessageType);
        this->msg = 0;
    }

    REGION(Methods)

    bytebuffer ShortMessageClass::GetBytes()
    {
        return BitConverter::GetBytes(msg);
    }

    int ShortMessageClass::PackStatus(int message, int status)
    {
        REGION(Require)

        if(status < 0 || status > StatusMaxValue)
        {
            throw new ArgumentOutOfRangeException("status", status,
                "Status value out of range.");
        }

        ENDREGION()

        return (message & StatusMask) | status;
    }

    int ShortMessageClass::PackData1(int message, int data1)
    {
        REGION(Require)

        if(data1 < 0 || data1 > DataMaxValue)
        {
            throw new ArgumentOutOfRangeException("data1", data1,
                "Data 1 value out of range.");
        }

        ENDREGION()

        return (message & Data1Mask) | (data1 << Shift);
    }

    int ShortMessageClass::PackData2(int message, int data2)
    {
        REGION(Require)

        if(data2 < 0 || data2 > DataMaxValue)
        {
            throw new ArgumentOutOfRangeException("data2", data2,
                "Data 2 value out of range.");
        }

        ENDREGION()

        return (message & Data2Mask) | (data2 << (Shift * 2));
    }

    int ShortMessageClass::UnpackStatus(int message)
    {
        return message & DataMask;
    }

    int ShortMessageClass::UnpackData1(int message)
    {
        return (message & ~Data1Mask) >> Shift;
    }

    int ShortMessageClass::UnpackData2(int message)
    {
        return (message & ~Data2Mask) >> (Shift * 2);
    }

    ENDREGION()

    REGION(Properties)

    /// <summary>
    /// Gets the short message as a packed integer.
    /// </summary>
    /// <remarks>
    /// The message is packed into an integer value with the low-order byte
    /// of the low-word representing the status value. The high-order byte
    /// of the low-word represents the first data value, and the low-order
    /// byte of the high-word represents the second data value.
    /// </remarks>
    int ShortMessageClass::get_Message()
    {
        return msg;
    }

    /// <summary>
    /// Gets the messages's status value.
    /// </summary>
    int ShortMessageClass::get_Status()
    {
        return UnpackStatus(msg);
    }

    ENDREGION()

    ENDREGION()

}}}

