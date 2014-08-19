#ifndef SYSREALTIMETYPE_H
#define SYSREALTIMETYPE_H

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
#include "ShortMessage.h"

namespace Sanford { namespace Multimedia { namespace Midi {

	REGION(System Realtime Message Types)
    
    /// <summary>
    /// Defines constants representing the various system realtime message types.
    /// </summary>
    enum SysRealtimeType
    {
        /// <summary>
        /// Represents the clock system realtime type.
        /// </summary>
        Clock = 0xF8,

        /// <summary>
        /// Represents the tick system realtime type.
        /// </summary>
        Tick,

        /// <summary>
        /// Represents the start system realtime type.
        /// </summary>
        StartRealtime,

        /// <summary>
        /// Represents the continue system realtime type.
        /// </summary>
        Continue,

        /// <summary>
        /// Represents the stop system realtime type.
        /// </summary>
        StopRealtime,    
    
        /// <summary>
        /// Represents the active sense system realtime type.
        /// </summary>
        ActiveSense = 0xFE,

        /// <summary>
        /// Represents the reset system realtime type.
        /// </summary>
        Reset
	};

    ENDREGION()

	class SysRealtimeMessageClass;
	typedef SysRealtimeMessageClass& SysRealtimeMessage;

	/// <summary>
	/// Represents MIDI system realtime messages.
	/// </summary>
	/// <remarks>
	/// System realtime messages are MIDI messages that are primarily concerned 
	/// with controlling and synchronizing MIDI devices. 
	/// </remarks>
	class SysRealtimeMessageClass : public ShortMessageClass
	{
        REGION(SysRealtimeMessage Members)

        REGION(System Realtime Messages)

	public:

        /// <summary>
        /// The instance of the system realtime start message.
        /// </summary>
        static const SysRealtimeMessage StartMessage; 

        /// <summary>
        /// The instance of the system realtime continue message.
        /// </summary>
        static const SysRealtimeMessage ContinueMessage;

        /// <summary>
        /// The instance of the system realtime stop message.
        /// </summary>
        static const SysRealtimeMessage StopMessage;

        /// <summary>
        /// The instance of the system realtime clock message.
        /// </summary>
        static const SysRealtimeMessage ClockMessage;

        /// <summary>
        /// The instance of the system realtime tick message.
        /// </summary>
        static const SysRealtimeMessage TickMessage;

        /// <summary>
        /// The instance of the system realtime active sense message.
        /// </summary>
        static const SysRealtimeMessage ActiveSenseMessage;

        /// <summary>
        /// The instance of the system realtime reset message.
        /// </summary>
        static const SysRealtimeMessage ResetMessage;

        ENDREGION()

	private:

        // Make construction private so that a system realtime message cannot 
        // be constructed directly.
        SysRealtimeMessageClass(SysRealtimeType type);

        REGION(Methods)

	public:

        /// <summary>
        /// Returns a value for the current SysRealtimeMessage suitable for use in 
        /// hashing algorithms.
        /// </summary>
        /// <returns>
        /// A hash code for the current SysRealtimeMessage.
        /// </returns>
        /*override*/ int GetHashCode();

        /// <summary>
        /// Determines whether two SysRealtimeMessage instances are equal.
        /// </summary>
        /// <param name="obj">
        /// The SysRealtimeMessage to compare with the current SysRealtimeMessage.
        /// </param>
        /// <returns>
        /// <b>true</b> if the specified SysRealtimeMessage is equal to the current 
        /// SysRealtimeMessage; otherwise, <b>false</b>.
        /// </returns>
        /*override*/ bool Equals(IEquatable obj);

        ENDREGION()

        REGION(Properties)

	public:
        
        /// <summary>
        /// Gets the SysRealtimeType.
        /// </summary>
        ReadOnlyProperty<Midi::SysRealtimeType> SysRealtimeType;
   
        /// <summary>
        /// Gets the MessageType.
        /// </summary>
        ReadOnlyProperty<Midi::MessageType> MessageType;

        ENDREGION()

        ENDREGION()
		
	private:
		SysRealtimeMessageClass();
        void init();
        Midi::SysRealtimeType get_SysRealtimeType();
        Midi::MessageType get_MessageType();
		
    public:
        static const SysRealtimeMessage null;

    };

}}}

#endif