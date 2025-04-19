#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../containers/sequence_containers/vector/s21_vector.h"

using namespace s21;
TEST(vectorTest, DefaultConstructor) {
  vector<int> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST(vectorTest, SizeConstructorTrivial) {
  vector<int> vec(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_GE(vec.capacity(), 5);
  EXPECT_FALSE(vec.empty());
}

TEST(vectorTest, SizeConstructorNotTrivial) {
  vector<std::string> vec(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_GE(vec.capacity(), 5);
  EXPECT_FALSE(vec.empty());
}

TEST(vectorTest, SizeConstructorNotTrivial2) {
  vector<std::vector<std::string>> vec(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_GE(vec.capacity(), 5);
  EXPECT_FALSE(vec.empty());
}

TEST(vectorTest, SizeConstructorNotTrivial3) {
  vector<vector<int>> vec(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_GE(vec.capacity(), 5);
  EXPECT_FALSE(vec.empty());
}

TEST(vectorTest, SizeConstructorNotTrivial4) {
  vector<vector<std::string>> vec(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_GE(vec.capacity(), 5);
  EXPECT_FALSE(vec.empty());
}

TEST(vectorTest, SizeConstructorNotTrivial5) {
  class s21_test_class {
   public:
    s21_test_class() = default;
    s21_test_class(const s21_test_class &other) = delete;
    s21_test_class(s21_test_class &&other) = delete;

    void show() const { std::cout << "x: " << x; }

   private:
    int x;
  };
  vector<s21_test_class> vec(5);
  std::vector<s21_test_class> vec_or(5);
  EXPECT_EQ(vec.size(), vec_or.size());
  EXPECT_EQ(vec.capacity(), vec_or.capacity());
  EXPECT_EQ(vec.empty(), vec_or.empty());
}

TEST(vectorTest, SizeValueConstructor) {
  vector<int> vec(5, 42);
  std::vector<int> vec1(5, 42);
  EXPECT_EQ(vec.size(), vec1.size());
  EXPECT_EQ(vec.capacity(), vec1.size());
  EXPECT_EQ(vec.empty(), vec1.empty());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], vec1[i]);
  }
}

TEST(vectorTest, SizeValueConstructorNonTrivial) {
  vector<std::string> vec(5, "100");
  std::vector<std::string> vec1(5, "100");
  EXPECT_EQ(vec.size(), vec1.size());
  EXPECT_EQ(vec.capacity(), vec1.size());
  EXPECT_EQ(vec.empty(), vec1.empty());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], vec1[i]);
  }
}

TEST(vectorTest, SizeValueConstructorNonTrivial2) {
  vector<vector<std::string>> vec(5, vector<std::string>(10, "100"));
  std::vector<std::vector<std::string>> vec1(
      5, std::vector<std::string>(10, "100"));
  EXPECT_EQ(vec.size(), vec1.size());
  EXPECT_EQ(vec.capacity(), vec1.size());
  EXPECT_EQ(vec.empty(), vec1.empty());
  for (size_t i = 0; i < vec.size(); ++i) {
    for (size_t j = 0; j < vec[0].size(); ++j) {
      EXPECT_EQ(vec[i][j], vec1[i][j]);
    }
  }
}

TEST(vectorTest, CopyConstructor) {
  vector<int> vec1(5, 42);
  vector<int> vec2(vec1);
  EXPECT_EQ(vec2.size(), 5);
  EXPECT_GE(vec2.capacity(), 5);
  EXPECT_FALSE(vec2.empty());
  for (size_t i = 0; i < vec2.size(); ++i) {
    EXPECT_EQ(vec2[i], 42);
  }
  vec1[0] = 100;
  EXPECT_NE(vec1[0], vec2[0]);
}

TEST(vectorTest, CopyConstructorWithOriginal) {
  vector<int> vec1(5, 42);
  vector<int> vec2(vec1);
  std::vector<int> vec3(5, 42);
  std::vector<int> vec4(vec3);
  EXPECT_EQ(vec2.size(), vec4.size());
  EXPECT_EQ(vec2.capacity(), vec4.capacity());
  EXPECT_EQ(vec2.empty(), vec4.empty());
  for (size_t i = 0; i < vec2.size(); ++i) {
    EXPECT_EQ(vec2[i], vec4[i]);
  }
}

TEST(vectorTest, MoveConstructor) {
  vector<int> vec1(5, 42);
  vector<int> vec2(std::move(vec1));
  std::vector<int> vec3(5, 42);
  std::vector<int> vec4(std::move(vec3));
  EXPECT_EQ(vec2.size(), vec4.size());
  EXPECT_EQ(vec2.capacity(), vec4.capacity());
  EXPECT_EQ(vec2.empty(), vec4.empty());
  for (size_t i = 0; i < vec2.size(); ++i) {
    EXPECT_EQ(vec2[i], vec4[i]);
  }
  EXPECT_EQ(vec1.size(), vec3.size());
  EXPECT_EQ(vec1.capacity(), vec3.capacity());
  EXPECT_EQ(vec1.empty(), vec3.empty());
}

