#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

using namespace std;

template <typename T>
class AvlTree
{
  public:
    AvlTree ()
    {
      this->right = nullptr;
      this->left = nullptr;
      this->info = nullptr;
      this->eq = 0;
    }


    void add (const T &info) throw (char*)
    {
      // Inserir aqui
      if (this->info == nullptr) {
        this->info =  new T(info);
      }
      // Já tem
      else if (info == *this->info) {
        throw "Info already on tree.";
      }

      // Inserir na esquerda
      else if (info < *this->info) {
        if (this->left == nullptr) {
          this->left = new AvlTree();
        }
        this->left->add(info);
        this->eq--;
      }
      // Inserir na direita
      else {
        if (this->right == nullptr) {
          this->right = new AvlTree();
        }
        this->right->add(info);
        this->eq++;
      }
      this->balance();
    }

    void remove (const T &info)
    {
      // Remover atual
      if (info == *this->info) {
        this->info = nullptr;
      }
      // Remover pra esquerda
      else if (info < *this->info) {
        if (this->left == nullptr) {
          throw "Info not on tree.";
        } else {
          this->left->remove(info);
          if (this->left->info == nullptr) {
            delete this->left;
            this->left = nullptr;
          }
        }
        this->eq++;
      }
      // Remover pra direita
      else {
        if (this->right == nullptr) {
          throw "Info not on tree.";
        } else {
          this->right->remove(info);
          if (this->right->info == nullptr) {
            delete this->right;
            this->right = nullptr;
          }
        }
        this->eq--;
      }
      this->balance();
    }

    template <typename U> friend ostream& operator<<(ostream& os, const AvlTree<U>& tree);
  private:
    AvlTree<T>* left;
    AvlTree<T>* right;
    T* info;
    int eq;

    void balance ()
    {
      if (this->eq > 1) {
        if (this->right->eq < 0) {
          this->rotateDoubleLeft();
        } else{
          this->rotateLeft();
        }
      } else if (this->eq < -1) {
        if (this->left->eq > 0) {
          this->rotateDoubleRight();
        } else {
          this->rotateRight();
        }
      }
    }

    void rotateLeft ()
    {
      AvlTree root = *this;
      AvlTree right = *this->right;
      AvlTree* leftOfRight = this->right->left;

      // Filho da direita vira raíz
      *this = right;

      // Raíz original vira filho da esquerda da nova raíz
      this->left = new AvlTree<T>();
      *this->left = root;

      // Filho da esquerda do filho da direita vira filho da direita do filho da esquerda
      if (leftOfRight == nullptr) {
        this->left->right = nullptr;
      } else {
        this->left->right = new AvlTree<T>();
        *this->left->right = *leftOfRight;
      }
    }

    void rotateRight ()
    {
      AvlTree root = *this;
      AvlTree left = *this->left;
      AvlTree* rightOfLeft = this->left->right;

      // Filho da esquerda vira raíz
      *this = left;

      // Raíz original vira filho da direita da nova raíz
      this->right = new AvlTree<T>();
      *this->right = root;

      // Filho da direita do filho da esquerda vira filho da esquerda do filho da direita
      if (rightOfLeft == nullptr) {
        this->right->left = nullptr;
      } else {
        this->right->left = new AvlTree<T>();
        *this->right->left = *rightOfLeft;
      }
    }

    void rotateDoubleLeft ()
    {
      this->right->rotateRight();
      this->rotateLeft();
    }

    void rotateDoubleRight ()
    {
      this->left->rotateLeft();
      this->rotateRight();
    }

    template <typename U> friend void printTree(ostream& os, const AvlTree<U>& tree, int count);
};

template <typename T>
void printTree(ostream& os, const AvlTree<T>& tree, int space)
{
    if (tree.info == nullptr) {
      return;
    }

    space += 5;

    if (tree.right != nullptr) {
      printTree(os, *tree.right, space);
    }

    os << endl;
    for (int i = 5 ; i < space; i++)
        os << " ";

    os << *tree.info << endl;


    if (tree.left != nullptr) {
      printTree(os, *tree.left, space);
    }
}

template <typename T>
ostream& operator<<(ostream& os, const AvlTree<T>& tree)
{
  os << "-------------" << endl;
  printTree(os, tree, 0);
  os << "-------------" << endl;
  return os;
}


#endif
