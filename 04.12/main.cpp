#include <iostream>

// используем специализацию + частичную специализацию структур + специализацию переменных
template <typename T> struct add_const { using type = const T; };
/* Обратим внимание, чтобы показать, что type является именно типом, 
 * а не статическим объектом класса (например полем), мы используем
 * ключевое слово typename.
 */
template <typename T> using add_const_t = typename add_const<T>::type;


template <typename T> struct remove_const           {using type = T;};
template <typename T> struct remove_const <const T> {using type = T;};

template <typename T> using remove_const_t = typename remove_const<T>::type;

int main()
{
    // static assert check predicate on the compilation stage
    static_assert(std::is_same_v<add_const_t<int>, const int>);
    static_assert(std::is_same_v<remove_const_t<const int>, int>);
}