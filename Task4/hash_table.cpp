#include "hash_table.h"

void TestHashTable() {
	HashTable<int, string> *H = new HashTable<int, string>(4);
	string str[] = { "nmsl", "dad", "dad", "sister","brother","uncle","aunt","grandpa"};
	cout << "-------------------------------" << endl;
	cout << "HashMap of <int, string>: " << endl;
	for (int i = 0; i < 8; i++) {
		H->Insert(i + 1, str[i]);
	}
	H->Print();
	cout<<"deleted <3,dad>" << endl;
	H->Delete(3);
	cout << "find result of 3: " << H->Find(3) << endl;
	cout << "find result of 6: " << H->Find(6) << endl;
	H->Print();
	H->Clear();
	cout << "-------------------------------" << endl;
	HashTable<string, int>* H1 = new HashTable<string, int>(4);
	cout << "HashMap of <string, int>: " << endl;
	for (int i = 0; i < 8; i++) {
		H1->Insert(str[i], i + 1);
	}
	H1->Print();
	cout << "deleted <nmsl,1>" << endl;
	H1->Delete("nmsl");
	cout << "find result of nmsl: " << H1->Find("nmsl") << endl;
	cout << "find result of aunt: " << H1->Find("aunt") << endl;
	H1->Print();
	H1->Clear();
}