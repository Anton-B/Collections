#include <iostream>
#include <string>
#include "collections.h"
using namespace std; 

#ifndef ARRAY_HEADER_FILE
#define ARRAY_HEADER_FILE

template <class T>
class Array : virtual Collections<T>
{
protected:
	T *array;
	int size = 0, ind = -1;
public:

	Array()
	{
		array = new T[size];
	}

	Array(const Array<T> &val)
	{
		array = new T[val.size];
		size = val.size;
		for (int i = 0; i < val.size; i++)
			array[i] = val.array[i];
	}

	void Add(const T &element)
	{
		Insert(size, element);
	}

	void Insert(const int index, const T &element)
	{
		T *tmpArr = new T[++size];
		int i = 0;
		for (int j = 0; i < size; i++, j++)
		{
			if (i == index)
			{
				tmpArr[i] = element;
				j--;
			}
			else
				tmpArr[i] = array[j];
		}
		array = tmpArr;
	}

	int IndexOf(const T &element)
	{
		for (int i = 0; i < size; i++)
		if (array[i] == element)
			return i;
		return -1;
	}

	int LastIndexOf(const T &element)
	{
		for (int i = size - 1; i >= 0; i--)
		if (array[i] == element)
			return i;
		return -1;
	}

	void Remove(const T &element)
	{
		int count = 0;
		for (int i = 0; i < size; i++)
			if (array[i] == element)
				count++;
		for (int i = 0; i < count; i++)
			RemoveLast(element);
	}

	void RemoveLast(const T &element)
	{
		for (int i = size - 1; i >= 0; i--)
			if (array[i] == element)
			{
				RemoveByIndex(i);
				break;
			}
	}

	void RemoveByIndex(const int &index)
	{
		if (index < size)
		{
			T *tmpArr = array;
			array = new T[--size];
			for (int i = 0, c = 0; i < size + 1; i++)
				if (i != index)
				{
					array[c] = tmpArr[i];
					c++;
				}
		}
	}

	T& operator[](const int &index)
	{
		return array[index];
	}

	void operator+=(const T &element)
	{
		Add(element);
	}

	void operator-=(const T &element)
	{
		RemoveLast(element);
	}

	Array<T> operator+(const T &element)
	{
		Array<T> *t = new Array<T>;
		t->size = size;
		t->array = array;
		t->Add(element);
		return *t;
	}

	Array<T> operator+(const Array<T> &arr)
	{
		Array<T> *t = new Array<T>;
		t->size = size;
		t->array = array;
		for (int i = 0; i < arr.size; i++)
			t->Add(arr.array[i]);
		return *t;
	}

	Array<T> operator-(const T &element)
	{
		Array<T> *t = new Array<T>;
		t->size = size;
		t->array = array;
		t->RemoveByIndex(t->IndexOf(element));
		return *t;
	}

	Array<T> operator-(const Array<T> &arr)
	{
		Array<T> *t = new Array<T>;
		t->size = size;
		t->array = array;
		for (int i = 0; i < arr.size; i++)
			t->RemoveByIndex(t->IndexOf(arr.array[i]));
		return *t;
	}

	friend	ostream& operator<<(ostream& out, const Array<T> &arr)
	{
		cout << "\n[";
		for (int i = 0; i < arr.size - 1; i++)
			out << arr.array[i] << ", ";
		out << arr.array[arr.size - 1];
		cout << "]\n";
		return out;
	}
};

#endif