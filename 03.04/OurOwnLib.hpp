#ifndef OUR_OWN_LIB_
#define OUR_OWN_LIB_

#include "ExternalLibA.hpp"
#include "ExternalLibB.hpp"

class FirstIntermediateParentClass: public ExternalClassA
{
public:
    virtual ~FirstIntermediateParentClass() {}

    virtual short FirstIntermediateFoo() const = 0;

private:
    short foo() const {
        return FirstIntermediateFoo();
    }
};

class SecondIntermediateParentClass: public ExternalClassB
{
public:
    virtual ~SecondIntermediateParentClass() {}

    virtual short SecondIntermediateFoo() const = 0;

private:
    short foo() const {
        return SecondIntermediateFoo();
    }
};

class Child: public FirstIntermediateParentClass, public SecondIntermediateParentClass
{
public:
    short FirstIntermediateFoo() const {
        std::cout << "Child first parent class method override" << std::endl;
        return 1;
    }

    short SecondIntermediateFoo() const {
        std::cout << "Child second parent class method override" << std::endl;
        return 2;
    }
};

#endif // OUR_OWN_LIB_