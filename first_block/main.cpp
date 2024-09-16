#include <iostream>

struct EamptyClass {
    EamptyClass() {
        std::cout << "Hello, world!" << std::endl;
    }
};

EamptyClass eampty_class_glog_var;

int main() {}