#include "scope_guard.hpp"
#include "lib.hpp"
#include <functional>
#include <iostream>

auto main() -> int
{
    std::cout << "Example with exception:" << std::endl;
    {
        scope_guard::ScopeGuard guard_exc(action_a_backward, action_b_except);
        action_a_forward();
        guard_exc.exec();
    }

    std::cout << std::endl;

    std::cout << "Example without exception:" << std::endl;
    {
        scope_guard::ScopeGuard guard_no_exc(action_a_backward, action_b_no_except);
        action_a_forward();
        guard_no_exc.exec();
    }
}
