#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int m, n;
    bool ok = true;
    cin >> m >> n;

    vector<int> res(n);
    vector<int> prices(m);
    vector<vector<double>> subst(m, vector<double>(n));

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            cin >> subst[i][j];
        }
        cin >> prices[i];
    }

    for (int j = 0; j < n; j++){
        int minPrice = 51;
        int minRow = -1;
        for (int i = 0; i < m; i++){
            if (prices[i] < minPrice && subst[i][j] != 0){
                minRow = i;
                minPrice = prices[i];
            }
        }

        if (minRow == -1){
            ok = false;
            break;
        }

        prices[minRow] = 51;
        res[j] = minRow + 1;
        
        for (int i = 0; i < m; i++){
            if(prices[i] == 51){
                continue;
            }

            double koeff = subst[i][j] / subst[minRow][j];
            for (int col = j; col < n; col++){
                subst[i][col] = subst[i][col] - (subst[minRow][col] * koeff);
            }
        }

    }

    if(!ok){
        cout << "-1\n";
        return 0;
    }

    sort(res.begin(), res.end());
    for (int i = 0; i < n; i++){
        cout << res[i] << ' ';
    }
    cout << '\n';

    return 0;

}
