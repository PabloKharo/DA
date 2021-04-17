#include <iostream>
#include <cstring>

using TUll = unsigned long long;
#include "tree.hpp"

const char OK[] = "OK";
const char EXIST[] = "Exist";
const char NO_SUCH_WORD[] = "NoSuchWord";
const char OUT_OF_MEMORY[] = "ERROR: out of memory";
const char FILE_NOT_OPEN[] = "ERROR: can't open file";
const char WRONG_VARIABLE[] = "ERROR: wrong variable in file";

void ToLower(char source[], char res[])
{
    for (size_t i = 0; source[i] != '\0'; ++i) {
        res[i] = tolower(source[i]);
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    char word[TTree::STR_SIZE] = "";
    TTree::VTree tree;
    while (std::cin >> word) {
        if (strcmp(word, "+") == 0) {
            char key[TTree::STR_SIZE] = "";
            TUll value;
            std::cin >> word >> value;
            ToLower(word, key);
            TTree::VInsert res = tree.Insert(key, value);
            if (res == TTree::VInsert::OK) {
                std::cout << OK << '\n';
            }else if(res == TTree::VInsert::EXIST) {
                std::cout << EXIST << '\n';
            }else if(res == TTree::VInsert::ERR_OUT_OF_MEMORY){
                std::cout << OUT_OF_MEMORY << '\n';
            }
            std::cout.flush();

        }else if (strcmp(word, "-") == 0) {
            char key[TTree::STR_SIZE] = "";
            std::cin >> word;
            ToLower(word, key);
            TTree::VDelete res = tree.Delete(key);
            if(res == TTree::VDelete::OK){
                std::cout << OK << '\n';
            }else{
                std::cout << NO_SUCH_WORD << '\n';
            }
            std::cout.flush();

        }else if (strcmp(word, "!") == 0) {
            std::cin >> word;
            if(strcmp(word, "Save") == 0){
                std::cin >> word;
                TTree::VSave res = tree.Save(word);
                if(res == TTree::VSave::OK){
                    std::cout << OK << '\n';
                }else if(res == TTree::VSave::ERR_OPEN){
                    std::cout << FILE_NOT_OPEN << '\n';
                }
            } 
            else if(strcmp(word, "Load") == 0){
                std::cin >> word;
                TTree::VLoad res = tree.Load(word);
                if(res == TTree::VLoad::OK){
                    std::cout << OK << '\n';
                }else if(res == TTree::VLoad::ERR_OPEN){
                    std::cout << FILE_NOT_OPEN << '\n';
                }else if(res == TTree::VLoad::ERR_WRONG_VARIABLE){
                    std::cout << WRONG_VARIABLE << '\n';
                }else if(res == TTree::VLoad::ERR_OUT_OF_MEMORY){
                    std::cout << OUT_OF_MEMORY << '\n';
                }
            }
            std::cout.flush();
        }else {
            char key[TTree::STR_SIZE] = "";
            ToLower(word, key);
            TTree::VSearch res = tree.Search(key);
            if (res.state == TTree::VSearch::OK) {
                std::cout << "OK: " << res.Key << '\n';
            }else {
                std::cout << NO_SUCH_WORD << '\n';
            }
            std::cout.flush();
        }
    }

    return 0;
}