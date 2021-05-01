#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>

using duration_t = std::chrono::milliseconds;

using namespace std;

using TLl = long long;
vector<vector<TLl>> matrix;
int n;
int m;

void FastSolution(){
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

    for(int j = 1; j < m; j++){
        if(minval > matrix[n-1][j]){
            minval = matrix[n-1][j];
        }
    }
}

TLl FindMin(int i, int j){
    if(i == 0){
        return matrix[i][j];
    }
    if (j == 0){
        return min(FindMin(i-1, j), FindMin(i-1, j+1));
    }else if (j == m - 1){
        return min(FindMin(i-1, j-1), FindMin(i-1, j));
    }else{
        return min({FindMin(i-1, j-1), FindMin(i-1, j), FindMin(i-1, j+1)});
    }

}


void SlowSolution(){
    TLl minval = 10000000+1;
    for(int j = 0; j < m; j++){
        TLl curval = FindMin(n-1, j);
        if(minval < curval){
            minval = curval;
        }
    }
}


int main(){
    cin >> n >> m;
    matrix.resize(n, vector<TLl>(m));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> matrix[i][j];
        }
    }
    
    std::chrono::time_point<std::chrono::system_clock> startSlow, endSlow, startFast, endFast;
    startSlow = std::chrono::system_clock::now();
    SlowSolution();
    endSlow = std::chrono::system_clock::now();

    startFast = std::chrono::system_clock::now();
    FastSolution();
    endFast = std::chrono::system_clock::now();

    cout << "Naive solution time: " << std::chrono::duration_cast<duration_t>(endSlow - startSlow).count() << "ms \n";
    cout << "Dynamic solution time: " << std::chrono::duration_cast<duration_t>(endFast - startFast).count() << "ms \n";


}
