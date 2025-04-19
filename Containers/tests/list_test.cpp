#include <gtest/gtest.h>

#include <cmath>
#include <list>
#include <string>

#include "../containers/sequence_containers/list/s21_list.h"

using namespace s21;

TEST(listTest, DefaultConstructor) {
  list<int> list;
  std::list<int> l1;
  EXPECT_EQ(list.max_size(), l1.max_size());
  EXPECT_EQ(list.size(), l1.size());
  EXPECT_EQ(list.empty(), l1.empty());
}

TEST(listTest, DefaultConstructorIterator) {
  list<int> list;
  std::list<int> l1;
  auto start = list.begin();
  auto start1 = l1.begin();
  EXPECT_EQ(*start, *start1);
}

TEST(list, ConstructorWithParameters) {
  list<std::string> list(10);
  std::list<std::string> l1(10);
  EXPECT_EQ(list.size(), l1.size());
}

TEST(list, ConstructorWithInitializerList) {
  list<std::string> list{"10", "10", "10", "10"};
  std::list<std::string> list_or{"10", "10", "10", "10"};

  EXPECT_EQ(list.size(), list_or.size());
  for (auto i = list.begin(), j = list.end(); i != j; ++i) {
    EXPECT_EQ(*i, "10");
  }
}

TEST(list, CopyConstructor) {
  list<std::string> list{"10", "20", "30", "40"};
  s21::list<std::string> list1(list);
  auto other_ptr = list1.begin();
  EXPECT_EQ(list.size(), list1.size());
  for (auto i = list.begin(), j = list.end(); i != j; ++i, ++other_ptr) {
    EXPECT_EQ(*i, *other_ptr);
  }
}

TEST(list, MoveConstructor) {
  list<std::string> list{"10", "20", "30", "40"};
  s21::list<std::string> list1(std::move(list));
  std::list<std::string> list2{"10", "20", "30", "40"};
  std::list<std::string> list3(std::move(list2));
  EXPECT_EQ(list1.size(), list3.size());
  auto itt = list3.begin();
  for (auto it = list1.begin(); it != list1.end(); ++it, ++itt)
    EXPECT_EQ(*it, *itt);
}

TEST(list, MoveOperator) {
  list<std::string> list{"10", "20", "30", "40"};
  s21::list<std::string> list1 = std::move(list);
  std::list<std::string> list2{"10", "20", "30", "40"};
  std::list<std::string> list3 = std::move(list2);
  EXPECT_EQ(list1.size(), list3.size());
  auto itt = list3.begin();
  for (auto it = list1.begin(); it != list1.end(); ++it, ++itt)
    EXPECT_EQ(*it, *itt);
}

TEST(list, emplaceBack) {
  list<int> list;
  std::list<int> list1;
  list.emplace_back(10);
  list.emplace_back(20);
  list.emplace_back(30);
  list1.emplace_back(10);
  list1.emplace_back(20);
  list1.emplace_back(30);
  EXPECT_EQ(list.size(), list1.size());
}

TEST(list, emplaceBackString) {
  list<std::string> list;
  std::list<std::string> list1;
  list.emplace_back("10");
  list.emplace_back("20");
  list.emplace_back("30");
  list1.emplace_back("10");
  list1.emplace_back("20");
  list1.emplace_back("30");
  EXPECT_EQ(list.size(), list1.size());
}

TEST(list, pop_back) {
  list<std::string> list;
  std::list<std::string> list1;
  list.emplace_back("10");
  list.emplace_back("20");
  list.emplace_back("30");
  list1.emplace_back("10");
  list1.emplace_back("20");
  list1.emplace_back("30");
  list.pop_back();
  list1.pop_back();
  EXPECT_EQ(list.size(), list1.size());
}

TEST(list, pop_back_all) {
  list<std::string> list;
  std::list<std::string> list1;
  list.emplace_back("10");
  list.emplace_back("20");
  list.emplace_back("30");
  list1.emplace_back("10");
  list1.emplace_back("20");
  list1.emplace_back("30");
  list.pop_back();
  list.pop_back();
  list.pop_back();
  list1.pop_back();
  list1.pop_back();
  list1.pop_back();
  EXPECT_EQ(list.size(), list1.size());
}

