#include <iostream>
#include <string>
using namespace std;

class Base
{
	
};

template <class T>
class Array :virtual Base
{
protected:
	T *a;	
	int size=0,tSize;
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

	~Array()
	{
		//delete [] a;
	}

	void Add(T element)
	{
		T *tmpArr=a;
		/*tmpArr = new T[size];
		for (int i = 0; i < size; i++)
			tmpArr[i] = a[i];*/
		size += 1;
		a = new T[size];
		for (int i = 0; i < size - 1; i++)
			a[i] = tmpArr[i];
		a[size - 1] = element;
	}

	void Insert(T element, int index)
	{
		if (index == size)
		{
			Add(element);
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
		/*a = new T[size];
		for (int i = 0; i < size; i++)
			a[i] = tmpArr[i];*/
	}

	void Show()
	{
		cout << "\nArray:\n";
		//cout << "size: " << size << endl;
		for (int i = 0; i < size; i++)
			cout << a[i] << endl;
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
		/*tmpArr = new T[size];
		for (int i = 0; i < size; i++)
			tmpArr[i] = a[i];*/
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

	Array<T> operator+(Array<T> arr)
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
};

template <class TKey, class TValue>
struct DictItem
{
	TKey k;
	TValue v;
	/*DictItem(TKey key, TValue value)
	{
		k = key;
		v = value;
	}*/
};

template <class TKey, class TValue>
class Dictionary:public Array<DictItem<TKey, TValue> >
{
public:
	void Add(TKey key, TValue value)
	{
		DictItem<TKey, TValue> DI = { key, value };
		//Add(DI);
		
	}

	
};


void main()
{
	/*Array<int> arrInt1,arrInt2,arrInt3;
	cout << "\nINT:\n";
	arrInt1.Add(6);
	arrInt1.Add(100);
	arrInt1 += 22;
	arrInt1.Add(53);
	arrInt1.Insert(7, 2);
	arrInt1.Show();
	cout << endl << arrInt1.IndexOf(4) << endl;
	cout << arrInt1.LastIndexOf(100) << endl;
	arrInt1.Remove(22);
	arrInt1 -= 6;
	cout << "\nAFTER REMOVE:\n";
	arrInt1.Show();
	cout << "\narrInt[index]: " << arrInt1[2] << endl;
	cout << "\nINT 2:\n";
	arrInt2=arrInt1+33;
	arrInt2.Show();
	arrInt3 = arrInt1 + arrInt2;
	arrInt3.Show();
	
	Array<string> arrStr1, arrStr2, arrStr3;
	cout << "\nSTR:\n";
	arrStr1.Add("asd");
	arrStr1 += "qwer";
	arrStr1.Add("zxcfdh");
	arrStr1.Add("zxcfdh");
	arrStr1.Add("asd");
	arrStr1.Add("rg");
	arrStr1.Insert("-!!-", 4);
	arrStr1.Show();
	cout << endl << arrStr1.IndexOf("asd") << endl;
	cout << arrStr1.LastIndexOf("t") << endl;
	arrStr1 -= "asd";
	arrStr1.Remove("zxcfdh");
	cout << "\nAFTER REMOVE:\n";
	arrStr1.Show();
	arrStr2 = arrStr1 - "asd";
	arrStr2.RemoveLast("-!!-");
	arrStr2.Show();
	arrStr3 = arrStr1 - arrStr2;
	arrStr3.Show();*/


	/*Dictionary <string, int> dic;
	dic.Add("OOO", 14);
	/*dic.Add("asdf", 7);
	dic.Add("OOO", 10);
	dic.Add("qwer", 14);
	dic.Show();
	dic.Remove("qwer");
	cout << "\nAFTER REMOVE:\n";
	dic.Show();
	if (dic.KeyExists("OOO"))
		cout << "\nKey is exist.\n";
	else
		cout << "\nNo keys :(\n";
	if (dic.ValueExists(435))
		cout << "\nValue is exist.\n";
	else
		cout << "\nNo values :(\n";*/

	cout << endl;
	system("pause");
}