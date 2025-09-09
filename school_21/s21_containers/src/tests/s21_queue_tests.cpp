#include <gtest/gtest.h>

#include <queue>

#include "../s21_containers.h"

template <typename value_type>
bool compare_queues(s21::queue<value_type> s21_queue,
                    std::queue<value_type> std_queue) {
  bool result = true;
  if (s21_queue.size() == std_queue.size()) {
    while (!s21_queue.empty() && !std_queue.empty()) {
      if (s21_queue.front() != std_queue.front()) {
        result = false;
        break;
      }
      s21_queue.pop();
      std_queue.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(QueueTest, CompareQueues_1) {
  s21::queue<int> s21_queue{1, 3, 10, -5, 20};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(3);
  std_queue.push(10);
  std_queue.push(-5);
  std_queue.push(20);
  EXPECT_TRUE(compare_queues(s21_queue, std_queue));
  std_queue.push(20);
  EXPECT_FALSE(compare_queues(s21_queue, std_queue));
}

TEST(QueueTest, CompareQueues_2) {
  s21::queue<int> s21_queue{1, 3, 10, -5, 20};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(3);
  std_queue.push(10);
  std_queue.push(-5);
  std_queue.push(100);
  EXPECT_FALSE(compare_queues(s21_queue, std_queue));
}

TEST(QueueTest, DefaultConstructor_1) {
  s21::queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0U);
}

TEST(QueueTest, DefaultConstructor_2) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(s21_queue.size(), 0U);
  EXPECT_TRUE(s21_queue.empty());
  EXPECT_TRUE(compare_queues(s21_queue, std_queue));
}

TEST(QueueTest, InitializerListConstructor_1) {
  s21::queue<int> q{1, 2, 3};
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 3U);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, InitializerqueueConstructor_2) {
  s21::queue<int> s21_queue{1, 2, 3, 7, 9};
  std::initializer_list<int> i = {1, 2, 3, 7, 9};
  std::queue<int> std_queue{i};
  EXPECT_TRUE(compare_queues(s21_queue, std_queue));
}

TEST(QueueTest, InitializerqueueConstructor_3) {
  std::initializer_list<int> b;
  s21::queue<int> s21_queue{b};
  std::queue<int> std_queue{b};
  EXPECT_TRUE(compare_queues(s21_queue, std_queue));
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> s21_queue{1, 2, 3, 7, 9};
  s21::queue<int> s21_queue_copy(s21_queue);
  std::initializer_list<int> i = {1, 2, 3, 7, 9};
  std::queue<int> std_queue{i};
  std::queue<int> std_queue_copy(std_queue);
  EXPECT_TRUE(compare_queues(s21_queue_copy, std_queue_copy));
}

TEST(QueueTest, CopyConstructorEmpty) {
  s21::queue<int> s21_queue;
  s21::queue<int> s21_queue_copy(s21_queue);
  std::queue<int> std_queue;
  std::queue<int> std_queue_copy(std_queue);
  EXPECT_TRUE(compare_queues(s21_queue_copy, std_queue_copy));
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> s21_queue{1, 2, 3, 7, 20};
  s21::queue<int> s21_queue_copy(s21_queue);
  s21::queue<int> s21_queue_move(std::move(s21_queue));
  std::initializer_list<int> i = {1, 2, 3, 7, 20};
  std::queue<int> std_queue{i};
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move(std::move(std_queue));
  EXPECT_TRUE(compare_queues(s21_queue_copy, std_queue_copy));
}

TEST(QueueTest, MoveConstructorEmpty) {
  s21::queue<int> s21_queue;
  s21::queue<int> s21_queue_copy(s21_queue);
  s21::queue<int> s21_queue_move(std::move(s21_queue));
  std::queue<int> std_queue;
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move(std::move(std_queue));
  EXPECT_TRUE(compare_queues(s21_queue_copy, std_queue_copy));
}

TEST(QueueTest, MoveAssignmentOperator) {
  s21::queue<int> s21_queue{1, 2, 3, 7, 20};
  s21::queue<int> s21_queue_copy(s21_queue);
  s21::queue<int> s21_queue_move = std::move(s21_queue);
  std::initializer_list<int> i = {1, 2, 3, 7, 20};
  std::queue<int> std_queue{i};
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move = std::move(std_queue);
  EXPECT_TRUE(compare_queues(s21_queue_move, std_queue_move));
}

TEST(QueueTest, MoveAssignmentOperatorEmpty) {
  s21::queue<int> s21_queue;
  s21::queue<int> s21_queue_copy(s21_queue);
  s21::queue<int> s21_queue_move = std::move(s21_queue);
  std::queue<int> std_queue;
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move = std::move(std_queue);
  EXPECT_TRUE(compare_queues(s21_queue_move, std_queue_move));
}

TEST(QueueTest, Front_1) {
  s21::queue<int> q{1, 2, 3};
  EXPECT_EQ(q.front(), 1);
  q.pop();
  EXPECT_EQ(q.front(), 2);
}

