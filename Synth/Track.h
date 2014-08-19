#ifndef TRACK_H
#define TRACK_H

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
#include "MidiEvent.h"

namespace Sanford { namespace Multimedia { namespace Midi {

    class TrackClass;
    typedef TrackClass& Track;

    /// <summary>
    /// Represents a collection of MidiEvents and a MIDI track within a 
    /// Sequence.
    /// </summary>
    class TrackClass : public objectClass
    {
        REGION(Track Members)

        REGION(Fields)

    private:

        // The number of MidiEvents in the Track. Will always be at least 1
        // because the Track will always have an end of track message.
        int count;

        // The number of ticks to offset the end of track message.
        int endOfTrackOffset;

        // The first MidiEvent in the Track.
        MidiEvent head;

        // The last MidiEvent in the Track, not including the end of track
        // message.
        MidiEvent tail;

        // The end of track MIDI event.
        MidiEvent endOfTrackMidiEvent;
        
        ENDREGION()

        REGION(Construction)
        
    public:

        TrackClass();
        
        ENDREGION()

        REGION(Methods)

    public:

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
        void Insert(int position, IMidiMessage message);

        /// <summary>
        /// Clears all of the MidiEvents, with the exception of the end of track
        /// message, from the Track.
        /// </summary>
        void Clear();

        /// <summary>
        /// Merges the specified Track with the current Track.
        /// </summary>
        /// <param name="trk">
        /// The Track to merge with.
        /// </param>
        void Merge(Track trk);

        /// <summary>
        /// Removes the MidiEvent at the specified index.
        /// </summary>
        /// <param name="index">
        /// The index into the Track at which to remove the MidiEvent.
        /// </param>
        void RemoveAt(int index);

        /// <summary>
        /// Gets the MidiEvent at the specified index.
        /// </summary>
        /// <param name="index">
        /// The index of the MidiEvent to get.
        /// </param>
        /// <returns>
        /// The MidiEvent at the specified index.
        /// </returns>
        MidiEvent GetMidiEvent(int index);

        /// <summary>
        /// Moves the MidiEvent to the specified index.
        /// </summary>
        /// <param name="e">
        /// The MidiEvent to be moved.
        /// </param>
        /// <param name="newPosition">
        /// The index that MidiEvent will be put.
        /// </param>
        void Move(MidiEvent e, int newPosition);
 
        ENDREGION()

        REGION(Properties)

    public:
        
        /// <summary>
        /// Gets the number of MidiEvents in the Track.
        /// </summary>
        ReadOnlyProperty<int> Count;

        /// <summary>
        /// Gets the length of the Track in ticks.
        /// </summary>
        ReadOnlyProperty<int> Length;

        /// <summary>
        /// Gets or sets the end of track meta message position offset.
        /// </summary>
        Property<int> EndOfTrackOffset;

        /// <summary>
        /// Gets an object that can be used to synchronize access to the Track.
        /// </summary>
        ReadOnlyProperty<object> SyncRoot;
        
        ENDREGION()

        ENDREGION()

	private:
		void AssertValid();

    private:
        void init();
        int get_Count();
        int get_Length();
        int get_EndOfTrackOffset();
        void set_EndOfTrackOffset(int value);
        object get_SyncRoot();

    public:
        static const Track null;
		Track operator = (const Track other);
		bool operator == (Track other);
		bool operator != (Track other);

    };

}}}

#endif