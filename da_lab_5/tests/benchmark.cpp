#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>

#include "../src/tree.hpp"

using duration_t = std::chrono::milliseconds;

using namespace std;

void FastSolution(string& str){
    NSuffTree::TTree tree(str);
    tree.FindMin();
}


void SlowSolution(string& str){
    string minStr = str;
    for(int i = 0; i < (int)str.size(); i++){
        string newStr = str.substr(i, str.size() - i) + str.substr(0, i);
        minStr = min(minStr, newStr);
    }
}


int main(){
    string str;
    cin >> str;
    
    std::chrono::time_point<std::chrono::system_clock> startSlow, endSlow, startFast, endFast;
    startSlow = std::chrono::system_clock::now();
    SlowSolution(str);
    endSlow = std::chrono::system_clock::now();

    startFast = std::chrono::system_clock::now();
    FastSolution(str);
    endFast = std::chrono::system_clock::now();

    cout << "Naive solution time: " << std::chrono::duration_cast<duration_t>(endSlow - startSlow).count() << "ms \n";
    cout << "Ukkonen solution time: " << std::chrono::duration_cast<duration_t>(endFast - startFast).count() << "ms \n";

}
