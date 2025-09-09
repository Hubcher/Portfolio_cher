#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(SetTest, DefaultConstructor) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0U);
}

TEST(SetTest, InitializerListConstructor_1) {
  s21::set<int> s({1, 2, 3});
  ASSERT_FALSE(s.empty());
  ASSERT_EQ(3U, s.size());
}

TEST(SetTest, InitializerListConstructor_2) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_EQ(s.size(), 3U);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetTest, CopyConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(SetTest, MoveConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3U);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, AssignmentOperator) {
  s21::set<int> s1({1, 2, 3});
  s21::set<int> s2;
  s2 = s1;
  ASSERT_FALSE(s1.empty());
  ASSERT_FALSE(s2.empty());
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(SetTest, Begin) {
  s21::set<int> s{3, 5, 1, 4, 2};
  auto item = s.begin();
  ASSERT_EQ(*item, 1);
}

TEST(SetTest, End) {
  s21::set<int> s{3, 5, 1, 4, 2};
  auto item = s.end();
  ASSERT_EQ(item, nullptr);
}

TEST(SetTest, Empty) {
  s21::set<int> s1({1, 2, 3});
  s21::set<int> s2;
  ASSERT_FALSE(s1.empty());
  ASSERT_TRUE(s2.empty());
}

TEST(SetTest, Size) {
  s21::set<int> s1({1, 2, 3});
  s21::set<int> s2;
  EXPECT_EQ(s1.size(), 3U);
  EXPECT_EQ(s2.size(), 0U);
}

TEST(SetTest, MaxSize) {
  s21::set<int> s({1, 2, 3});
  EXPECT_EQ(s.max_size(), std::numeric_limits<size_t>::max());
}

TEST(SetTest, Clear_1) {
  s21::set<int> s{3, 5, 1, 4, 2};
  ASSERT_EQ(s.size(), 5U);
  s.clear();
  ASSERT_EQ(s.size(), 0U);
}

TEST(SetTest, Clear_2) {
  s21::set<int> s{3, 5, 1, 4, 2};
  s.clear();
  auto item = s.begin();
  ASSERT_EQ(item, nullptr);
}

TEST(SetTest, Insert) {
  s21::set<int> s;
  ASSERT_TRUE(s.empty());
  s.insert(1);
  EXPECT_EQ(s.size(), 1U);
  s.insert(5);
  EXPECT_EQ(s.size(), 2U);
  ASSERT_FALSE(s.empty());
  ASSERT_TRUE(s.contains(5));
}

TEST(SetTest, Erase) {
  s21::set<int> s{1, 2, 3, 4, 5};
  auto item = s.find(3);
  s.erase(item);
  EXPECT_EQ(s.size(), 4U);
  EXPECT_FALSE(s.contains(3));
}

TEST(SetTest, Swap) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{4, 5, 6};
  s1.swap(s2);
  EXPECT_EQ(s1.size(), 3U);
  EXPECT_EQ(s2.size(), 3U);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s1.contains(4));
}

TEST(SetTest, Merge) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {3, 4, 5};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 5U);
  EXPECT_EQ(s2.size(), 3U);
  ASSERT_TRUE(s1.contains(1));
  ASSERT_TRUE(s1.contains(2));
  ASSERT_TRUE(s1.contains(3));
  ASSERT_TRUE(s1.contains(4));
  ASSERT_TRUE(s1.contains(5));
}

TEST(SetTest, Find) {
  s21::set<int> s{1, 2, 3};
  auto item1 = s.find(2);
  EXPECT_EQ(*item1, 2);
  auto item2 = s.find(4);
  EXPECT_EQ(item2, s.end());
}

TEST(SetTest, InsertMany_1) {
  s21::set<int> s;
  auto v = s.insert_many(1, 2);
  EXPECT_EQ(s.size(), 2U);
  EXPECT_TRUE(v[0].second);
  EXPECT_TRUE(v[1].second);
}

TEST(SetTest, InsertMany_2) {
  s21::set<int> s{1, 2, 3};
  auto v = s.insert_many(1, 4);
  EXPECT_EQ(s.size(), 4U);
  EXPECT_FALSE(v[0].second);
  EXPECT_TRUE(v[1].second);
}

TEST(SetTest, InsertMany_3) {
  s21::set<int> s;
  auto v = s.insert_many(0, 0);
  EXPECT_EQ(v.size(), 2U);
  EXPECT_TRUE(v[0].second);
  EXPECT_FALSE(v[1].second);
}
