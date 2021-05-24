#include <gtest.h>
#include <Text.h>

TEST(Text, can_create_empty_text) {
  ASSERT_NO_THROW(Text A());
}


TEST(Text, can_create_non_empty_text) {
  char* const temp = "It is text";
  ASSERT_NO_THROW(Text A(temp));
}


TEST(Text, can_multiple_lines_be_added) {
  char* const temp = "It is text. \nIt is new line of text.";
  ASSERT_NO_THROW(Text A(temp));
}


TEST(Text, can_insert_data_into_text) {
  char* temp = "It is text.";
  Text A(temp);
  TextIter B = A.Find("e");
  ASSERT_NO_THROW(A.InsertData("new data", B));
}


TEST(TextIter, get_the_first_character) {
  char* const temp = "It is text";
  Text A(temp);
  TextIter iter = A.GetRoot();
  iter.GoNextChar(); 
  ASSERT_EQ(iter.Get()->GetC(), 'I'); 
}


TEST(Text, get_the_first_character_of_the_next_word) {
  char* const temp = "It is text";
  Text A(temp);
  TextIter iter = A.GetRoot();

  while (iter.Get()->GetC() != ' ') 
  {
    iter.GoNextChar();
  }
  iter.GoNextChar(); 
  ASSERT_EQ(iter.Get()->GetC(), 'i'); 
}


TEST(Text, cannot_get_the_next_character_if_there_is_none) {
  char* const temp = "A";
  Text A(temp);
  TextIter iter = A.GetRoot();
  iter.GoNextChar(); 
  ASSERT_EQ(iter.GoNextChar(), false); 
}


TEST(Text, can_go_next) {
  char* const temp = "It is text";
  Text A(temp);
  TextIter iter = A.GetRoot();
  ASSERT_EQ(iter.GoNext(), true);
}


TEST(Text, can_find_the_letter) {
  char* const temp = "It is text";
  Text A(temp);
  TextIter iter = A.Find('e'); 
  iter.GoNextChar();
  ASSERT_EQ(iter.Get()->GetC(), 'x'); 
}


TEST(Text, can_insert_a_letter) {
  char* const temp = "It is text";
  Text A(temp);
  TextIter iter = A.GetRoot();
  ASSERT_NO_THROW(A.Insert("Q", iter));
}


TEST(Text, can_find_the_word) {
  char* const temp = "It is text";
  Text A(temp);
  char* const temp_find = "text";
  TextIter iter = A.FindWord(temp_find); 
  iter.GoNextChar();
  ASSERT_EQ(iter.Get()->GetC(), 't'); 
}


TEST(Text, text_find_word_3) {
  char* const temp = "It is text";
  Text A(temp);
  char* const temp_find = "qwe";
  TextIter iter = A.FindWord(temp_find);
  ASSERT_EQ(iter.IsEnd(), true); 
}


TEST(Text, text_delete_0) {
  char* const temp = "It is text";
  Text A(temp);
  char* const temp_find = "is";
  TextIter iter = A.FindWord(temp_find); 
  ASSERT_NO_THROW(A.Delete(2, iter)); 
}


TEST(Text, can_save_to_file) {
  char* const temp = "It is text";
  Text A(temp);
  ASSERT_NO_THROW(A.SaveToFile());
}


TEST(Text, can_load_from_file) {
  char* const temp = "";
  Text A(temp);
  ASSERT_NO_THROW(A.LoadFromFile("DataText.txt"));
}


TEST(Text, can_copy) {
  char* const temp = "Abcd text";
  Text A(temp);
  char temp_find = 't';
  TextIter iter = A.Find(temp_find); 
  ASSERT_NO_THROW(char* res = A.Copy(4, iter)); 
}