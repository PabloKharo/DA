#include <iostream>
#include <string>

#include "lz77/lz77.hpp"

using namespace std;

int main(){
    string type;
    cin >> type;
    if(type == "compress"){
        LZ77::CompressText();
    }else if(type == "decompress"){
        LZ77::DecompressText();
    }

    return 0;

}
