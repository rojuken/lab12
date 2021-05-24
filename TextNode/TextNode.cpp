#include "TextNode.h"

TTextNode* TTextNode::firstFree = 0;
TTextNode* TTextNode::textNodes = 0;

std::ostream& operator<<(std::ostream& o, TTextNode& t)
{
	if (t.level == 3)
	{
		o << t.c;
		if (t.next != NULL)
			o << *(t.next);
	}
	else
	{
		if (t.down != NULL)
			o << *(t.down);
		if (t.next != NULL)
			o << *(t.next);
	}
	return o;
}

TTextNode::TTextNode(int l, char _c)
{
	next = NULL;
	down = NULL;
	c = _c;
	level = l;
}

TTextNode::TTextNode(const TTextNode& node)
{
	next = NULL;
	down = NULL;
	c = node.c;
	level = node.level;
}

TTextNode::TTextNode(char* s, int l)
{
	if (l < 1 || l>3)
		throw new exception;

	if (l == 1)
	{
		next = NULL;
		c = 0;
		level = l;
		int sz = strlen(s);
		if (sz > 0)
		{
			int start = 0;
			TTextNode* wcur = new TTextNode(2);
			this->SetDown(wcur);
			for (int i = 0; i < sz; i++)
			{
				if (s[i] == ' ' || i == sz - 1)
				{
					if (start != 0)
					{
						wcur->SetNext(new TTextNode(2));
						wcur = wcur->GetNext();
					}
					TTextNode* lcur = new TTextNode(3, s[start]);
					wcur->SetDown(lcur);
					for (int j = start + 1; j <= i; j++)
					{
						lcur->SetNext(new TTextNode(3, s[j]));
						lcur = lcur->GetNext();
					}
					lcur->SetNext(NULL);
					start = i + 1;
				}
			}
			wcur->SetNext(NULL);
		}
	}
	if (l == 2)
	{
		next = NULL;
		c = 0;
		level = l;
		int sz = strlen(s);
		if (sz > 0)
		{
			TTextNode* lcur = new TTextNode(3, s[0]);
			this->SetDown(lcur);
			for (int i = 0; i < sz; i++)
			{
				lcur->SetNext(new TTextNode(3, s[i]));
				lcur = lcur->GetNext();
			}
			lcur->SetNext(NULL);
		}
	}
	if (l == 3)
	{
		c = s[0];
		level = l;
		next = NULL;
		down = NULL;
	}
}

TTextNode::~TTextNode()
{
}

TTextNode* TTextNode::GetNext()
{
	return next;
}

TTextNode* TTextNode::GetDown()
{
	return down;
}

char TTextNode::getC()
{
	return c;
}

int TTextNode::GetLevel()
{
	return level;
}

void TTextNode::SetNext(TTextNode* _next)
{
	next = _next;
}

void TTextNode::SetDown(TTextNode* _down)
{
	down = _down;
}

void TTextNode::Set(char _c)
{
	c = _c;
}

void TTextNode::SetLevel(int _l)
{
	if (_l >= 1 && _l <= 3)
		level = _l;
	else
		throw - 1;
}

void TTextNode::initMem(int size)
{
	if (size <= 0)
		throw new exception;
	if (firstFree == 0 && textNodes == 0)
	{
		textNodes = new TTextNode[size];
		firstFree = textNodes;
		
	}
	else if (firstFree != 0 && textNodes == 0)
	{
		throw new exception;
	}
	else
	{
		TTextNode* nt = new TTextNode[size];
		for (int i = 0; i < size; i++)
		{
			nt[i] = textNodes[i];
		}

		textNodes = new TTextNode[size * 2];
		firstFree = textNodes;

		for (int i = 0; i < size; i++)
			textNodes[i] = nt[i];

		delete[] nt;
	}
}

void TTextNode::FreeMem()
{
	if (textNodes != 0)
		delete[] textNodes;
	textNodes = 0;
	firstFree = 0;
}

void* TTextNode::operator new(size_t size)
{
	if (firstFree == 0 && textNodes == 0)
		initMem();
	if (firstFree == 0 && textNodes != 0)
		initMem();

	TTextNode* node = firstFree;
	firstFree = firstFree->next;

	node->next = 0;

	return node;
}

void TTextNode::operator delete(void* p)
{
	TTextNode* node = (TTextNode*)p;

	if (firstFree == 0 && textNodes == 0)
		throw new exception;

	node->next = NULL;
	node->down = NULL;
	node->c = 0;
	node->level = 3;

	node->next = firstFree;
	firstFree = node;
}
