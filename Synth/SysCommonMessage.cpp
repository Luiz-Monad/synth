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

#include "SysCommonMessage.h"

namespace Sanford { namespace Multimedia { namespace Midi {

    typedef SysCommonMessageClass cls;

    const SysCommonMessage cls::null = cls(0);

    void cls::init() 
    {
        ShortMessageClass::init();
        this->SysCommonType = Functor::New(this, &cls::get_SysCommonType);
        this->Data1 = Functor::New(this, &cls::get_Data1);
        this->Data2 = Functor::New(this, &cls::get_Data2);
    }

    REGION(Construction)

    /// <summary>
    /// Initializes a new instance of the SysCommonMessage class with the
    /// specified type.
    /// </summary>
    /// <param name="type">
    /// The type of SysCommonMessage.
    /// </param>
    SysCommonMessageClass::SysCommonMessageClass(Midi::SysCommonType type)
    {
        init();
        msg = (int)type;

        REGION(Ensure)

        Assert(SysCommonType == type);

        ENDREGION()
    }

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
    SysCommonMessageClass::SysCommonMessageClass(Midi::SysCommonType type, int data1)
    { 
        init();
        msg = (int)type;
        msg = PackData1(msg, data1);

        REGION(Ensure)

        Assert(SysCommonType == type);
        Assert(Data1 == data1);

        ENDREGION()
    }

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
    SysCommonMessageClass::SysCommonMessageClass(Midi::SysCommonType type, int data1, int data2)
    {
        init();
        msg = (int)type;
        msg = PackData1(msg, data1);
        msg = PackData2(msg, data2);

        REGION(Ensure)

        Assert(SysCommonType == type);
        Assert(Data1 == data1);
        Assert(Data2 == data2);

        ENDREGION()
    }       
 
    SysCommonMessageClass::SysCommonMessageClass(int message)
    {
        init();
        this->msg = message;
    }

    /// <summary>
    /// Returns a value for the current SysCommonMessage suitable for use 
    /// in hashing algorithms.
    /// </summary>
    /// <returns>
    /// A hash code for the current SysCommonMessage.
    /// </returns>
    int SysCommonMessageClass::GetHashCode()
    {
        return msg;
    }

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
    bool SysCommonMessageClass::Equals(IEquatable obj)
    {
        REGION(Guard)

        if(!(isinst<SysCommonMessage>(obj)))
        {
            return false;
        }

        ENDREGION()

        SysCommonMessage message = (SysCommonMessage)obj;

        return (this->SysCommonType == message.SysCommonType &&
            this->Data1 == message.Data1 &&
            this->Data2 == message.Data2);
    }
                
    ENDREGION()

    REGION(Properties)

    /// <summary>
    /// Gets the SysCommonType.
    /// </summary>
    SysCommonType SysCommonMessageClass::get_SysCommonType()
    {
        return (Midi::SysCommonType)UnpackStatus(msg);
    }
        
    /// <summary>
    /// Gets the first data value.
    /// </summary>
    int SysCommonMessageClass::get_Data1()
    {
        return UnpackData1(msg);
    }

    /// <summary>
    /// Gets the second data value.
    /// </summary>
    int SysCommonMessageClass::get_Data2()
    {
        return UnpackData2(msg);
    }                    

    /// <summary>
    /// Gets the MessageType.
    /// </summary>
    MessageType SysCommonMessageClass::get_MessageType()
    {
        return MessageType::SystemCommon;
    }
    
    ENDREGION()

    ENDREGION()

}}}
