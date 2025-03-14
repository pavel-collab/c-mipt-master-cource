#include <iostream>

// Определяем тип указателя на функцию
typedef void* (*FunctionPtr)();

void* selfReturningFunction() {
    // Возвращаем указатель на саму себя
    return (void*)selfReturningFunction;
}

// Посредник, который вызывает функцию и возвращает её указатель
FunctionPtr getSelfReturningFunction() {
    return selfReturningFunction;
}

int main() {
    // Получаем указатель на функцию
    FunctionPtr funcPtr = getSelfReturningFunction();

    // Вызываем функцию через указатель
    FunctionPtr returnedPtr = (FunctionPtr)funcPtr();

    // Проверяем, что указатель на функцию совпадает с оригиналом
    if (returnedPtr == funcPtr) {
        std::cout << "Pointers are equal" << std::endl;
    } else {
        std::cout << "Pointers are not equal" << std::endl;
    }

    return 0;
}
