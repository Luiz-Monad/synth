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

#include "SysExMessage.h"
#include "Exception.h"

namespace Sanford { namespace Multimedia { namespace Midi {
	 
    typedef SysExMessageClass cls;
    void cls::init() 
    {
        this->Length = Functor::New(this, &cls::get_Length);
        this->SysExType = Functor::New(this, &cls::get_SysExType);
        this->Status = Functor::New(this, &cls::get_Status);
        this->MessageType = Functor::New(this, &cls::get_MessageType);
        this->data = bytebufferclass::null;
    }

    REGION(Construction)

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
    SysExMessageClass::SysExMessageClass(bytebuffer data) :
		data(data)
    {
		init();
        REGION(Require)

        if(data.Length < 1)
        {
            throw new ArgumentException(
                "System exclusive data is too short.", "data");
        }
        else if(data[0] != (byte)SysExType::Start && 
            data[0] != (byte)SysExType::Continuation)
        {
            throw new ArgumentException(
                "Unknown status value.", "data");
        }

        ENDREGION()            
         
        this->data = bytebufferclass(data.Length);
        data.CopyTo(this->data, 0);
    }        

    ENDREGION()

    REGION(Methods)

    bytebuffer SysExMessageClass::GetBytes()
    {
        return data.Clone();
    }

    void SysExMessageClass::CopyTo(bytebuffer buffer, int index)
    {
        data.CopyTo(buffer, index);
    }

    bool SysExMessageClass::Equals(IEquatable obj)
    {
        REGION(Guard)

		if(!(isinst<SysExMessage>(obj)))
        {
            return false;
        }

        ENDREGION()

        SysExMessage message = (SysExMessage)obj;

        bool equals = true;

        if(this->Length != message.Length)
        {
            equals = false;
        }

        for(int i = 0; i < this->Length && equals; i++)
        {
            if((*this)[i] != message[i])
            {
                equals = false;
            }
        }

        return equals;
    }

    int SysExMessageClass::GetHashCode()
    {
        return data.GetHashCode();
    }

    ENDREGION()

    REGION(Properties)

    /// <summary>
    /// Gets the element at the specified index.
    /// </summary>
    /// <exception cref="ArgumentOutOfRangeException">
    /// If index is less than zero or greater than or equal to the length 
    /// of the message.
    /// </exception>
    const byte& SysExMessageClass::operator [](int index)
    {
        REGION(Require)

        if(index < 0 || index >= Length)
        {
            throw new ArgumentOutOfRangeException("index", index,
                "Index into system exclusive message out of range.");
        }

        ENDREGION()

        return data[index];
    }

    /// <summary>
    /// Gets the length of the system exclusive data.
    /// </summary>
    int SysExMessageClass::get_Length()
    { 
        return data.Length;
    }

    /// <summary>
    /// Gets the system exclusive type.
    /// </summary>
    SysExType SysExMessageClass::get_SysExType()
    {
        return (Midi::SysExType)(data[0]);
    }

    ENDREGION()

    ENDREGION()

    /// <summary>
    /// Gets the status value.
    /// </summary>
    int SysExMessageClass::get_Status()
    {
        return (int)data[0];
    }

    /// <summary>
    /// Gets the MessageType.
    /// </summary>
    MessageType SysExMessageClass::get_MessageType()
    {
        return MessageType::SystemExclusive;
    }

    REGION(IEnumerable Members)

    bytebufferclass::iterator SysExMessageClass::GetIterator()
    {
        return data.GetIterator();
    }

    ENDREGION()

}}}
