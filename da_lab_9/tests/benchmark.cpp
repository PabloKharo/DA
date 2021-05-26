#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <cmath>

using duration_t = std::chrono::milliseconds;

using namespace std;
using TLl = long long;
const TLl MAX_VAL = pow(10, 15);

struct TEdge {
	TLl From, To, Price;
};

vector<TEdge> edges;
int n, m, start, finish;

vector<bool> was;
TLl SlowSolution(int from){
    if(from == finish){
        return 0;
    }

    TLl res = MAX_VAL;
    was[from] = true;
    for(const TEdge& e : edges){
        if(e.From == from && was[e.To] == false){
            res = min(res, SlowSolution(e.To) + e.Price);
        }
    }
    was[from] = false;

    return res;
}

void FastSolution(){
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
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

	cin >> n >> m >> start >> finish;
	start--;
    finish--; 
    
	edges.resize(m);
	TLl from, to, price;
	for (int i = 0; i < m; i++){
		cin >> from >> to >> price;
		from--; 
        to--;
		edges[i].From = from; 
        edges[i].To = to; 
        edges[i].Price = price;
	}
    
    
    std::chrono::time_point<std::chrono::system_clock> startSlow, endSlow, startFast, endFast;
    startSlow = std::chrono::system_clock::now();
    was.resize(n);
    SlowSolution(start);
    endSlow = std::chrono::system_clock::now();

    startFast = std::chrono::system_clock::now();
    FastSolution();
    endFast = std::chrono::system_clock::now();

    cout << "Naive solution time: " << std::chrono::duration_cast<duration_t>(endSlow - startSlow).count() << "ms \n";
    cout << "FordBellman solution time: " << std::chrono::duration_cast<duration_t>(endFast - startFast).count() << "ms \n";


}
