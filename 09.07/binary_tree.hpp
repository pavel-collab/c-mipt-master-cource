#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <iostream>
#include <memory>

struct Node {
    //? it can be a private fields
    int value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::weak_ptr<Node> parent;

    Node(int val)
        : value(val)
    {
    }
};

class BinaryTree {
public:
    std::shared_ptr<Node> root;

    void insert(int value)
    {
        if (!root) {
            root = std::make_shared<Node>(value);
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
    void insertHelper(std::shared_ptr<Node> node, int value)
    {
        if (value < node->value) {
            if (!node->left) {
                node->left = std::make_shared<Node>(value);
                node->left->parent = node;
            } else {
                insertHelper(node->left, value);
            }
        } else {
            if (!node->right) {
                node->right = std::make_shared<Node>(value);
                node->right->parent = node;
            } else {
                insertHelper(node->right, value);
            }
        }
    }

    void inorderHelper(std::shared_ptr<Node> node) const
    {
        if (!node)
            return;
        inorderHelper(node->left);
        std::cout << node->value << " ";
        inorderHelper(node->right);
    }
};

#endif // _BINARY_TREE_H