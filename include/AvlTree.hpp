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
      this->height = 0;
      this->correctHeight = true;
    }

    void add (const T &info) throw (char*)
    {
      // Inserir no this
      if (this->info == nullptr) {
        this->info = new T(info);
        this->height = 1;
      }
      // Inserir na esquerda
      else if (info < *this->info) {
        if (this->left == nullptr) {
          this->left = new AvlTree();
        }
        this->left->add(info);
      }
      // Inserir na direita
      else if (info > *this->info) {
        if (this->right == nullptr) {
          this->right = new AvlTree();
        }
        this->right->add(info);
      }
      // Ja tem
      else {
        throw "Info already on tree";
      }
      this->correctHeight = false;
      this->calculateHeight();
      this->balance();
    }

    void remove (const T &info)
    {
      // Nao tem (so entra aqui se for raiz)
      if (this->info == nullptr) {
        throw "Info not on tree";
      }
      // Remover aqui
       else if (info == *this->info) {
        if (this->left != nullptr) {
          *this->info = this->left->getBiggestInfo();
          this->left->remove(*this->info);
        } else if (this->right != nullptr) {
          *this->info = this->right->getSmallestInfo();
          this->right->remove(*this->info);
        } else {
          this->info = nullptr;
          return;
        }
      }
      // Remover pra esquerda
      else if (info < *this->info) {
        if (this->left == nullptr) {
          throw "Info not on tree.";
        } else {
          this->left->remove(info);
        }
      }
      // Remover pra direita
      else {
        if (this->right == nullptr) {
          throw "Info not on tree.";
        } else {
          this->right->remove(info);
        }
      }

      // Deleta no da direita se estiver vazio
      if (this->right != nullptr && this->right->info == nullptr) {
        delete this->right;
        this->right = nullptr;
      }

      // Deleta no da esquerda se estiver vazio
      if (this->left != nullptr && this->left->info == nullptr) {
        delete this->left;
        this->left = nullptr;
      }

      // Recalcula altura e equilibra a arvore
      this->correctHeight = false;
      this->calculateHeight();
      this->balance();
    }

    T* get (T info)
    {
      if (this->info == nullptr) {
        return nullptr;
      }
      else if (info == *this->info) {
        return this->info;
      } else if (info > *this->info) {
        if (this->right != nullptr) {
          return this->right->get(info);
        } else {
          return nullptr;
        }
      } else {
        if (this->left != nullptr) {
          return this->left->get(info);
        } else {
          return nullptr;
        }
      }
    }

    template <typename U> friend ostream& operator<<(ostream& os, const AvlTree<U>& tree);
  private:
    AvlTree<T>* left;
    AvlTree<T>* right;
    T* info;
    int height;
    bool correctHeight;

    int getBalance ()
    {
      int left = 0;
      int right = 0;

      if (this->left != nullptr) {
        left = this->left->height;
      }

      if (this->right != nullptr) {
        right = this->right->height;
      }

      return (right - left);
    }

    void balance ()
    {
      if (this->getBalance() > 1) {
        if (this->right->getBalance() < 0) {
          this->rotateDoubleLeft();
        } else{
          this->rotateLeft();
        }
      } else if (this->getBalance() < -1) {
        if (this->left->getBalance() > 0) {
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

      // Filho da direita vira raiz
      *this = right;

      // Raiz original vira filho da esquerda da nova raiz
      this->left = new AvlTree<T>();
      *this->left = root;

      // Filho da esquerda do filho da direita vira filho da direita do filho da esquerda
      if (leftOfRight == nullptr) {
        this->left->right = nullptr;
      } else {
        this->left->right = new AvlTree<T>();
        *this->left->right = *leftOfRight;
      }

      this->correctHeight = false;
      this->left->correctHeight = false;
      this->calculateHeight();
    }

    void rotateRight ()
    {
      AvlTree root = *this;
      AvlTree left = *this->left;
      AvlTree* rightOfLeft = this->left->right;

      // Filho da esquerda vira raiz
      *this = left;

      // Raiz original vira filho da direita da nova raiz
      this->right = new AvlTree<T>();
      *this->right = root;

      // Filho da direita do filho da esquerda vira filho da esquerda do filho da direita
      if (rightOfLeft == nullptr) {
        this->right->left = nullptr;
      } else {
        this->right->left = new AvlTree<T>();
        *this->right->left = *rightOfLeft;
      }

      this->correctHeight = false;
      this->right->correctHeight = false;
      this->calculateHeight();
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

    void calculateHeight()
    {
      if (!this->correctHeight) {
        int left = 0;
        int right = 0;

        if (this->right != nullptr) {
          this->right->calculateHeight();
          right = this->right->height;
        }

        if (this->left != nullptr) {
          this->left->calculateHeight();
          left = this->left->height;
        }

        this->height = max(left, right) + 1;
        this->correctHeight = true;
      }
    }

    T getBiggestInfo ()
    {
      if (this->right == nullptr) {
        return *this->info;
      } else {
        return this->right->getBiggestInfo();
      }
    }

    T getSmallestInfo ()
    {
      if (this->left == nullptr) {
        return *this->info;
      } else {
        return this->left->getSmallestInfo();
      }
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
  os << "--------------------------" << endl;
  printTree(os, tree, 0);
  os << "--------------------------" << endl;
  return os;
}


#endif
