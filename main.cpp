#include <iostream>
#include "include/AvlTree.hpp"

using namespace std;

int main()
{
  AvlTree<int>* tree = new AvlTree<int>();
  tree->add(1);
  cout << *tree << endl;
  tree->add(2);
  cout << *tree << endl;
  tree->add(3);
  cout << *tree << endl;
  tree->add(4);
  cout << *tree << endl;
  tree->add(5);
  cout << *tree << endl;
  tree->add(6);
  cout << *tree << endl;
  tree->add(7);
  cout << *tree << endl;
  tree->add(8);
  cout << *tree << endl;
  return 0;
}
