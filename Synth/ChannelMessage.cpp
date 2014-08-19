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

#include "ChannelMessage.h"
#include "Exception.h"

namespace Sanford { namespace Multimedia { namespace Midi {

    typedef ChannelMessageClass cls;

    const ChannelMessage cls::null = cls(0);

    void cls::init() 
    {
        ShortMessageClass::init();
        this->Command = Functor::New(this, &cls::get_Command);
        this->MidiChannel = Functor::New(this, &cls::get_MidiChannel);
        this->Data1 = Functor::New(this, &cls::get_Data1);
        this->Data2 = Functor::New(this, &cls::get_Data2);
    }

    REGION(Construction)

    /// <summary>
    /// Initializes a new instance of the ChannelEventArgs class with the
    /// specified command, MIDI channel, and data 1 values.
    /// </summary>
    /// <param name="command">
    /// The command value.
    /// </param>
    /// <param name="midiChannel">
    /// The MIDI channel.
    /// </param>
    /// <param name="data1">
    /// The data 1 value.
    /// </param>
    /// <exception cref="ArgumentOutOfRangeException">
    /// If midiChannel is less than zero or greater than 15. Or if 
    /// data1 is less than zero or greater than 127.
    /// </exception>
    ChannelMessageClass::ChannelMessageClass(ChannelCommand command, int midiChannel, int data1)
    { 
        init();
        msg = 0;

        msg = PackCommand(msg, command);
        msg = PackMidiChannel(msg, midiChannel);
        msg = PackData1(msg, data1);

        REGION(Ensure)

        Assert(Command == command);
        Assert(MidiChannel == midiChannel);
        Assert(Data1 == data1);

        ENDREGION()
    }        

    /// <summary>
    /// Initializes a new instance of the ChannelEventArgs class with the 
    /// specified command, MIDI channel, data 1, and data 2 values.
    /// </summary>
    /// <param name="command">
    /// The command value.
    /// </param>
    /// <param name="midiChannel">
    /// The MIDI channel.
    /// </param>
    /// <param name="data1">
    /// The data 1 value.
    /// </param>
    /// <param name="data2">
    /// The data 2 value.
    /// </param>
    /// <exception cref="ArgumentOutOfRangeException">
    /// If midiChannel is less than zero or greater than 15. Or if 
    /// data1 or data 2 is less than zero or greater than 127. 
    /// </exception>
    ChannelMessageClass::ChannelMessageClass(ChannelCommand command, int midiChannel, int data1, int data2)
    {
        init();
        msg = 0;

        msg = PackCommand(msg, command);
        msg = PackMidiChannel(msg, midiChannel);
        msg = PackData1(msg, data1);
        msg = PackData2(msg, data2);

        REGION(Ensure)

        Assert(Command == command);
        Assert(MidiChannel == midiChannel);
        Assert(Data1 == data1);
        Assert(Data2 == data2);

        ENDREGION()
    }

    ChannelMessageClass::ChannelMessageClass(int message)
    {
        init();
        this->msg = message;            
    }

    /// <summary>
    /// Returns a value for the current ChannelEventArgs suitable for use in 
    /// hashing algorithms.
    /// </summary>
    /// <returns>
    /// A hash code for the current ChannelEventArgs.
    /// </returns>
    int ChannelMessageClass::GetHashCode()
    {
        return msg;
    }

    /// <summary>
    /// Determines whether two ChannelEventArgs instances are equal.
    /// </summary>
    /// <param name="obj">
    /// The ChannelMessageEventArgs to compare with the current ChannelEventArgs.
    /// </param>
    /// <returns>
    /// <b>true</b> if the specified object is equal to the current 
    /// ChannelMessageEventArgs; otherwise, <b>false</b>.
    /// </returns>
    bool ChannelMessageClass::Equals(IEquatable obj)
    {
        REGION(Guard)

        if(!(isinst<ChannelMessage>(obj)))
        {
            return false;
        }

        ENDREGION()
            
        ChannelMessage e = (ChannelMessage)obj;            

        return this->msg == e.msg;
    }

