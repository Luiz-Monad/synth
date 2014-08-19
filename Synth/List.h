#ifndef LIST_H
#define LIST_H

#include "Hashtable.h"
#include "Buffer.h"

template<typename T>
class List
{
private:

	Hashtable<int, T> table;
	Hashtable<T, int> index;

public:

	List<T>()
	{
		table = Hashtable<int, T>();
		index = Hashtable<T, int>();
		Count = table.Count;
	}

	Property<long> Count;

	void Add(T item)
	{
		table.Add(table.Count, item);
		index.Add(item, index.Count);
	}

	bool Remove(T item)
	{
		if (!Contains(item)) return false;
		table.Remove(index[item]);
		index.Remove(item);
		return true;
	}

	bool Contains(T item)
	{
		return (index[item] != 0);
	}

	void Clear()
	{
		table.Clear();
		index.Clear();
	}

	T operator[](const int& index) const
	{
		return table[index];
	}

	template<typename E>
	void CopyTo(buffer<E> destArray, int arrayIndex)
	{
		long cnt = table.Count;
		long x = arrayIndex;
		for(long i = 0; i < cnt; i++)
		{
			if (index[table[i]] != 0)
			{
				destArray[x++] = table[i];
			}
		}
	}

	class iterator 
	{
	private:
		const List<T>& _list;
		int _pos;
		int _begin;
		int _end;
		iterator(const List<T>& list, int begin, int end, int pos) :
			_list(list)
		{
			this->_begin = begin;
			this->_end = end;
			this->_pos = pos;
		}
	public:
		iterator(const List<T>& list) :
			_list(list)
		{
			this->_begin = 0;
			this->_end = _begin + list.Count - 1;
			this->_pos = _begin;
		}
		iterator(const iterator& other) :
			_list(other._list)
		{
			this->_begin = other._begin;
			this->_end = other._end;
			this->_pos = other._pos;
		}
		iterator& operator ++ ()
		{
			++_pos;
			return *this;
		}
		iterator& operator = (const iterator& other)
		{
			return iterator(other);
		}
		bool operator == (const iterator& other)
		{
			return _pos == other._pos;
		}
		bool operator != (const iterator& other)
		{
			return _pos != other._pos;
		}
		operator const T&() const
		{
			return this->_list[_pos];
		}
		iterator begin()
		{
			return iterator(_list, _begin, _end, _begin);
		}
		iterator end()
		{
			return iterator(_list, _begin, _end, _end);
		}
	};
	
	iterator& GetIterator()
	{
		return iterator(*this);
	}
	
	List(const List& other)
	{
		iterator it = iterator(other);
        for(it = it.begin(); it != it.end(); it++)
        {
            this->Add((T)it);
        }
	}

};

#endif