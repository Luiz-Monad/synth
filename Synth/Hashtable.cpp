
#include "Hashtable.h"

namespace hashtable
{

	typedef size_t key_s;

	typedef int (*key_compare)(key_s& k1, key_s& k2);

	typedef int (*key_hash)(key_s& k);

	typedef void (*key_destroy)(key_s& k);

	typedef size_t value_s;

	typedef value_s (*value_null)();

	typedef void (*value_destroy)(value_s& v);

	struct entry_s {
		key_s key;
		value_s value;
		struct entry_s *next;
	};

	typedef struct entry_s* entry_t;

	struct hashtable_s {
		long size;
		long used;
		entry_t *table;	
	};

	typedef struct hashtable_s* hashtable_t;

	/* Create a new hashtable. */
	hashtable_t ht_create( long size ) {

		hashtable_t hashtable = nullptr;
		long i;

		if( size < 1 ) return nullptr;

		/* Allocate the table itself. */
		hashtable = new hashtable_s;
		if( hashtable == nullptr ) {
			return nullptr;
		}

		/* Allocate pointers to the head nodes. */
		hashtable->table = new entry_t[size];
		if( hashtable->table == nullptr ) {
			return nullptr;
		}
		for( i = 0; i < size; i++ ) {
			hashtable->table[i] = nullptr;
		}

		hashtable->size = size;

		return hashtable;	
	}
	
	/* Hash a string for a particular hash table. */
	long ht_hash( hashtable_t hashtable, key_s key, key_hash hash ) {

		unsigned long hashval;
		hashval = hash(key);
		return hashval % hashtable->size;
	}

	/* Create a key-value pair. */
	entry_t ht_newpair( key_s key, value_s value ) {
		entry_t newpair;

		newpair = new entry_s;
		if( newpair == nullptr ) {
			return nullptr;
		}

		newpair->key = key;
		newpair->value = value;
		newpair->next = nullptr;

		return newpair;
	}

	void ht_grow( hashtable_t hashtable, key_hash hash, key_compare compare  );

	/* Insert a key-value pair into a hash table. */
	void ht_set( hashtable_t hashtable, key_s key, value_s value, key_hash hash, key_compare compare ) {
		int bin = 0;
		entry_t newpair = nullptr;
		entry_t next = nullptr;
		entry_t last = nullptr;

		bin = ht_hash( hashtable, key, hash );

		next = hashtable->table[ bin ];

		while( next != nullptr && compare(key, next->key) < 0 ) {
			last = next;
			next = next->next;
		}

		/* There's already a pair.  Let's replace that item. */
		if( next != nullptr && compare(key, next->key) == 0 ) {

			next->value = value;

		/* Nope, could't find it.  Time to grow a pair. */
		} else {
			newpair = ht_newpair( key, value );

			/* We're at the start of the linked list in this bin. */
			if( next == hashtable->table[ bin ] ) {
				newpair->next = next;
				hashtable->table[ bin ] = newpair;
			
			/* We're at the end of the linked list in this bin. */
			} else if ( next == nullptr ) {
				last->next = newpair;
			
			/* We're in the middle of the list. */
			} else {
				newpair->next = next;
				last->next = newpair;
			}

			hashtable->used++;
			if (hashtable->used > hashtable->size * 0.75) {
				ht_grow(hashtable, hash, compare);
			}

		}
	}
	
	/* Create new hashtable and copy from old. */
	void ht_grow( hashtable_t hashtable, key_hash hash, key_compare compare  )
	{
		hashtable_t htnew = ht_create(hashtable->size * 2);
		
		for( long i = 0; i < htnew->size; i++ ) {
			entry_t pair = hashtable->table[i];
			if (pair != nullptr) {
				ht_set(htnew, pair->key, pair->value, hash, compare);
			}
		}

	}

