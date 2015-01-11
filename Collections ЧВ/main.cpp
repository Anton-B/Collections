#include <iostream>
#include <string>
#include "collections.h"
#include "array.h"
#include "dictionary.h"
#include "list.h"
using namespace std;

void main()
{
	Array<int> arrInt1,arrInt2,arrInt3;
	cout << "\nINT:\n";
	arrInt1.Add(6);
	arrInt1.Add(100);
	arrInt1 += 22;
	arrInt1.Add(53);
	arrInt1.Insert(2, 7);
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
	arrStr1.Insert(4, "-!!-");
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
	
	di->key = "uuuuuuu";
	di->value = 321;
	dic += di;
	dic2.Add("q", 1);
	dic2.Add("w", 2);
	dic2.Add("e", 3);
	dic2.Add("r", 4);
	di->key = "z";
	di->value = 9;
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
	list.Add(33);
	list.AddToBegin(177);
	list.Insert(2, 9);
	list.Add(400);
	list.AddAfter(9, 421);
	list.Remove(400);
	if (list.Exists(177))
		cout << "List item exists.\n";
	else
		cout << "List item doesn't exist.\n";
	cout << list;

	cout << endl;
	system("pause");
}