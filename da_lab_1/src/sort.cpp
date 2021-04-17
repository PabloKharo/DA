#include "sort.hpp"

using TUll = unsigned long long;
using TVector_pair = NVector::TVector<TPair<NMd5::TMd5, TUll>>;
const size_t ONE = 1;
const size_t MAX_BLOCK_VAL = ONE << (NMd5::BLOCK_LEN * NMd5::BITS);

void RadixSort(TVector_pair& v){
    NVector::TVector<TUll> count(MAX_BLOCK_VAL); // Максимально возможное число в каждом блоке md5
    TVector_pair secv(v.Size()); // Вектор, в который записываем промежуточные результаты сортировки.

    for(int block = NMd5::MD5_BLOCKS - 1; block >= 0; --block)
    {          
        for(size_t i = 0; i < MAX_BLOCK_VAL; ++i){ 
            count[i] = 0;
        }

        for(size_t i = 0; i < v.Size(); ++i){ 
            TUll blockVal = v[i].Key[block];
            ++count[blockVal];
        }
        // Теперь в count[blockVal] хранится количество элементов, где значение блока равняется blockVal
        
        for(size_t i = 1; i < MAX_BLOCK_VAL; ++i){
            count[i] += count[i-1];
        }
        // Теперь в count[i] хранится количество элементов, которые меньше i. 
        // (Позиция в векторе для элемента, содержащего этот блок)

        for(long long i = v.Size() - 1; i >= 0; --i){
            TUll blockVal = v[i].Key[block];
            TUll pos = count[blockVal] - 1;
            secv[pos] = v[i];
            --count[blockVal];
        }
        // Теперь вектор secv - отсортированный по блоку вектор v и 
        // для дальнейшей работы необходимо поменять их местами.
        v.Swap(secv);
    }
}