	/* Retrieve a key-value pair from a hash table. */
	value_s ht_get( hashtable_t hashtable, key_s key, key_hash hash, key_compare compare, value_null null ) {
		long bin = 0;
		entry_t pair;

		bin = ht_hash( hashtable, key, hash );

		/* Step through the bin, looking for our value. */
		pair = hashtable->table[ bin ];
		while( pair != nullptr && compare(key, pair->key) == 0 ) {
			pair = pair->next;
		}

		/* Did we actually find anything? */
		if( pair == nullptr || !compare(key, pair->key) == 0 ) {
			return null();

		} else {
			return pair->value;
		}
	
	}

	/* Destroys a hashtable. */
	void ht_destroy( hashtable_t hashtable, key_destroy destroy_key, value_destroy destroy_value ) {

		for( long i = 0; i < hashtable->size; i++ ) {
			destroy_key(hashtable->table[i]->key);
			destroy_value(hashtable->table[i]->value);
			delete hashtable->table[i];
		}
		delete hashtable->table;
		delete hashtable;

	}

}

template<typename K, typename V>
void Hashtable<K, V>::init()
{
	this->Count = Function::New(this, &Hashtable<K, V>::get_Count);
}

template<typename K, typename V>
Hashtable<K, V>::Hashtable()
{
	this->table = hashtable::ht_create();
}

template<typename K, typename V>
Hashtable<K, V>::Hashtable(int size)
{
	this->table = hashtable::ht_create(size);
}

template<typename K, typename V>
Hashtable<K, V> Hashtable<K, V>::Synchronized(Hashtable<K, V>& hashtable)
{
	return Hashtable<K, V>(); //err, ignore multithread safety
}

template<typename K, typename V>
int Hashtable<K, V>::get_Count()
{ 
    return ((hashtable::hashtable_t)this->table)->used;
}

template<typename K, typename V>
void Hashtable<K, V>::Clear()
{
	hashtable::ht_destroy(this->table);
	this->table = nullptr;
}

template<typename K, typename V>
Hashtable<K, V>::~Hashtable()
{
	Clear();
}

template<typename K, typename V>
void Hashtable<K, V>::Add(const K& k, const V& v)
{
	hashtable::hashtable_t table = (hashtable::hashtable_t)(this->table);
	hashtable::ht_set(table, key_get(k), value_get(v), &this->key_compare, &this->key_hash);
}

template<typename K, typename V>
const V& Hashtable<K, V>::operator[](const K& k) const
{
	hashtable::hashtable_t table = (hashtable::hashtable_t)(this->table);
	hashtable::value_s value = hashtable::ht_get(table, key_get(k), &this->key_hash, &this->key_compare, &this->value_null);
	if (sizeof(V) <= sizeof(value_s)) {
		return (V)(value);
	} else {
		V* valueptr = (V*)value;
		return *valueptr;
	}
}

template<typename K, typename V>
size_t Hashtable<K, V>::value_null()
{
	return 0;
}

template<typename K, typename V>
int Hashtable<K, V>::key_compare(K& k1, K& k2)
{
	if (k1 > k2) return 1;
	else if (k1 < k2) return -1;
	else return 0;
}

template<typename K, typename V>
int Hashtable<K, V>::key_hash(K& k)
{
	return ((IEquatable)k).GetHashCode();
}

template<typename K, typename V>
size_t Hashtable<K, V>::key_get(const K& key)
{
	if (sizeof(K) <= sizeof(key_s)) {
		return (key_s)(key);
	} else {
		K* ptr = new K;
		*ptr = key;
		return (key_s)(ptr);
	}
}

template<typename K, typename V>
size_t Hashtable<K, V>::value_get(const V& value)
{
	if (sizeof(V) <= sizeof(value_s)) {
		return (value_s)(value);
	} else {
		V* ptr = new V;
		*ptr = value;
		return (value_s)(ptr);
	}
}

template<typename K, typename V>
void Hashtable<K, V>::key_destroy(size_t key)
{
	if (sizeof(K) > sizeof(key_s)) {
		K* ptr = (K*)key;
		delete ptr;
	}
}

template<typename K, typename V>
void Hashtable<K, V>::value_destroy(size_t value)
{
	if (sizeof(V) > sizeof(value_s)) {
		V* ptr = (V*)value;
		delete ptr;
	}
}
