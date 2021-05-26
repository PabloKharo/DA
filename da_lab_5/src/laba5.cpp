#include <iostream>
#include <string>

#include "tree.hpp"

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string str;
    cin >> str;
    NSuffTree::TTree tree(str);
    cout << tree.FindMin() << endl;
}


