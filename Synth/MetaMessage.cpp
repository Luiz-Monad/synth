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

#include "MetaMessage.h"
#include "Exception.h"

namespace Sanford { namespace Multimedia { namespace Midi {
    
    typedef MetaMessageClass cls;

    const MetaMessage cls::EndOfTrackMessage = cls(MetaType::EndOfTrack, bytebufferclass(0));

    void cls::init() 
    {
        this->Length = Functor::New(this, &cls::get_Length);
        this->MetaType = Functor::New(this, &cls::get_MetaType);
        this->Status = Functor::New(this, &cls::get_Status);
        this->MessageType = Functor::New(this, &cls::get_MessageType);
        this->type = MetaType::ProprietaryEvent;
        this->data = bytebufferclass::null;
        this->hashCode = 0;
    }

    REGION(Construction)

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
    MetaMessageClass::MetaMessageClass(Midi::MetaType type, bytebuffer data) :
        data(data)
    {
        init();
        REGION(Require)
        
        if(data == bytebufferclass::null)
        {
            throw new ArgumentNullException("data");
        }
        else if(!ValidateDataLength(type, data.Length))
        {
            throw new ArgumentException(
                "Length of data not valid for meta message type.");
        }

        ENDREGION()

        this->type = type;
            
        // Create storage for meta message data.
        this->data = bytebufferclass(data.Length);

        // Copy data into storage.
        data.CopyTo(this->data, 0);

        CalculateHashCode();
    }

    ENDREGION()

    REGION(Methods)
        
    /// <summary>
    /// Gets a copy of the data bytes for this meta message.
    /// </summary>
    /// <returns>
    /// A copy of the data bytes for this meta message.
    /// </returns>
    bytebuffer MetaMessageClass::GetBytes()
    {
        return data.Clone();
    }

    /// <summary>
    /// Returns a value for the current MetaMessage suitable for use in 
    /// hashing algorithms.
    /// </summary>
    /// <returns>
    /// A hash code for the current MetaMessage.
    /// </returns>
    int MetaMessageClass::GetHashCode()
    {
        return hashCode;
    }

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
    bool MetaMessageClass::Equals(IEquatable obj)
    {
        REGION(Guard)

        if(!(isinst<MetaMessage>(obj)))
        {
            return false;
        }

        ENDREGION()

        bool equal = true;
        MetaMessage message = (MetaMessage)obj;

        // If the types do not match.
        if(MetaType != message.MetaType)
        {
            // The messages are not equal
            equal = false;
        }

        // If the message lengths are not equal.
        if(equal && Length != message.Length)
        {
            // The message are not equal.
            equal = false;
        }

        // Check to see if the data is equal.
        for(int i = 0; i < Length && equal; i++)
        {
            // If a data value does not match.
            if((*this)[i] != message[i])
            {
                // The messages are not equal.
                equal = false;
            }
        }

        return equal;
    }

    // Calculates the hash code.
    void MetaMessageClass::CalculateHashCode()
    {            
        // TODO: This algorithm may need work.

        hashCode = (int)MetaType;

        for(int i = 0; i < data.Length; i += 3)
        {
            hashCode ^= data[i];
        }

        for(int i = 1; i < data.Length; i += 3)
        {
            hashCode ^= data[i] << Shift;
        }

        for(int i = 2; i < data.Length; i += 3)
        {
            hashCode ^= data[i] << Shift * 2;
        }
    }

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
    bool MetaMessageClass::ValidateDataLength(Midi::MetaType type, int length)
    {
        REGION(Require)

        Assert(length >= 0);

        ENDREGION()

        bool result = true;

        // Determine which type of meta message this is and check to make
        // sure that the data length value is valid.
        switch(type)
        {
        case MetaType::SequenceNumber:
                if(length != 0 || length != 2)
                {
                    result = false;
                }
                break;

            case MetaType::EndOfTrack:
                if(length != 0)
                {
                    result = false;
                }
                break;

            case MetaType::Tempo:
                if(length != TempoLength)
                {
                    result = false;
                }
                break;

            case MetaType::SmpteOffset:
                if(length != SmpteOffsetLength)
                {
                    result = false;
                }
                break;

            case MetaType::TimeSignature:
                if(length != TimeSigLength)
                {
                    result = false;
                }
                break;

            case MetaType::KeySignature:
                if(length != KeySigLength)
                {
                    result = false;
                }
                break;

            default:
                result = true;
                break;
        }

        return result;      
    }

    ENDREGION()

    REGION(Properties)

    /// <summary>
    /// Gets the element at the specified index.
    /// </summary>
    /// <exception cref="ArgumentOutOfRangeException">
    /// index is less than zero or greater than or equal to Length.
    /// </exception>
    const byte& MetaMessageClass::operator [](int index)
    {
        REGION(Require)

        if(index < 0 || index >= Length)
        {
            throw new ArgumentOutOfRangeException("index", index,
                "Index into MetaMessage out of range.");
        }

        ENDREGION()

        return data[index];
    }

    /// <summary>
    /// Gets the length of the meta message.
    /// </summary>
    int MetaMessageClass::get_Length()
    { 
        return data.Length;
    }
        
    /// <summary>
    /// Gets the type of meta message.
    /// </summary>
    MetaType MetaMessageClass::get_MetaType()
    {
        return type;
    }

    ENDREGION()

    ENDREGION()        

    REGION(IMidiMessage Members)

    /// <summary>
    /// Gets the status value.
    /// </summary>
    int MetaMessageClass::get_Status()
    {
        // All meta messages have the same status value (0xFF).
        return 0xFF;
    }

    /// <summary>
    /// Gets the MetaMessage's MessageType.
    /// </summary>
    MessageType MetaMessageClass::get_MessageType()
    {
        return MessageType::Meta;
    }

    ENDREGION()

}}}


