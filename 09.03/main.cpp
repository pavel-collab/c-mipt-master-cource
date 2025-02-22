#include "scope_guard.hpp"
#include <iostream>
#include <functional>

void forward ()
{
    std::cout << "Forward function (A)" << std::endl;
}

void backward ()
{
    std::cout << "Backward function (A)" << std::endl;
}

void throw_exc ()
{
    std::cout << "B action with exception" << std::endl;
    throw std::runtime_error ("B EXCEPTION!!!");
}

void non_throw_exc ()
{
    std::cout << "B action without exception" << std::endl;
}

auto main () -> int
{
    //TODO: refactor output
    std::cout << "Example with exception:" << std::endl;
    {
        scope_guard guard_exc (backward, throw_exc);
        forward ();
        guard_exc.exec ();
    }

    std::cout << std::endl << "-----------" << std::endl;

    std::cout << "Example without exception:" << std::endl;
    {
        scope_guard guard_no_exc (backward, non_throw_exc);
        forward ();
        guard_no_exc.exec ();
    }
}

