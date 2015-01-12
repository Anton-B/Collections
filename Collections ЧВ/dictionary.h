#include <iostream>
#include <string>
#include "collections.h"
#include "array.h"
using namespace std; 

#ifndef DICTIONARY_HEADER_FILE
#define DICTIONARY_HEADER_FILE

template <class TKey, class TValue>
struct DictItem
{
	TKey key;
	TValue value;

	friend ostream& operator<<(ostream& out, const DictItem* DI)
	{
		out << "{\"" << DI->key << "\":\"" << DI->value << "\"}";
		return out;
	}
};

template <class TKey, class TValue>
class Dictionary : public Array<DictItem<TKey, TValue>* >
{
public:
	void Add(const TKey &k, const TValue &v)
	{
		DictItem<TKey, TValue>* DI = new DictItem<TKey, TValue>;
		DI->key = k;
		DI->value = v;
		Array::Add(DI);
	}

	TValue& operator[](const TKey &k)
	{
		for (int i = 0; i < size; i++)
			if (array[i]->key == k)
				return array[i]->value;
	}
	void Remove(const TKey &k)
	{
		for (int i = 0; i < size; i++)
			if (array[i]->key == k)
				Array::Remove(array[i]);
	}

	void operator+=(DictItem<TKey, TValue>* DI)
	{
		Array::Add(DI);
	}

	bool KeyExists(const TKey &k)
	{
		for (int i = 0; i < size; i++)
			if (array[i]->key == k)
				return true;
		return false;
	}

	bool ValueExists(const TValue &v)
	{
		for (int i = 0; i < size; i++)
			if (array[i]->value == v)
				return true;
		return false;
	}
};

#endif