#include <../gtest/gtest.h>
#include "Text.h"

TEST(Text, can_create_empty_text) 
{
	ASSERT_NO_THROW(Text A());
}

TEST(Text, can_create_non_empty_text) 
{
	char* const temp = "Hello world";
	ASSERT_NO_THROW(Text A(temp));
}

TEST(Text, can_multiple_lines_be_added) 
{
	char* const temp = "Hello world \n Nice.";
	ASSERT_NO_THROW(Text A(temp));
}

TEST(Text, can_insert_into_text)
{
	char* temp = "Hello world.";
	Text A(temp);
	TextIter B = A.Find("d");

	ASSERT_NO_THROW(A.InsertData("new data", B));
}

TEST(TextIter, get_the_first_character)
{
	char* const temp = "Hello world";
	Text A(temp);
	TextIter iter = A.GetRoot();
	iter.GoNextChar();
	ASSERT_EQ(iter.Get()->getC(), 'H');
}

TEST(Text, get_the_first_character_of_the_next_word)
{
	char* const temp = "Hello world";
	Text A(temp);
	TextIter iter = A.GetRoot();

	while (iter.Get()->getC() != ' ')
	{
		iter.GoNextChar();
	}

	iter.GoNextChar();
	ASSERT_EQ(iter.Get()->getC(), 'w');
}

TEST(Text, cannot_get_the_next_character_if_there_is_none) 
{
	char* const temp = "A";
	Text A(temp);
	TextIter iter = A.GetRoot();
	iter.GoNextChar();

	ASSERT_EQ(iter.GoNextChar(), false);
}

TEST(Text, can_go_next) 
{
	char* const temp = "Hello world";
	Text A(temp);
	TextIter iter = A.GetRoot();
	ASSERT_EQ(iter.GoNext(), true);
}

TEST(Text, can_find_the_letter) 
{
	char* const temp = "Hello world";
	Text A(temp);
	TextIter iter = A.Find('e');
	iter.GoNextChar();
	ASSERT_EQ(iter.Get()->getC(), 'l');
}

TEST(Text, can_insert_a_letter)
{
	char* const temp = "Hello world";
	Text A(temp);
	TextIter iter = A.GetRoot();
	A.Insert("Q", iter);
	ASSERT_NO_THROW(A.Insert("Q", iter));
}

TEST(Text, can_find_the_word)
{
	char* const temp = "Hello new world";
	Text A(temp);

	char* const temp_find = "new";
	TextIter iter = A.FindWord(temp_find);
	iter.GoNextChar();
	ASSERT_EQ(iter.Get()->getC(), 'n');
}

TEST(Text, text_delete) 
{
	char* const temp = "Hello new world";
	Text A(temp);

	char* const temp_find = "new";
	TextIter iter = A.FindWord(temp_find);
	ASSERT_NO_THROW(A.Delete(2, iter));
}

TEST(Text, can_copy)
{
	char* temp = "Hello new world";
	Text A(temp);
	char c = 'r';
	TextIter iter = A.Find(c);
	ASSERT_NO_THROW(char* copied = A.Copy(3, iter));
}