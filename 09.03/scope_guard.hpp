#ifndef _SCOPE_GUARD_H_
#define _SCOPE_GUARD_H_

#include <functional>

//TODO: add namespace
//TODO: move forward, backword functions to namespace

template <typename BackwardAction, typename ForwardAction>
//todo: rafector name of the class
class scope_guard
{
private:
    std::function<BackwardAction> backward_;
    std::function<ForwardAction> act_;

    //todO: REFACTOR names
    bool backward_flag_;

public:
    scope_guard (BackwardT *backward, ActionT *act)
      : backward_ (backward), act_ (act), backward_flag_ (true) {}

    //? What about rule of 5? Copy constructor, copy assignment, move constructor, move assignment

    ~scope_guard ()
    {
        if (!backward_flag_)
            return;

        try
        {
            backward_ ();
        }
        catch (...) { /* Ignore it.  */ }
    }

    void exec ()
    {
        try
        {
            act_ ();
            /* If we're here then exception not happenned.  */
            backward_flag_ = false;
        }
        catch (...)
        {
            /* Backward will happen.  */
        }
    }
};

#endif // _SCOPE_GUARD_H_