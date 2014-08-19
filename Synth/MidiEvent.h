#ifndef MIDIEVENT_H
#define MIDIEVENT_H

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

#include "Types.h"
#include "IMidiMessage.h"

namespace Sanford { namespace Multimedia { namespace Midi {

    class MidiEventClass;
    typedef MidiEventClass& MidiEvent;

    class MidiEventClass
    {

    private:
        
        object owner;

        int absoluteTicks;

        IMidiMessage message;

        MidiEvent next;

        MidiEvent previous;

    public:
        
        MidiEventClass(object owner, int absoluteTicks, IMidiMessage message);

        void SetAbsoluteTicks(int absoluteTicks);

        ReadOnlyProperty<object> Owner;

        ReadOnlyProperty<int> AbsoluteTicks;

        ReadOnlyProperty<int> DeltaTicks;

        ReadOnlyProperty<IMidiMessage> MidiMessage;

        Property<MidiEvent> Next;

        Property<MidiEvent> Previous;

    private:
        MidiEventClass();
        void init();
        object get_Owner();
        int get_AbsoluteTicks();
        int get_DeltaTicks();
        IMidiMessage get_MidiMessage();
        MidiEvent get_Next();
        void set_Next(MidiEvent value);
        MidiEvent get_Previous();
        void set_Previous(MidiEvent value);

    public:
        static const MidiEvent null;
        MidiEvent operator = (const MidiEvent other);
        bool operator == (MidiEvent other);
        bool operator != (MidiEvent other);

    };

}}}

#endif