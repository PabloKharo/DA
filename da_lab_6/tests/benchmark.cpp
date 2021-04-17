#include "long_num.hpp"
#include <gmpxx.h>
#include <chrono>
#include <string>

using namespace std;
using duration_t = std::chrono::microseconds;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    mpz_t a,b,c;
    mpz_init(a);
    mpz_init(b);
    mpz_init(c);
    NLongNum::TLongNum num1, num2, num3;
    char action;
    std::string str1, str2;
    long long my_ts = 0, gmp_ts = 0;
    while (cin >> str1 >> str2 >> action) {
        NLongNum::TLongNum num1(str1);
        NLongNum::TLongNum num2(str2);
        NLongNum::TLongNum num3;
        mpz_set_str(a,str1.c_str(),10);
        mpz_set_str(b,str2.c_str(),10);
        std::chrono::time_point<std::chrono::system_clock> start, end;
        if (action == '+') {
            start = std::chrono::system_clock::now();
            (num1 + num2);
            end = std::chrono::system_clock::now();
            my_ts += std::chrono::duration_cast<duration_t>( end - start ).count();

            start = std::chrono::system_clock::now();
            mpz_add(c,a,b);
            end = std::chrono::system_clock::now();
            gmp_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
        }else if (action == '-') {
            if (num1 < num2) {
                continue;
            }
            start = std::chrono::system_clock::now();
            (num1 - num2);
            end = std::chrono::system_clock::now();
            my_ts += std::chrono::duration_cast<duration_t>( end - start ).count();

            start = std::chrono::system_clock::now();
            mpz_sub(c,a,b);
            end = std::chrono::system_clock::now();
            gmp_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
        }else if (action == '*') {
            start = std::chrono::system_clock::now();
            (num1 * num2);
            end = std::chrono::system_clock::now();
            my_ts += std::chrono::duration_cast<duration_t>( end - start ).count();

            start = std::chrono::system_clock::now();
            mpz_mul(c,a,b);
            end = std::chrono::system_clock::now();
            gmp_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
        }else if(action == '/'){
            if(num2.IsZero()){
                continue;
            }
            start = std::chrono::system_clock::now();
            (num1 / num2);
            end = std::chrono::system_clock::now();
            my_ts += std::chrono::duration_cast<duration_t>( end - start ).count();

            start = std::chrono::system_clock::now();
            mpz_div(c,a,b);
            end = std::chrono::system_clock::now();
            gmp_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
        }
    }

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(c);
    std::cout << "my mcs= " << my_ts << "\ngmp mcs= " << gmp_ts << std::endl;
    return 0;
}