TEST(vectorTest, InitializerListConstructor) {
  vector<int> vec({1, 2, 3, 4, 5});
  std::vector<int> vec1({1, 2, 3, 4, 5});
  EXPECT_EQ(vec.size(), vec1.size());
  EXPECT_EQ(vec.capacity(), vec1.capacity());
  EXPECT_EQ(vec.empty(), vec1.empty());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], vec1[i]);
  }
}

TEST(vectorTest, AssignmentOperator) {
  vector<int> vec1({1, 2, 3, 4, 5, 6});
  vector<int> vec2 = std::move(vec1);
  std::vector<int> vec3({1, 2, 3, 4, 5, 6});
  std::vector<int> vec4 = std::move(vec3);
  EXPECT_EQ(vec2.size(), vec4.size());
  EXPECT_EQ(vec2.capacity(), vec4.capacity());
  EXPECT_EQ(vec2.empty(), vec4.empty());
  for (size_t i = 0; i < vec2.size(); ++i) {
    EXPECT_EQ(vec2[i], vec4[i]);
  }
  EXPECT_EQ(vec1.size(), vec3.size());
  EXPECT_EQ(vec1.capacity(), vec3.capacity());
  EXPECT_EQ(vec1.empty(), vec3.empty());
}

TEST(vectorTest, ClearTest) {
  vector<std::string> vec{"1", "2030", "00420-"};
  std::vector<std::string> vec1{"1", "2030", "00420-"};
  vec.clear();
  vec1.clear();
  EXPECT_EQ(vec.size(), vec1.size());
  EXPECT_EQ(vec.capacity(), vec1.capacity());
  EXPECT_EQ(vec.empty(), vec1.empty());
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_TRUE(vec[i].empty());
  }
}

TEST(vectorTest, IteratorTest) {
  vector<int> p(10, 5);
  for (auto start = p.begin(), finish = p.end(); start != finish; ++start) {
    EXPECT_EQ(*start, 5);
  }
}

TEST(vectorTest, emplace_backTest) {
  vector<int> vec;
  vec.emplace_back(1);
  vec.emplace_back(2);
  vec.emplace_back(3);
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], i + 1);
  }
  EXPECT_EQ(vec.capacity(), 4);
}

TEST(vectorTest, emplace_backTest1) {
  vector<int> vec;
  vec.emplace_back(1);
  vec.emplace_back(2);
  vec.emplace_back(3);
  vec.emplace_back(4);
  vec.emplace_back(5);
  vec.emplace_back(6);
  vec.emplace_back(7);
  vec.emplace_back(8);
  vec.emplace_back(vec[5]);
  for (size_t i = 0; i < vec.size() - 1; ++i) {
    EXPECT_EQ(vec[i], i + 1);
  }
  EXPECT_EQ(vec[5], vec.back());
  EXPECT_EQ(vec.capacity(), 16);
}

TEST(vectorTest, emplace_backTest2) {
  vector<std::pair<int, int>> vec;
  vec.emplace_back(1, 2);
  vec.emplace_back(3, 4);
  vec.emplace_back(5, 6);
  vec.emplace_back(vec[0].first, vec[0].second);
  for (size_t i = 0; i < vec.size() - 1; ++i) {
    EXPECT_EQ(vec[i].first, i * 2 + 1);
    EXPECT_EQ(vec[i].second, i * 2 + 2);
  }
  EXPECT_EQ(vec[0].first, vec.back().first);
  EXPECT_EQ(vec[0].second, vec.back().second);
  EXPECT_EQ(vec.capacity(), 4);
}

TEST(vectorTest, emplace_backTest3) {
  vector<std::string> vec;
  vec.emplace_back("10");
  vec.emplace_back("20");
  vec.emplace_back("30");
  vec.emplace_back("40");
  vec.emplace_back("50");
  vec.emplace_back("60");
  vec.emplace_back("70");
  vec.emplace_back("80");
  vec.emplace_back(vec[0]);
  EXPECT_EQ(vec[0], vec.back());
  EXPECT_EQ(vec.capacity(), 16);
}

TEST(vectorTest, emplace_backTest4) {
  vector<std::vector<int>> vec;
  vec.emplace_back(5, 10);
  vec.emplace_back(6, 10);
  vec.emplace_back(7, 10);
  vec.emplace_back(8, 10);
  vec.emplace_back(9, 10);
  vec.emplace_back(10, 10);
  vec.emplace_back(11, 10);
  vec.emplace_back(12, 10);
  vec.emplace_back(vec[0]);
  EXPECT_EQ(vec[0], vec.back());
  EXPECT_EQ(vec.capacity(), 16);
}

TEST(vectorTest, emplace_backTest5) {
  vector<std::string> vec;
  vec.emplace_back("10");
  vec.emplace_back(vec[0]);
  vec.emplace_back(vec[0]);
  vec.emplace_back(vec[0]);
  vec.emplace_back(vec[3]);
  vec.emplace_back(vec[0]);
  vec.emplace_back(vec[0]);
  vec.emplace_back(vec[0]);
  vec.emplace_back(vec[5]);
  vec[2] = "100";
  EXPECT_EQ(vec[0], vec.back());
  EXPECT_EQ(vec.capacity(), 16);
}

