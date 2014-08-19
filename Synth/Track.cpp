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

#include "Track.h"
#include "NullMessage.h"
#include "MetaMessage.h"
#include "Exception.h"

namespace Sanford { namespace Multimedia { namespace Midi {
    
    typedef TrackClass cls;

    const Track cls::null = cls();

	void cls::init() 
    {
        this->Count = Functor::New(this, &cls::get_Count);
        this->Length = Functor::New(this, &cls::get_Length);
        this->EndOfTrackOffset = Functor::New(this, &cls::get_EndOfTrackOffset, &cls::set_EndOfTrackOffset);
        this->SyncRoot = Functor::New(this, &cls::get_SyncRoot);
        this->count = 1;
        this->endOfTrackOffset = 0;
        this->head = MidiEventClass::null;
        this->tail = MidiEventClass::null;
    }
	
	bool cls::operator == (Track other)
	{
        return (this->count == other.count && 
            this->endOfTrackOffset == other.endOfTrackOffset &&
            this->head == other.head && 
			this->tail == other.tail);
	}
	
    bool cls::operator != (Track other)
    {
        return (!(*this == other));
    }
        
    Track cls::operator = (const Track other)
    {
        if (this != &other)
        {
            this->count = other.count;
            this->endOfTrackOffset = other.endOfTrackOffset;
            this->head = other.head;
            this->tail = other.tail;
        }
        return *this;
    }

    REGION(Construction)

    TrackClass::TrackClass() :
        head(MidiEventClass::null), tail(MidiEventClass::null), endOfTrackMidiEvent(MidiEventClass::null)
    {
		init();
        this->endOfTrackMidiEvent = MidiEventClass(*this, Length, MetaMessageClass::EndOfTrackMessage);
    }

    /// <summary>
    /// Inserts an IMidiMessage at the specified position in absolute ticks.
    /// </summary>
    /// <param name="position">
    /// The position in the Track in absolute ticks in which to insert the
    /// IMidiMessage.
    /// </param>
    /// <param name="message">
    /// The IMidiMessage to insert.
    /// </param>
    void TrackClass::Insert(int position, IMidiMessage message)
    {
        REGION(Require)

        if(position < 0)
        {
            throw new ArgumentOutOfRangeException("position", position,
                "IMidiMessage position out of range.");
        }
        else if(message == NullMessageClass::null)
        {
            throw new ArgumentNullException("message");
        }

        ENDREGION()

        MidiEvent newMidiEvent = MidiEventClass(*this, position, message);

        if(head == MidiEventClass::null)
        {
            head = newMidiEvent;
            tail = newMidiEvent;
        }
        else if(position >= tail.AbsoluteTicks)
        {
            newMidiEvent.Previous = tail;
            tail.Next = newMidiEvent;
            tail = newMidiEvent;  
            endOfTrackMidiEvent.SetAbsoluteTicks(Length);
            endOfTrackMidiEvent.Previous = tail;
        }
        else
        {
            MidiEvent current = head;

            while(current.AbsoluteTicks < position)
            {
                current = current.Next;
            }

            newMidiEvent.Next = current;
            newMidiEvent.Previous = current.Previous;

            if((MidiEvent)current.Previous != MidiEventClass::null)
            {
                ((MidiEvent)current.Previous).Next = newMidiEvent;
            }
            else
            {
                head = newMidiEvent;
            }

            current.Previous = newMidiEvent;
        }

        count++;

        REGION(Invariant)

        AssertValid();

        ENDREGION()
    }

    /// <summary>
    /// Clears all of the MidiEvents, with the exception of the end of track
    /// message, from the Track.
    /// </summary>
    void TrackClass::Clear()
    {
        head = tail = MidiEventClass::null;

        count = 1;

        REGION(Invariant)

        AssertValid();

        ENDREGION()
    }

