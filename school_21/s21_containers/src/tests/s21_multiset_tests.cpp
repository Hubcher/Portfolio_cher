#include <gtest/gtest.h>

#include "../s21_containers.h"
#include "../s21_containersplus.h"

TEST(MultisetTest, DefaultConstructor) {
  s21::multiset<int> miltiset;
  ASSERT_TRUE(miltiset.empty());
  EXPECT_EQ(miltiset.size(), 0U);
}

TEST(MultisetTest, InitializerListConstructor) {
  s21::multiset<int> ms({1, 2, 3, 2, 4, 2});
  ASSERT_FALSE(ms.empty());
  ASSERT_EQ(6U, ms.size());
}

TEST(MultisetTest, CopyConstructor) {
  s21::multiset<int> ms1({1, 2, 3, 2});
  s21::multiset<int> ms2(ms1);
  ASSERT_FALSE(ms1.empty());
  ASSERT_FALSE(ms2.empty());
  ASSERT_EQ(ms1.size(), ms2.size());
}

TEST(MultisetTest, MoveConstructor) {
  s21::multiset<int> ms1({1, 2, 3});
  s21::multiset<int> ms2(std::move(ms1));
  ASSERT_TRUE(ms1.empty());
  ASSERT_FALSE(ms2.empty());
  ASSERT_EQ(3U, ms2.size());
  EXPECT_EQ(ms1.size(), 0U);
}

TEST(MultisetTest, AssignmentOperator_1) {
  s21::multiset<int> ms1({1, 2, 3});
  s21::multiset<int> ms2;
  ms2 = ms1;
  ASSERT_FALSE(ms1.empty());
  ASSERT_FALSE(ms2.empty());
  ASSERT_EQ(ms1.size(), ms2.size());
}

TEST(MultisetTest, AssignmentOperator_2) {
  s21::multiset<int> ms1({1, 2, 3});
  s21::multiset<int> ms2;
  ms2 = std::move(ms1);
  ASSERT_TRUE(ms1.empty());
  ASSERT_FALSE(ms2.empty());
  ASSERT_EQ(3U, ms2.size());
}

TEST(MultisetTest, Begin) {
  s21::multiset<int> ms({1, 2, 3, 1, 5});
  s21::multiset<int>::iterator ms_begin;
  ms_begin = ms.begin();
  s21::set<int>::iterator ms_find;
  ms_find = ms.find(1);
  ASSERT_TRUE(ms_begin == ms_find);
  ASSERT_EQ(ms_find, ms_begin);
}

TEST(MultisetTest, End) {
  s21::multiset<int> ms({1, 2, 3, 1, 5});
  auto item = ms.end();
  ASSERT_EQ(item, nullptr);
}

TEST(MultisetTest, Empty) {
  s21::multiset<int> ms1({1, 2, 3});
  s21::multiset<int> ms2;
  ASSERT_FALSE(ms1.empty());
  ASSERT_TRUE(ms2.empty());
}

TEST(MultisetTest, Size) {
  s21::multiset<int> ms1({1, 2, 3});
  s21::multiset<int> ms2;
  EXPECT_EQ(ms1.size(), 3U);
  EXPECT_EQ(ms2.size(), 0U);
}

TEST(MultisetTest, MaxSize) {
  s21::multiset<int> ms({1, 2, 3});
  EXPECT_EQ(ms.max_size(), std::numeric_limits<size_t>::max());
}

TEST(MultisetTest, Clear_1) {
  s21::multiset<int> ms({1, 2, 3});
  ASSERT_FALSE(ms.empty());
  ms.clear();
  ASSERT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0U);
}

TEST(MultisetTest, Clear_2) {
  s21::multiset<int> ms({1, 2, 3});
  ms.clear();
  auto item = ms.begin();
  ASSERT_EQ(item, nullptr);
}

TEST(MultisetTest, Insert_1) {
  s21::multiset<int> ms;
  ASSERT_TRUE(ms.empty());
  ms.insert(1);
  EXPECT_EQ(ms.size(), 1U);
  ms.insert(5);
  EXPECT_EQ(ms.size(), 2U);
  ms.insert(5);
  EXPECT_EQ(ms.size(), 3U);
  ASSERT_FALSE(ms.empty());
  ASSERT_TRUE(ms.contains(5));
}

