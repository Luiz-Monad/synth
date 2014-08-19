#ifndef SEQUENCE_H
#define SEQUENCE_H

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
#include "Track.h"
#include "MidiFileProperties.h"
#include "List.h"
#include "Event.h"
#include "BackgroundWorker.h"

typedef object ISite;

namespace Sanford { namespace Multimedia { namespace Midi {

	typedef buffer<TrackClass> TrackArray;

	class SequenceClass;
	typedef SequenceClass& Sequence;

	/// <summary>
    /// Represents a collection of Tracks.
    /// </summary>
    class SequenceClass //: ICollectionIf<Track>
    {
        REGION(Sequence Members)

        REGION(Fields)

	private:

        // The collection of Tracks for the Sequence.
        List<Track> tracks;

        // The Sequence's MIDI file properties.
        MidiFileProperties properties;

        BackgroundWorker loadWorker;

        BackgroundWorker saveWorker;

        ISite site;

        bool disposed;

        ENDREGION()

        REGION(Events)

	public:

        RunWorkerCompletedEventHandler LoadCompleted;

        ProgressChangedEventHandler LoadProgressChanged;

        RunWorkerCompletedEventHandler SaveCompleted;

        ProgressChangedEventHandler SaveProgressChanged;

        ENDREGION()

        REGION(Construction)

	public:

        /// <summary>
        /// Initializes a new instance of the Sequence class.
        /// </summary>
        SequenceClass();

        /// <summary>
        /// Initializes a new instance of the Sequence class with the specified division.
        /// </summary>
        /// <param name="division">
        /// The Sequence's division value.
        /// </param>
        SequenceClass(int division);

        /// <summary>
        /// Initializes a new instance of the Sequence class with the specified
        /// file name of the MIDI file to load.
        /// </summary>
        /// <param name="fileName">
        /// The name of the MIDI file to load.
        /// </param>
        SequenceClass(string fileName);

	private:
		
		void InitializeBackgroundWorkers();

        ENDREGION()

        REGION(Methods)

	public:

        /// <summary>
        /// Loads a MIDI file into the Sequence.
        /// </summary>
        /// <param name="fileName">
        /// The MIDI file's name.
        /// </param>
        void Load(string fileName);

        void LoadAsync(string fileName);

        void LoadAsyncCancel();

        /// <summary>
        /// Saves the Sequence as a MIDI file.
        /// </summary>
        /// <param name="fileName">
        /// The name to use for saving the MIDI file.
        /// </param>
        void Save(string fileName);

        void SaveAsync(string fileName);

        void SaveAsyncCancel();

        /// <summary>
        /// Gets the length in ticks of the Sequence.
        /// </summary>
        /// <returns>
        /// The length in ticks of the Sequence.
        /// </returns>
        /// <remarks>
        /// The length in ticks of the Sequence is represented by the Track 
        /// with the longest length.
        /// </remarks>
        int GetLength();

	private:

        void OnLoadCompleted(object sender, RunWorkerCompletedEventArgs e);

        void OnLoadProgressChanged(object sender, ProgressChangedEventArgs e);

        void LoadDoWork(object sender, DoWorkEventArgs e);

        void OnSaveCompleted(object sender, RunWorkerCompletedEventArgs e);

        void OnSaveProgressChanged(object sender, ProgressChangedEventArgs e);

        void SaveDoWork(object sender, DoWorkEventArgs e);

        ENDREGION()

        REGION(Properties)

	public:

        /// <summary>
        /// Gets the Track at the specified index.
        /// </summary>
        /// <param name="index">
        /// The index of the Track to get.
        /// </param>
        /// <returns>
        /// The Track at the specified index.
        /// </returns>
		const Track operator[](int index);

        /// <summary>
        /// Gets the Sequence's division value.
        /// </summary>
        Property<int> Division;

        /// <summary>
        /// Gets or sets the Sequence's format value.
        /// </summary>
        Property<int> Format;

        /// <summary>
        /// Gets the Sequence's type.
        /// </summary>
        ReadOnlyProperty<Midi::SequenceType> SequenceType;

        ReadOnlyProperty<bool> IsBusy;

        ENDREGION()

        ENDREGION()

        REGION(ICollection<Track> Members)

		public:

        void Add(Track item);

        void Clear();

        bool Contains(Track item);

        void CopyTo(TrackArray destArray, int arrayIndex);

        ReadOnlyProperty<int> Count;

        ReadOnlyProperty<bool> IsReadOnly;

        bool Remove(Track item);

        ENDREGION()

        REGION(IEnumerable<Track> Members)

		public:

        List<Track>::iterator GetIterator();

        ENDREGION()

        REGION(IEnumerable Members)

        //IEnumerator IEnumerable.GetEnumerator();

        ENDREGION()

        REGION(IComponent Members)

	public:
			
		EventHandler<object> Disposed;

        Property<ISite> Site;

        ENDREGION()

        REGION(IDisposable Members)

	public:
			
		void Dispose();

        ENDREGION()

	private:
		~SequenceClass();
		void init();
		int get_Division();
		void set_Division(int value);
        int get_Format();
        void set_Format(int value);
        Midi::SequenceType get_SequenceType();
        bool get_IsBusy();
		int get_Count();
        bool get_IsReadOnly();
		ISite get_Site();
		void set_Site(ISite value);


    };

}}}

#endif