#ifndef BUFFER_H
#define BUFFER_H

template<typename T>
class buffer
{
public:

    ReadOnlyProperty<long> Length;

private:

    T* arr;
    long size;
    long get_Length() { return size; }

    void init(long size, T* arr)
    {
        this->Length = Functor::New(this, &buffer::get_Length);
        this->size = size;
        this->arr = arr; 
    }

    void init(long size)
    {
		if (size == 0) 
		{
			init(0, nullptr);
		} else {
			init(size, new T[size]);
		}
    }

    void kill()
    {
        delete[] this->arr;
    }

public:

    static const buffer<T>& null;

    buffer() { init(0); }
    buffer(int i) { init(i); }
	buffer(int i, T* arr) { init(i, arr); }
    ~buffer() { kill(); }

    template<typename V>
    void set(const V& value, long index)
    {
        *((V*)(arr[index])) = value;
    }
	    
	template<typename V>
    V& get(long index)
    {
        return *((V*)(arr[index]));
    }

    bool operator == (buffer<T> other)
    {
        return (other.size == this->size && 
            other.arr == this->arr);
    }
	
    void CopyTo(buffer<T> other, long index)
    {
		for(long i = 0; i < size; i++) 
		{
			other.arr[i + index] = arr[i];
		}
    }
	
    void CopyTo(buffer<T> other, long index, long length)
    {
		for(long i = 0; i < size && i < length; i++) 
		{
			other.arr[i + index] = arr[i];
		}
    }
	
    buffer<T> Clone()
    {
		buffer<T> n = buffer<T>(this->size);
		CopyTo(n, 0);
		return n;
    }

	void Reverse()
	{
		for(long i = 0; i < size / 2; i++) 
		{
			T tmp = arr[i];
			arr[i] = arr[size-i-1];
			arr[size-i-1] = tmp;
		}
	}
    
    T& operator [] (long index)
    {
		return arr[index];
    }

	int GetHashCode()
	{
		return -1;
	}

	buffer<T> Offset(long index)
	{
		buffer<T> n = buffer<T>();
		n.init(this->size-index, this->arr + index);
		return n;
	}

	class iterator 
	{
	private:
		T *_pos;
		T *_begin;
		T *_end;
		iterator(iterator begin, iterator end, T *pos)
		{
			this->_begin = begin;
			this->_end = end;
			this->_pos = pos;
		}
	public:
		iterator(buffer<T>& buffer)
		{
			this->_begin = buffer.arr;
			this->_end = _begin + buffer.size - 1;
			this->_pos = _begin;
		}
		iterator(const iterator& other)
		{
			this->_begin = other._begin;
			this->_end = other._end;
			this->_pos = other._pos;
		}
		iterator& operator ++ ()
		{
			++pos;
			return *this;
		}
		iterator& operator = (const iterator& other)
		{
			return iterator(other);
		}
		bool operator == (const iterator& other)
		{
			return pos == other.pos;
		}
		bool operator != (const iterator& other)
		{
			return pos != other.pos;
		}
		operator const T&() const
		{
			return *pos;
		}
		iterator begin()
		{
			return iterator(_begin, _end, _begin);
		}
		iterator end()
		{
			return iterator(_begin, _end, _end);
		}
	};
	
	iterator& GetIterator()
	{
		return iterator(*this);
	}

};

typedef buffer<byte> bytebufferclass;
typedef buffer<byte>& bytebuffer;

const buffer<byte>& buffer<byte>::null = buffer<byte>(0);

class BitConverter
{
private:
	template <typename T>
    static bytebuffer GetBytes(T value)
    {
        bytebuffer b = bytebufferclass(sizeof(T));
        b.set<T>(value, 0);
        return b;
    }
public:
    static bytebuffer GetBytes(int value)
    {
        return GetBytes<int>(value);
    }
    static bytebuffer GetBytes(unsigned short value)
    {
        return GetBytes<unsigned short>(value);
    }
    static bytebuffer GetBytes(short value)
    {
        return GetBytes<short>(value);
    }
	static int ToInt32(bytebuffer buffer, long index)
	{
		return buffer.get<int>(index);
	}
	static unsigned short ToUInt16(bytebuffer buffer, long index)
	{
		return buffer.get<unsigned short>(index);
	}
	static short ToInt16(bytebuffer buffer, long index)
	{
		return buffer.get<short>(index);
	}
	static bool IsLittleEndian()
	{
		return false;
	}
};

#endif