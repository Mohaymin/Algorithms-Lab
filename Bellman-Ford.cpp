#include<stdio.h>
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
typedef pair<int, int> mypair;

int main()
{
    freopen("_in.txt", "r", stdin);
    int totalNumberOfNodes;
    int totalNumberOfEdges;
    int predecessorNode;
    int successorNode;
    int weight;
    int sourceNode;
    bool hasNegativeCycle;
    stack<int> stackOfPath;
    pair<int, int> adjacentNodeAndWeight;

    cin >> totalNumberOfNodes >> totalNumberOfEdges;

    vector< pair<int, int> > nodesAdjacentTo[totalNumberOfNodes+1];
    int distanceOf[totalNumberOfEdges+1];
    int predecessorOf[totalNumberOfEdges+1];
    /// receiving user input
    for(int i=0; i<totalNumberOfEdges; i++)
    {
        cin >> predecessorNode >> successorNode >> weight;
        adjacentNodeAndWeight = make_pair(successorNode, weight);
        nodesAdjacentTo[predecessorNode].push_back(adjacentNodeAndWeight);
    }
    cin >> sourceNode;
    /// initialization
    for(int theNode=1; theNode<=totalNumberOfNodes; theNode++)
    {
        distanceOf[theNode] = INT_MAX;
        predecessorOf[theNode] = theNode;
    }
    distanceOf[sourceNode] = 0;
    /// BELLMAN-FORD implementation
    for(int i=0; i<totalNumberOfNodes-1; i++)
    {
        for(int selectedNode=1; selectedNode<=totalNumberOfNodes; selectedNode++)
        {
            for(int k=0; k<nodesAdjacentTo[selectedNode].size(); k++)
            {
                adjacentNodeAndWeight = nodesAdjacentTo[selectedNode][k];
                /// relaxation
                weight = distanceOf[selectedNode]+adjacentNodeAndWeight.second;
                if(distanceOf[adjacentNodeAndWeight.first] > weight)
                {
                    distanceOf[adjacentNodeAndWeight.first] = weight;
                    predecessorOf[adjacentNodeAndWeight.first] = selectedNode;
                }
            }
        }
    }
    /// check negative cycle
    hasNegativeCycle = false;
    for(int selectedNode=1; selectedNode<=totalNumberOfNodes && !hasNegativeCycle; selectedNode++)
    {
        for(int k=0; k<nodesAdjacentTo[selectedNode].size(); k++)
        {
            adjacentNodeAndWeight = nodesAdjacentTo[selectedNode][k];
            weight = distanceOf[selectedNode]+adjacentNodeAndWeight.second;
            if(distanceOf[adjacentNodeAndWeight.first] > weight)
            {
                hasNegativeCycle = true;
                break;
            }
        }
    }
    /// output
    if(!hasNegativeCycle)
    {
        for(int i=1; i<=totalNumberOfNodes; i++)
        {
            cout << "\nDistance from " << sourceNode;
            cout << " to " << i << " is " << distanceOf[i] << endl;
            cout << "The shortest path:";
            successorNode = i;
            while(predecessorOf[successorNode] != successorNode)
            {
                stackOfPath.push(successorNode);
                successorNode = predecessorOf[successorNode];
            }
            stackOfPath.push(successorNode);
            while(stackOfPath.empty()!=true)
            {
                cout << " " << stackOfPath.top();
                stackOfPath.pop();
            }
            cout << endl;
        }
    }
    else
    {
        puts("Negative cycle exists!");
        puts("No solution for shortest path.");
        cout << endl;
    }
    return 0;
}
