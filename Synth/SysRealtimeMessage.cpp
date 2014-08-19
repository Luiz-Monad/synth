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

#include "SysRealtimeMessage.h"

namespace Sanford { namespace Multimedia { namespace Midi {

	typedef SysRealtimeMessageClass cls;
	
    const SysRealtimeMessage cls::null = cls();

    const SysRealtimeMessage cls::StartMessage = cls(SysRealtimeType::StartRealtime);
    const SysRealtimeMessage cls::ContinueMessage = cls(SysRealtimeType::Continue);
    const SysRealtimeMessage cls::StopMessage = cls(SysRealtimeType::StopRealtime);
    const SysRealtimeMessage cls::ClockMessage = cls(SysRealtimeType::Clock);
    const SysRealtimeMessage cls::TickMessage = cls(SysRealtimeType::Tick);
    const SysRealtimeMessage cls::ActiveSenseMessage = cls(SysRealtimeType::ActiveSense);
    const SysRealtimeMessage cls::ResetMessage = cls(SysRealtimeType::Reset);

    void cls::init() 
    {
		ShortMessageClass::init();
        this->SysRealtimeType = Functor::New(this, &cls::get_SysRealtimeType);
        this->MessageType = Functor::New(this, &cls::get_MessageType);
    }
	        
    cls::SysRealtimeMessageClass()
    {
        init();
    }

    ENDREGION()

    // Make construction private so that a system realtime message cannot 
    // be constructed directly.
	SysRealtimeMessageClass::SysRealtimeMessageClass(Midi::SysRealtimeType type)
    {
		init();
        msg = (int)type;

        REGION(Ensure)

        Assert(SysRealtimeType == type);

        ENDREGION()
    }

    REGION(Methods)

    /// <summary>
    /// Returns a value for the current SysRealtimeMessage suitable for use in 
    /// hashing algorithms.
    /// </summary>
    /// <returns>
    /// A hash code for the current SysRealtimeMessage.
    /// </returns>
    int SysRealtimeMessageClass::GetHashCode()
    {
        return msg;
    }

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
    bool SysRealtimeMessageClass::Equals(IEquatable obj)
    {
        REGION(Guard)

		if(!(isinst<SysRealtimeMessage>(obj)))
        {
            return false;
        }

        ENDREGION()

        SysRealtimeMessage message = (SysRealtimeMessage)obj;

        return this->msg == message.msg;
    }

    ENDREGION()

    REGION(Properties)
        
    /// <summary>
    /// Gets the SysRealtimeType.
    /// </summary>
	SysRealtimeType SysRealtimeMessageClass::get_SysRealtimeType()
	{
        return (Midi::SysRealtimeType)msg;
    }
   
    /// <summary>
    /// Gets the MessageType.
    /// </summary>
    MessageType SysRealtimeMessageClass::get_MessageType()
    {
        return MessageType::SystemRealtime;
    }

    ENDREGION()

    ENDREGION()

}}}