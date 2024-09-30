#include <iostream>
#include <vector>

/*

NOTE: in this implementation we assume, that the 0 Fibbonachi number is 0,
the 1st one is 1, 2nd is 1, 3rd is 2, etc.

As we're limeted by numbers computer representation, by this
implementation we can compute only 93 Fibbonachies number.

The most powerful number type in C++ is unsigned long long which is 128 bit
and the upper limit is 18446744073709551615 in decimal.
However, the 94th Fibbonachi is 19740274219868223167, that is not fit 
to unsigned long long. If we want to compute next, we should use long arithmetics in boost
or smth else, but I'm not shure, we have to do it in this task.

*/

unsigned long long stupid_get_fib(unsigned long long n) {
    if (n == 0)
        return 0;
    
    if (n == 1 || n == 2) {
        return 1;
    }

    return stupid_get_fib(n - 1) + stupid_get_fib(n - 2);
}

unsigned long long get_fib(unsigned long long n, std::vector<unsigned long long>& save) {
    if (n == 0)
        return 0;
    
    if (n == 1 || n == 2) {
        return 1;
    }

    if (save[n-2] == 0) {
        save[n-2] = get_fib(n-2, save);
    }

    if (save[n-1] == 0) {
        save[n-1] = get_fib(n-1, save);
    }

    save[n] = save[n-2] + save[n-1];

    return save[n];
}

int main() {

    unsigned long long N;
    std::cin >> N;

    // std::cout << stupid_get_fib(N) << std::endl;

    std::vector<unsigned long long> save(N+1, 0);
    std::cout << get_fib(N, save) << std::endl;
}