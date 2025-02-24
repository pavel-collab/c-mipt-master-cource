#ifndef _NODE_H_
#define _NODE_H_

namespace node
{
    template <typename T>
    class Node {
        public:

        Node(int val)
            : m_value(val)
        {
        }

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

        private:

        T m_value;
        std::shared_ptr<Node> m_left;
        std::shared_ptr<Node> m_right;
        std::weak_ptr<Node> m_parent;
    };
}

#endif //_NODE_H_