#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Property.h"
#include "Types.h"

template<typename K, typename V>
class Hashtable
{
private:
	void* table;

public:

	Hashtable();

	Hashtable(int size);

	~Hashtable();

    static Hashtable<K, V> Synchronized(Hashtable<K, V>& hashtable);

	ReadOnlyProperty<int> Count;

    void Clear();

    void Add(const K& k, const V& v);

	void Remove(const K& k);

    const V& operator[](const K& k) const;

private:
	void init();
	int get_Count();
	int key_compare(K& k1, K& k2);
	int key_hash(K& k);
	size_t key_get(const K& key);
	size_t value_get(const V& value);
	size_t value_null();
	void key_destroy(size_t key);
	void value_destroy(size_t value);

};

#endif