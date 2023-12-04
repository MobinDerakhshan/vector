//
// Created by mobin on 03/12/23.
//
#include "vector.h"
#include "gtest/gtest.h"

template <typename T> class VectorTest : public ::testing::Test {};

using MyTypes = ::testing::Types<int, float, double, char, int *, char *>;
TYPED_TEST_SUITE(VectorTest, MyTypes);

TYPED_TEST(VectorTest, constructor) {
  TypeParam i, j;
  int n = 5;
  vector<TypeParam> vec1(n, i);
  EXPECT_EQ(vec1.size(), n);
}

TYPED_TEST(VectorTest, copy) {
  int n = 6;
  TypeParam i;
  vector<TypeParam> vec(n, i), copiedVector = vec;
  EXPECT_TRUE(vec == copiedVector);
  EXPECT_EQ(copiedVector.size(), vec.size());

  vector<TypeParam> copiedVector2(n);
  copiedVector2 = vec;
  EXPECT_TRUE(vec == copiedVector2);
  EXPECT_EQ(copiedVector2.size(), vec.size());
}

TYPED_TEST(VectorTest, move) {
  int n = 6;
  TypeParam i;
  vector<TypeParam> vec(n, i), movedVector = std::move(vec);
  EXPECT_TRUE(movedVector[0] == i);
  EXPECT_EQ(movedVector.size(), n);
  EXPECT_EQ(vec.size(), 0);

  vector<TypeParam> movedVector2(n);
  movedVector2 = std::move(movedVector);
  EXPECT_TRUE(movedVector2[0] == i);
  EXPECT_EQ(movedVector2.size(), n);
  EXPECT_EQ(movedVector.size(), 0);
}

TYPED_TEST(VectorTest, push_pop_eq) {
  TypeParam i, j, k;
  vector<TypeParam> vec1, vec2, vec3, vec4;
  vec1.push_back(i);
  vec1.push_back(j);

  vec2.push_back(k);
  vec2.push_back(i);

  vec3.push_back(i);
  vec3.push_back(j);
  vec3.push_back(j);

  vec4.push_back(i);
  vec4.push_back(j);

  EXPECT_FALSE(vec1 == vec2);
  EXPECT_FALSE(vec1 == vec3);
  EXPECT_TRUE(vec1 == vec4);

  EXPECT_EQ(vec1.pop_back(), j);
  EXPECT_EQ(vec1.pop_back(), i);
}

TYPED_TEST(VectorTest, iterator) {
  int n = 5;
  TypeParam i, k;
  vector<TypeParam> vec1(n, i), vec2;
  for (auto j : vec1) {
    vec2.push_back(j);
  }
  EXPECT_TRUE(vec1 == vec2);
  vec1.push_back(k);

  EXPECT_EQ(*vec1.begin(), i);
}

TYPED_TEST(VectorTest, vector_of_vector) {
  int n = 3, m = 4;
  TypeParam i, j;

  vector<TypeParam> v1(n, i), v2(m, j);
  vector<vector<TypeParam>> vec1, vec2;

  vec1.push_back(v1);
  vec1.push_back(v2);

  EXPECT_EQ(vec1.size(), 2);
  EXPECT_TRUE(vec1[0] == v1);
  EXPECT_TRUE(vec1[1] == v2);

  EXPECT_TRUE(vec1.pop_back() == v2);
  EXPECT_TRUE(vec1[0] == v1);
  EXPECT_EQ(vec1.size(), 1);

  vec2 = std::move(vec1);
  EXPECT_EQ(vec1.size(), 0);
  EXPECT_EQ(vec2.size(), 1);

  vector<vector<TypeParam>> vec3 = std::move(vec2);
  EXPECT_EQ(vec2.size(), 0);
  EXPECT_EQ(vec3.size(), 1);
}
