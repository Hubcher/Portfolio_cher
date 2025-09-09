#include <gtest/gtest.h>

#include "../containers/s21_list.h"

TEST(ListTest, DefaultConstructor) {
  s21::List<int> list;
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, SizeConstructor) {
  s21::List<int> list(5);
  EXPECT_EQ(list.size(), 5);
  for (auto it = list.begin(); it != list.end(); ++it) {
    EXPECT_EQ(*it, 0);
  }
}

TEST(ListTest, InitializerListConstructor) {
  s21::List<int> list = {1, 2, 3, 4, 5};
  EXPECT_EQ(list.size(), 5);
  auto it = list.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);
}

TEST(ListTest, CopyConstructor) {
  s21::List<int> list1 = {1, 2, 3};
  s21::List<int> list2(list1);
  EXPECT_EQ(list2.size(), 3);
  auto it = list2.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
}

TEST(ListTest, MoveConstructor) {
  s21::List<int> list1 = {1, 2, 3};
  s21::List<int> list2(std::move(list1));
  EXPECT_EQ(list2.size(), 3);
  EXPECT_TRUE(list1.empty());
}

TEST(ListTest, Front) {
  s21::List<int> list = {10, 20, 30};
  EXPECT_EQ(list.front(), 10);
}

TEST(ListTest, Back) {
  s21::List<int> list = {10, 20, 30};
  EXPECT_EQ(list.back(), 30);
}

TEST(ListTest, PushBackAndPopBack) {
  s21::List<int> list;
  list.push_back(10);
  list.push_back(20);
  EXPECT_EQ(list.back(), 20);
  list.pop_back();
  EXPECT_EQ(list.back(), 10);
  list.pop_back();
  EXPECT_TRUE(list.empty());
}

TEST(ListTest, PushFrontAndPopFront) {
  s21::List<int> list;
  list.push_front(10);
  list.push_front(20);
  EXPECT_EQ(list.front(), 20);
  list.pop_front();
  EXPECT_EQ(list.front(), 10);
  list.pop_front();
  EXPECT_TRUE(list.empty());
}

TEST(ListTest, InsertAndErase) {
  s21::List<int> list = {1, 2, 4};
  auto it = list.insert(list.begin(), 0);
  EXPECT_EQ(*it, 0);
  list.insert(list.end(), 5);
  EXPECT_EQ(list.back(), 5);
  list.erase(list.begin());
  EXPECT_EQ(list.front(), 1);
}

TEST(ListTest, Swap) {
  s21::List<int> list1 = {1, 2, 3};
  s21::List<int> list2 = {4, 5, 6};
  list1.swap(list2);
  EXPECT_EQ(list1.front(), 4);
  EXPECT_EQ(list2.front(), 1);
}

TEST(ListTest, Merge) {
  s21::List<int> list1 = {1, 3, 5};
  s21::List<int> list2 = {2, 4, 6};
  list1.merge(list2);
  EXPECT_EQ(list1.size(), 6);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, Splice) {
  s21::List<int> list1 = {1, 2};
  s21::List<int> list2 = {3, 4};
  list1.splice(list1.end(), list2);
  EXPECT_EQ(list1.size(), 4);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, Reverse) {
  s21::List<int> list = {1, 2, 3, 4};
  list.reverse();
  EXPECT_EQ(list.front(), 4);
  EXPECT_EQ(list.back(), 1);
}

TEST(ListTest, Unique) {
  s21::List<int> list = {1, 1, 2, 2, 3, 3};
  list.unique();
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, Sort) {
  s21::List<int> list = {3, 1, 2};
  list.sort();
  auto it = list.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
}

TEST(List_Insert_Many, Insert_Many) {
  s21::List<int> list_int = {1, 2, 6, 7, 8};
  list_int.insert_many(list_int.const_begin(), 3, 4, 5);

  EXPECT_EQ(list_int.size(), 8);
  auto it = list_int.begin();
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
}

TEST(List_Insert_Many, Insert_Many_Back) {
  s21::List<int> list_int = {1, 2, 6, 7, 8};
  list_int.insert_many_back(3, 4, 5);
  auto it = list_int.begin();

  EXPECT_EQ(list_int.size(), 8);
  for (int i = 0; i < 5; ++i) {
    ++it;
  }
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
}

TEST(List_Insert_Many, Insert_Many_Front) {
  s21::List<int> list_int = {1, 2, 6, 7, 8};
  list_int.insert_many_front(3, 4, 5);
  auto it = list_int.begin();

  EXPECT_EQ(list_int.size(), 8);
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
}
