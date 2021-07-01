#include <iostream>
#include <string>

#include "lz77.hpp"
#include "sufftree/tree.hpp"
#include <chrono>

int Buffer = 16384;
using duration_t = std::chrono::milliseconds;

namespace LZ77{
void CompressText(){
    NSuffTree::TTree tree;
    int textLen = 0;
    int prevRes = 0;
    int curLen = 0;
    // std::chrono::time_point<std::chrono::system_clock> start, end;
    // int64_t res_time = 0;
    char c;
    // cout << "decompress\n";
    while(cin >> c){
        // start = std::chrono::system_clock::now();
        int curRes;
        tree.Add(c);
        textLen++;
        if((curRes = tree.FindLastChar()) != -1){ 
            curLen++;
            prevRes = curRes;
            // end = std::chrono::system_clock::now();
            // res_time += std::chrono::duration_cast<duration_t>( end - start ).count();
            continue;
        }

        if(textLen > Buffer){
            tree.Deinit();
            tree.Init();
            textLen = 0;
        }
        // end = std::chrono::system_clock::now();
        // res_time += std::chrono::duration_cast<duration_t>( end - start ).count();

        if (curLen == 0) {
            cout << 0 << " " << 0 << c;
        }else {
            cout << (textLen - 1) - prevRes << " " << curLen << c;
        }

        if(textLen > Buffer){
            textLen = 0;
        }
        curLen = 0;
        prevRes = 0;      
    }

    if (curLen != 0) {
        cout << textLen - prevRes << " " << curLen - 1 << c;
    }
    cerr << "time: " << res_time << '\n';

}

void DecompressText(){
    string text;
    int offset;
    int len;
    char c;

    int textLen = 0;
    // std::chrono::time_point<std::chrono::system_clock> start, end;
    // int64_t res_time = 0;
    // cout << "compress\n";
    while (cin >> offset >> len >> c) {
        // start = std::chrono::system_clock::now();
        for (int i = 0; i < len; i++) {
            text += text[textLen - offset];
            textLen++;
        }
        
        text += c;
        textLen++;

        if(textLen > Buffer){
            cout << text;
            textLen = 0;
            text = "";
        }
        // end = std::chrono::system_clock::now();
        // res_time += std::chrono::duration_cast<duration_t>( end - start ).count();
    }
    if(text != ""){
        cout << text;
    }
    cerr << "time: " << res_time << '\n';

}
}