TEST(MultisetTest, Insert_2) {
  s21::multiset<int> ms;
  ASSERT_TRUE(ms.empty());
  ms.insert(10);
  EXPECT_EQ(ms.size(), 1U);
  ms.insert(5);
  EXPECT_EQ(ms.size(), 2U);
  ASSERT_FALSE(ms.empty());
  ASSERT_TRUE(ms.contains(10));
}

TEST(MultisetTest, Erase) {
  s21::multiset<int> ms = {1, 2, 3, 2};
  EXPECT_EQ(ms.size(), 4U);
  auto item = ms.find(2);
  ms.erase(item);
  EXPECT_EQ(ms.size(), 3U);
  ASSERT_TRUE(ms.contains(2));
  item = ms.end();
  ASSERT_ANY_THROW(ms.erase(item));
}

TEST(MultisetTest, Swap) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2 = {4, 5, 6};
  ms1.swap(ms2);
  EXPECT_EQ(ms1.size(), 3U);
  EXPECT_EQ(ms2.size(), 3U);
  ASSERT_TRUE(ms1.contains(4));
  ASSERT_TRUE(ms1.contains(5));
  ASSERT_TRUE(ms1.contains(6));
  ASSERT_TRUE(ms2.contains(1));
  ASSERT_TRUE(ms2.contains(2));
  ASSERT_TRUE(ms2.contains(3));
}

TEST(MultisetTest, Merge) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2 = {3, 4, 5};
  ms1.merge(ms2);
  EXPECT_EQ(ms1.size(), 6U);
  EXPECT_EQ(ms2.size(), 0U);
  ASSERT_TRUE(ms1.contains(1));
  ASSERT_TRUE(ms1.contains(2));
  ASSERT_TRUE(ms1.contains(3));
  ASSERT_TRUE(ms1.contains(4));
  ASSERT_TRUE(ms1.contains(5));
}

TEST(MultisetTest, Count) {
  s21::multiset<int> ms = {1, 2, 3, 2, 3, 7, 2};
  EXPECT_EQ(ms.size(), 7U);
  EXPECT_EQ(ms.count(2), 3U);
  EXPECT_EQ(ms.count(3), 2U);
  EXPECT_EQ(ms.count(10), 0U);
}

TEST(MultisetTest, Find) {
  s21::multiset<int> ms = {1, 2, 3, 2, 3, 7, 2};
  auto item = ms.find(2);
  EXPECT_EQ(*item, 2);
}

TEST(MultisetTest, EqualRange) {
  s21::multiset<int> ms = {1, 2, 3, 3, 7};
  EXPECT_EQ(ms.size(), 5U);
  auto range = ms.equal_range(3);
  ASSERT_EQ(*range.first, 3);
  ASSERT_EQ(*range.second, 7);
  range = ms.equal_range(7);
  ASSERT_EQ(*range.first, 7);
  ASSERT_EQ(range.second, ms.end());
  range = ms.equal_range(8);
  ASSERT_EQ(range.first, ms.end());
  ASSERT_EQ(range.second, ms.end());
}

TEST(MultisetTest, LowerBound) {
  s21::multiset<int> ms = {1, 2, 3, 3, 7};
  EXPECT_EQ(ms.size(), 5U);
  auto item = ms.lower_bound(3);
  ASSERT_EQ(*item, 3);
  ++item;
  ASSERT_EQ(*item, 3);
  ++item;
  ASSERT_EQ(*item, 7);
}

TEST(MultisetTest, UpperBound) {
  s21::multiset<int> ms = {1, 7, 3, 3, 2};
  EXPECT_EQ(ms.size(), 5U);
  auto item = ms.upper_bound(3);
  ASSERT_EQ(*item, 7);
}

TEST(MultisetTest, InsertMany_1) {
  s21::multiset<int> ms;
  ASSERT_TRUE(ms.empty());
  auto v = ms.insert_many(ms, 1, 2, 3, 4, 4, 4);
  EXPECT_EQ(ms.size(), 6U);
  EXPECT_EQ(*v[0], 1);
  EXPECT_EQ(*v[1], 2);
  EXPECT_EQ(*v[2], 3);
  EXPECT_EQ(*v[3], 4);
  EXPECT_EQ(*v[4], 4);
  EXPECT_EQ(*v[5], 4);
}

TEST(MultisetTest, InsertMany_2) {
  s21::multiset<int> ms;
  auto v = ms.insert_many(ms);
  EXPECT_EQ(ms.size(), 0U);
}