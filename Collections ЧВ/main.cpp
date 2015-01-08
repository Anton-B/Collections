#include <iostream>
#include <string>
using namespace std;

template <class T>
class Collections
{
	virtual void Add(T element) = 0;
	virtual void Insert(T element, int index) = 0;
	virtual int IndexOf(T element) = 0;
	virtual int LastIndexOf(T element) = 0;
	virtual void Remove(T element) = 0;
	virtual void RemoveLast(T element) = 0;
	virtual void AddAfter(T item, T new_element) = 0;
	virtual void AddToBegin(T element) = 0;
	virtual void Delete(T item) = 0;
};

template <class T>
class Array :virtual Collections<T>
{
protected:
	T *a;
	int size = 0, ind = -1;
public:

	Array()
	{
		a = new T[size];
	}

	Array(const Array<T> &val)
	{
		a = new T[val.size];
		size = val.size;
		for (int i = 0; i < val.size; i++)
			a[i] = val.a[i];
	}

	void AddAfter(T item, T new_element){}
	void AddToBegin(T element){}
	void Delete(T item){}

	void Add(T element)
	{
		Insert(element, size);
	}

	void Insert(T element, int index)
	{
		if (index == size)
		{
			T *tmpArr = a;
			size += 1;
			a = new T[size];
			for (int i = 0; i < size - 1; i++)
				a[i] = tmpArr[i];
			a[size - 1] = element;
			return;
		}
		T *tmpArr;
		tmpArr = new T[size + 1];
		int c = 0;
		for (int i = 0; i < size; i++)
		{
			if (c != index)
				tmpArr[c] = a[i];
			else
			{
				tmpArr[c] = element;
				i--;
			}
			c++;
		}
		size += 1;
		a = tmpArr;
	}

	int IndexOf(T element)
	{
		for (int i = 0; i < size; i++)
		if (a[i] == element)
			return i;
		return -1;
	}

	int LastIndexOf(T element)
	{
		for (int i = size - 1; i >= 0; i--)
		if (a[i] == element)
			return i;
		return -1;
	}

	void Remove(T element)
	{
		T *tmpArr=a;
		a = new T[size];
		int c = 0;
		for (int i = 0; i < size; i++)
			if (tmpArr[i] != element)
			{
				a[c] = tmpArr[i];
				c++;
			}
		size = c;
	}

	void RemoveLast(T element)
	{
		int e = -10;
		T *tmpArr;
		tmpArr = new T[size];
		for (int i = size - 1; i >= 0; i--)
		{
			if (a[i] == element&&e == -10)
				e = i;
			tmpArr[i] = a[i];
		}
		if (e != -10)
		{
			a = new T[size - 1];
			for (int i = e; i < size - 1; i++)
				a[i] = tmpArr[i + 1];
			for (int i = 0; i < e; i++)
				a[i] = tmpArr[i];
			size--;
		}
	}

	T& operator[](int index)
	{
		return a[index];
	}

	void operator+=(T element)
	{
		Add(element);
	}

	void operator-=(T element)
	{
		RemoveLast(element);
	}

	Array<T> operator+(T element)
	{
		Array<T> *t;
		t = new Array<T>;
		t->a = new T[size + 1];
		for (int i = 0; i < size; i++)
			t->a[i] = a[i];
		t->a[size] = element;
		t->size = size + 1;
		return *t;
	}

	Array<T> operator+(Array<T> &arr)
	{
		Array<T> *t;
		t = new Array<T>;
		t->a = new T[size + arr.size];
		for (int i = 0; i < size; i++)
			t->a[i] = a[i];
		for (int j = size, i = 0; j < size + arr.size; j++, i++)
			t->a[j] = arr.a[i];
		t->size = size + arr.size;
		return *t;
	}

	Array<T> operator-(T element)
	{
		Array<T> *t;
		t = new Array<T>;
		int e = -10;
		for (int i = size - 1; i >= 0; i--)
		{
			if (a[i] == element&&e == -10)
				e = i;
			//t->a[i] = a[i];
		}
		if (e != -10)
		{
			t->a = new T[size - 1];
			for (int i = e; i < size - 1; i++)
				t->a[i] = a[i + 1];
			for (int i = 0; i < e; i++)
				t->a[i] = a[i];
			t->size = size - 1;
		}
		else
		{
			t->a = new T[size];
			for (int i = 0; i < size; i++)
				t->a[i] = a[i];
			t->size = size;
		}
		return *t;
	}

	Array<T> operator-(Array<T> arr)
	{
		Array<T> *t;
		t = new Array<T>;
		int fl = 0, c = 0;
		t->a = new T[size];
		for (int i = 00; i < size; i++)
		{
			fl = 0;
			for (int j = 0; j < arr.size; j++)
			{
				if (a[i] == arr.a[j])
				{
					fl = 1;
				}
			}
			if (fl == 0)
			{
				t->a[c] = a[i];
				c++;
			}
		}

		t->size = c;
		return *t;
	}

	friend	ostream& operator<<(ostream& out, Array<T> arr)
	{
		cout << "\n[";
		for (int i = 0; i < arr.size-1; i++)
			out << arr.a[i] << ", ";
		out << arr.a[arr.size - 1];
		cout <<"]\n";
		return out;
	}
};

template <class TKey, class TValue>
struct DictItem
{
	TKey k;
	TValue v;

	friend ostream& operator<<(ostream& out, DictItem* DI)
	{
		out << "{\"" << DI->k << "\":\"" << DI->v << "\"}";
		return out;
	}
};

template <class TKey, class TValue>
class Dictionary :public Array<DictItem<TKey, TValue>* >
{
public:
	void Add(TKey key, TValue value)
	{
		DictItem<TKey, TValue>* DI = new DictItem<TKey, TValue>;
		DI->k = key;
		DI->v = value;
		Array::Add(DI);
	}
	
