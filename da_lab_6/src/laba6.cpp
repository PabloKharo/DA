#include "long_num.hpp"

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    NLongNum::TLongNum num1, num2;
    char action;
    while (cin >> num1 >> num2 >> action) {
        if (action == '+') {
            cout << num1 + num2 << '\n';
        }else if (action == '-') {
            if (num1 < num2) {
                cout << "Error" << '\n';
                cout.flush();
                continue;
            }
            cout << num1 - num2 << '\n';
        }else if (action == '*') {
            cout << num1 * num2 << '\n';
        }else if(action == '^'){
            if(num1.IsZero() && num2.IsZero()){
                cout << "Error" << '\n';
                cout.flush();
                continue;
            }
            cout << (num1 ^ num2) << '\n';
        }else if(action == '/'){
            if(num2.IsZero()){
                cout << "Error" << '\n';
                cout.flush();
                continue;
            }
            cout << num1 / num2 << '\n';
        }else if(action == '<'){
            cout << ((num1 < num2) ? "true" : "false") << '\n';
        }else if(action == '>'){
            cout << ((num1 > num2) ? "true" : "false") << '\n';
        }else if(action == '=' ){
            cout << ((num1 == num2) ? "true" : "false") << '\n';
        }
        cout.flush();
    }
    return 0;
}

