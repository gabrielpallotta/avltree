#include <cmath>
#include <algorithm>
#include <stdexcept>

#include "avl_tree.hpp"
#include "gtest/gtest.h"

using namespace std;

class AvlTreeTest : public ::testing::Test {
  protected:
    void SetUp() override {
      this->tree = AvlTree<int>();
    }

    void TearDown() override {
      this->tree.~AvlTree();
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
  int total = 0;
  for (int i = -1000; i <= 1000; i++) {
    tree.add(i);
    total++;
    ASSERT_TRUE(validHeight(total, tree.getHeight()));
  }
}

TEST_F(AvlTreeTest, BalancesOnDescendingInsertion) {
  int total = 0;
  for (int i = 1000; i >= -1000; i--) {
    tree.add(i);
    total++;
    ASSERT_TRUE(validHeight(total, tree.getHeight()));
  }
}

TEST_F(AvlTreeTest, BalancesOnAscendingRemoval) {
  int total = 0;
  for (int i = -1000; i <= 1000; i++) {
    tree.add(i);
    total++;
  }

  for (int i = -1000; i <= 1000; i++) {
    tree.remove(i);
    total--;
    ASSERT_TRUE(validHeight(total, tree.getHeight()));
  }
}

TEST_F(AvlTreeTest, BalancesOnDescendingRemoval) {
  int total = 0;
  for (int i = -1000; i <= 1000; i++) {
    tree.add(i);
    total++;
  }

  for (int i = 1000; i >= -1000; i--) {
    tree.remove(i);
    total--;
    ASSERT_TRUE(validHeight(total, tree.getHeight()));
  }
}

TEST_F(AvlTreeTest, BalancesOnRandomInsertionAndRemoval) {
  int total = 0;

  vector<int> values;
  for (int i = -1000; i <= 1000; i++) {
    values.push_back(i);
  }

  random_shuffle(values.begin(), values.end());
  
  for (auto value : values) {
    tree.add(value);
    total++;
    ASSERT_TRUE(validHeight(total, tree.getHeight()));
  }
   
  random_shuffle(values.begin(), values.end());

  for (auto value : values) {
    tree.remove(value);
    total--;
    ASSERT_TRUE(validHeight(total, tree.getHeight()));
  }
}

TEST_F(AvlTreeTest, ThrowsExceptionOnInvalidInsertion) {
  tree.add(1);
  ASSERT_THROW(tree.add(1), invalid_argument);
}

TEST_F(AvlTreeTest, ThrowsExceptionOnInvalidRemoval) {
  ASSERT_THROW(tree.remove(1), invalid_argument);
}