#include "AVLNode.h"
#include <stdlib.h> // abs
#include <algorithm>

template <class T>
class AVLTree {
public:
    AVLTree()
    {
        pRoot = nullptr;
    }

    ~AVLTree()
    {
        delete pRoot;
    }

    void insert(const T &data)
    {
        insert(data, pRoot);
    }

    int contains(const T &match)
    {
        return contains(match, pRoot);
    }

    int height()
    {
        if (pRoot == nullptr)
        {
            return -1;
        }

        return height(pRoot);
    }

    int validate()
    {
        return validate(pRoot);
    }

private:
    AVLNode<T>* pRoot;

    int height(AVLNode<T>* node)
    {
        return node == nullptr ? -1 : node->height;
    }

    int contains(const T &match, const AVLNode<T>* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        if (node->data == match)
        {
            return 1;
        }

        else if (node->data > match)
        {
            return contains(match, node->pLeft);
        }

        else if (node->data < match)
        {
            return contains(match, node->pRight);
        }

        return 0;
    }

    void insert(const T &data, AVLNode<T>* &node)
    {
        if (node == nullptr)
        {
            node = new AVLNode<T>(data);
        }

        else if (data < node->data)
        {
            insert(data, node->pLeft);
            if (!validateLR(node))
            {
                if (node->pLeft->data > data)
                {
                    node = leftRotate(node); //case 1
                }
                else
                {
                    node = doubleLeftRotate(node); //case 2
                }
            }
        }

        else if (data > node->data)
        {
            insert(data, node->pRight);
            if (!validateLR(node))
            {
                if (node->pRight->data < data)
                {
                    node = rightRotate(node); //case 3
                }
                else
                {
                    node = doubleRightRotate(node); //case 4
                }
            }
        }

        node->height = 1 + std::max(height(node->pLeft), height(node->pRight));
    }

    AVLNode<T>* leftRotate(AVLNode<T>* &node)
    {
        AVLNode<T> * tmpNode = node->pLeft;
        node->pLeft = tmpNode->pRight;
        tmpNode->pRight = node;

        node->height = 1 + std::max(height(node->pLeft), height(node->pRight));
        tmpNode->height = 1 + std::max(height(tmpNode->pLeft), (node->height));

        return tmpNode;
    }

    AVLNode<T>* rightRotate(AVLNode<T>* &node)
    {
        AVLNode<T>* tmpNode = node->pRight;
        node->pRight = tmpNode->pLeft;
        tmpNode->pLeft = node;

        node->height = 1 + std::max(height(node->pRight), height(node->pLeft));
        tmpNode->height = 1 + std::max(height(tmpNode->pRight), (node->height));

        return tmpNode;
    }

    AVLNode<T>* doubleRightRotate(AVLNode<T> * & node)
    {
        node->pRight = leftRotate(node->pRight);
        node = rightRotate(node);
        return node;
    }

    AVLNode<T>* doubleLeftRotate(AVLNode<T> * & node)
    {
        node->pLeft = rightRotate(node->pLeft);
        node = leftRotate(node);
        return node;
    }

    int validateLR(AVLNode<T>* root)
    {
        int diff = height(root->pLeft) - height(root->pRight);

        return !(abs(diff) > 1);
    }

    int validate(AVLNode<T>* node)
    {
        if (node == nullptr)
        {
            return 1;
        }
        else if (!validateLR(node))
        {
            return 0;
        }

        return validate(node->pLeft) == validate(node->pRight);
    }
};