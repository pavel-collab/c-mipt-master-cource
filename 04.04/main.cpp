#include <iostream>


template <typename T>
void count_int(int& result, T arg){}

template <>
void count_int(int& result, int arg)
{
	result += arg;
}

template < typename T, typename ... Ts > 
void count_int(int& result, T arg, Ts ... args)
{
	count_int(result, arg);
	count_int(result, args...);
}


int main() {
	int result = 0;
    count_int(result, 'a', 12.4, 12.0, 1, 'b', 'm', 2, 3); // expected 6
    std::cout << result << std::endl;
}  