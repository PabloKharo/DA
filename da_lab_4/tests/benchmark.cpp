#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include "aho_corasick.hpp"

#include <chrono>

using namespace std;
using TUll = unsigned long long;

using duration_t = std::chrono::milliseconds;

void SplitPattern(string& line, vector<string>& vec){
    TUll i = 0;
    string word = "";
    while(i < line.size() && isspace(line[i])){
        i++;
    }
    while(i < line.size()){
        while(i < line.size() && !isspace(line[i])){
            word += tolower(line[i]);
            i++;
        }
        vec.push_back(word);
        word.clear();

        while(i < line.size() && isspace(line[i])){
            i++;
        }
    }

    if(word != ""){
        vec.push_back(word);
    }
}

void SplitText(string& line, vector<VInput>& vec, TUll numLine){
    TUll i = 0;
    TUll elem = 1;
    string word = "";
    while(i < line.size() && isspace(line[i])){
        i++;
    }

    while(i < line.size()){
        while(i < line.size() && !isspace(line[i])){
            word += tolower(line[i]);
            i++;
        }
        vec.push_back({word, numLine, elem});
        elem++;
        word.clear();

        while(i < line.size() && isspace(line[i])){
            i++;
        }
    }

    if(word != ""){
        vec.push_back({word, numLine, elem});
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    NAlgo::TTrie trie;
    string word;
    vector<string> pattern;
    vector<string> findlines;

    TUll line = 1;
    string strline = "";
    while(getline(cin, strline)){
        SplitPattern(strline, pattern);

        if(pattern.size() == 0){
            break;
        }
        string thisline = " ";
        for(size_t i = 0; i < pattern.size(); i++){
            thisline += pattern[i] + ' ';
        }
        findlines.push_back(thisline);

        trie.AddPattern(pattern, line);
        line++;
        pattern.clear();
    }

    trie.MakeSuffixes(); 

    vector<VInput> text;
    vector<TResults> results;
    line = 1;
    while(getline(cin, strline)){
        SplitText(strline, text, line);
        line++;
    }
    string alltext = " ";
    for(size_t i = 0; i < text.size(); i++){
        alltext += text[i].Str + ' ';
    }


    std::chrono::time_point<std::chrono::system_clock> start_aho, end_aho, start, end;
    start_aho = std::chrono::system_clock::now();
    trie.SearchPatterns(text, results);
    end_aho = std::chrono::system_clock::now();
    int64_t aho_time = std::chrono::duration_cast<duration_t>( end_aho - start_aho ).count();

    TUll count = 0;
    start = std::chrono::system_clock::now();
    for(size_t i = 0; i < findlines.size(); i++){
        size_t left = 0;
        while(true){
            left = alltext.find(findlines[i], left);
            if(left == string::npos){
                break;
            }
            left++;
            count++;
        }
    }
    end = std::chrono::system_clock::now();
    int64_t find_time = std::chrono::duration_cast<duration_t>( end - start ).count();

    cout << "aho time: " << aho_time << "ms \n";
    cout << "find time: " << find_time << "ms \n"; 

}