#include <gtest/gtest.h>

#include <set>

#include "../containers/associative_containers/multiset/s21_multiset.h"

using namespace s21;

TEST(MulSetTest, constructor_default) {
  multiset<int> s21_array;
  std::multiset<int> std_array;
  EXPECT_EQ(s21_array.empty(), std_array.empty());
}

TEST(MulSetTest, constructor_list) {
  multiset<int> myMulSet = {1, 2, 5};
  std::multiset<int> std_MulSet = {1, 2, 5};
  EXPECT_EQ(myMulSet.size(), std_MulSet.size());
}

TEST(MulSetTest, constructor_copy) {
  multiset<int> myMulSet = {1, 2, 5};
  multiset<int> copy(myMulSet);
  std::multiset<int> std_MulSet = {1, 2, 5};
  std::multiset<int> std_copy(std_MulSet);
  EXPECT_EQ(copy.size(), std_copy.size());
}

TEST(MulSetTest, constructor_move) {
  multiset<int> myMulSet = {1, 2, 5, 10};
  multiset<int> copy(std::move(myMulSet));

  std::multiset<int> std_MulSet = {1, 2, 5, 10};
  std::multiset<int> std_copy(std::move(std_MulSet));

  EXPECT_EQ(copy.size(), std_copy.size());
  EXPECT_EQ(myMulSet.size(), 0);
  EXPECT_EQ(std_MulSet.size(), 0);
}

TEST(MulSetTest, constructor_move_eq) {
  multiset<int> myMulSet = {1, 2, 5};
  multiset<int> copy = {54, 5, 12, 16};
  copy = (std::move(myMulSet));

  std::multiset<int> std_MulSet = {1, 2, 5};
  std::multiset<int> std_copy = {54, 5, 12, 16};
  std_copy = (std::move(std_MulSet));

  EXPECT_EQ(copy.size(), std_copy.size());
  EXPECT_EQ(myMulSet.size(), std_MulSet.size());
}


TEST(MulSetTest, merge_fn) {
  multiset<int> myMulSet = {1, 2, 5};
  multiset<int> myMulSet2 = {54, 5, 12, 16};
  myMulSet.merge(myMulSet2);

  std::multiset<int> std_MulSet = {1, 2, 5};
  std::multiset<int> std_MulSet2 = {54, 5, 12, 16};
  std_MulSet.merge(std_MulSet2);

  EXPECT_EQ(myMulSet.size(), std_MulSet.size());
}

TEST(MulSetTest, contains_fn) {
  multiset<int> myMulSet = {1, 2, 5};
  multiset<int> myMulSet2 = {54, 5, 12, 16};
  myMulSet.merge(myMulSet2);

  EXPECT_EQ(myMulSet.contains(54), true);
  EXPECT_EQ(myMulSet.contains(10), false);
}

TEST(MulSetTest, clear_fn) {
  multiset<int> myMulSet = {1, 2, 5};
  myMulSet.clear();
  std::multiset<int> std_MulSet = {1, 2, 5};
  std_MulSet.clear();
  EXPECT_EQ(myMulSet.size(), std_MulSet.size());
}

TEST(MulSetTest, fn_erase) {
  multiset<int> myMulSet = {1, 2, 5, 6, 7, 10, 11};

  multiset<int>::iterator myit = myMulSet.begin();
  myMulSet.erase(myit);

  EXPECT_EQ(myMulSet.contains(1), false);
}

TEST(MulSetTest, iterator_test) {
  multiset<int> myMulSet = {1, 2, 5, 6, 7, 10, 11};

  multiset<int>::iterator myit = myMulSet.begin();
  size_t sizeMulSet = 0;
  while (myit != myMulSet.end()) {
    ++myit;
    sizeMulSet++;
  }
  EXPECT_EQ(myMulSet.size(), sizeMulSet);
}

TEST(MulSetTest, iterator_test_1) {
  multiset<int> myMulSet = {1, 2, 5, 6, 7, 10, 11};

  multiset<int>::iterator myit = myMulSet.end();
  size_t sizeMulSet = 0;
  while (myit != myMulSet.begin()) {
    --myit;
    sizeMulSet++;
  }
  EXPECT_EQ(myMulSet.size(), sizeMulSet);
}

TEST(MulSetTest, insert_fn) {
  multiset<int> myMulSet = {1, 2, 5};
  myMulSet.insert(10);

  EXPECT_EQ(myMulSet.contains(10), true);
}

TEST(MulSetTest, insert_fn_1) {
  multiset<int> myMulSet = {1, 2, 5};
  myMulSet.insert(10);

  EXPECT_EQ((*myMulSet.find(10)), 10);
}

TEST(MulSetTest, count_test) {
  multiset<int> myMulSet = {1, 2, 5, 5, 5, 1, 4, 9, 8};

  std::multiset<int> std_MulSet = {1, 2, 5, 5, 5, 1, 4, 9, 8};

  EXPECT_EQ(myMulSet.count(5), std_MulSet.count(5));
}

TEST(MulSetTest, equal_range_test) {
  multiset<int> myMulSet = {1, 2, 5, 5, 5, 1, 4, 9, 8};
  std::pair<multiset<int>::iterator, multiset<int>::iterator> aaa =
      myMulSet.equal_range(5);
  size_t count = 0;
  if ((*aaa.first) == 5) {
    count++;
    while (aaa.first != aaa.second) {
      count++;
      ++aaa.first;
    }
  }
  EXPECT_EQ(myMulSet.count(5), count);
}

TEST(MulSetTest, lower_bound_test) {
  multiset<int> myMulSet = {1, 2, 5, 5, 5, 1, 4, 9, 8};
  multiset<int>::iterator aaa = myMulSet.lower_bound(5);

  EXPECT_EQ((*aaa), 5);
}

TEST(MulSetTest, upper_bound_test) {
  multiset<int> myMulSet = {1, 2, 5, 5, 5, 1, 4, 9, 8};
  multiset<int>::iterator aaa = myMulSet.upper_bound(5);

  EXPECT_EQ((*aaa), 8);
}

TEST(MapTest, insert_many) {
  multiset<int> myMap = {1, 2, 5, 10};
  vector<multiset<int>::iterator> aaa = myMap.insert_many(11, 12, 10);

  EXPECT_EQ((*aaa[0]), 11);
  EXPECT_EQ((*aaa[2]), 10);

  EXPECT_EQ(myMap.contains(12), true);
  EXPECT_EQ(myMap.contains(11), true);
}


TEST(MulSetTest, insert_mnogo) {
  multiset<int> myMap;
  for (int i = 0; i < 10000; i++) {
        myMap.insert(i);
    }
  for (int i = 300; i < 800; i++) {
        myMap.erase(myMap.find(i));
    }
  for (int i = 5000; i < 15000; i++) {
        myMap.insert(i);
    }
  EXPECT_EQ(myMap.size(), 19500);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
