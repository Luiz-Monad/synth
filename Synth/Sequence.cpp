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

#include "Sequence.h"
#include "Exception.h"
#include "Stream.h"
#include "TrackReader.h" 

namespace Sanford { namespace Multimedia { namespace Midi {
    
	typedef SequenceClass cls;
    void cls::init() 
    {
        this->tracks = List<Track>();
		this->disposed = false;
	}

    REGION(Construction)

    /// <summary>
    /// Initializes a new instance of the Sequence class.
    /// </summary>
    SequenceClass::SequenceClass() :
		properties(MidiFilePropertiesClass()), loadWorker(BackgroundWorkerClass()), saveWorker(BackgroundWorkerClass()), site(objectClass())
    {
		init();
        InitializeBackgroundWorkers();
    }        

    /// <summary>
    /// Initializes a new instance of the Sequence class with the specified division.
    /// </summary>
    /// <param name="division">
    /// The Sequence's division value.
    /// </param>
    SequenceClass::SequenceClass(int division) :
		properties(MidiFilePropertiesClass()), loadWorker(BackgroundWorkerClass()), saveWorker(BackgroundWorkerClass()), site(objectClass())
    {
		init();
        properties.Division = division;
        properties.Format = 1;

        InitializeBackgroundWorkers();
    }

    /// <summary>
    /// Initializes a new instance of the Sequence class with the specified
    /// file name of the MIDI file to load.
    /// </summary>
    /// <param name="fileName">
    /// The name of the MIDI file to load.
    /// </param>
    SequenceClass::SequenceClass(string fileName) :
		properties(MidiFilePropertiesClass()), loadWorker(BackgroundWorkerClass()), saveWorker(BackgroundWorkerClass()), site(objectClass())
    {
		init();
        InitializeBackgroundWorkers();

        Load(fileName);
    }

    void SequenceClass::InitializeBackgroundWorkers()
    {
        loadWorker.DoWork += DoWorkEventHandler(EventFunctor::New(this, &cls::LoadDoWork));
        loadWorker.ProgressChanged += ProgressChangedEventHandler(EventFunctor::New(this, &cls::OnLoadProgressChanged));
        loadWorker.RunWorkerCompleted += RunWorkerCompletedEventHandler(EventFunctor::New(this, &cls::OnLoadCompleted));
        loadWorker.WorkerReportsProgress = true;

        saveWorker.DoWork += DoWorkEventHandler(EventFunctor::New(this, &cls::SaveDoWork));
        saveWorker.ProgressChanged += ProgressChangedEventHandler(EventFunctor::New(this, &cls::OnSaveProgressChanged));
        saveWorker.RunWorkerCompleted += RunWorkerCompletedEventHandler(EventFunctor::New(this, &cls::OnSaveCompleted));
        saveWorker.WorkerReportsProgress = true;
    }        

    ENDREGION()

    REGION(Methods)

    /// <summary>
    /// Loads a MIDI file into the Sequence.
    /// </summary>
    /// <param name="fileName">
    /// The MIDI file's name.
    /// </param>
    void SequenceClass::Load(string fileName)
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }
        else if(IsBusy)
        {
            throw new InvalidOperationException();
        }
        else if(fileName == nullptr)
        {
            throw new ArgumentNullException("fileName");
        }

        ENDREGION()                        

        FileStream stream = FileStreamClass(fileName, FileMode::ModeOpen,
            FileAccess::AccessRead, FileShare::ShareNone);

        {
	        _using u = _using(stream);

            MidiFileProperties newProperties = MidiFilePropertiesClass();
            TrackReader reader = TrackReaderClass();
            List<Track> newTracks = List<Track>();

            newProperties.Read(stream);

            for(int i = 0; i < newProperties.TrackCount; i++)
            {
                reader.Read(stream);
                newTracks.Add(reader.Track);
            }

            properties = newProperties;
            tracks = newTracks;
        }

        REGION(Ensure)

        Assert(Count == properties.TrackCount);

        ENDREGION()
    }

