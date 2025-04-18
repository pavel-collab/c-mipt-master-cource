#include <iostream>
#include <vector>

//TODO: спросить у Даника, должно ли так быть, что 1й и 2й тесты почти идентичны
//TODO: придумать что-то с третьим тестом

/*
В случае, когда мы сохдаем вектор через value initialisation, vector.size = vactor.capacity.
Под вектор в этом случае выделяется ровно столько памяти, сколько заявлено объектов. 
Скорее всего, в конструкторе под капотом вызывается функция reserve с аргументом, равным количеству элементов в векторе.
При нехватке памяти происходит реаллокация памяти, начальное значение capacity увеличивается в 2 раза.
*/
float test_1() {
    std::cout << "Test capacity factor check" << std::endl << std::endl;

    std::vector<int> test_vector = {1, 2, 3};
    auto start_capacity = test_vector.capacity();

    std::cout << "vector capacity after declaration is " << start_capacity << std::endl;

    int _ = 0;
    while (test_vector.capacity() == start_capacity)
    {
        test_vector.push_back(_++);
    }
    std::cout << "vector reallocation was on the vector size " << test_vector.size() << std::endl;

    float factor = test_vector.capacity() / start_capacity;
    return factor;
}

/*
В случае, когда память резервируется вручную вектор заполняется ровно до размера, который мы задали.
Далее происходит реаллокация, память увеличивается в 2 раза. Отличие данного случая от первого заключается лишь в том,
что вектор реаллоцирует память не сразу, а в тот момент, когда зарезервированная память заполнится значениями.
*/
float test_2() {
    std::cout << "Test capacity factor check after reservatoion" << std::endl << std::endl;

    std::vector<int> test_vector;
    // reserve space for a 10 elements 
    test_vector.reserve(10);

    auto start_capacity = test_vector.capacity();
    std::cout << "vector capacity after reservation is " << start_capacity << std::endl;

    int _ = 0;
    while (test_vector.capacity() == start_capacity)
    {
        test_vector.push_back(_++);
    }
    std::cout << "vector reallocation was on the vector size " << test_vector.size() << std::endl;

    float factor = test_vector.capacity() / start_capacity;
    return factor;
}

/*
В случае, когда вектор резервирует больше памяти, чем может выделить операционная система, конструктор кидает
исключение std::bad_alloc. Происходит раскрутка стека и завершение программы без утечки памяти.
*/
void test_3() {
    try
    {
        std::vector<double> test_vector (1'000'000'000'000);
    } catch(const std::bad_alloc& e)
    {
        std::cerr << e.what() << '\n';
    }
}

int main() {
    #if TEST==1
    auto std_vector_factor = test_1();
    std::cout << "The factor of std::vector capacity increase is " << std_vector_factor << std::endl;    
    #endif

    #if TEST==2
    auto std_vector_factor = test_2();
    std::cout << "The factor of std::vector capacity increase is " << std_vector_factor << std::endl;
    #endif

    #if TEST==3
    test_3();
    #endif
}