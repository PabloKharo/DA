#include <iostream>
#include <chrono>
#include <algorithm>

#include "vector.hpp"
#include "pair.hpp"
#include "md5.hpp"
#include "sort.hpp"

// using duration_t = std::chrono::microseconds;
// const std::string DURATION_PREFIX = "us";

using duration_t = std::chrono::milliseconds;
const std::string DURATION_PREFIX = "ms";

using TUll = unsigned long long;
using TVector_pair = NVector::TVector<TPair<NMd5::TMd5, TUll>>;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    TVector_pair input;
    TVector_pair input_stl;   
    TPair<NMd5::TMd5, TUll> p;
    while (std::cin >> p) {
      input.PushBack(p);
    }

    input_stl = input;

    std::cout << "Count of lines is " << input.Size() << std::endl;

    // Измеряем время работы разрядной сортировки.
    std::chrono::time_point < std::chrono::system_clock > start_ts = std::chrono::system_clock::now();
    RadixSort(input);
    auto end_ts = std::chrono::system_clock::now();
    uint64_t counting_sort_ts = std::chrono::duration_cast < duration_t > ( end_ts - start_ts ).count();

    // Измеряем время работы stl сортировки.
    start_ts = std::chrono::system_clock::now();
    std::stable_sort(input_stl.Begin(), input_stl.End() );
    end_ts = std::chrono::system_clock::now();

    uint64_t stl_sort_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();
    std::cout << "Radix sort time: " << counting_sort_ts << DURATION_PREFIX << std::endl;
    std::cout << "STL stable sort time: " << stl_sort_ts << DURATION_PREFIX << std::endl;
}