    /// <summary>
    /// Returns a value indicating how many bytes are used for the 
    /// specified ChannelCommand.
    /// </summary>
    /// <param name="command">
    /// The ChannelCommand value to test.
    /// </param>
    /// <returns>
    /// The number of bytes used for the specified ChannelCommand.
    /// </returns>
    int ChannelMessageClass::DataBytesPerType(ChannelCommand command)
    {
        int result;

        if(command == ChannelCommand::ChannelPressure ||
            command == ChannelCommand::ProgramChange)
        {
            result = 1;
        }
        else
        {
            result = 2;
        }

        return result;
    }
   
    /// <summary>
    /// Unpacks the command value from the specified integer channel 
    /// message.
    /// </summary>
    /// <param name="message">
    /// The message to unpack.
    /// </param>
    /// <returns>
    /// The command value for the packed message.
    /// </returns>
    ChannelCommand ChannelMessageClass::UnpackCommand(int message)
    {
        return (ChannelCommand)(message & DataMask & MidiChannelMask);
    }
     
    /// <summary>
    /// Unpacks the MIDI channel from the specified integer channel 
    /// message.
    /// </summary>
    /// <param name="message">
    /// The message to unpack.
    /// </param>
    /// <returns>
    /// The MIDI channel for the pack message.
    /// </returns>
    int ChannelMessageClass::UnpackMidiChannel(int message)
    {
        return message & DataMask & CommandMask;
    }

    /// <summary>
    /// Packs the MIDI channel into the specified integer message.
    /// </summary>
    /// <param name="message">
    /// The message into which the MIDI channel is packed.
    /// </param>
    /// <param name="midiChannel">
    /// The MIDI channel to pack into the message.
    /// </param>
    /// <returns>
    /// An integer message.
    /// </returns>
    /// <exception cref="ArgumentOutOfRangeException">
    /// If midiChannel is less than zero or greater than 15.
    /// </exception>
    int ChannelMessageClass::PackMidiChannel(int message, int midiChannel)
    {
        REGION(Preconditons)

        if(midiChannel < 0 || midiChannel > MidiChannelMaxValue)
        {
            throw new ArgumentOutOfRangeException("midiChannel", midiChannel,
                "MIDI channel out of range.");
        }

        ENDREGION()

        return (message & MidiChannelMask) | midiChannel;
    }

    /// <summary>
    /// Packs the command value into an integer message.
    /// </summary>
    /// <param name="message">
    /// The message into which the command is packed.
    /// </param>
    /// <param name="command">
    /// The command value to pack into the message.
    /// </param>
    /// <returns>
    /// An integer message.
    /// </returns>
    int ChannelMessageClass::PackCommand(int message, ChannelCommand command)
    {
        return (message & CommandMask) | (int)command;
    }        
            
    ENDREGION()

    REGION(Properties)

    /// <summary>
    /// Gets the channel command value.
    /// </summary>
    ChannelCommand ChannelMessageClass::get_Command()
    {
        return UnpackCommand(msg);
    }
        
    /// <summary>
    /// Gets the MIDI channel.
    /// </summary>
    int ChannelMessageClass::get_MidiChannel()
    {
        return UnpackMidiChannel(msg);
    }

    /// <summary>
    /// Gets the first data value.
    /// </summary>
    int ChannelMessageClass::get_Data1()
    {
        return UnpackData1(msg);
    }                
        
    /// <summary>
    /// Gets the second data value.
    /// </summary>
    int ChannelMessageClass::get_Data2()
    {
        return UnpackData2(msg);
    }

    /// <summary>
    /// Gets the EventType.
    /// </summary>
    MessageType ChannelMessageClass::get_MessageType()
    {
        return MessageType::Channel;
    }

    ENDREGION()

    ENDREGION()

}}}

