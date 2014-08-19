#ifndef EVENT_H
#define EVENT_H

#include "Types.h"
#include "List.h"

template<typename T>
class EventHandler
{
private:

	List<EventHandler<T>> listeners;

public:

	EventHandler()
	{
		this->listeners = List<EventHandler<T>>();
	}
	~EventHandler()
	{
		this->listeners.Clear();
	}

	const EventHandler<T>& operator += (const EventHandler<T>& other)
	{
		this->listeners.Add(other);
		return *this;
	}

	const EventHandler<T>& operator -= (const EventHandler<T>& other)
	{
		this->listeners.Remove(other);
		return *this;
	}

	bool operator == (const void* other)
	{
		if (other != nullptr) return true;
		return (this->listeners->Count == 0);
	}

	bool operator != (const void* other)
	{
		return (!(this == other));
	}

	void operator () (const void* sender, const T args)
	{
		List<EventHandler<T>>::iterator it = this->listeners.GetIterator();
        for(it = it.begin(); it != it.end(); it++)
        {
            ((EventHandler<T>)it)(sender, args);
        }
	}

};

template<typename C, typename T>
class EventHandlerInstance : public EventHandler<T>
{
private:

	typedef void (C::*funcPtr)(object sender, T e);
	funcPtr invoke;

public:

	EventHandlerInstance(funcPtr invoke) : invoke(invoke)
	{
	}

};

class EventFunctor
{
public:

    template<typename C, typename T>
    static EventHandler<T>& New(C* thisObj, void (C::*invoke)(object sender, T e))
    {
        return EventHandlerInstance<C, T>(invoke);
    }   

};

class EventArgs
{
public:
	static const object Empty;
};

class ProgressChangedEventArgs : public EventArgs
{
public:
	int ProgressPercentage;
	void* UserState;
};

typedef EventHandler<ProgressChangedEventArgs> ProgressChangedEventHandler;

class AsyncCompletedEventArgs : public EventArgs
{
public:
	bool Cancelled;
	void* Error;
	void* UserState;
	AsyncCompletedEventArgs() { }
	AsyncCompletedEventArgs(void* Error, bool Cancelled, void* UserState) : 
		Cancelled(Cancelled), Error(Error), UserState(UserState) { }
};

class RunWorkerCompletedEventArgs : public AsyncCompletedEventArgs
{
public:
	void* Result;
	RunWorkerCompletedEventArgs() { }
	RunWorkerCompletedEventArgs(void* Error, bool Cancelled, void* Result) : 
		AsyncCompletedEventArgs(Error, Cancelled, Result), Result(Result) { }
};

typedef EventHandler<RunWorkerCompletedEventArgs> RunWorkerCompletedEventHandler;

class CancelEventArgs : public EventArgs
{
public:
	bool Cancel;
};

class DoWorkEventArgs : public CancelEventArgs
{
public:
	void* Argument;
	void* Result;
};

typedef EventHandler<DoWorkEventArgs> DoWorkEventHandler;

#endif