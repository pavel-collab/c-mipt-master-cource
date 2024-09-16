#include <iostream>

int main() {
    char symb;
    std::cin >> symb;

    switch (symb)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        std::cout << "digit" << std::endl;
        break;
    case '+':
    case '-':
    case '*':
    case '/':
        std::cout << "operator" << std::endl;
        break;
    case '(':
    case ')':
        std::cout << "braket" << std::endl;
        break;
    default:
        std::cout << "other symbol" << std::endl;
        break;
    }
}