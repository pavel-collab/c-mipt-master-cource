#ifndef EXTERNAL_LIB_A_
#define EXTERNAL_LIB_A_

#include <iostream>

class ExternalClassA 
{
public:
    virtual short foo() const {
        std::cout << "ExternalClassA class foo method" << std::endl;
        return 1;
    }

    virtual ~ExternalClassA() {}
};

size_t ExternalLibACheckFunction(ExternalClassA* const obj) {
    auto asssert_code = obj->foo();
    if (asssert_code != 1) {
        std::cout << "[Error] object is not valid" << std::endl;
        return 1;
    }
    return 0;
}

#endif // EXTERNAL_LIB_A_