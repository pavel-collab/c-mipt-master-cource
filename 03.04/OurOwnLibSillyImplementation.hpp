#ifndef OUR_OWN_LIB_SILLY_IMPLEMENTATION_
#define OUR_OWN_LIB_SILLY_IMPLEMENTATION_

#include "ExternalLibA.hpp"
#include "ExternalLibB.hpp"

/*
 * First attempt: try just derive child class and override the method
*/
class SimpleChild: public ExternalClassA, public ExternalClassB  
{
public:
    short foo() const override {
        std::cout << "SimpleChild class method foo" << std::endl;
        return 1;
    }
};

#endif // OUR_OWN_LIB_SILLY_IMPLEMENTATION_