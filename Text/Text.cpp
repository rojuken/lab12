#include "Text.h"

ostream& operator<<(ostream& o, Text& t)
{
	o << *(t.root);
	return o;
}

Text::Text(char* s)
{
	root = new TTextNode(s, 1);
}

Text::~Text()
{
	TTextNode::FreeMem();
}

TextIter Text::GetRoot()
{
	TStack<TTextNode*> A(100);
	TextIter B(*this, root, A);
	return B;
}

TextIter Text::Find(char c)
{
	TextIter iter = GetRoot();
	while (iter.GoNextChar())
	{
		if (iter.Get()->getC() == c)
			return iter;
	}
	return iter;
}

TextIter Text::Find(char* c)
{
	TStack<TTextNode*> A(100);
	TextIter iter(*this, root, A);
	int n = strlen(c);

	while (iter.GoNextChar())
	{
		TextIter cur = iter;
		int i = 0;
		bool ok = true;
		bool isGo = true;
		while (i < n)
		{
			if (!isGo)
			{
				ok = false;
				break;
			}
			if (c[i] != cur.Get()->getC())
			{
				ok = false;
				break;
			}
			isGo = cur.GoNextChar();
			i++;
		}
		if (ok)
		{
			return iter;
		}
	}
}

TextIter Text::FindWord(char* c)
{
	TStack<TTextNode*> A(100);
	TextIter i(*this, root, A);
	while (i.GoNext())
	{
		if (i.Get()->GetLevel() == 2)
		{
			TextIter res = i;
			bool ok = true;
			int j = 0;
			int n = strlen(c);
			while (i.GoNext() && j < n)
			{
				if (i.Get()->GetLevel() == 2)
				{
					ok = false;
					break;
				}

				if (i.Get()->getC() != c[j])
				{
					ok = false;
					break;
				}
				j++;
			}
			if (ok)
				return res;
		}
	}
	return i;
}

void Text::Insert(char* c, TextIter i)
{
	TTextNode* node = new TTextNode(c, i.Get()->GetLevel());
	TTextNode* next = i.Get()->GetNext();
	node->SetNext(next);
	i.Get()->SetNext(node);
}

void Text::InsertData(char* c, TextIter i)
{
	if (strlen(c) == 1)
		Insert(c, i);
	else
	{
		int lvl = 2;
		for (int j = 0; j < strlen(c); j++)
		{
			if (c[j] == ' ')
			{
				lvl = 1;
				break;
			}
		}

		TextIter fin = i;
		TTextNode* next = i.Get()->GetNext();

		if (next->getC() == ' ' || next->getC() == '.')
		{
			i.GoNextChar();
			int size = strlen(c);
			char* x = new char[strlen(c) + 1];
			x[strlen(c) + 1] = '\0';

			for (int j = 0; j < strlen(c); j++)
				x[j] = c[j];

			x[strlen(c)] = ' ';

			TTextNode* node = new TTextNode(x, lvl);

			next->SetNext(node);
			i.Get()->SetNext(node);
		}
		else
		{
			int count = 0;
			char symbol = ' ';
			TTextNode* cnode = i.Get()->GetNext();

			while (cnode->getC() != '.' && cnode->getC() != ' ' && cnode->getC() != '\n')
			{
				count++;
				cnode = cnode->GetNext();
			}
			if (cnode->getC() == '.')
				symbol = '.';
			if (cnode->getC() == '\n')
				symbol = '\n';

			char* tmp = new char[strlen(c) + count + 3];
			tmp[strlen(c) + count + 3] = '\0';
			tmp[0] = ' ';

			int j = 1;
			int k = 0;

			for (j; j < strlen(c) + 1; j++, k++)
				tmp[j] = c[k];
			tmp[j] = ' ';

			TTextNode* tnode = i.Get()->GetNext();
			for (j = j + 1; j < strlen(c) + count + 2; j++)
			{
				tmp[j] = tnode->getC();
				tnode = tnode->GetNext();
			}

			tmp[strlen(c) + count + 2] = symbol;

			fin.GoNext();
			this->Delete(count, fin);

			TTextNode* node = new TTextNode(tmp, lvl);
			next->SetNext(node);
			i.Get()->SetNext(node);
		}
	}
}

