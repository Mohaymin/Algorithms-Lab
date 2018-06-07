/**
TOPIC: TOPOLOGICAL SORT
INPUT FORMAT:
total number of nodes - N
total number of edges - E
E lines containing two nodes
that are connected to each other.
*/

#include<bits/stdc++.h>
using namespace std;

typedef vector<int> vint;
stack<int> topSortedElements;

void topologicalSort(vint adjList[], bool vis[], int node)
{
    if(vis[node])
        return;
    vis[node] = true;
    int adjNode;
    for(int i=0; i<adjList[node].size(); i++)
    {
        adjNode = adjList[node][i];
        if(vis[adjNode])
            continue;
        topologicalSort(adjList, vis, adjNode);
    }
    topSortedElements.push(node);
}


int main()
{
    //freopen("in.txt", "r", stdin);
    int noOfNodes, noOfEdges;
    cin >> noOfNodes >> noOfEdges;

    vint adjList[noOfNodes];
    bool visited[noOfNodes];
    memset(visited, false, sizeof(visited));
    //initialize visited[] with false

    int node1, node2;
    for(int i=0; i<noOfEdges; i++)
    {
        cin >> node1 >> node2;
        adjList[node1].push_back(node2);
    }
    for(int i=0; i<noOfNodes; i++)
    {
        if(visited[i])
            continue;
        topologicalSort(adjList, visited, i);
    }
    puts("THE TOPOLOGICALLY SORTED ORDER:");
    while(topSortedElements.empty() != true)
    {
        cout << topSortedElements.top() << " ";
        topSortedElements.pop();
    }
    return 0;
}
