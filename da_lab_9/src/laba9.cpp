#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using TLl = long long;

const TLl MAX_VAL = pow(10, 15);

struct TEdge {
	TLl From, To, Price;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, start, finish;
	cin >> n >> m >> start >> finish;
	start--;
    finish--; 
    
	vector<TEdge> edges(m);
	TLl from, to, price;
	for (int i = 0; i < m; i++){
		cin >> from >> to >> price;
		from--; 
        to--;
		edges[i].From = from; 
        edges[i].To = to; 
        edges[i].Price = price;
	}

    vector<TLl> distances(n, MAX_VAL);
	distances[start] = 0;

	for (int i = 1; i < n; i++){
		bool changed = false;
		for (const TEdge& e : edges){
			if(distances[e.To] > distances[e.From] + e.Price){
				distances[e.To] = distances[e.From] + e.Price;
				changed = true;
			}
		}

		if(changed == false){
			break;
		}
	}

	if (distances[finish] == MAX_VAL){
		cout << "No solution" << '\n';
    }else{
		cout << distances[finish] << '\n';
    }

    return 0;
}
