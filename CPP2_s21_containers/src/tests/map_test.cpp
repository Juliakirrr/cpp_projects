#include <gtest/gtest.h>

#include <map>

#include "../containers/associative_containers/map/s21_map.h"

using namespace s21;

TEST(MapTest, constructor_default) {
  map<int, std::string> myMap;
  std::map<int, std::string> std_Map;
  EXPECT_EQ(myMap.empty(), std_Map.empty());
}

TEST(MapTest, constructor_list) {
  map<int, std::string> myMap = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  std::map<int, std::string> std_Map = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  EXPECT_EQ(myMap.size(), std_Map.size());
}

TEST(MapTest, constructor_copy) {
  map<int, std::string> myMap = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  map<int, std::string> copy(myMap);
  std::map<int, std::string> std_Map = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  std::map<int, std::string> std_copy(std_Map);
  EXPECT_EQ(copy.size(), std_copy.size());
}

TEST(MapTest, constructor_move) {
  map<int, std::string> myMap = {
      {1, "me"}, {2, "45"}, {5, "ldjnh"}, {10, "khk"}};
  map<int, std::string> copy(std::move(myMap));

  std::map<int, std::string> std_Map = {
      {1, "me"}, {2, "45"}, {5, "ldjnh"}, {10, "khk"}};
  std::map<int, std::string> std_copy(std::move(std_Map));

  EXPECT_EQ(copy.size(), std_copy.size());
  EXPECT_EQ(myMap.size(), 0);
  EXPECT_EQ(std_Map.size(), 0);
}

TEST(MapTest, constructor_move_eq) {
  map<int, std::string> myMap = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  map<int, std::string> copy = {
      {54, "ljb"}, {5, "jhv"}, {12, "jhgjh"}, {16, "kjlkjb"}};
  copy = (std::move(myMap));

  std::map<int, std::string> std_Map = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  std::map<int, std::string> std_copy = {
      {54, "ljb"}, {5, "jhv"}, {12, "jhgjh"}, {16, "kjlkjb"}};
  std_copy = (std::move(std_Map));

  EXPECT_EQ(copy.size(), std_copy.size());
  EXPECT_EQ(myMap.size(), std_Map.size());
}

TEST(MapTest, merge_fn) {
  map<int, std::string> myMap = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  map<int, std::string> myMap2 = {
      {54, "ljb"}, {5, "jhv"}, {12, "jhgjh"}, {16, "kjlkjb"}};
  myMap.merge(myMap2);

  std::map<int, std::string> std_Map = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  std::map<int, std::string> std_Map2 = {
      {54, "ljb"}, {5, "jhv"}, {12, "jhgjh"}, {16, "kjlkjb"}};
  std_Map.merge(std_Map2);

  EXPECT_EQ(myMap.size(), std_Map.size());
}

TEST(MapTest, contains_fn) {
  map<int, std::string> myMap = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  map<int, std::string> myMap2 = {
      {54, "ljb"}, {5, "jhv"}, {12, "jhgjh"}, {16, "kjlkjb"}};
  myMap.merge(myMap2);

  EXPECT_EQ(myMap.contains(54), true);
  EXPECT_EQ(myMap.contains(10), false);
}

TEST(MapTest, clear_fn) {
  map<int, std::string> myMap = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  myMap.clear();
  std::map<int, std::string> std_Map = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  std_Map.clear();
  EXPECT_EQ(myMap.size(), std_Map.size());
}

TEST(MapTest, operator_at) {
  map<int, std::string> myMap = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  std::map<int, std::string> std_Map = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};

  EXPECT_EQ(myMap.at(1), std_Map.at(1));
}

TEST(MapTest, operator_SB) {
  map<int, std::string> myMap = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  std::map<int, std::string> std_Map = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  myMap[1] = "aaa";
  std_Map[1] = "aaa";
  EXPECT_EQ(myMap.at(1), std_Map.at(1));
}

