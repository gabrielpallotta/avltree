#include <cmath>
#include <stdexcept>

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

bool validHeight(int n, int height) {
  if (height < ceil(log2(n + 1))) {
    return false;
  }

  if (height > floor(1.44f * log2(n + 2) - 0.328f)) {
    return false;
  }

  return true;
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

TEST_F(AvlTreeTest, GetsNullPointer) {
  ASSERT_EQ(nullptr, tree.get(0));
}

TEST_F(AvlTreeTest, GetsTreeHeight) {
  ASSERT_EQ(0, tree.getHeight());
  tree.add(1);
  ASSERT_EQ(1, tree.getHeight());
  tree.remove(1);
  ASSERT_EQ(0, tree.getHeight());
}

TEST_F(AvlTreeTest, BalancesOnAscendingInsertion) {
  for (int i = 1; i <= 1000; i++) {
    tree.add(i);
    ASSERT_TRUE(validHeight(i, tree.getHeight()));
  }
}

TEST_F(AvlTreeTest, BalancesOnDescendingInsertion) {
  for (int i = 1000; i > 0; i--) {
    tree.add(i);
    ASSERT_TRUE(validHeight(1001 - i, tree.getHeight()));
  }
}

TEST_F(AvlTreeTest, BalancesOnAscendingRemoval) {
  for (int i = 1; i <= 1000; i++) {
    tree.add(i);
  }

  for (int i = 1; i <= 1000; i++) {
    tree.remove(i);
    ASSERT_TRUE(validHeight(1000 - i, tree.getHeight()));
  }
}

TEST_F(AvlTreeTest, BalancesOnDescendingRemoval) {
  for (int i = 1; i <= 1000; i++) {
    tree.add(i);
  }

  for (int i = 1000; i > 0; i--) {
    tree.remove(i);
    ASSERT_TRUE(validHeight(i - 1, tree.getHeight()));
  }
}


TEST_F(AvlTreeTest, ThrowsExceptionOnInvalidInsertion) {
  tree.add(1);
  ASSERT_EQ(1, *tree.get(1));
  ASSERT_THROW(tree.add(1), invalid_argument);
}

TEST_F(AvlTreeTest, ThrowsExceptionOnInvalidRemoval) {
  ASSERT_THROW(tree.remove(1), invalid_argument);
}