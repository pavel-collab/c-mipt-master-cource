#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <stdexcept>

double evaluateRPN(const std::string& expression) {
    std::istringstream iss(expression);
    std::stack<double> stack;
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0]) || 
           (token.length() > 1 && token[0] == '-' && std::isdigit(token[1]))) {
            // Число (возможно отрицательное)
            stack.push(std::stod(token));
        } else if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.size() < 2)
                throw std::runtime_error("Недостаточно операндов для операции");

            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            double result = 0;

            if (token == "+") result = a + b;
            else if (token == "-") result = a - b;
            else if (token == "*") result = a * b;
            else if (token == "/") {
                if (b == 0) throw std::runtime_error("Деление на ноль");
                result = a / b;
            }

            stack.push(result);
        } else {
            throw std::runtime_error("Неверный токен: " + token);
        }
    }

    if (stack.size() != 1)
        throw std::runtime_error("Неверное количество элементов в стеке после вычисления");

    return stack.top();
}

int main() {
    std::string input;
    std::cout << "Введите выражение в обратной польской нотации (через пробел):\n";
    std::getline(std::cin, input);

    try {
        double result = evaluateRPN(input);
        std::cout << "Результат: " << result << '\n';
    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << '\n';
    }

    return 0;
}