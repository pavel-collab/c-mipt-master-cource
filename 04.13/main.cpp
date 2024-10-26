#include <iostream>

/*
 * decay is a template of the standart lib,
 * so, we can check out possible implementation 
 * https://en.cppreference.com/w/cpp/types/decay
 */

template<class T>
struct my_decay
{
private:
    // using remove reference to convert any type of reference to it's actual type
    typedef typename std::remove_reference<T>::type U;
public:
    // when we get some type, we have two basic option -- is it an some kind of array or function
    typedef typename std::conditional< 
        std::is_array<U>::value, // if it's an array just convert it to pointer
        typename std::add_pointer<typename std::remove_extent<U>::type>::type,
        typename std::conditional< 
            std::is_function<U>::value,
            typename std::add_pointer<U>::type, // if it's a function, convert to pointer
            typename std::remove_cv<U>::type // otherwise remove any const volatile annotation
        >::type
    >::type type;
};

template< class T >
using my_decay_t = typename my_decay<T>::type;

static_assert( std::is_same_v<my_decay_t<int>,        int>);
static_assert(!std::is_same_v<my_decay_t<int>,        float>);
static_assert( std::is_same_v<my_decay_t<int&>,       int>);
static_assert( std::is_same_v<my_decay_t<int&&>,      int>);
static_assert( std::is_same_v<my_decay_t<const int&>, int>);
static_assert( std::is_same_v<my_decay_t<int[2]>,     int*>);
static_assert(!std::is_same_v<my_decay_t<int[4][2]>,  int*>);
static_assert(!std::is_same_v<my_decay_t<int[4][2]>,  int**>);
static_assert( std::is_same_v<my_decay_t<int[4][2]>,  int(*)[2]>);
static_assert( std::is_same_v<my_decay_t<int(int)>,   int(*)(int)>);

int main()
{

}