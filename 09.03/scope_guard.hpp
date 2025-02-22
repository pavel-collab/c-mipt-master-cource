#ifndef _SCOPE_GUARD_H_
#define _SCOPE_GUARD_H_

#include <functional>

namespace scope_guard {

template <typename ActionT, typename BackwardT>
class ScopeGuard {

public:
    ScopeGuard(BackwardT* backward, ActionT* act)
        : m_backward(backward)
        , m_action(act)
        , m_backward_flag(true)
    {
    }

    //? What about rule of 5? Copy constructor, copy assignment, move constructor, move assignment

    ~ScopeGuard()
    {
        if (!m_backward_flag)
            return;

        try {
            backward_();
        } catch (...) { /* Ignore it.  */
        }
    }

    void exec()
    {
        try {
            act_();
            /* If we're here then exception not happenned.  */
            m_backward_flag = false;
        } catch (...) {
            /* Backward will happen.  */
        }
    }

private:
    std::function<BackwardAction> m_backward;
    std::function<Action> m_action;

    bool m_backward_flag;
};

}

#endif // _SCOPE_GUARD_H_