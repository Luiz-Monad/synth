#ifndef BACKGROUNDWORKER_H
#define BACKGROUNDWORKER_H

#include "Types.h"
#include "Event.h"
#include "Property.h"

class BackgroundWorkerClass;
typedef BackgroundWorkerClass& BackgroundWorker;

class BackgroundWorkerClass : public IDisposableIf
{
public:

	DoWorkEventHandler DoWork;
	ProgressChangedEventHandler ProgressChanged;
	RunWorkerCompletedEventHandler RunWorkerCompleted;

	Property<bool> WorkerReportsProgress;
	ReadOnlyProperty<bool> CancellationPending;
	Property<bool> IsBusy;

	void RunWorkerAsync(void* argument)
	{
	}
	
	void CancelAsync()
	{
	}

	void ReportProgress(void* progress)
	{
	}
	
	void Dispose()
	{
	}

};

#endif