TEST(list, pop_front) {
  list<std::string> list;
  std::list<std::string> list1;
  list.emplace_back("10");
  list.emplace_back("20");
  list.emplace_back("30");
  list1.emplace_back("10");
  list1.emplace_back("20");
  list1.emplace_back("30");
  list.pop_front();
  list1.pop_front();
  EXPECT_EQ(list.size(), list1.size());
}

TEST(list, pop_front_all) {
  list<std::string> list;
  std::list<std::string> list1;
  list.emplace_front("10");
  list.emplace_front("20");
  list.emplace_front("30");
  list1.emplace_front("10");
  list1.emplace_front("20");
  list1.emplace_front("30");
  list.pop_front();
  list.pop_front();
  list.pop_front();
  list1.pop_front();
  list1.pop_front();
  list1.pop_front();
  EXPECT_EQ(list.size(), list1.size());
}

TEST(list, eraseTestOnBegin) {
  list<std::string> list;
  std::list<std::string> list1;
  list.push_back("10");
  list.push_back("20");
  list.push_back("30");
  list1.push_back("10");
  list1.push_back("20");
  list1.push_back("30");
  EXPECT_EQ(*list1.erase(list1.begin()), *list.erase(list.begin()));
  EXPECT_EQ(*list1.erase(list1.begin()), *list.erase(list.begin()));
  list1.erase(list1.begin());
  list.erase(list.begin());
  list.push_back("20");
  list1.push_back("20");
  EXPECT_EQ(*list1.begin(), *list.begin());
}

TEST(list, eraseTestOnEnd) {
  list<std::string> list;
  std::list<std::string> list1;
  list.push_back("10");
  list.push_back("20");
  list.push_back("30");
  list1.push_back("10");
  list1.push_back("20");
  list1.push_back("30");
  list1.erase(--list1.end());
  list.erase(--list.end());
  list1.erase(--list1.end());
  list.erase(--list.end());
  list1.erase(--list1.end());
  list.erase(--list.end());
  EXPECT_EQ(list1.size(), list.size());
}

TEST(list, swapTest) {
  list<std::string> list{"10", "20", "30", "40"};
  s21::list<std::string> list2{"40", "30", "20", "10", "0"};
  std::list<std::string> list1{"10", "20", "30", "40"};
  std::list<std::string> list3{"40", "30", "20", "10", "0"};
  list.swap(list2);
  list1.swap(list3);
  auto fit = list1.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++it, ++fit) {
    EXPECT_EQ(*it, *fit);
  }
  EXPECT_EQ(list.size(), list1.size());
  fit = list3.begin();
  for (auto it = list2.begin(), eit = list2.end(); it != eit; ++it, ++fit) {
    EXPECT_EQ(*it, *fit);
  }
  EXPECT_EQ(list2.size(), list3.size());
}

TEST(list, swapTest2) {
  list<std::string> list{"10", "20", "30", "40"};
  s21::list<std::string> list2;
  std::list<std::string> list1{"10", "20", "30", "40"};
  std::list<std::string> list3;
  list.swap(list2);
  list1.swap(list3);
  EXPECT_TRUE(list.begin() == list.end());
  EXPECT_TRUE(list1.begin() == list1.end());
  auto fit = list3.begin();
  for (auto it = list2.begin(), eit = list2.end(); it != eit; ++it, ++fit) {
    EXPECT_EQ(*it, *fit);
  }
  EXPECT_EQ(list2.size(), list3.size());
}

TEST(list, swapTest3) {
  list<std::string> list;
  s21::list<std::string> list2{"10", "20", "30", "40"};
  std::list<std::string> list1;
  std::list<std::string> list3{"10", "20", "30", "40"};
  list.swap(list2);
  list1.swap(list3);
  EXPECT_TRUE(list2.begin() == list2.end());
  EXPECT_TRUE(list3.begin() == list3.end());
  auto fit = list1.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++it, ++fit) {
    EXPECT_EQ(*it, *fit);
  }
  EXPECT_EQ(list2.size(), list3.size());
}

TEST(list, swapTest4) {
  list<std::string> list;
  s21::list<std::string> list2;
  std::list<std::string> list1;
  std::list<std::string> list3;
  list.swap(list2);
  list1.swap(list3);
  EXPECT_TRUE(list2.begin() == list2.end());
  EXPECT_TRUE(list3.begin() == list3.end());
  EXPECT_EQ(list2.size(), list3.size());
}

