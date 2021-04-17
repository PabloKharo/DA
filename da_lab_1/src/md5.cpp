#include "md5.hpp"
#include <stdexcept>
#include <string>
#include <iomanip>

namespace NMd5{

    unsigned short TMd5::operator[] (const int i) const{
        if(i >= 0 && i < MD5_BLOCKS){
            return this->Blocks[i];
        }else{
            throw std::length_error{ "Md5 index is out of range" };
        }
    }

    bool TMd5::operator<(const TMd5& md5)
    {
        for(int block = 0; block < MD5_BLOCKS; ++block){
            if((*this)[block] < md5[block]){
                return true;
            }else{
                return false;
            }
            
        }
        return false;
    }
    
    std::istream& operator>> (std::istream &in, TMd5& md5){
        std::string str;

        if (!(in >> str)){
            return in;
        }
        
        for (int block = 0; block < MD5_BLOCKS; ++block){ 
            unsigned short blockVal = 0;// Значение блока

            for (int i = 0; i < BLOCK_LEN; ++i){
                blockVal = blockVal << BITS; // Сдвигается текущее значение блока на 4 бита 
                                             //(столько необходимо для 16-ного числа)
                char c = str[block * BLOCK_LEN + i];   
                // К значению блока прибавляется значение следующего разряда         
                if ('0' <= c && c <= '9'){
                    blockVal += c - '0';
                }else{
                    blockVal += c - 'a' + DECIMAL;
                }
            }
            md5.Blocks[block] = blockVal;
        }

        return in;
    }

    std::ostream& operator<< (std::ostream &out, const TMd5& md5){
        for (int block = 0; block < MD5_BLOCKS; ++block){
            std::ios_base::fmtflags f(out.flags()); // Сохраняем флаги потока, чтобы следующие числа выводить
                                                    // в стандартном формате
            out << std::hex << std::setfill('0') << std::setw(BLOCK_LEN) << md5[block];
            out.flags(f);
        }
        return out; 
    }


}