	TValue& operator[](TKey key)
	{
		for (int i = 0; i < size; i++)
			if (a[i]->k == key)
				return a[i]->v;
	}

	void Remove(TKey key)
	{
		for (int i = 0; i < size; i++)
			if (a[i]->k == key)
				Array::Remove(a[i]);
	}

	void operator+=(DictItem<TKey, TValue>* DI)
	{
		Array::Add(DI);
	}

	bool KeyExists(TKey key)
	{
		for (int i = 0; i < size; i++)
			if (a[i]->k == key)
				return true;
			return false;
	}

	bool ValueExists(TValue value)
	{
		for (int i = 0; i < size; i++)
			if (a[i]->v == value)
				return true;
		return false;
	}

};

template <class T>
struct ListItem
{
	T value;
	ListItem<T>* next;
	

	ListItem(T v)
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
	int count = 0;

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

	void Insert(T element, int index){}
	int IndexOf(T element){ return 0; }
	int LastIndexOf(T element){ return 0; }
	void Remove(T element){}
	void RemoveLast(T element){}

	ListItem<T>* getLast()
	{
		if (beg == NULL)
			return NULL;
		ListItem<T> *p = beg;
		while (p->next != NULL)
			p = p->next;
		return p;
	}

	friend ostream& operator<<(ostream& out, List<T> list)
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
	
	void Add(T element)
	{
		if (beg != NULL)
		{
			ListItem<T> *t = new ListItem<T>(element);
			this->getLast()->next = t;
		}
		else
			AddToBegin(element);
	}
	
	void AddToBegin(T element)
	{
		ListItem<T> *t = new ListItem<T>(element);
		t->value = element;
		t->next = beg;
		beg = t;
		count++;
		
	}

	void AddAfter(T item, T new_element)
	{
		ListItem<T> *t = new ListItem<T>(new_element);
		ListItem<T> *b = beg;
		while (b && b->value != item)
			b = b->next;
		if (b && b->value == item)
		{
			t->next = b->next;
			b->next = t;
		}	
	}

	void Delete(T item)
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

	ListItem<T>* Search(ListItem<T>* item)
	{
		ListItem<T> *t = beg;
		while (t != NULL&&t != item)
			t = t->next;
		return (t == item) ? t : NULL;
	}
};

void main()
{
	Array<int> arrInt1,arrInt2,arrInt3;
	cout << "\nINT:\n";
	arrInt1.Add(6);
	arrInt1.Add(100);
	arrInt1 += 22;
	arrInt1.Add(53);
	arrInt1.Insert(7, 2);
	cout << arrInt1;
	cout << arrInt1;
	cout << endl << arrInt1.IndexOf(4) << endl;
	cout << arrInt1.LastIndexOf(100) << endl;
	arrInt1.Remove(22);
	arrInt1 -= 6;
	cout << "\nAFTER REMOVE:\n";
	cout<<arrInt1;
	cout << "\narrInt[index]: " << arrInt1[2] << endl;
	cout << "\nINT 2:\n";
	arrInt2=arrInt1+33;
	cout<<arrInt2;
	arrInt3 = arrInt1 + arrInt2;
	cout << arrInt3;
	
	Array<string> arrStr1, arrStr2, arrStr3;
	cout << "\nSTR:\n";
	arrStr1.Add("asd");
	arrStr1 += "qwer";
	arrStr1.Add("zxcfdh");
	arrStr1.Add("zxcfdh");
	arrStr1.Add("asd");
	arrStr1.Add("rg");
	arrStr1.Insert("-!!-", 4);
	cout<<arrStr1;
	cout << endl << arrStr1.IndexOf("asd") << endl;
	cout << arrStr1.LastIndexOf("t") << endl;
	arrStr1 -= "asd";
	arrStr1.Remove("zxcfdh");
	cout << "\nAFTER REMOVE:\n";
	cout<<arrStr1;
	arrStr2 = arrStr1 - "asd";
	arrStr2.RemoveLast("-!!-");
	cout << arrStr2;
	arrStr3 = arrStr1 - arrStr2;
	cout << arrStr3;


	Dictionary<string, int> dic, dic2, dic3;
	DictItem<string, int>* di = new DictItem<string, int>;
	
	dic.Add("mwsd", 14);
	dic.Add("asdf", 7);
	dic.Add("OOO", 10);
	dic.Add("qwer", 14);
	
	cout << dic;
	cout << dic["OOO"];
	dic.Remove("OOO");
	
	cout << "\nAFTER REMOVE:\n";
	cout << dic;
	
	di->k = "uuuuuuu";
	di->v = 321;
	dic += di;
	dic2.Add("q", 1);
	dic2.Add("w", 2);
	dic2.Add("e", 3);
	dic2.Add("r", 4);
	di->k = "z";
	di->v = 9;
	//dic3 = dic + dic2;
	cout << dic;

	if (dic.KeyExists("uuuuuuu"))
		cout << "\nKey is exist.\n";
	else
		cout << "\nNo keys :(\n";
	if (dic.ValueExists(435))
		cout << "\nValue is exist.\n";
	else
		cout << "\nNo values :(\n";

	List<int> list;
	ListItem<int>* node = new ListItem<int>(177);
	ListItem<int>* node1 = new ListItem<int>(33);
	ListItem<int>* node2 = new ListItem<int>(9);
	ListItem<int>* node3 = new ListItem<int>(400);
	list.Add(33);
	list.AddToBegin(177);
	list.Add(9);
	list.Add(400);
	list.AddAfter(9, 421);
	list.Delete(9);
	list.Search(node1);

	cout << list;

	cout << endl;
	system("pause");
}