void Text::Delete(int count, TextIter i)
{
	if (count == 0)
		return;

	TStack<TTextNode*> stacks[3];
	int deleted = 0;

	if (i.Get()->GetLevel() < 3)
		i.GoNextChar();

	int level = i.Get()->GetLevel();
	
	if (level < 3)
		i.GoNextChar();

	if (level >= 1 && level <= 3)
	{
		stacks[level - 1].Push(i.Get());
		if (level == 3)
			deleted++;
	}

	TextIter j = i;

	while (j.GoNext() && deleted < count)
	{
		level = j.Get()->GetLevel();
		if (level >= 1 && level <= 3)
		{
			stacks[level - 1].Push(j.Get());
			if (level == 3)
				deleted++;
		}
	}

	if (deleted < count)
		throw new exception;

	if (stacks[0].IsEmpty() && stacks[1].IsEmpty())
	{
		TextIter prev = i;
		prev.ResetToWord();
		while (prev.Get()->GetNext() != i.Get() && prev.Get()->GetDown() != i.Get())
		{
			prev.GoNext();
		}
		TTextNode* last = stacks[2].Get();
		if (prev.Get()->GetLevel() == 2)
		{
			prev.Get()->SetDown(last->GetNext());
		}
		else
		{
			prev.Get()->SetNext(last->GetNext());
		}
		delete last;
		return;
	}

	TextIter prev = i;
	prev.ResetToWord();
	while (prev.Get()->GetNext() != i.Get() && prev.Get()->GetDown() != i.Get())
	{
		prev.GoNext();
	}

	if (prev.Get()->GetNext() == i.Get())
		prev.Get()->SetNext(NULL);
	else
		prev.Get()->SetDown(NULL);

	if (stacks[0].IsEmpty())
	{
		TTextNode* last_word = stacks[1].Get();
		TTextNode* last_letter = stacks[2].Get();
		TextIter cur = i;
		cur.ResetToWord();
		cur.Get()->SetNext(last_word);
		last_word->SetDown(last_letter->GetNext());
		delete last_letter;
		for (int k = 1; k < 3; k++)
		{
			while (!stacks[k].IsEmpty())
			{
				TTextNode* del = stacks[k].Get();
				delete del;
			}
		}
		return;
	}
	else
	{
		TTextNode* last_string = stacks[0].Get();
		TTextNode* last_word = stacks[1].Get();
		TTextNode* last_letter = stacks[2].Get();
		TextIter cur = i;
		cur.ResetToString();
		cur.Get()->SetNext(last_string);
		cur.ResetToWord();
		cur.Get()->SetNext(last_word);
		last_word->SetDown(last_letter->GetNext());
		delete last_letter;
		for (int k = 0; k < 3; k++)
		{
			while (!stacks[k].IsEmpty())
			{
				TTextNode* del = stacks[k].Get();
				delete del;
			}
		}

	}
}

char* Text::Copy(int count, TextIter i)
{
	if (count < 0)
		throw new exception;
	
	char* res = new char[count + 1];
	TextIter cur = i;
	while (cur.Get()->GetLevel() < 3)
	{
		cur.GoNext();
	}

	if (count > 0)
	{
		res[0] = cur.Get()->getC();
		int j = 1;
		while (cur.GoNextChar() && j < count)
		{
			res[j] = cur.Get()->getC();
			j++;
		}
	}
	res[count] = '\0';
	return res;;
}

TextIter::TextIter(Text& _text, TTextNode* _node, TStack<TTextNode*> _st) : text(_text)
{
	node = _node;
	st = _st;
}

TextIter::TextIter(const TextIter& t) : text(t.text)
{
	node = t.node;
	st = t.st;
}

bool TextIter::GoNext()
{
	if (node->GetLevel() == 3)
	{
		if (node->GetNext() != 0)
			node = node->GetNext();
		else
		{
			node = st.Get();
			if (node->GetNext() != 0)
				node = node->GetNext();
			else
			{
				node = st.Get();
				if (node->GetNext() != 0)
					node = node->GetNext();
				else
				{
					node = 0;
					return false;
				}
			}
		}
	}
	else
	{
		st.Push(node);
		node = node->GetDown();
	}
	return true;
}

bool TextIter::GoNextChar()
{
	if (node->GetLevel() == 1)
	{
		st.Push(node);
		node = node->GetDown();
		st.Push(node);
		node = node->GetDown();
		return true;
	}

	if (node->GetLevel() == 2)
	{
		st.Push(node);
		node = node->GetDown();
		return true;
	}

	if (node->GetLevel() == 3 && node->GetNext() != NULL)
	{
		node = node->GetNext();
		return true;
	}

	if (node->GetLevel() == 3 && node->GetNext() == NULL)
	{
		if (st.IsEmpty())
			throw new exception;
	
		TTextNode* prev = st.Get();
		if (prev->GetNext() != NULL)
		{
			st.Push(prev->GetNext());
			node = prev->GetNext()->GetDown();
			return true;
		}
		return false;
	}
	return false;
}

bool TextIter::IsEnd()
{
	if (node == NULL)
		return true;

	if (node->GetLevel() == 1 || node->GetLevel() == 2)
	{
		return false;
	}

	if (node->GetLevel() == 3 && node->GetNext() != NULL)
	{
		return false;
	}

	if (node->GetLevel() == 3 && node->GetNext() == NULL)
	{
		if (st.IsEmpty())
			throw new exception;

		TTextNode* prev = st.Get();
		if (prev->GetNext() != NULL)
			return false;

		return true;
	}
	return true;
}

void TextIter::ResetToString()
{
	while (node->GetLevel() > 1)
	{
		if (st.IsEmpty())
			throw new exception;
		node = st.Get();
	}
}

void TextIter::ResetToWord()
{
	if (node->GetLevel() == 1)
	{
		st.Push(node);
		node = node->GetDown();
	}
	else if (node->GetLevel() == 3)
		node = st.Get();
}

TTextNode* TextIter::Get()
{
	return node;
}
