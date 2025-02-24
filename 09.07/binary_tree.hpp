#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "node.hpp"

#include <iostream>
#include <memory>

namespace tree
{

    template <typename T>
    class BinaryTree {
    public:

        void insert(int value)
        {
            if (!root) {
                root = std::make_shared<node::Node<T> >(value);
            } else {
                insertHelper(root, value);
            }
        }

        void inorderTraversal() const
        {
            inorderHelper(root);
            std::cout << std::endl;
        }

    private:
        void insertHelper(std::shared_ptr<node::Node<T> > node, int value)
        {
            if (value < node->getValue()) {
                if (!node->getLeftChild()) {
                    node->bindLeftChild(std::make_shared<node::Node<T> >(value));
                    node->getLeftChild()->bindParent(node);
                } else {
                    insertHelper(node->getLeftChild(), value);
                }
            } else {
                if (!node->getRightChild()) {
                    node->bindRightChild(std::make_shared<node::Node<T> >(value));
                    node->getRightChild()->bindParent(node);
                } else {
                    insertHelper(node->getRightChild(), value);
                }
            }
        }

        void inorderHelper(std::shared_ptr<node::Node<T> > node) const
        {
            if (!node)
                return;
            inorderHelper(node->getLeftChild());
            std::cout << node->getValue() << " ";
            inorderHelper(node->getRightChild());
        }

        std::shared_ptr<node::Node<T> > root;
    };

}

#endif // _BINARY_TREE_H