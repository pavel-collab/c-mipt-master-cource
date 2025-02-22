#ifndef _LIB_H_
#define _LIB_H_

#include <iostream>

//=============================================================================================

void action_a_forward()
{
    std::cout << "Forward function A" << std::endl;
}

void action_a_backward()
{
    std::cout << "Backward function A" << std::endl;
}

//=============================================================================================

void action_b_except()
{
    std::cout << "Action B with exception" << std::endl;
    throw std::runtime_error("B EXCEPTION!!!");
}

void action_b_no_except()
{
    std::cout << "Action B without exception" << std::endl;
}

//=============================================================================================

#endif //_LIB_H_