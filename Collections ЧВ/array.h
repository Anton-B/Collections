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

	void Insert(const int &index, const T &element)
	{
		if (index == size)
		{
			T *tmpArr = array;
			size++;
			array = new T[size];
			for (int i = 0; i < size - 1; i++)
				array[i] = tmpArr[i];
			array[size - 1] = element;
			return;
		}
		T *tmpArr = new T[size + 1];
		int c = 0;
		for (int i = 0; i < size; i++)
		{
			if (c != index)
				tmpArr[c] = array[i];
			else
			{
				tmpArr[c] = element;
				i--;
			}
			c++;
		}
		size++;
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
		T *tmpArr = array;
		array = new T[size];
		int c = 0;
		for (int i = 0; i < size; i++)
		if (tmpArr[i] != element)
		{
			array[c] = tmpArr[i];
			c++;
		}
		size = c;
	}

	void RemoveLast(const T &element)
	{
		int e = -10;
		T *tmpArr = new T[size];
		for (int i = size - 1; i >= 0; i--)
		{
			if (array[i] == element && e == -10)
				e = i;
			tmpArr[i] = array[i];
		}
		if (e != -10)
		{
			array = new T[size - 1];
			for (int i = e; i < size - 1; i++)
				array[i] = tmpArr[i + 1];
			for (int i = 0; i < e; i++)
				array[i] = tmpArr[i];
			size--;
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
		t->array = new T[size + 1];
		for (int i = 0; i < size; i++)
			t->array[i] = array[i];
		t->array[size] = element;
		t->size = size + 1;
		return *t;
	}

	Array<T> operator+(const Array<T> &arr)
	{
		Array<T> *t = new Array<T>;
		t->array = new T[size + arr.size];
		for (int i = 0; i < size; i++)
			t->array[i] = array[i];
		for (int j = size, i = 0; j < size + arr.size; j++, i++)
			t->array[j] = arr.array[i];
		t->size = size + arr.size;
		return *t;
	}

	Array<T> operator-(const T &element)
	{
		Array<T> *t = new Array<T>;
		int e = -10;
		for (int i = size - 1; i >= 0; i--)
		{
			if (array[i] == element && e == -10)
				e = i;
		}
		if (e != -10)
		{
			t->array = new T[size - 1];
			for (int i = e; i < size - 1; i++)
				t->array[i] = array[i + 1];
			for (int i = 0; i < e; i++)
				t->array[i] = array[i];
			t->size = size - 1;
		}
		else
		{
			t->array = new T[size];
			for (int i = 0; i < size; i++)
				t->array[i] = array[i];
			t->size = size;
		}
		return *t;
	}

	Array<T> operator-(const Array<T> &arr)
	{
		Array<T> *t = new Array<T>;
		int fl = 0, c = 0;
		t->array = new T[size];
		for (int i = 0; i < size; i++)
		{
			fl = 0;
			for (int j = 0; j < arr.size; j++)
			{
				if (array[i] == arr.array[j])
				{
					fl = 1;
				}
			}
			if (fl == 0)
			{
				t->array[c] = array[i];
				c++;
			}
		}

		t->size = c;
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

#endif ARRAY_HEADER_FILE