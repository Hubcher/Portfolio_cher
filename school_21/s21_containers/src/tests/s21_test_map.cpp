#include <gtest/gtest.h>

#include "../containers/s21_map.h"

TEST(MapTest, DefaultConstructor) {
  Map<int, std::string> map;
  EXPECT_TRUE(map.empty());
  EXPECT_EQ(map.size(), 0);
}

TEST(MapTest, InitializerListConstructor) {
  Map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map.at(2), "two");
  EXPECT_EQ(map.at(3), "three");
}

TEST(MapTest, ClearMethod) {
  Map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  map.clear();
  EXPECT_TRUE(map.empty());
  EXPECT_EQ(map.size(), 0);
}

TEST(MapTest, MergeMethod) {
  Map<int, std::string> map1 = {{1, "one"}, {2, "two"}};
  Map<int, std::string> map2 = {{2, "zwei"}, {3, "three"}};
  map1.merge(map2);

  EXPECT_EQ(map1.size(), 3);
  EXPECT_TRUE(map1.contains(1));
  EXPECT_TRUE(map1.contains(2));
  EXPECT_TRUE(map1.contains(3));
  EXPECT_EQ(map2.size(), 2);
}

TEST(MapTest, ContainsMethod) {
  Map<int, std::string> map = {{1, "one"}, {2, "two"}};
  EXPECT_TRUE(map.contains(1));
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}

TEST(MapTest, CopyAndMoveConstructors) {
  Map<int, std::string> map1 = {{1, "one"}, {2, "two"}};
  Map<int, std::string> map2(map1);
  EXPECT_EQ(map2.size(), 2);
  EXPECT_EQ(map2.at(1), "one");

  Map<int, std::string> map3(std::move(map1));
  EXPECT_EQ(map3.at(1), "one");
  EXPECT_TRUE(map1.empty());
}

TEST(MapTest, MoveAssignmentOperator) {
  Map<int, std::string> map1 = {{1, "one"}, {2, "two"}};
  Map<int, std::string> map2;
  map2 = std::move(map1);
  EXPECT_EQ(map2.size(), 2);
  EXPECT_EQ(map2.at(1), "one");
  EXPECT_TRUE(map1.empty());
}
