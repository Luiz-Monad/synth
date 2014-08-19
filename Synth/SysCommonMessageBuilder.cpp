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

#include "SysCommonMessageBuilder.h"

namespace Sanford { namespace Multimedia { namespace Midi {
    
    typedef SysCommonMessageBuilderClass cls;

    void cls::init() 
    {
        if (Functor::IsNull(this, this->Count)) this->Count = Functor::New(&cls::get_Count);
        this->Result = Functor::New(this, &cls::get_Result);
        this->Message = Functor::New(this, &cls::get_Message, &cls::set_Message);
        this->Type = Functor::New(this, &cls::get_Type, &cls::set_Type);
        this->Data1 = Functor::New(this, &cls::get_Data1, &cls::set_Data1);
        this->Data2 = Functor::New(this, &cls::get_Data2, &cls::set_Data2);
        this->messageCache = Hashtable<int, SysCommonMessage>::Synchronized(Hashtable<int, SysCommonMessage>());
        this->message = 0;
        this->result = SysCommonMessageClass::null;
    }
        
	SysCommonMessageBuilder cls::operator = (const SysCommonMessageBuilder other)
	{
        if (this != &other)
        {
            this->messageCache = other.messageCache;
            this->message = other.message;
            this->result = other.result;
        }
        return *this;
	}

    REGION(Construction)

    /// <summary>
    /// Initializes a new instance of the SysCommonMessageBuilder class.
    /// </summary>
    SysCommonMessageBuilderClass::SysCommonMessageBuilderClass() :
        result(SysCommonMessageClass::null)
    {
        init();
        this->Type = SysCommonType::TuneRequest;
    }

    /// <summary>
    /// Initializes a new instance of the SysCommonMessageBuilder class 
    /// with the specified SystemCommonMessage.
    /// </summary>
    /// <param name="message">
    /// The SysCommonMessage to use for initializing the 
    /// SysCommonMessageBuilder.
    /// </param>
    /// <remarks>
    /// The SysCommonMessageBuilder uses the specified SysCommonMessage to 
    /// initialize its property values.
    /// </remarks>
    SysCommonMessageBuilderClass::SysCommonMessageBuilderClass(SysCommonMessage message) :
        result(SysCommonMessageClass::null)
    {
        init();
        Initialize(message);
    }
        
    ENDREGION()

    REGION(Methods)
        
    /// <summary>
    /// Initializes the SysCommonMessageBuilder with the specified 
    /// SysCommonMessage.
    /// </summary>
    /// <param name="message">
    /// The SysCommonMessage to use for initializing the 
    /// SysCommonMessageBuilder.
    /// </param>
    void SysCommonMessageBuilderClass::Initialize(SysCommonMessage message)
    {
        this->message = message.Message;
    }

    /// <summary>
    /// Clears the SysCommonMessageBuilder cache.
    /// </summary>
    void SysCommonMessageBuilderClass::Clear()
    {
        messageCache.Clear();
    }          
    
    ENDREGION()

    REGION(Properties)
    
    /// <summary>
    /// Gets the number of messages in the SysCommonMessageBuilder cache.
    /// </summary>
    int SysCommonMessageBuilderClass::get_Count()
    {
        return messageCache.Count;
    }

    /// <summary>
    /// Gets the built SysCommonMessage.
    /// </summary>
    SysCommonMessage SysCommonMessageBuilderClass::get_Result()
    {
        return result;
    }

    /// <summary>
    /// Gets or sets the SysCommonMessage as a packed integer.
    /// </summary>
    int SysCommonMessageBuilderClass::get_Message()
    {
        return message;
    }
    void SysCommonMessageBuilderClass::set_Message(int value)
    {
        message = value;
    }

    /// <summary>
    /// Gets or sets the type of SysCommonMessage.
    /// </summary>
    SysCommonType SysCommonMessageBuilderClass::get_Type()
    {
        return (SysCommonType)ShortMessageClass::UnpackStatus(message);
    }
    void SysCommonMessageBuilderClass::set_Type(SysCommonType value)
    {
        message = ShortMessageClass::PackStatus(message, (int)value);
    }

    /// <summary>
    /// Gets or sets the first data value to use for building the 
    /// SysCommonMessage.
    /// </summary>
    /// <exception cref="ArgumentOutOfRangeException">
    /// Data1 is set to a value less than zero or greater than 127.
    /// </exception>
    int SysCommonMessageBuilderClass::get_Data1()
    {
        return ShortMessageClass::UnpackData1(message);
    }
    void SysCommonMessageBuilderClass::set_Data1(int value)
    {
        message = ShortMessageClass::PackData1(message, value);
    }

    /// <summary>
    /// Gets or sets the second data value to use for building the 
    /// SysCommonMessage.
    /// </summary>
    /// <exception cref="ArgumentOutOfRangeException">
    /// Data2 is set to a value less than zero or greater than 127.
    /// </exception>
    int SysCommonMessageBuilderClass::get_Data2()
    {
        return ShortMessageClass::UnpackData2(message);
    }
    void SysCommonMessageBuilderClass::set_Data2(int value)
    {
        message = ShortMessageClass::PackData2(message, value);
    }
    
    ENDREGION()
        
    ENDREGION()

    REGION(IMessageBuilder Members)

    /// <summary>
    /// Builds a SysCommonMessage.
    /// </summary>
    void SysCommonMessageBuilderClass::Build()
    {
        result = (SysCommonMessage)messageCache[message];

        if(result == SysCommonMessageClass::null)
        {
            result = SysCommonMessageClass(message);

            messageCache.Add(message, result);
        }
    }
    
    ENDREGION()

}}}

