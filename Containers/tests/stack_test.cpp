#include <gtest/gtest.h>

#include <stack>

#include "../containers/container_adaptors/stack/s21_stack.h"

using namespace s21;

TEST(StackTest, Constructor_default) {
  s21::stack<int> stack;
  std::stack<int> std_stack;
  EXPECT_EQ(stack.size(), std_stack.size());
}

TEST(StackTest, Constructor_initializer_list_1) {
  s21::stack<int> stack{1, 2, 4};
  EXPECT_EQ(stack.size(), 3);
  EXPECT_EQ(stack.top(), 4);
}

TEST(StackTest, Constructor_initializer_list_2) {
  std::initializer_list<int> b;
  s21::stack<int> stack{b};
  std::stack<int> std_stack{b};
  EXPECT_EQ(stack.size(), std_stack.size());
}

TEST(StackTest, Constructor_copy_1) {
  std::initializer_list<int> il1 = {1, 2, 3};
  s21::stack<int> stack{il1};
  s21::stack<int> stack_copy{stack};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_copy{std_stack};
  EXPECT_EQ(stack_copy.size(), std_stack_copy.size());
  EXPECT_EQ(stack_copy.top(), std_stack_copy.top());
}

TEST(StackTest, Constructor_move_1) {
  std::initializer_list<int> il1 = {1, 2, 3};
  s21::stack<int> stack{il1};
  s21::stack<int> stack_move{stack};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_move{std_stack};
  EXPECT_EQ(stack_move.size(), std_stack_move.size());
  EXPECT_EQ(stack_move.top(), std_stack_move.top());
}

TEST(StackTest, Opertator_move_1) {
  std::initializer_list<int> il1 = {1, 2, 3};
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::stack<int> stack{il1};
  s21::stack<int> stack_move{il2};
  stack = std::move(stack_move);

  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_move{il2};
  std_stack = std::move(std_stack_move);

  EXPECT_EQ(stack.size(), std_stack.size());
  EXPECT_EQ(stack.top(), std_stack.top());
}

TEST(StackTest, Opertator_move_2) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2 = {1, 2, 3};

  s21::stack<int> stack{il1};
  s21::stack<int> stack_move{il2};
  stack = std::move(stack_move);

  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_move{il2};
  std_stack = std::move(std_stack_move);

  EXPECT_EQ(stack.size(), std_stack.size());
  EXPECT_EQ(stack.top(), std_stack.top());
}

TEST(StackTest, Opertator_move_3) {
  std::initializer_list<int> il1;
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::stack<int> stack{il1};
  s21::stack<int> stack_move{il2};
  stack = std::move(stack_move);

  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_move{il2};
  std_stack = std::move(std_stack_move);

  EXPECT_EQ(stack.size(), std_stack.size());
  EXPECT_EQ(stack.top(), std_stack.top());
}

TEST(StackTest, Top_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  s21::stack<int> stack{il1};
  std::stack<int> std_stack{il1};
  EXPECT_EQ(stack.top(), std_stack.top());
}

TEST(StackTest, Empty_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  s21::stack<int> stack{il1};
  std::stack<int> std_stack{il1};
  EXPECT_EQ(stack.empty(), std_stack.empty());
}

TEST(StackTest, Empty_2) {
  std::initializer_list<int> il1;
  s21::stack<int> stack{il1};
  std::stack<int> std_stack{il1};
  EXPECT_EQ(stack.empty(), std_stack.empty());
}

TEST(StackTest, Size_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  s21::stack<int> stack{il1};
  std::stack<int> std_stack{il1};
  EXPECT_EQ(stack.size(), std_stack.size());
}

TEST(StackTest, Size_2) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  s21::stack<int> stack{il1};
  std::stack<int> std_stack{il1};
  EXPECT_EQ(stack.size(), std_stack.size());
}

TEST(StackTest, Push_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  s21::stack<int> stack{il1};
  std::stack<int> std_stack{il1};
  stack.push(1);
  std_stack.push(1);
  EXPECT_EQ(stack.size(), std_stack.size());
  EXPECT_EQ(stack.top(), std_stack.top());
}

TEST(StackTest, Push_2) {
  std::initializer_list<int> il1;
  s21::stack<int> stack{il1};
  std::stack<int> std_stack{il1};
  stack.push(1);
  std_stack.push(1);
  EXPECT_EQ(stack.size(), std_stack.size());
  EXPECT_EQ(stack.top(), std_stack.top());
}

TEST(StackTest, Pop_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  s21::stack<int> stack{il1};
  std::stack<int> std_stack{il1};
  stack.pop();
  std_stack.pop();
  EXPECT_EQ(stack.size(), std_stack.size());
  EXPECT_EQ(stack.top(), std_stack.top());
}

TEST(StackTest, Swap_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2 = {1, 2, 3};
  s21::stack<int> stack{il1};
  s21::stack<int> stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  stack.swap(stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(stack.size(), std_stack.size());
  EXPECT_EQ(stack.top(), std_stack.top());

  EXPECT_EQ(stack_swap.size(), std_stack_swap.size());
  EXPECT_EQ(stack_swap.top(), std_stack_swap.top());
}

TEST(StackTest, Swap_2) {
  std::initializer_list<int> il1 = {1, 2, 3};
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::stack<int> stack{il1};
  s21::stack<int> stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  stack.swap(stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(stack.size(), std_stack.size());
  EXPECT_EQ(stack.top(), std_stack.top());

  EXPECT_EQ(stack_swap.size(), std_stack_swap.size());
  EXPECT_EQ(stack_swap.top(), std_stack_swap.top());
}

TEST(StackTest, Swap_3) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2;

  s21::stack<int> stack{il1};
  s21::stack<int> stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  stack.swap(stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(stack.size(), std_stack.size());

  EXPECT_EQ(stack_swap.size(), std_stack_swap.size());
}

TEST(StackTest, Swap_4) {
  std::initializer_list<int> il1;
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::stack<int> stack{il1};
  s21::stack<int> stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  stack.swap(stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(stack.size(), std_stack.size());

  EXPECT_EQ(stack_swap.size(), std_stack_swap.size());
}

TEST(StackTest, Swap_5) {
  std::initializer_list<int> il1;
  std::initializer_list<int> il2;

  s21::stack<int> stack{il1};
  s21::stack<int> stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  stack.swap(stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(stack.size(), std_stack.size());

  EXPECT_EQ(stack_swap.size(), std_stack_swap.size());
}

TEST(StackTest, Swap_6) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::stack<int> stack{il1};
  s21::stack<int> stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  stack.swap(stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(stack.size(), std_stack.size());
  EXPECT_EQ(stack.top(), std_stack.top());

  EXPECT_EQ(stack_swap.size(), std_stack_swap.size());
  EXPECT_EQ(stack_swap.top(), std_stack_swap.top());
}

TEST(s21_stack, insert_manybackTest) {
  s21::stack<std::string> stack{"3", "2", "1"};
  stack.insert_many_back("2", "3", "4");
  s21::stack<std::string> test_stack{"3", "2", "1", "2", "3", "4"};
  EXPECT_EQ(stack, test_stack);
}

TEST(s21_stack, insert_manybackTest_) {
  s21::stack<std::string> stack{"3", "2", "1"};
  stack.insert_many_back();
  s21::stack<std::string> test_stack{"3", "2", "1"};
  EXPECT_EQ(stack, test_stack);
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
