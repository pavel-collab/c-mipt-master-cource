#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <iostream>
#include <memory>

template <typename T>
class BinaryTree;

template <typename T>
class Node {
    public:

    Node(int val)
        : m_value(val)
    {
    }

    template <typename U>
    friend class BinaryTree;

    private:

    T getValue()
    {
        return m_value;
    }

    std::shared_ptr<Node> getLeftChild()
    {
        return m_left;
    }

    std::shared_ptr<Node> getRightChild()
    {
        return m_right;
    }

    std::weak_ptr<Node> getParent()
    {
        return m_parent;
    }

    void bindLeftChild(std::shared_ptr<Node> left_child)
    {
        m_left = left_child;
    }

    void bindRightChild(std::shared_ptr<Node> right_child)
    {
        m_right = right_child;
    }

    void bindParent(std::weak_ptr<Node> parent)
    {
        m_parent = parent;
    }

    T m_value;
    std::shared_ptr<Node> m_left;
    std::shared_ptr<Node> m_right;
    std::weak_ptr<Node> m_parent;
};

template <typename T>
class BinaryTree {
public:

    void insert(int value)
    {
        if (!root) {
            root = std::make_shared<Node<T> >(value);
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
    void insertHelper(std::shared_ptr<Node<T> > node, int value)
    {
        if (value < node->getValue()) {
            if (!node->getLeftChild()) {
                node->bindLeftChild(std::make_shared<Node<T> >(value));
                node->getLeftChild()->bindParent(node);
            } else {
                insertHelper(node->getLeftChild(), value);
            }
        } else {
            if (!node->getRightChild()) {
                node->bindRightChild(std::make_shared<Node<T> >(value));
                node->getRightChild()->bindParent(node);
            } else {
                insertHelper(node->getRightChild(), value);
            }
        }
    }

    void inorderHelper(std::shared_ptr<Node<T> > node) const
    {
        if (!node)
            return;
        inorderHelper(node->getLeftChild());
        std::cout << node->getValue() << " ";
        inorderHelper(node->getRightChild());
    }

    std::shared_ptr<Node<T> > root;
};

#endif // _BINARY_TREE_H