#include<iostream>
#include<stack>
#include<vector>
#include<string.h>
#include<stdio.h>
using namespace std;


void DFS(vector<int> adjListOf[], int totalNodes)
{
    int visitedNode;
    int toBeVisitedNode;
    stack<int> storedNodes;
    bool haveVisited[totalNodes];///hasBeenStacked == has been visited

    ///initialize the Boolean array with false
    memset(haveVisited, false, sizeof(haveVisited));

    for(int i=0; i<totalNodes; i++)
    {
        if(haveVisited[i] == true)
            continue;

        storedNodes.push(i);

        while(storedNodes.empty() != true)
        {
            visitedNode = storedNodes.top();
            storedNodes.pop();

            if(haveVisited[visitedNode] == true)
                continue;

            haveVisited[visitedNode] = true;
            cout << "Visited: " << visitedNode << endl;

            for(int i=0; i<adjListOf[visitedNode].size(); i++)
            {
                toBeVisitedNode = adjListOf[visitedNode][i];
                if(haveVisited[toBeVisitedNode] == false)
                {
                    storedNodes.push(toBeVisitedNode);
                }
            }
        }
    }
}


void prepareAdjacencyList(vector<int> adjacencyListOf[], int totalInputs)
{
    int node1, node2;
    for(int i=0; i<totalInputs; i++)
    {
        cin >> node1 >> node2;
        adjacencyListOf[node1].push_back(node2);
        adjacencyListOf[node2].push_back(node1);
    }
}

int main()
{
    freopen("_in.txt", "r", stdin);
    int totalNumberOfNodes;
    int totalNumberOfEdges;
    stack<int> storedNodes;

    cin >> totalNumberOfNodes;
    cin >> totalNumberOfEdges;

    vector<int> adjacencyListOf[totalNumberOfNodes];

    prepareAdjacencyList(adjacencyListOf, totalNumberOfEdges);

    DFS(adjacencyListOf, totalNumberOfEdges);

    return 0;
}
