#include <iostream>

#include "vector.hpp"
#include "pair.hpp"
#include "md5.hpp"
#include "sort.hpp"

using TUll = unsigned long long;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    NVector::TVector<TPair<NMd5::TMd5, TUll>> v;
    TPair<NMd5::TMd5, TUll> p;
    while (std::cin >> p) {
        v.PushBack(p);
    }

    RadixSort(v);
    
    for(TUll i = 0; i < v.Size(); ++i) {
        std::cout << v[i] << '\n';
    }

    return 0;
}

