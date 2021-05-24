#pragma once
#include <iostream>
#include "TextNode.h"
#include <string>
#include <fstream>
#include "Stack.h"

using namespace std;

class Text;

class TextIter 
{
protected:
	Text& text;
	TTextNode* node;
	TStack<TTextNode*> st;
public:
	TextIter(Text& _text, TTextNode* _node, TStack<TTextNode*> _st);
	TextIter(const TextIter& t);

	bool GoNext();
	bool GoNextChar();
	bool IsEnd();

	void ResetToString();
	void ResetToWord();

	TTextNode* Get();
};

class Text
{
protected:
	TTextNode* root;
public:
	Text(char* s = 0);
	~Text();

	TextIter GetRoot();
	TextIter Find(char c);
	TextIter Find(char* c);
	TextIter FindWord(char* c);

	void Insert(char* c, TextIter i);
	void InsertData(char* c, TextIter i);
	void Delete(int count, TextIter i);
	char* Copy(int count, TextIter i);

	friend ostream& operator<<(ostream& o, Text& t);
};