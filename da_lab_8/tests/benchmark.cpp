#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>

using duration_t = std::chrono::milliseconds;

using namespace std;

int m, n;

void FastSol(vector<vector<double>>& subst){
    for (int j = 0; j < n; j++){
        int minPrice = 51;
        int minRow = -1;
        for (int i = 0; i < m; i++){
            if (subst[i][n] < minPrice && subst[i][j] != 0){
                minRow = i;
                minPrice = subst[i][n];
            }
        }

        if (minRow == -1){
            break;
        }

        subst[minRow][n] = 51;
        
        for (int i = 0; i < m; i++){
            if(subst[minRow][n] == 51){
                continue;
            }

            double koeff = subst[i][j] / subst[minRow][j];
            for (int col = j; col < n; col++){
                subst[i][col] = subst[i][col] - (subst[minRow][col] * koeff);
            }
        }

    }
}

void SlowSol(vector<vector<double>>& subst){
    int price = 0;
    for (int j = 0; j < n; j++){
        int minRow = -1;
        for (int i = 0; i < m; i++){
            if (subst[i][n] != 51 && subst[i][j] != 0){
                minRow = i;
                price += subst[i][n];
                break;
            }
        }

        if (minRow == -1){
            break;
        }

        subst[minRow][n] = 51;
        
        for (int i = 0; i < m; i++){
            if(subst[minRow][n] == 51){
                continue;
            }

            double koeff = subst[i][j] / subst[minRow][j];
            for (int col = j; col < n; col++){
                subst[i][col] = subst[i][col] - (subst[minRow][col] * koeff);
            }
        }

    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> m >> n;
    vector<vector<double>> subst(m, vector<double>(n + 1));

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n + 1; j++){
            cin >> subst[i][j];
        }
    }

    vector<vector<double>> tmpSubst = subst;
    
    std::chrono::time_point<std::chrono::system_clock> startSlow, endSlow, startFast, endFast;
    startFast = std::chrono::system_clock::now();
    FastSol(tmpSubst);
    endFast = std::chrono::system_clock::now();
    cout << "Greed solution time: " << std::chrono::duration_cast<duration_t>(endFast - startFast).count() << "ms \n";

    
    startSlow = std::chrono::system_clock::now();
    do{
        tmpSubst = subst;
        SlowSol(tmpSubst);
    }while(next_permutation(subst.begin(), subst.end()));
    endSlow = std::chrono::system_clock::now();
    cout << "Naive solution time: " << std::chrono::duration_cast<duration_t>(endSlow - startSlow).count() << "ms \n";

}