TEST(MapTest, fn_erase) {
  map<int, std::string> myMap = {{1, "me"}, {2, "45"},  {5, "ldjnh"}, {6, "54"},
                                 {7, "54"}, {10, "54"}, {11, "54"}};

  map<int, std::string>::iterator myit = myMap.begin();
  myMap.erase(myit);

  EXPECT_EQ(myMap.contains(1), false);
}

TEST(MapTest, iterator_test) {
  map<int, std::string> myMap = {{1, "me"}, {2, "45"},  {5, "ldjnh"}, {6, "54"},
                                 {7, "54"}, {10, "54"}, {11, "54"}};

  map<int, std::string>::iterator myit = myMap.begin();
  size_t sizeMap = 0;
  while (myit != myMap.end()) {
    ++myit;
    sizeMap++;
  }
  EXPECT_EQ(myMap.size(), sizeMap);
}

TEST(MapTest, iterator_test_1) {
  map<int, std::string> myMap = {{1, "me"}, {2, "45"},  {5, "ldjnh"}, {6, "54"},
                                 {7, "54"}, {10, "54"}, {11, "54"}};

  map<int, std::string>::iterator myit = myMap.end();
  size_t sizeMap = 0;
  while (myit != myMap.begin()) {
    --myit;
    sizeMap++;
  }
  EXPECT_EQ(myMap.size(), sizeMap);
}

TEST(MapTest, insert_fn) {
  map<int, std::string> myMap = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  myMap.insert(10, "abc");
  std::map<int, std::string> std_Map = {{1, "me"}, {2, "45"}, {5, "ldjnh"}};
  std_Map.insert(std::make_pair(10, "abc"));

  EXPECT_EQ((*myMap.find(10)).second, (*std_Map.find(10)).second);
}

TEST(MapTest, insert_fn_1) {
  map<int, std::string> myMap = {
      {1, "me"}, {2, "45"}, {5, "ldjnh"}, {10, "abc"}};
  myMap.insert(std::make_pair(10, "abc1"));
  std::map<int, std::string> std_Map = {
      {1, "me"}, {2, "45"}, {5, "ldjnh"}, {10, "abc"}};
  std_Map.insert(std::make_pair(10, "abc1"));

  EXPECT_EQ((*myMap.find(10)).second, (*std_Map.find(10)).second);
}

TEST(MapTest, insert_fn_2) {
  map<int, std::string> myMap = {
      {1, "me"}, {2, "45"}, {5, "ldjnh"}, {10, "abc"}};
  myMap.insert_or_assign(10, "abc1");
  std::map<int, std::string> std_Map = {
      {1, "me"}, {2, "45"}, {5, "ldjnh"}, {10, "abc"}};
  std_Map.insert_or_assign(10, "abc1");

  EXPECT_EQ((*myMap.find(10)).second, (*std_Map.find(10)).second);
}

TEST(MapTest, insert_many) {
  map<int, std::string> myMap = {
      {1, "me"}, {2, "45"}, {5, "ldjnh"}, {10, "abc"}};
  vector<std::pair<map<int, std::string>::iterator, bool>> aaa =
      myMap.insert_many((std::make_pair(11, "abc")),
                        (std::make_pair(12, "abc")),
                        (std::make_pair(10, "abc")));

  EXPECT_EQ((*aaa[0].first).first, 11);
  EXPECT_EQ(aaa[0].second, true);
  EXPECT_EQ(aaa[2].second, false);

  EXPECT_EQ(myMap.contains(12), true);
  EXPECT_EQ(myMap.contains(11), true);
}


TEST(MapTest, insert_mnogo) {
  map<int, int> myMap;
  for (int i = 0; i < 10000; i++) {
        myMap.insert(i, i);
    }
  for (int i = 300; i < 800; i++) {
        myMap.erase(myMap.find(i));
    }
   myMap[101] = 10;
   myMap[108381] = 39;
   myMap[8381] = 739;
  EXPECT_EQ(myMap[101], 10);
  EXPECT_EQ(myMap[108381], 39);
  EXPECT_EQ(myMap[8381], 739);
  for (int i = 5000; i < 15000; i++) {
        myMap.insert(i, i);
    }
  EXPECT_EQ(myMap.size(), 14501);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