TEST(list, spliceTest) {
  list<int> list{1, 2, 3, 4};
  s21::list<int> list1{4, 3, 2, 1};
  std::list<int> list2{1, 2, 3, 4};
  std::list<int> list3{4, 3, 2, 1};
  list.splice(list.begin(), list1);
  list2.splice(list2.begin(), list3);
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, spliceTest1) {
  list<int> list{1, 2, 3, 4};
  s21::list<int> list1{4, 3, 2, 1};
  std::list<int> list2{1, 2, 3, 4};
  std::list<int> list3{4, 3, 2, 1};
  list.splice(list.end(), list1);
  list2.splice(list2.end(), list3);
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, spliceTest2) {
  list<int> list;
  s21::list<int> list1{4, 3, 2, 1};
  std::list<int> list2;
  std::list<int> list3{4, 3, 2, 1};
  list.splice(list.end(), list1);
  list2.splice(list2.end(), list3);
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, spliceTest3) {
  list<std::string> list;
  s21::list<std::string> list1{"4", "3", "2", "1"};
  std::list<std::string> list2;
  std::list<std::string> list3{"4", "3", "2", "1"};
  list.splice(list.begin(), list1);
  list2.splice(list2.begin(), list3);
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, spliceTest4) {
  list<std::string> list;
  s21::list<std::string> list1{"4", "3", "2", "1"};
  std::list<std::string> list2;
  std::list<std::string> list3{"4", "3", "2", "1"};
  list.splice(list.begin(), list1, list1.begin());
  list2.splice(list2.begin(), list3, list3.begin());
  EXPECT_EQ(list.size(), list2.size());
  EXPECT_EQ(list1.size(), list3.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, spliceTest5) {
  list<std::string> list;
  s21::list<std::string> list1{"4", "3", "2", "1"};
  std::list<std::string> list2;
  std::list<std::string> list3{"4", "3", "2", "1"};
  list.splice(list.end(), list1, list1.begin());
  list2.splice(list2.end(), list3, list3.begin());
  EXPECT_EQ(list.size(), list2.size());
  EXPECT_EQ(list1.size(), list3.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, spliceTest6) {
  list<std::string> list;
  s21::list<std::string> list1{"4", "3", "2", "1"};
  std::list<std::string> list2;
  std::list<std::string> list3{"4", "3", "2", "1"};
  list.splice(list.end(), list1, --list1.end());
  list2.splice(list2.end(), list3, --list3.end());
  EXPECT_EQ(list.size(), list2.size());
  EXPECT_EQ(list1.size(), list3.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, spliceTest7) {
  list<std::string> list;
  s21::list<std::string> list1{"4", "3", "2", "1"};
  std::list<std::string> list2;
  std::list<std::string> list3{"4", "3", "2", "1"};
  list.splice(--list.end(), list1, ++(++list1.end()));
  list2.splice(--list2.end(), list3, ++(++list3.end()));
  EXPECT_EQ(list.size(), list2.size());
  EXPECT_EQ(list1.size(), list3.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, spliceTest8) {
  list<std::string> list{"1", "2", "3", "4"};
  std::list<std::string> list2{"1", "2", "3", "4"};
  list.splice(list.end(), list, ++list.end());
  list2.splice(list2.end(), list2, ++list2.end());
  EXPECT_EQ(list.size(), list2.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, spliceTest9) {
  list<std::string> list{"1", "2", "3", "4"};
  std::list<std::string> list2{"1", "2", "3", "4"};
  list.splice(list.begin(), list, ++list.end());
  list2.splice(list2.begin(), list2, ++list2.end());
  EXPECT_EQ(list.size(), list2.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, spliceTest10) {
  list<std::string> list{"10"};
  s21::list<std::string> list1{"4", "3", "2", "1"};
  std::list<std::string> list2{"10"};
  std::list<std::string> list3{"4", "3", "2", "1"};
  list.splice(list.end(), list1, list1.begin(), list1.end());
  list2.splice(list2.end(), list3, list3.begin(), list3.end());
  EXPECT_EQ(list.size(), list2.size());
  EXPECT_EQ(list1.size(), list3.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, spliceTest11) {
  list<std::string> list;
  s21::list<std::string> list1{"4", "3", "2", "1"};
  std::list<std::string> list2;
  std::list<std::string> list3{"4", "3", "2", "1"};
  list.splice(list.begin(), list1, ++list1.begin(), --list1.end());
  list2.splice(list2.begin(), list3, ++list3.begin(), --list3.end());
  EXPECT_EQ(list.size(), list2.size());
  EXPECT_EQ(list1.size(), list3.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, spliceTest12) {
  list<std::string> list;
  s21::list<std::string> list1{"4", "3", "2", "1"};
  std::list<std::string> list2;
  std::list<std::string> list3{"4", "3", "2", "1"};
  list.splice(list.begin(), list1, ++list1.end(), list1.begin());
  list2.splice(list2.begin(), list3, ++list3.end(), list3.begin());
  EXPECT_EQ(list.size(), list2.size());
  EXPECT_EQ(list1.size(), list3.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, mergeTest) {
  list<std::string> list{"1", "2", "3", "4"};
  s21::list<std::string> list1{"4", "3", "2", "1"};
  std::list<std::string> list2{"1", "2", "3", "4"};
  std::list<std::string> list3{"4", "3", "2", "1"};
  list.merge(list1);
  list2.merge(list3);
  EXPECT_EQ(list.size(), list2.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, mergeTest1) {
  list<std::string> list{"1", "2", "3", "4"};
  s21::list<std::string> list1{"1", "2", "3", "4"};
  std::list<std::string> list2{"1", "2", "3", "4"};
  std::list<std::string> list3{"1", "2", "3", "4"};
  list.merge(list1);
  list2.merge(list3);
  EXPECT_EQ(list.size(), list2.size());
  EXPECT_EQ(list1.size(), list3.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, mergeTest2) {
  list<std::string> list{"1", "2", "3", "4"};
  s21::list<std::string> list1{"1", "2", "4", "3"};
  std::list<std::string> list2{"1", "2", "3", "4"};
  std::list<std::string> list3{"1", "2", "4", "3"};
  list.merge(list1);
  list2.merge(list3);
  EXPECT_EQ(list.size(), list2.size());
  EXPECT_EQ(list1.size(), list3.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, mergeTest3) {
  list<std::string> list{"1", "2", "3", "4"};
  s21::list<std::string> list1{"1", "3", "2", "4"};
  std::list<std::string> list2{"1", "2", "3", "4"};
  std::list<std::string> list3{"1", "3", "2", "4"};
  list.merge(list1);
  list2.merge(list3);
  EXPECT_EQ(list.size(), list2.size());
  EXPECT_EQ(list1.size(), list3.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, reverseTest) {
  list<std::string> list{"1", "2", "3", "4"};
  std::list<std::string> list2{"1", "2", "3", "4"};
  list.reverse();
  list2.reverse();
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, reverseTest1) {
  list<std::string> list{"1"};
  std::list<std::string> list2{"1"};
  list.reverse();
  list2.reverse();
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, uniqueTest) {
  list<std::string> list{"1", "1"};
  std::list<std::string> list2{"1", "1"};
  list.unique();
  list2.unique();
  EXPECT_EQ(list.size(), list2.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, sortTest) {
  list<std::string> list{"3", "2", "1"};
  std::list<std::string> list2{"3", "2", "1"};
  list.sort();
  list2.sort();
  EXPECT_EQ(list.size(), list2.size());
  auto sit = list2.begin();
  for (auto it = list.begin(), eit = list.end(); it != eit; ++sit, ++it) {
    EXPECT_EQ(*it, *sit);
  }
}

TEST(list, insert_manyTest) {
  list list{"3", "2", "1"};
  list.insert_many(std::next(list.begin()), "2", "3", "4");
  s21::list test_list{"3", "2", "3", "4", "2", "1"};
  EXPECT_EQ(list, test_list);
}

TEST(list, insert_manybackTest) {
  list list{"3", "2", "1"};
  list.insert_many_back("2", "3", "4");
  s21::list test_list{"3", "2", "1", "2", "3", "4"};
  EXPECT_EQ(list, test_list);
}

TEST(list, insert_manyfrontTest) {
  list list{"3", "2", "1"};
  list.insert_many_front("2", "3", "4");
  s21::list test_list{"2", "3", "4", "3", "2", "1"};
  EXPECT_EQ(list, test_list);
}

TEST(list, insert_manyTestBackcycle) {
  list<std::string> list{"3", "2", "1"};
  for (int i = 0; i < 100000; ++i) {
        list.push_back(std::to_string(i));
  }
  EXPECT_EQ(list.size(), 100003);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