    /// <summary>
    /// Merges the specified Track with the current Track.
    /// </summary>
    /// <param name="trk">
    /// The Track to merge with.
    /// </param>
    void TrackClass::Merge(Track trk)
    {
        REGION(Require)

        if(trk == null)
        {
            throw new ArgumentNullException("trk");
        }

        ENDREGION()

        REGION(Guard)

        if(trk == *this)
        {
            return;
        }
        else if(trk.Count == 1)
        {
            return;
        }

        ENDREGION()

        int oldCount = Count;

        count += trk.Count - 1;

        MidiEvent a = head;
        MidiEvent b = trk.head;
        MidiEvent current = MidiEventClass::null;

        Assert(b != null);

        if(a != MidiEventClass::null && a.AbsoluteTicks <= b.AbsoluteTicks)
        {
            current = MidiEventClass(*this, a.AbsoluteTicks, a.MidiMessage);
            a = a.Next;
        }
        else
        {
            current = MidiEventClass(*this, b.AbsoluteTicks, b.MidiMessage);
            b = b.Next;
        }

        head = current;

        while(a != MidiEventClass::null && b != MidiEventClass::null)
        {
            while(a != MidiEventClass::null && a.AbsoluteTicks <= b.AbsoluteTicks)
            {
                current.Next = MidiEventClass(*this, a.AbsoluteTicks, a.MidiMessage);
                ((MidiEvent)current.Next).Previous = current;
                current = current.Next;
                a = a.Next;
            }

            if(a != MidiEventClass::null)
            {
                while(b != MidiEventClass::null && b.AbsoluteTicks <= a.AbsoluteTicks)
                {
                    current.Next = MidiEventClass(*this, b.AbsoluteTicks, b.MidiMessage);
                    ((MidiEvent)current.Next).Previous = current;
                    current = current.Next;
                    b = b.Next;
                }
            }
        }

        while(a != MidiEventClass::null)
        {
            current.Next = MidiEventClass(*this, a.AbsoluteTicks, a.MidiMessage);
            ((MidiEvent)current.Next).Previous = current;
            current = current.Next;
            a = a.Next;
        }

        while(b != MidiEventClass::null)
        {
            current.Next = MidiEventClass(*this, b.AbsoluteTicks, b.MidiMessage);
            ((MidiEvent)current.Next).Previous = current;
            current = current.Next;
            b = b.Next;
        }

        tail = current;

        endOfTrackMidiEvent.SetAbsoluteTicks(Length);
        endOfTrackMidiEvent.Previous = tail;

        REGION(Ensure)

        Assert(count == oldCount + trk.Count - 1);

        ENDREGION()

        REGION(Invariant)

        AssertValid();

        ENDREGION()
    }

    /// <summary>
    /// Removes the MidiEvent at the specified index.
    /// </summary>
    /// <param name="index">
    /// The index into the Track at which to remove the MidiEvent.
    /// </param>
    void TrackClass::RemoveAt(int index)
    {
        REGION(Require)

        if(index < 0)
        {
            throw new ArgumentOutOfRangeException("index", index, "Track index out of range.");
        }
        else if(index == Count - 1)
        {
            throw new ArgumentException("Cannot remove the end of track event.", "index");
        }

        ENDREGION()

        MidiEvent current = GetMidiEvent(index);

        if((MidiEvent)current.Previous != MidiEventClass::null)
        {
            ((MidiEvent)current.Previous).Next = current.Next;
        }
        else
        {
            Assert(current == head);

            head = head.Next;
        }

        if((MidiEvent)current.Next != MidiEventClass::null)
        {
            ((MidiEvent)current.Next).Previous = current.Previous;
        }
        else
        {
            Assert(current == tail);

            tail = tail.Previous;

            endOfTrackMidiEvent.SetAbsoluteTicks(Length);
            endOfTrackMidiEvent.Previous = tail;
        }

        current.Next = current.Previous = MidiEventClass::null;

        count--;

        REGION(Invariant)

        AssertValid();

        ENDREGION()
    }

    /// <summary>
    /// Gets the MidiEvent at the specified index.
    /// </summary>
    /// <param name="index">
    /// The index of the MidiEvent to get.
    /// </param>
    /// <returns>
    /// The MidiEvent at the specified index.
    /// </returns>
    MidiEvent TrackClass::GetMidiEvent(int index)
    {
        REGION(Require)

        if(index < 0 || index >= Count)
        {
            throw new ArgumentOutOfRangeException("index", index,
                "Track index out of range.");
        }

        ENDREGION()

        MidiEvent result = MidiEventClass::null;

        if(index == Count - 1)
        {
            result = endOfTrackMidiEvent;
        }
        else
        {
            if(index < Count / 2)
            {
                result = head;

                for(int i = 0; i < index; i++)
                {
                    result = result.Next;
                }
            }
            else
            {
                result = tail;

                for(int i = Count - 2; i > index; i--)
                {
                    result = result.Previous;
                }
            }
        }

        REGION(Ensure)

#if(DEBUG)
        if(index == Count - 1)
        {
            Assert(result.AbsoluteTicks == Length);
            Assert(result.MidiMessage == MetaMessage.EndOfTrackMessage);
        }
        else
        {
            MidiEvent t = head;

            for(int i = 0; i < index; i++)
            {
                t = t.Next;
            }

            Assert(t == result);
        }
#endif

        ENDREGION()

        return result;
    }

