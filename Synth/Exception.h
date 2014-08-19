#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Types.h"

class ArgumentOutOfRangeException
{
public:
    ArgumentOutOfRangeException(string message)
    {
    }
    ArgumentOutOfRangeException(string field, int value, string message)
    {
    }
};

class ArgumentNullException
{
public:
    ArgumentNullException(string message)
    {
    }
};

class ArgumentException
{
public:
    ArgumentException(string message)
    {
    }
    ArgumentException(string field, string message)
    {
    }
};

class InvalidOperationException
{
public:
	InvalidOperationException()
	{
	}
    InvalidOperationException(string message)
    {
    }
};

class ObjectDisposedException
{
public:
    ObjectDisposedException(string message)
    {
    }
};

class NotImplementedException
{
public:
    NotImplementedException()
    {
    }
};

class MidiFileException
{
public:
	MidiFileException(string message)
	{
	}
};

#endif