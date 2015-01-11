#include <iostream>
#include <string>
#include "collections.h"
using namespace std;

template <class T>
struct ListItem
{
	T value;
	ListItem<T>* next;

	ListItem(const T &v)
	{
		next = NULL;
		value = v;
	}
};

template <class T>
class List : virtual Collections<T>
{
private:
	ListItem<T>* beg;
public:
	List()
	{
		beg = NULL;
	}

	~List()
	{
		while (beg != NULL)
		{
			ListItem<T>* t = beg->next;
			delete beg;
			beg = t;
		}
	}

	ListItem<T>* getLast()
	{
		if (beg == NULL)
			return NULL;
		ListItem<T> *p = beg;
		while (p->next != NULL)
			p = p->next;
		return p;
	}

	friend ostream& operator<<(ostream& out, const List<T> &list)
	{
		ListItem<T> *l = list.beg;
		out << "\n[";
		while (l != NULL)
		{
			if (l->next == NULL)
				out << l->value;
			else
				out << l->value << ", ";
			l = l->next;
		}
		out << "]\n";
		return out;
	}

	void Add(const T &element)
	{
		if (beg != NULL)
		{
			ListItem<T> *t = new ListItem<T>(element);
			this->getLast()->next = t;
		}
		else
			AddToBegin(element);
	}

	void AddToBegin(const T &element)
	{
		ListItem<T> *t = new ListItem<T>(element);
		t->value = element;
		t->next = beg;
		beg = t;
	}

	void Insert(const int &index, const T &element)
	{
		ListItem<T> *t = new ListItem<T>(element), *b = beg;
		int c = 1;
		while (b && c != index)
		{
			b = b->next;
			c++;
		}
		if (b && c == index)
		{
			t->next = b->next;
			b->next = t;
		}
	}

	void AddAfter(const T &item, const T &element)
	{
		ListItem<T> *t = new ListItem<T>(element), *b = beg;
		while (b && b->value != item)
			b = b->next;
		if (b && b->value == item)
		{
			t->next = b->next;
			b->next = t;
		}
	}

	void Remove(const T &item)
	{
		ListItem<T> *b = new ListItem<T>(NULL);
		b->next = beg;
		while (b->next && b->next->value != item)
			b = b->next;
		if (b->value)
			b->next = b->next->next;
		else
			beg = b->next->next;
	}

	bool Exists(const T &item)
	{
		ListItem<T> *t = beg;
		while (t != NULL)
		{
			if (t->value == item)
				return true;
			t = t->next;
		}
		return false;
	}
};