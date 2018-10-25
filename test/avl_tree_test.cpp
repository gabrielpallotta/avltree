#include <cmath>
#include <exception>

#include "avl_tree.hpp"
#include "gtest/gtest.h"

using namespace std;

class AvlTreeTest : public ::testing::Test {
  protected:
    void SetUp() override {
      this->tree = AvlTree<int>();
    }

    AvlTree<int> tree;
};

int idealHeight(int n) {
  return ceil(log2(n + 1));
}

TEST_F(AvlTreeTest, InsertsAndGetsValue) {
  tree.add(0);
  ASSERT_EQ(0, *tree.get(0));
  tree.add(-1);
  ASSERT_EQ(-1, *tree.get(-1));
  tree.add(1);
  ASSERT_EQ(1, *tree.get(1));
}

TEST_F(AvlTreeTest, RemovesValue) {
  for (int i = 0; i < 10; i++) {
    tree.add(i);
  }
  
  for (int i = 0; i < 10; i++) {
    tree.remove(i);
    ASSERT_EQ(nullptr, tree.get(i));
  }
}

TEST_F(AvlTreeTest, GetReturnsNullPointer) {
  ASSERT_EQ(nullptr, tree.get(0));
}

TEST_F(AvlTreeTest, HeightIsCorrect) {
  ASSERT_EQ(0, tree.getHeight());
  tree.add(1);
  ASSERT_EQ(1, tree.getHeight());
  tree.remove(1);
  ASSERT_EQ(0, tree.getHeight());
}

TEST_F(AvlTreeTest, IsBalanced) {
  int it;
  int i;

  for (i = 0; i < 1000; i++) {
    tree.add(i);
  }
  i--;
  for (it = 1000; it >= 0; it -= 10) {
    for (; i > it; i--) {
      tree.remove(i);
    }
    ASSERT_EQ(idealHeight(i + 1), tree.getHeight());
  }
  tree.remove(i);
  ASSERT_EQ(0, tree.getHeight());
}


TEST_F(AvlTreeTest, ThrowsExceptionOnInvalidInsertion) {
  tree.add(1);
  ASSERT_EQ(1, *tree.get(1));
  ASSERT_THROW(tree.add(1), invalid_argument);
}

TEST_F(AvlTreeTest, ThrowsExceptionOnInvalidRemoval) {
  ASSERT_THROW(tree.remove(1), invalid_argument);
}