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

#include "ChannelMessageBuilder.h"

namespace Sanford { namespace Multimedia { namespace Midi {

    typedef ChannelMessageBuilderClass cls;

    void cls::init() 
    {
        if (Functor::IsNull(this, this->Count)) this->Count = Functor::New(&cls::get_Count);
        this->Result = Functor::New(this, &cls::get_Result);
        this->Message = Functor::New(this, &cls::get_Message, &cls::set_Message);
        this->Command = Functor::New(this, &cls::get_Command, &cls::set_Command);
        this->MidiChannel = Functor::New(this, &cls::get_MidiChannel, &cls::set_MidiChannel);
        this->Data1 = Functor::New(this, &cls::get_Data1, &cls::set_Data1);
        this->Data2 = Functor::New(this, &cls::get_Data2, &cls::set_Data2);
        this->messageCache = Hashtable<int, ChannelMessage>::Synchronized(Hashtable<int, ChannelMessage>());
        this->message = 0;
        this->result = ChannelMessageClass::null;
    }
    
	ChannelMessageBuilder cls::operator = (const ChannelMessageBuilder other)
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
    /// Initializes a new instance of the ChannelMessageBuilder class.
    /// </summary>
    ChannelMessageBuilderClass::ChannelMessageBuilderClass() :
        result(ChannelMessageClass::null)
    {
        init();
        this->Command = ChannelCommand::Controller;
        this->MidiChannel = 0;
        this->Data1 = (int)ControllerType::AllSoundOff;
        this->Data2 = 0;
    }

    /// <summary>
    /// Initializes a new instance of the ChannelMessageBuilder class with
    /// the specified ChannelMessageEventArgs.
    /// </summary>
    /// <param name="message">
    /// The ChannelMessageEventArgs to use for initializing the ChannelMessageBuilder.
    /// </param>
    /// <remarks>
    /// The ChannelMessageBuilder uses the specified ChannelMessageEventArgs to 
    /// initialize its property values.
    /// </remarks>
    ChannelMessageBuilderClass::ChannelMessageBuilderClass(ChannelMessage message) :
        result(ChannelMessageClass::null)
    {
        init();
        Initialize(message);
    }
        
    ENDREGION()

    REGION(Methods)
        
    /// <summary>
    /// Initializes the ChannelMessageBuilder with the specified 
    /// ChannelMessageEventArgs.
    /// </summary>
    /// <param name="message">
    /// The ChannelMessageEventArgs to use for initializing the ChannelMessageBuilder.
    /// </param>
    void ChannelMessageBuilderClass::Initialize(ChannelMessage message)
    {
        this->message = message.Message;
    }

    /// <summary>
    /// Clears the ChannelMessageEventArgs cache.
    /// </summary>
    void ChannelMessageBuilderClass::Clear()
    {
        messageCache.Clear();
    }        
    
    ENDREGION()

    REGION(Properties)
    
    /// <summary>
    /// Gets the number of messages in the ChannelMessageEventArgs cache.
    /// </summary>
    int ChannelMessageBuilderClass::get_Count()
    {
        return messageCache.Count;
    }

    /// <summary>
    /// Gets the built ChannelMessageEventArgs.
    /// </summary>
    ChannelMessage ChannelMessageBuilderClass::get_Result()
    {
        return result;
    }

    /// <summary>
    /// Gets or sets the ChannelMessageEventArgs as a packed integer. 
    /// </summary>
    int ChannelMessageBuilderClass::get_Message()
    {
        return message;
    }
    void ChannelMessageBuilderClass::set_Message(int value)
    {
        message = value;
    }

    /// <summary>
    /// Gets or sets the Command value to use for building the 
    /// ChannelMessageEventArgs.
    /// </summary>
    ChannelCommand ChannelMessageBuilderClass::get_Command()
    {
        return ChannelMessageClass::UnpackCommand(message);
    }
    void ChannelMessageBuilderClass::set_Command(ChannelCommand value)
    {
        message = ChannelMessageClass::PackCommand(message, value);
    }

    /// <summary>
    /// Gets or sets the MIDI channel to use for building the 
    /// ChannelMessageEventArgs.
    /// </summary>
    /// <exception cref="ArgumentOutOfRangeException">
    /// MidiChannel is set to a value less than zero or greater than 15.
    /// </exception>
    int ChannelMessageBuilderClass::get_MidiChannel()
    {
        return ChannelMessageClass::UnpackMidiChannel(message);
    }
    void ChannelMessageBuilderClass::set_MidiChannel(int value)
    {
        message = ChannelMessageClass::PackMidiChannel(message, value);
    }

    /// <summary>
    /// Gets or sets the first data value to use for building the 
    /// ChannelMessageEventArgs.
    /// </summary>
    /// <exception cref="ArgumentOutOfRangeException">
    /// Data1 is set to a value less than zero or greater than 127.
    /// </exception>
    int ChannelMessageBuilderClass::get_Data1()
    {
        return ShortMessageClass::UnpackData1(message);
    }
    void ChannelMessageBuilderClass::set_Data1(int value)
    {
        message = ShortMessageClass::PackData1(message, value);
    }

    /// <summary>
    /// Gets or sets the second data value to use for building the 
    /// ChannelMessageEventArgs.
    /// </summary>
    /// <exception cref="ArgumentOutOfRangeException">
    /// Data2 is set to a value less than zero or greater than 127.
    /// </exception>
    int ChannelMessageBuilderClass::get_Data2()
    {
        return ShortMessageClass::UnpackData2(message);
    }
    void ChannelMessageBuilderClass::set_Data2(int value)
    {
        message = ShortMessageClass::PackData2(message, value);
    }
    
    ENDREGION()
        
    ENDREGION()

    REGION(IMessageBuilder Members)

    /// <summary>
    /// Builds a ChannelMessageEventArgs.
    /// </summary>
    void ChannelMessageBuilderClass::Build()
    {
        result = (ChannelMessage)messageCache[message];

        // If the message does not exist.
        if(result == ChannelMessageClass::null)
        {
            result = ChannelMessageClass(message);

            // Add message to cache.
            messageCache.Add(message, result);
        }
    }
    
    ENDREGION()

}}}

