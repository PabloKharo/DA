#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
using TLl = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<TLl>> matrix(n, vector<TLl>(m));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> matrix[i][j];
        }
    }
    
    for(int i = 1; i < n; i++){
        for (int j = 0; j < m; j++) {
            if (j == 0){
                matrix[i][j] += min(matrix[i-1][j], matrix[i-1][j+1]);
            }else if (j == m - 1){
                matrix[i][j] += min(matrix[i-1][j-1], matrix[i-1][j]);
            }else{
                matrix[i][j] += min({matrix[i-1][j-1], matrix[i-1][j], matrix[i-1][j+1]});
            }
        }
    }

    TLl minval = matrix[n-1][0];
    int mincol = 0;

    for(int j = 1; j < m; j++){
        if(minval > matrix[n-1][j]){
            minval = matrix[n-1][j];
            mincol = j;
        }
    }

    vector<int> path(n);
    for(int i = n-1; i >= 0; i--){
        if (mincol == 0) {
            if(matrix[i][mincol+1] < matrix[i][mincol]){
                mincol++;
            }
        }else if (mincol == m - 1) {
             if(matrix[i][mincol-1] < matrix[i][mincol]){
                mincol--;
            }
        }else {
            TLl colval = min({matrix[i][mincol-1], matrix[i][mincol], matrix[i][mincol+1]});
            if (colval == matrix[i][mincol-1]){
                mincol--;
            }else if(colval == matrix[i][mincol+1]){
                mincol++;
            }
        }
        path[i] = mincol;
    }

    cout << minval << '\n';
    for(int i = 0; i < n-1; i++){
        cout << '(' << i+1 << ',' << path[i]+1 << ") ";
    }
    cout << '(' << n << ',' << path[n-1]+1 << ")\n";

}
