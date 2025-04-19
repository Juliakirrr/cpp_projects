#include <gtest/gtest.h>

#include <set>

#include "../containers/associative_containers/set/s21_set.h"

using namespace s21;

TEST(SetTest, constructor_default) {
  set<int> s21_array;
  std::set<int> std_array;
  EXPECT_EQ(s21_array.empty(), std_array.empty());
}

TEST(SetTest, constructor_list) {
  set<int> mySet = {1, 2, 5};
  std::set<int> std_Set = {1, 2, 5};
  EXPECT_EQ(mySet.size(), std_Set.size());
}

TEST(SetTest, constructor_copy) {
  set<int> mySet = {1, 2, 5};
  set<int> copy(mySet);
  std::set<int> std_Set = {1, 2, 5};
  std::set<int> std_copy(std_Set);
  EXPECT_EQ(copy.size(), std_copy.size());
}

TEST(SetTest, constructor_move) {
  set<int> mySet = {1, 2, 5, 10};
  set<int> copy(std::move(mySet));

  std::set<int> std_Set = {1, 2, 5, 10};
  std::set<int> std_copy(std::move(std_Set));

  EXPECT_EQ(copy.size(), std_copy.size());
  EXPECT_EQ(mySet.size(), 0);
  EXPECT_EQ(std_Set.size(), 0);
}

TEST(SetTest, constructor_move_eq) {
  set<int> mySet = {1, 2, 5};
  set<int> copy = {54, 5, 12, 16};
  copy = (std::move(mySet));

  std::set<int> std_Set = {1, 2, 5};
  std::set<int> std_copy = {54, 5, 12, 16};
  std_copy = (std::move(std_Set));

  EXPECT_EQ(copy.size(), std_copy.size());
  EXPECT_EQ(mySet.size(), std_Set.size());
}

TEST(SetTest, merge_fn) {
  set<int> mySet = {1, 2, 5};
  set<int> mySet2 = {54, 5, 12, 16};
  mySet.merge(mySet2);

  std::set<int> std_Set = {1, 2, 5};
  std::set<int> std_Set2 = {54, 5, 12, 16};
  std_Set.merge(std_Set2);

  EXPECT_EQ(mySet.size(), std_Set.size());
}

TEST(SetTest, contains_fn) {
  set<int> mySet = {1, 2, 5};
  set<int> mySet2 = {54, 5, 12, 16};
  mySet.merge(mySet2);

  EXPECT_EQ(mySet.contains(54), true);
  EXPECT_EQ(mySet.contains(10), false);
}

TEST(SetTest, clear_fn) {
  set<int> mySet = {1, 2, 5};
  mySet.clear();
  std::set<int> std_Set = {1, 2, 5};
  std_Set.clear();
  EXPECT_EQ(mySet.size(), std_Set.size());
}

TEST(SetTest, fn_erase) {
  set<int> mySet = {1, 2, 5, 6, 7, 10, 11};

  set<int>::iterator myit = mySet.begin();
  mySet.erase(myit);

  EXPECT_EQ(mySet.contains(1), false);
}

TEST(SetTest, iterator_test) {
  set<int> mySet = {1, 2, 5, 6, 7, 10, 11};

  set<int>::iterator myit = mySet.begin();
  size_t sizeSet = 0;
  while (myit != mySet.end()) {
    ++myit;
    sizeSet++;
  }
  EXPECT_EQ(mySet.size(), sizeSet);
}

TEST(SetTest, iterator_test_1) {
  set<int> mySet = {1, 2, 5, 6, 7, 10, 11};

  set<int>::iterator myit = mySet.end();
  size_t sizeSet = 0;
  while (myit != mySet.begin()) {
    --myit;
    sizeSet++;
  }
  EXPECT_EQ(mySet.size(), sizeSet);
}

TEST(SetTest, insert_fn) {
  set<int> mySet = {1, 2, 5};
  mySet.insert(10);

  EXPECT_EQ(mySet.contains(10), true);
}

TEST(SetTest, insert_fn_1) {
  set<int> mySet = {1, 2, 5};
  mySet.insert(10);

  EXPECT_EQ((*mySet.find(10)), 10);
}

TEST(SetTest, insert_many) {
  set<int> myMap = {1, 2, 5, 10};
  vector<std::pair<set<int>::iterator, bool>> aaa =
      myMap.insert_many(11, 12, 10);

  EXPECT_EQ((*aaa[0].first), 11);
  EXPECT_EQ(aaa[0].second, true);
  EXPECT_EQ(aaa[2].second, false);

  EXPECT_EQ(myMap.contains(12), true);
  EXPECT_EQ(myMap.contains(11), true);
}

TEST(MulSetTest, insert_mnogo) {
  set<int> myMap;
  for (int i = 0; i < 10000; i++) {
        myMap.insert(i);
    }
  for (int i = 300; i < 800; i++) {
        myMap.erase(myMap.find(i));
    }
  for (int i = 5000; i < 15000; i++) {
        myMap.insert(i);
    }
  EXPECT_EQ(myMap.size(), 14500);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
