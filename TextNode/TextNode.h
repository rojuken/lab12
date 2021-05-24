#pragma once
#include <iostream>
#include <cstring>
#include "Stack.h"
using namespace std;

class TTextNode
{
protected:

	static TTextNode* firstFree;
	static TTextNode* textNodes;

	TTextNode* next;
	TTextNode* down;
	char c;
	int level; // 0 - text, 1 - line, 2 - word, 3 - letter
public:
	TTextNode(int l = 3, char _c = 0);
	TTextNode(const TTextNode& node);
	TTextNode(char* s, int l);
	~TTextNode();

	TTextNode* GetNext();
	TTextNode* GetDown();
	char getC();
	int GetLevel();

	void SetNext(TTextNode* _next);
	void SetDown(TTextNode* _down);
	void Set(char _c);
	void SetLevel(int _l);

	friend std::ostream& operator<< (std::ostream& o, TTextNode& t);

	static void initMem(int size = 10);
	static void FreeMem();

	void* operator new (size_t size);
	void operator delete(void* p);
};