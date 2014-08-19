//REGION(License)

/* Copyright (c) 2006 Leslie Sanford
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

#include "MidiEvent.h"
#include "NullMessage.h"
#include "Exception.h"

namespace Sanford { namespace Multimedia { namespace Midi {
    
    typedef MidiEventClass cls;

    const MidiEvent cls::null = cls();

    void cls::init() 
    {
        this->Owner = Functor::New(this, &cls::get_Owner);
        this->AbsoluteTicks = Functor::New(this, &cls::get_AbsoluteTicks);
        this->DeltaTicks = Functor::New(this, &cls::get_DeltaTicks);
        this->MidiMessage = Functor::New(this, &cls::get_MidiMessage);
        this->Next = Functor::New(this, &cls::get_Next, &cls::set_Next);
        this->Previous = Functor::New(this, &cls::get_Previous, &cls::set_Previous);
        this->owner = objectClass();
        this->absoluteTicks = 0;
        this->message = NullMessageClass::null;
        this->next = null;
        this->previous = null;
    }
        
    cls::MidiEventClass() :
        owner(objectClass()), message(NullMessageClass::null), next(null), previous(null)
    {
        init();
    }
	
    bool cls::operator == (MidiEvent other)
    {
        return (this->owner == other.owner && 
            this->absoluteTicks == other.absoluteTicks &&
            this->message == other.message);
    }

    bool cls::operator != (MidiEvent other)
    {
        return (!(*this == other));
    }
    
    MidiEvent cls::operator = (const MidiEvent other)
    {
        if (this != &other)
        {
            this->owner = other.owner;
            this->absoluteTicks = other.absoluteTicks;
            this->message = other.message;
            this->next = other.next;
            this->previous = other.previous;
        }
        return *this;
    }

    MidiEventClass::MidiEventClass(object owner, int absoluteTicks, IMidiMessage message) :
        owner(objectClass()), message(NullMessageClass::null), next(null), previous(null)
    {
        init();
        REGION(Require)

        if(owner == nullptr)
        {
            throw new ArgumentNullException("owner");
        }
        else if(absoluteTicks < 0)
        {
            throw new ArgumentOutOfRangeException("absoluteTicks", absoluteTicks,
                "Absolute ticks out of range.");
        }
        else if(message == NullMessageClass::null)
        {
            throw new ArgumentNullException("e");
        }

        ENDREGION()

        this->owner = owner;
        this->absoluteTicks = absoluteTicks;
        this->message = message;
    }

    void MidiEventClass::SetAbsoluteTicks(int absoluteTicks)
    {
        this->absoluteTicks = absoluteTicks;
    }

    object MidiEventClass::get_Owner()
    {
        return owner;
    }

    int MidiEventClass::get_AbsoluteTicks()
    {
        return absoluteTicks;
    }

    int MidiEventClass::get_DeltaTicks()
    {
        int deltaTicks;

        if((MidiEvent)Previous != null)
        {
            deltaTicks = AbsoluteTicks - previous.AbsoluteTicks;
        }
        else
        {
            deltaTicks = AbsoluteTicks;
        }

        return deltaTicks;
    }

    IMidiMessage MidiEventClass::get_MidiMessage()
    {
        return message;
    }

    MidiEvent MidiEventClass::get_Next()
    {
        return next;
    }
    void MidiEventClass::set_Next(MidiEvent value)
    {
        next = value;
    }

    MidiEvent MidiEventClass::get_Previous()
    {
        return previous;
    }
    void MidiEventClass::set_Previous(MidiEvent value)
    {
        previous = value;
    }

}}}

