#include <type_traits>

/*
 * decay is a template of the standart lib,
 * so, we can check out possible implementation 
 * https://en.cppreference.com/w/cpp/types/is_class
 */

namespace detail
{
    /* 
     * std::integral_constast is a base class for all structs from type_traits.  This
     * function checks for two things: T is not an union (this one can be done only using
     * std::is_union, cause compiler hook is necessary) and T has a pointer to a member.  
     */
    template<class T>
    std::integral_constant<bool, !std::is_union<T>::value> test(int T::*);
 
    /* Return std::false_type if there is no pointer to a member.  */
    template<class>
    std::false_type test(...);
}
 
template<class T>
struct my_is_class : decltype(detail::test<T>(nullptr)) {};

/* TESTS.  */
class A {};
class B { int j; };
struct C {};
union D { int a; char c; };
enum E { FIRST, SECOND, };

static_assert (my_is_class<A>::value);
static_assert (my_is_class<B>::value);
static_assert (my_is_class<C>::value);
static_assert (not my_is_class<D>::value);
static_assert (not my_is_class<E>::value);

int main ()
{}
