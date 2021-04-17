#include <iostream>
#include <map>
#include <chrono>

#include "tree.hpp"

using duration_t = std::chrono::microseconds;

int main() {
    std::map<std::string, unsigned long long> rb_tree;
    TTree::VTree tree;
    char action;
    char key[257];
    unsigned long long value;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t rb_ts = 0, bst_ts = 0;
    while( std::cin >> action ) {
        if( action == '+' ) {
            std::cin >> key >> value;
            {
                start = std::chrono::system_clock::now();
                rb_tree.insert( {key, value} );
                end = std::chrono::system_clock::now();
                rb_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
            {
                start = std::chrono::system_clock::now();
                tree.Insert( key, value );
                end = std::chrono::system_clock::now();
                bst_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
        }
        else if(action == '-'){
            std::cin >> key;
            {
                start = std::chrono::system_clock::now();
                rb_tree.erase(key);
                end = std::chrono::system_clock::now();
                rb_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
            {
                start = std::chrono::system_clock::now();
                tree.Delete(key);
                end = std::chrono::system_clock::now();
                bst_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
        }else{
            {
                start = std::chrono::system_clock::now();
                rb_tree.find(key);
                end = std::chrono::system_clock::now();
                rb_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
            {
                start = std::chrono::system_clock::now();
                tree.Search(key);
                end = std::chrono::system_clock::now();
                bst_ts += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
        }
    }
    std::cout << "std::map ms= " << rb_ts << "\nrb ms= " << bst_ts << std::endl;
}