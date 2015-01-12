#include <iostream>
#include <string>
using namespace std;

#ifndef COLLECTIONS_HEADER_FILE
#define COLLECTIONS_HEADER_FILE

template <class T>
class Collections
{
	virtual void Add(const T &element) = 0;
	virtual void Insert(const int index, const T &element) = 0;
	virtual void Remove(const T &element) = 0;
};

#endif