    /// <summary>
    /// Moves the MidiEvent to the specified index.
    /// </summary>
    /// <param name="e">
    /// The MidiEvent to be moved.
    /// </param>
    /// <param name="newPosition">
    /// The index that MidiEvent will be put.
    /// </param>
    void TrackClass::Move(MidiEvent e, int newPosition)
    {
        REGION(Require)

        if((object)e.Owner != this)
        {
            throw new ArgumentException("MidiEvent does not belong to this Track.");
        }
        else if(newPosition < 0)
        {
            throw new ArgumentOutOfRangeException("newPosition");
        }
        else if(e == endOfTrackMidiEvent)
        {
            throw new InvalidOperationException(
                "Cannot move end of track message. Use the EndOfTrackOffset property instead.");
        }

        ENDREGION()

        MidiEvent previous = e.Previous;
        MidiEvent next = e.Next;

        if((MidiEvent)e.Previous != MidiEventClass::null && ((MidiEvent)e.Previous).AbsoluteTicks > newPosition)
        {
            ((MidiEvent)e.Previous).Next = e.Next;

            if((MidiEvent)e.Next != MidiEventClass::null)
            {
                ((MidiEvent)e.Next).Previous = e.Previous;
            }

            while(previous != MidiEventClass::null && previous.AbsoluteTicks > newPosition)
            {
                next = previous;
                previous = previous.Previous;
            }                
        }
        else if((MidiEvent)e.Next != MidiEventClass::null && ((MidiEvent)e.Next).AbsoluteTicks < newPosition)
        {
            ((MidiEvent)e.Next).Previous = e.Previous;

            if((MidiEvent)e.Previous != MidiEventClass::null)
            {
                ((MidiEvent)e.Previous).Next = e.Next;
            }

            while(next != MidiEventClass::null && next.AbsoluteTicks < newPosition)
            {
                previous = next;
                next = next.Next;
            }
        }

        if(previous != MidiEventClass::null)
        {
            previous.Next = e;
        }

        if(next != MidiEventClass::null)
        {
            next.Previous = e;
        }

        e.Previous = previous;
        e.Next = next;
        e.SetAbsoluteTicks(newPosition);

        if(newPosition < head.AbsoluteTicks)
        {
            head = e;
        }

        if(newPosition > tail.AbsoluteTicks)
        {
            tail = e;                
        }

        endOfTrackMidiEvent.SetAbsoluteTicks(Length);
        endOfTrackMidiEvent.Previous = tail;

        REGION(Invariant)

        AssertValid();

        ENDREGION()
    }

    #if(DEBUG)
    void TrackClass::AssertValid()
    {
        int c = 1;
        MidiEvent current = head;
        int ticks = 1;

        while(current != MidiEventClass::null)
        {
            ticks += current.DeltaTicks;

            if((MidiEvent)current.Previous != MidiEventClass::null)
            {
                Assert(current.AbsoluteTicks >= current.Previous.AbsoluteTicks);
                Assert(current.DeltaTicks == current.AbsoluteTicks - current.Previous.AbsoluteTicks);
            }

            if((MidiEvent)current.Next == MidiEventClass::null)
            {
                Assert(tail == current);
            }

            current = current.Next;

            c++;
        }

        ticks += EndOfTrackOffset;

        Assert(ticks == Length, "Length mismatch");
        Assert(c == Count, "Count mismatch");
    }
    #else
	void TrackClass::AssertValid() { }
    #endif

    ENDREGION()

    REGION(Properties)

    /// <summary>
    /// Gets the number of MidiEvents in the Track.
    /// </summary>
    int TrackClass::get_Count()
    {
        return count;
    }

    /// <summary>
    /// Gets the length of the Track in ticks.
    /// </summary>
    int TrackClass::get_Length()
    {
        int length = EndOfTrackOffset;

        if(tail != MidiEventClass::null)
        {
            length += tail.AbsoluteTicks;
        }

        return length + 1;
    }

    /// <summary>
    /// Gets or sets the end of track meta message position offset.
    /// </summary>
    int TrackClass::get_EndOfTrackOffset()
    {
        return endOfTrackOffset;
    }
    void TrackClass::set_EndOfTrackOffset(int value)
    {
        REGION(Require)

        if(value < 0)
        {
            throw new ArgumentOutOfRangeException("EndOfTrackOffset", value,
                "End of track offset out of range.");
        }

        ENDREGION()

        endOfTrackOffset = value;

        endOfTrackMidiEvent.SetAbsoluteTicks(Length);
    }

    /// <summary>
    /// Gets an object that can be used to synchronize access to the Track.
    /// </summary>
    object TrackClass::get_SyncRoot()
    {
        return *this;
    }

}}}
