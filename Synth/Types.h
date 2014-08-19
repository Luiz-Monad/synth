#ifndef TYPES_H
#define TYPES_H

#define Assert(X) //

#define REGION(X) //

#define ENDREGION() //

#include "Property.h"

typedef char byte;

typedef char sbyte;

typedef char* string;

typedef unsigned short ushort;

class IEquatableIf;
typedef IEquatableIf& IEquatable;

class IEquatableIf
{
public:
    virtual int GetHashCode() = 0;
    virtual bool Equals(IEquatable obj) = 0;
};

class objectClass;
typedef objectClass& object;

class objectClass : public IEquatableIf
{
public:

	objectClass()
	{
	}

	bool operator == (const objectClass& other)
	{
		return (this->Equals((IEquatable)other));
	}
		
	bool operator != (const objectClass& other)
	{
		return (!(this->Equals((IEquatable)other)));
	}

	bool operator == (const objectClass* other)
	{
		return (this == other);
	}

	bool operator != (const objectClass* other)
	{
		return (this != other);
	}

	int GetHashCode()
	{
		return (int)((long)this & 0xFFFFFFFF);
	}

	bool Equals(IEquatable obj) 
	{
		return false;
	}
	
};

template <typename T, typename U> 
bool isinst(U u) {
   return dynamic_cast<T>(u) != nullptr;
};

template <typename T>
bool isinst(IEquatable u) {
    return false;
   //return dynamic_cast<T>((void*)u) != nullptr;
};

class IDisposableIf;
typedef IDisposableIf& IDisposable;

class IDisposableIf
{
public:
    virtual void Dispose() = 0;
};

class _using
{
private:
	IDisposable disposable;
public:
	_using(IDisposable disposable) : disposable(disposable)
	{
	}
	~_using()
	{
		this->disposable.Dispose();
	}
};

#endif
