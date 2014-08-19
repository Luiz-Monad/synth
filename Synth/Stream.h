#ifndef STREAM_H
#define STREAM_H

#include "Types.h"

class StreamClass;
typedef StreamClass& Stream;

class StreamClass
{
public:
	byte ReadByte()
	{
		return byte();
	}
	byte Read(bytebuffer buffer, long start, long length)
	{
		return byte();
	}
	void Write(bytebuffer buffer, long start, long length)
	{
	}
	static bool IsNull(Stream stream)
	{
		return false;
	}
};

class FileStreamClass;
typedef FileStreamClass& FileStream;

enum FileMode
{
	ModeOpen = 1,
	ModeCreate = 2,
};
enum FileAccess
{
	AccessRead = 1,
	AccessWrite = 2,
};
enum FileShare
{
	ShareNone = 1,
	ShareRead = 2,
};

class FileStreamClass : public StreamClass, public IDisposableIf
{
public:
	FileStreamClass(string path, FileMode mode, FileAccess access, FileShare share)
	{
	}
	void Dispose()
	{
	}
};

#endif