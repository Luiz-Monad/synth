#ifndef CHANNELMESSAGEBUILDER_H
#define CHANNELMESSAGEBUILDER_H

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
#include "Hashtable.h"
#include "IMessageBuilder.h"
#include "ChannelMessage.h"

template Hashtable<int, Sanford::Multimedia::Midi::ChannelMessage>;

namespace Sanford { namespace Multimedia { namespace Midi {

    class ChannelMessageBuilderClass;
    typedef ChannelMessageBuilderClass& ChannelMessageBuilder;

    /// <summary>
    /// Provides functionality for building ChannelMessages.
    /// </summary>
    class ChannelMessageBuilderClass : IMessageBuilderIf
    {
        REGION(ChannelMessageBuilder Members)

        REGION(Class Fields)

    private:

        // Stores the ChannelMessages.
        static Hashtable<int, ChannelMessage> messageCache;

        ENDREGION()

        REGION(Fields)
        
    private:

        // The channel message as a packed integer.
        int message;

        // The built ChannelMessage
        ChannelMessage result;

        ENDREGION()

        REGION(Construction)

    public:

        /// <summary>
        /// Initializes a new instance of the ChannelMessageBuilder class.
        /// </summary>
        ChannelMessageBuilderClass();

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
        ChannelMessageBuilderClass(ChannelMessage message);

        ENDREGION()

        REGION(Methods)

    public:
        
        /// <summary>
        /// Initializes the ChannelMessageBuilder with the specified 
        /// ChannelMessageEventArgs.
        /// </summary>
        /// <param name="message">
        /// The ChannelMessageEventArgs to use for initializing the ChannelMessageBuilder.
        /// </param>
        void Initialize(ChannelMessage message);

        /// <summary>
        /// Clears the ChannelMessageEventArgs cache.
        /// </summary>
        static void Clear();

        ENDREGION()

        REGION(Properties)
        
    public:
        
        /// <summary>
        /// Gets the number of messages in the ChannelMessageEventArgs cache.
        /// </summary>
        static ReadOnlyProperty<int> Count;

        /// <summary>
        /// Gets the built ChannelMessageEventArgs.
        /// </summary>
        ReadOnlyProperty<ChannelMessage> Result;

        /// <summary>
        /// Gets or sets the ChannelMessageEventArgs as a packed integer. 
        /// </summary>
        Property<int> Message;

        /// <summary>
        /// Gets or sets the Command value to use for building the 
        /// ChannelMessageEventArgs.
        /// </summary>
        Property<ChannelCommand> Command;

        /// <summary>
        /// Gets or sets the MIDI channel to use for building the 
        /// ChannelMessageEventArgs.
        /// </summary>
        /// <exception cref="ArgumentOutOfRangeException">
        /// MidiChannel is set to a value less than zero or greater than 15.
        /// </exception>
        Property<int> MidiChannel;

        /// <summary>
        /// Gets or sets the first data value to use for building the 
        /// ChannelMessageEventArgs.
        /// </summary>
        /// <exception cref="ArgumentOutOfRangeException">
        /// Data1 is set to a value less than zero or greater than 127.
        /// </exception>
        Property<int> Data1;

        /// <summary>
        /// Gets or sets the second data value to use for building the 
        /// ChannelMessageEventArgs.
        /// </summary>
        /// <exception cref="ArgumentOutOfRangeException">
        /// Data2 is set to a value less than zero or greater than 127.
        /// </exception>
        Property<int> Data2;

        ENDREGION()
        
        ENDREGION()

        REGION(IMessageBuilder Members)
        
    public:

        /// <summary>
        /// Builds a ChannelMessageEventArgs.
        /// </summary>
        void Build();
       
        ENDREGION()

    private:
        void init();
        static int get_Count();
        ChannelMessage get_Result();
        int get_Message();
        void set_Message(int value);
        ChannelCommand get_Command();
        void set_Command(ChannelCommand value);
        int get_MidiChannel();
        void set_MidiChannel(int value);
        int get_Data1();
        void set_Data1(int value);
        int get_Data2();
        void set_Data2(int value);

	public:
		ChannelMessageBuilder operator = (const ChannelMessageBuilder other);

    };

}}}

#endif