TEST(vectorTest, eraseTest) {
  vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  p.erase(p.begin());
  EXPECT_EQ(p[0], "20");
}

TEST(vectorTest, eraseTest1) {
  vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  auto pointer = p.begin();
  pointer -= 10;
  p.erase(pointer);
  EXPECT_EQ(p[0], "10");
}

TEST(vectorTest, eraseTest2) {
  vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  auto pointer = p.begin();
  pointer += 10;
  p.erase(pointer);
  EXPECT_EQ(p[0], "10");
}

TEST(vectorTest, eraseTest3) {
  vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  auto pointer = p.begin();
  pointer++;
  p.erase(pointer);
  std::vector<std::string> vec;
  vec.push_back("10");
  vec.push_back("20");
  vec.push_back("30");
  auto pointer1 = vec.begin();
  pointer1++;
  vec.erase(pointer1);
  EXPECT_EQ(p[0], vec[0]);
  EXPECT_EQ(p[1], vec[1]);
}

TEST(vectorTest, multipleEraseTest) {
  vector<int> p;
  p.push_back(10);
  p.push_back(20);
  p.push_back(30);
  auto pointer = p.begin();
  auto pointer1 = p.end();
  pointer1++;
  auto pointer2 = p.erase(pointer, pointer1);
  EXPECT_EQ(*pointer2, 10);
}

TEST(vectorTest, multipleEraseTest2) {
  vector<int> p;
  p.push_back(10);
  p.push_back(20);
  p.push_back(30);
  auto pointer = p.begin();
  pointer++;
  auto pointer1 = p.end();
  auto pointer2 = p.erase(pointer, pointer1);
  EXPECT_EQ(*pointer2, 20);
}

TEST(vectorTest, multipleEraseTest3) {
  vector<int> p;
  p.push_back(10);
  p.push_back(20);
  p.push_back(30);
  p.push_back(40);
  auto pointer = p.begin();
  pointer++;
  auto pointer1 = p.end();
  pointer1--;
  auto pointer2 = p.erase(pointer, pointer1);
  EXPECT_EQ(*pointer2, 40);
  EXPECT_EQ(p[1], 40);
}

TEST(vectorTest, emplaceTest) {
  vector<int> p;
  p.push_back(10);
  p.push_back(20);
  p.push_back(30);
  p.push_back(40);
  auto pointer = p.begin();
  pointer++;
  p.emplace(pointer, p[0]);
  EXPECT_EQ(p[0], p[1]);
}

TEST(vectorTest, emplaceTest2) {
  vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  p.push_back("40");
  p.push_back("50");
  auto pointer = p.begin();
  pointer++;
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  EXPECT_EQ(p[0], p[1]);
}

TEST(vectorTest, emplaceTest3) {
  vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  p.push_back("40");
  auto pointer = p.begin();
  pointer++;
  p.emplace(pointer, p[0]);
  EXPECT_EQ(p[0], p[1]);
}

TEST(vectorTest, emplaceTest4) {
  vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  p.push_back("40");
  p.push_back("50");
  auto pointer = p.begin();
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  EXPECT_EQ(p[0], p[1]);
}

TEST(vectorTest, emplaceTest5) {
  vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  p.push_back("40");
  p.push_back("50");
  auto pointer = p.end();
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  p.emplace(pointer, p[0]);
  EXPECT_EQ(p[0], p[p.size() - 1]);
}

TEST(vectorTest, shrink_to_fitTest) {
  vector<int> p;
  p.push_back(10);
  p.push_back(20);
  p.push_back(30);
  p.push_back(40);
  vector<int>::iterator pointer = p.begin();
  pointer++;
  p.emplace(pointer, p[0]);
  p.shrink_to_fit();
  EXPECT_EQ(p.capacity(), 5);
}

TEST(vectorTest, shrink_to_fitTest2) {
  vector<std::string> p;
  p.push_back("10");
  p.push_back("20");
  p.push_back("30");
  p.push_back("40");
  p.push_back("50");
  p.shrink_to_fit();
  EXPECT_EQ(p.capacity(), 5);
}

TEST(vectorTest, insert_manyTest) {
  vector list{"3", "2", "1"};
  list.insert_many(std::next(list.begin()), "2", "3", "4");
  vector test_list{"3", "2", "3", "4", "2", "1"};
  EXPECT_EQ(list, test_list);
}

TEST(vectorTest, insert_manybackTest) {
  vector list{"3", "2", "1"};
  list.insert_many_back("2", "3", "4");
  vector test_list{"3", "2", "1", "2", "3", "4"};
  EXPECT_EQ(list, test_list);
}


TEST(vectorTest, insert_manybackTest_) {
  vector list{"3", "2", "1"};
  list.insert_many_back();
  vector test_list{"3", "2", "1"};
  EXPECT_EQ(list, test_list);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
