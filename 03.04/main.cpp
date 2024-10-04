#include "ExternalLibA.hpp"
#include "ExternalLibB.hpp"
#include "OurOwnLibSillyImplementation.hpp"
#include "OurOwnLib.hpp"

#include <iostream>

/*
 * Note: in community this problem is known as a "Siamese Twin Functions" problem.
 * Check this out: http://www.gotw.ca/publications/mill07.htm
 */

/*
 * What is the case: let's assume we have two external libs: ExternlaLibA and ExternalLibB.
 * We have virtual parent classes in this libs and we want to derive our own child class 
 * with our own functionality to be able to pass our class object to the functions from this libs
 * via poiter or referens of the parent classes (default situation).
 * 
 * But here we have a little problem: it's similar semantic functions in both of the parent classes.
 * So, if we just override this function in the derived class, when we will call this function
 * through the pointer to the parent class we will give the logic from the child class in both cases.
 * That is not we actually want. Instead of it we want to create the Child class object, take the
 * first parent class pointer, take the second parent class pointer and see the different logic
 * in the two different cases.
 */


/*
 * Check out silly case:
 * g++ -DSILLY=1 main.cpp
 * Check out the right case:
 * g++ main.cpp
 */

int main() {

#if SILLY==1 // check out the silly implementation
    ExternalClassA* const external_class_a_ptr = new SimpleChild();
    ExternalClassB* const external_class_b_ptr = new SimpleChild();

    if (ExternalLibACheckFunction(external_class_a_ptr)) { // it's ok
        perror("[Err] error with checking external class a ptr");
    }
    /*
     * it will failed, cz second external lib check function is waiting for a return value 2, 
     * but we have no chance return 2 throught the method overriding
     */
    if (ExternalLibBCheckFunction(external_class_b_ptr)) {
        perror("[Err] error with checking external class b ptr");
    }

#else // check out correct implementation
    ExternalClassA* const external_class_a_ptr = new Child();
    ExternalClassB* const external_class_b_ptr = new Child();

    /* 
     * In this case we will get correct output.
     * On the one hand we overrided the logic of our functions,
     * on the other hand we saved the logic important for the external lib functions.
     */
    if (ExternalLibACheckFunction(external_class_a_ptr)) { // it's ok
        perror("[Err] error with checking external class a ptr");
    }
    if (ExternalLibBCheckFunction(external_class_b_ptr)) { // it's ok
        perror("[Err] error with checking external class b ptr");
    }

#endif

    return 0;
}