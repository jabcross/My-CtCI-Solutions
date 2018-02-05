#include <bits/stdc++.h>

using namespace std;

bool has_path(vector<vector<int> > &adj_list, int source, int dest){
    vector<bool> visited (adj_list.size(), false);
    queue<int> node_queue;

    node_queue.push(source);

    while (!node_queue.empty()){
        int x = node_queue.front();
        node_queue.pop();

        if (x == dest) return true;

        visited[x] = true;

        for (int node: adj_list[x]){
            if (!visited[node]){
                node_queue.push(node);
            }
        }
    }
    return false;
}

int main(){
    vector<vector<int> > graph;

    for (int i : {0,1,2}){
        graph.push_back(vector<int>());
    }

    graph[0].push_back(1);
    graph[1].push_back(2);
    graph[0].push_back(2);

    assert(has_path(graph,0,2));
    assert(!has_path(graph,2,0));

    cout << "Tests passed" << endl;

    return 0;
}