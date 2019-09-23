#include <bits/stdc++.h>
using namespace std;


// Returns a vector with a valid topological sort of the directed graph.
// Returns an empty vector if a cycle is found.
vector<int> topological_sort(vector<vector<int> > &adj_list){
    vector<int> rv;
    queue<int> q;
    vector<int> incoming_edges(adj_list.size(),0);
    for (auto source_list: adj_list) {
        for (int dest: source_list){
            incoming_edges[dest]++;
        }
    }

    for (int i = 0; i < incoming_edges.size(); i++){
        if (incoming_edges[i] == 0){
            q.push(i);
        }
    }
    
    while (!q.empty()){
        rv.push_back(q.front());
        for (int neighbor : adj_list[q.front()]){
            incoming_edges[neighbor] --;
            if (incoming_edges[neighbor] == 0){
                q.push(neighbor);
            }
        }
        q.pop();
    }

    for (int i: incoming_edges){
        if (i > 0){
            return vector<int>(0);
        }
    }

    return rv;
}

int main(){
    vector<vector<int> > graph1 = {
        {1},
        {2},
        {4},
        {2},
        {5},
        {}
    };

    auto t_s = topological_sort(graph1);
    assert(t_s.size() == graph1.size());

    vector<vector<int> > cycle = {
        {1},
        {2},
        {0},
        {0}
    };

    t_s = topological_sort(cycle);

    assert(t_s.size() == 0);

    cout << "Tests passed" << endl;

    return 0;
}