TEST(QueueTest, Front_2) {
  s21::queue<int> s21_queue{99, 2, 3, 4, 5};
  std::initializer_list<int> i = {99, 1, 3, 7, 20};
  std::queue<int> std_queue{i};
  EXPECT_EQ(s21_queue.front(), std_queue.front());
}

TEST(QueueTest, Back_1) {
  s21::queue<int> q{1, 2, 3};
  EXPECT_EQ(q.back(), 3);
  q.push(4);
  EXPECT_EQ(q.back(), 4);
}

TEST(QueueTest, Back_2) {
  s21::queue<int> s21_queue{1, 2, 3, 3, 4, 99};
  std::initializer_list<int> i = {99, 1, 3, 5, 4, 7, 99};
  std::queue<int> std_queue{i};
  EXPECT_EQ(s21_queue.back(), std_queue.back());
}

TEST(QueueTest, Empty) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
  s21_queue.push(2354);
  std_queue.push(2354);
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(QueueTest, Size) {
  s21::queue<int> s21_queue{1, 2, 3, 4, 5, 6, 7, 8};
  std::initializer_list<int> i = {1, 2, 3, 4, 5, 6, 7, 8};
  std::queue<int> std_queue{i};
  EXPECT_EQ(s21_queue.size(), std_queue.size());
}

TEST(QueueTest, Clear_1) {
  s21::queue<int> q{1, 2, 3};
  q.clear();
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0U);
}

TEST(QueueTest, Push) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue.push(627);
  std_queue.push(627);
  s21_queue.push(2354);
  std_queue.push(2354);
  EXPECT_TRUE(compare_queues(s21_queue, std_queue));
}

TEST(QueueTest, Pop) {
  s21::queue<int> s21_queue{1, 2, 3, 4, 5, 6, 7, 8};
  std::initializer_list<int> i = {1, 2, 3, 4, 5, 6, 7, 8};
  std::queue<int> std_queue{i};
  s21_queue.pop();
  s21_queue.pop();
  std_queue.pop();
  std_queue.pop();
  EXPECT_TRUE(compare_queues(s21_queue, std_queue));
  EXPECT_EQ(s21_queue.front(), 3);
}

TEST(QueueTest, Swap_1) {
  s21::queue<int> s21_queue1{1, 2, 3, 4, 5};
  s21::queue<int> s21_queue2{6, 7, 8, 9, 10, 11};
  s21_queue1.swap(s21_queue2);

  std::initializer_list<int> i1 = {1, 2, 3, 4, 5};
  std::initializer_list<int> i2 = {6, 7, 8, 9, 10, 11};
  std::queue<int> std_queue1{i1};
  std::queue<int> std_queue2{i2};
  std_queue1.swap(std_queue2);

  EXPECT_TRUE(compare_queues(s21_queue1, std_queue1));
  EXPECT_TRUE(compare_queues(s21_queue2, std_queue2));
}

TEST(QueueTest, Swap_2) {
  s21::queue<int> s21_queue1{1, 2, 99, 4, 242};
  s21::queue<int> s21_queue2;
  s21_queue1.swap(s21_queue2);

  std::initializer_list<int> i = {1, 2, 99, 4, 242};
  std::queue<int> std_queue1{i};
  std::queue<int> std_queue2;
  std_queue1.swap(std_queue2);

  EXPECT_TRUE(compare_queues(s21_queue1, std_queue1));
  EXPECT_TRUE(compare_queues(s21_queue2, std_queue2));
}

TEST(QueueTest, InsertManyBack_1) {
  s21::queue<int> q;
  q.insert_many_back(10);
  EXPECT_EQ(q.size(), 1U);
  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.back(), 10);
}

TEST(QueueTest, InsertManyBack_2) {
  s21::queue<int> q;
  q.insert_many_back(1, 2, 3, 4, 5);
  EXPECT_EQ(q.size(), 5U);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 5);
}

TEST(QueueTest, InsertManyBack_3) {
  s21::queue<int> q;
  q.push(100);
  EXPECT_EQ(q.size(), 1U);
  q.insert_many_back(1, 2, 3);
  EXPECT_EQ(q.size(), 4U);
  EXPECT_EQ(q.front(), 100);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, InsertManyBack_4) {
  s21::queue<int> q;
  q.insert_many_back(1, 2, 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
  q.pop();
  EXPECT_EQ(q.front(), 2);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, InsertManyBack_5) {
  s21::queue<int> q;
  q.insert_many_back(1, 2, 3);
  q.pop();
  EXPECT_EQ(q.size(), 2U);
  EXPECT_EQ(q.front(), 2);
  q.insert_many_back(4, 5);
  EXPECT_EQ(q.size(), 4U);
  EXPECT_EQ(q.front(), 2);
  EXPECT_EQ(q.back(), 5);
}