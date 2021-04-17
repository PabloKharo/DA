#pragma once

#include <iostream>

namespace NMd5{

    const int BITS = 4;                 
    const int MD5_LEN = 32;      
    const int BLOCK_LEN = 4;
    const int MD5_BLOCKS = MD5_LEN/BLOCK_LEN;  
    const int DECIMAL = 10;   
    
    class TMd5{
    private:
        unsigned short Blocks[MD5_BLOCKS];
    public:
        unsigned short operator[] (const int i) const;
        friend std::istream& operator>> (std::istream &in, TMd5& md5);
        bool operator< (const TMd5&);
    };
    
    std::ostream& operator<< (std::ostream &out, const TMd5& md5);

}