#ifndef SYSCOMMONMESSAGEBUILDER_H
#define SYSCOMMONMESSAGEBUILDER_H

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
#include "SysCommonMessage.h"

template Hashtable<int, Sanford::Multimedia::Midi::SysCommonMessage>;

namespace Sanford { namespace Multimedia { namespace Midi {

    class SysCommonMessageBuilderClass;
    typedef SysCommonMessageBuilderClass& SysCommonMessageBuilder;

    /// <summary>
    /// Provides functionality for building SysCommonMessages.
    /// </summary>
    class SysCommonMessageBuilderClass : IMessageBuilderIf
    {
        REGION(SysCommonMessageBuilder Members)

        REGION(Class Fields)

    private:

        // Stores the SystemCommonMessages.
        static Hashtable<int, SysCommonMessage> messageCache;
        
        ENDREGION()

        REGION(Fields)
        
    private:

        // The SystemCommonMessage as a packed integer.
        int message;

        // The built SystemCommonMessage.
        SysCommonMessage result;
        
        ENDREGION()

        REGION(Construction)

    public:

        /// <summary>
        /// Initializes a new instance of the SysCommonMessageBuilder class.
        /// </summary>
        SysCommonMessageBuilderClass();

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
        SysCommonMessageBuilderClass(SysCommonMessage message);
        
        ENDREGION()

        REGION(Methods)

    public:
        
        /// <summary>
        /// Initializes the SysCommonMessageBuilder with the specified 
        /// SysCommonMessage.
        /// </summary>
        /// <param name="message">
        /// The SysCommonMessage to use for initializing the 
        /// SysCommonMessageBuilder.
        /// </param>
        void Initialize(SysCommonMessage message);

        /// <summary>
        /// Clears the SysCommonMessageBuilder cache.
        /// </summary>
        static void Clear();
        
        ENDREGION()

        REGION(Properties)
        
    public:
        
        /// <summary>
        /// Gets the number of messages in the SysCommonMessageBuilder cache.
        /// </summary>
        static ReadOnlyProperty<int> Count;

        /// <summary>
        /// Gets the built SysCommonMessage.
        /// </summary>
        ReadOnlyProperty<SysCommonMessage> Result;

        /// <summary>
        /// Gets or sets the SysCommonMessage as a packed integer.
        /// </summary>
        Property<int> Message;

        /// <summary>
        /// Gets or sets the type of SysCommonMessage.
        /// </summary>
        Property<SysCommonType> Type;

        /// <summary>
        /// Gets or sets the first data value to use for building the 
        /// SysCommonMessage.
        /// </summary>
        /// <exception cref="ArgumentOutOfRangeException">
        /// Data1 is set to a value less than zero or greater than 127.
        /// </exception>
        Property<int> Data1;

        /// <summary>
        /// Gets or sets the second data value to use for building the 
        /// SysCommonMessage.
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
        /// Builds a SysCommonMessage.
        /// </summary>
        void Build();
            
        ENDREGION()

    private:
        void init();
        static int get_Count();
        SysCommonMessage get_Result();
        int get_Message();
        void set_Message(int value);
        SysCommonType get_Type();
        void set_Type(SysCommonType value);
        int get_Data1();
        void set_Data1(int value);
        int get_Data2();
        void set_Data2(int value);

	public:
		SysCommonMessageBuilder operator = (const SysCommonMessageBuilder other);

    };

}}}

#endif