    void SequenceClass::LoadAsync(string fileName)
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }
        else if(IsBusy)
        {
            throw new InvalidOperationException();
        }
        else if(fileName == nullptr)
        {
            throw new ArgumentNullException("fileName");
        }

        ENDREGION()

        loadWorker.RunWorkerAsync(fileName);
    }

    void SequenceClass::LoadAsyncCancel()
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }

        ENDREGION()

        loadWorker.CancelAsync();
    }

    /// <summary>
    /// Saves the Sequence as a MIDI file.
    /// </summary>
    /// <param name="fileName">
    /// The name to use for saving the MIDI file.
    /// </param>
    void SequenceClass::Save(string fileName)
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }
        else if(fileName == nullptr)
        {
            throw new ArgumentNullException("fileName");
        }

        ENDREGION()

        FileStream stream = FileStreamClass(fileName, FileMode::ModeCreate,
            FileAccess::AccessWrite, FileShare::ShareNone);

        {
	        _using u = _using(stream);

            properties.Write(stream);

            //TrackWriter writer = new TrackWriter();

			List<Track>::iterator it = this->GetIterator();
			for(it = it.begin(); it != it.end(); it++)
			{
				Track trk = (Track)it;
                //writer.Track = trk;
                //writer.Write(stream);
            }
			throw new NotImplementedException();
        }
    }

    void SequenceClass::SaveAsync(string fileName)
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }
        else if(IsBusy)
        {
            throw new InvalidOperationException();
        }
        else if(fileName == nullptr)
        {
            throw new ArgumentNullException("fileName");
        }

        ENDREGION()

        saveWorker.RunWorkerAsync(fileName);
    }

    void SequenceClass::SaveAsyncCancel()
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }

        ENDREGION()

        saveWorker.CancelAsync();
    }

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
    int SequenceClass::GetLength()
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }

        ENDREGION()

        int length = 0;

		List<Track>::iterator it = this->GetIterator();
        for(it = it.begin(); it != it.end(); it++)
        {
			Track t = (Track)it;
            if(t.Length > length)
            {
                length = t.Length;
            }
        }

        return length;
    }

    void SequenceClass::OnLoadCompleted(object sender, RunWorkerCompletedEventArgs e)
    {
        RunWorkerCompletedEventHandler handler = LoadCompleted;

        if(handler != nullptr)
        {
            handler(this, RunWorkerCompletedEventArgs(e.Error, e.Cancelled, nullptr));
        }
    }

    void SequenceClass::OnLoadProgressChanged(object sender, ProgressChangedEventArgs e)
    {
        ProgressChangedEventHandler handler = LoadProgressChanged;

        if(handler != nullptr)
        {
            handler(this, e);
        }
    }

	void SequenceClass::LoadDoWork(object sender, DoWorkEventArgs e)
    {
        string fileName = (string)e.Argument;

        FileStream stream = FileStreamClass(fileName, FileMode::ModeOpen,
            FileAccess::AccessRead, FileShare::ShareRead);

        {
	        _using u = _using(stream);

            MidiFileProperties newProperties = MidiFilePropertiesClass();
            TrackReader reader = TrackReaderClass();
            List<Track> newTracks = List<Track>();

            newProperties.Read(stream);

            float percentage;

            for(int i = 0; i < newProperties.TrackCount && !loadWorker.CancellationPending; i++)
            {
                reader.Read(stream);
                newTracks.Add(reader.Track);

                percentage = (i + 1.0) / newProperties.TrackCount;

                loadWorker.ReportProgress(new int(100 * percentage));
            }

            if(loadWorker.CancellationPending)
            {
                e.Cancel = true;
            }
            else
            {
                properties = newProperties;
                tracks = newTracks;
            }
        }            
    }

    void SequenceClass::OnSaveCompleted(object sender, RunWorkerCompletedEventArgs e)
    {
        RunWorkerCompletedEventHandler handler = SaveCompleted;

        if(handler != nullptr)
        {
            handler(this, RunWorkerCompletedEventArgs(e.Error, e.Cancelled, nullptr));
        }
    }

    void SequenceClass::OnSaveProgressChanged(object sender, ProgressChangedEventArgs e)
    {
        ProgressChangedEventHandler handler = SaveProgressChanged;

        if(handler != nullptr)
        {
            handler(this, e);
        }
    }

    void SequenceClass::SaveDoWork(object sender, DoWorkEventArgs e)
    {
        string fileName = (string)e.Argument;

        FileStream stream = FileStreamClass(fileName, FileMode::ModeCreate,
            FileAccess::AccessWrite, FileShare::ShareNone);

        {
	        _using u = _using(stream);

            properties.Write(stream);

            //TrackWriter writer = new TrackWriter();

            float percentage;

            for(int i = 0; i < tracks.Count && !saveWorker.CancellationPending; i++)
            {
                //writer.Track = tracks[i];
                //writer.Write(stream);

                percentage = (i + 1.0) / properties.TrackCount;

                saveWorker.ReportProgress(new int(100 * percentage));
            }
			throw new NotImplementedException();

            if(saveWorker.CancellationPending)
            {
                e.Cancel = true;
            }
        }
    }

    ENDREGION()

    REGION(Properties)

    /// <summary>
    /// Gets the Track at the specified index.
    /// </summary>
    /// <param name="index">
    /// The index of the Track to get.
    /// </param>
    /// <returns>
    /// The Track at the specified index.
    /// </returns>
	const Track SequenceClass::operator [](int index)
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }
        else if(index < 0 || index >= Count)
        {
            throw new ArgumentOutOfRangeException("index", index,
                "Sequence index out of range.");
        }

        ENDREGION()

        return tracks[index];
    }

    /// <summary>
    /// Gets the Sequence's division value.
    /// </summary>
    int SequenceClass::get_Division()
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }

        ENDREGION()

        return properties.Division;
    }

    /// <summary>
    /// Gets or sets the Sequence's format value.
    /// </summary>
    int SequenceClass::get_Format()
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }

        ENDREGION()

        return properties.Format;
    }
    void SequenceClass::set_Format(int value)
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }
        else if(IsBusy)
        {
            throw new InvalidOperationException();
        }

        ENDREGION()

        properties.Format = value;
    }

    /// <summary>
    /// Gets the Sequence's type.
    /// </summary>
    SequenceType SequenceClass::get_SequenceType()
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }

        ENDREGION()

        return properties.SequenceType;
    }

	bool SequenceClass::get_IsBusy()
    {
        return loadWorker.IsBusy || saveWorker.IsBusy;
    }

    ENDREGION()

    ENDREGION()

    REGION(ICollection<Track> Members)

    void SequenceClass::Add(Track item)
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        } 
        else if(item == TrackClass::null)
        {
            throw new ArgumentNullException("item");
        }

        ENDREGION()

        tracks.Add(item);

        properties.TrackCount = tracks.Count;
    }

    void SequenceClass::Clear()
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }

        ENDREGION()

        tracks.Clear();

        properties.TrackCount = tracks.Count;
    }

    bool SequenceClass::Contains(Track item)
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }

        ENDREGION()

        return tracks.Contains(item);
    }

    void SequenceClass::CopyTo(TrackArray destArray, int arrayIndex)
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }

        ENDREGION()

        tracks.CopyTo(destArray, arrayIndex);
    }

    int SequenceClass::get_Count()
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }

        ENDREGION()

        return tracks.Count;
    }

	bool SequenceClass::get_IsReadOnly()
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }

        ENDREGION()

        return false;
    }

    bool SequenceClass::Remove(Track item)
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }

        ENDREGION()

        bool result = tracks.Remove(item);

        if(result)
        {
            properties.TrackCount = tracks.Count;
        }

        return result;
    }

    ENDREGION()

    REGION(IEnumerable<Track> Members)

    List<Track>::iterator SequenceClass::GetIterator()
    {
        REGION(Require)

        if(disposed)
        {
            throw new ObjectDisposedException("Sequence");
        }

        ENDREGION()

        return tracks.GetIterator();
    }

    ENDREGION()

    REGION(IEnumerable Members)

    //IEnumerator SequenceClass::IEnumerable.GetEnumerator()

    ENDREGION()

    REGION(IComponent Members)

    ISite SequenceClass::get_Site()
    {
        return site;
    }
    void SequenceClass::set_Site(ISite value)
    {
        site = value;
    }

    ENDREGION()

    REGION(IDisposable Members)

    void SequenceClass::Dispose()
    {
        REGION(Guard)

        if(disposed)
        {
            return;
        }

        ENDREGION()

        loadWorker.Dispose();
        saveWorker.Dispose();

        disposed = true;

        EventHandler<object> handler = Disposed;

        if(handler != nullptr)
        {
            handler(this, EventArgs::Empty);
        }
    }

    ENDREGION()

}}}

