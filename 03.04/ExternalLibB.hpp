#ifndef EXTERNAL_LIB_B_
#define EXTERNAL_LIB_B_

#include <iostream>

class ExternalClassB 
{
public:
    virtual short foo() const {
        std::cout << "ExternalClassB class foo method" << std::endl;
        return 2;
    }

    virtual ~ExternalClassB() {}
};

size_t ExternalLibBCheckFunction(ExternalClassB* const obj) {
    auto asssert_code = obj->foo();
    if (asssert_code != 2) {
        std::cout << "[Error] object is not valid" << std::endl;
        return 1;
    }
    return 0;
}

#endif // EXTERNAL_LIB_B_