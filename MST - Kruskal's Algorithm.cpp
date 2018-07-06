#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

typedef pair<pair<int, int>, int> mypair;

vector<mypair> mstEdges;

bool comparator(mypair a, mypair b)
{
    return a.second < b.second;
}

bool comparator2(mypair a, mypair b)
{
    if(a.first.first == b.first.first)
        return a.first.second < b.first.second;
    return a.first.first < b.first.first;
}

void showPairs(mypair a[], int len)
{
    for(int i=0; i<len; i++)
    {
        cout << a[i].first.first << " ";
        cout << a[i].first.second << " ";
        cout << a[i].second << " ";
        cout << endl;
    }
}

int getParentOf(int theNode, int parentOf[])
{
    if(parentOf[theNode] == theNode)
        return theNode;
    return getParentOf(parentOf[theNode], parentOf);
}

void joinTogetherIfPossible(mypair p, int parentOf[])
{
    int node1 = p.first.first;
    int node2 = p.first.second;
    int parent1 = getParentOf(node1, parentOf);
    int parent2 = getParentOf(node2, parentOf);
    if(parent1 != parent2)
    {
        parentOf[getParentOf(node2, parentOf)] = parentOf[getParentOf(node1, parentOf)];
        mstEdges.push_back(p);
    }
}

int main()
{
    freopen("_in.txt", "r", stdin);
    int noOfNodes, noOfEdges;
    int node1, node2, weight;
    cin >> noOfNodes >> noOfEdges;
    // edges.first = pair of nodes
    // edges.second = weight between the nodes
    mypair edges[noOfEdges];
    int parentOf[noOfNodes+1];

    // mark all nodes as their parent nodes
    for(int i=0; i<=noOfNodes; i++)
    {
        parentOf[i] = i;
    }

    /// STEP 1: RECEIVE AND SORT EDGES
    ///         ACCORDING TO THEIR WEIGHTS
    for(int i=0; i<noOfEdges; i++)
    {
        cin >> node1 >> node2 >> weight;
        edges[i].first = make_pair(node1, node2);
        edges[i].second = weight;
    }

    sort(edges, edges+noOfEdges, comparator);
    /// COMPLETED STEP 1!

    /// STEP 2: START ADDING EDGES FROM THE
    ///   SMALLEST WEIGHT TO THAT OF THE LARGEST
    /// STEP 3: DISCARD THE EDGES THAT FORM CYCLE
    for(int i=0; i<noOfEdges-1; i++)
    {
        joinTogetherIfPossible(edges[i], parentOf);
    }

    sort(mstEdges.begin(), mstEdges.end(), comparator2);
    for(int i=0; i<mstEdges.size(); i++)
    {
        cout << mstEdges[i].first.first << " ";
        cout << mstEdges[i].first.second << " ";
        cout << mstEdges[i].second << "\n";
    }
    return 0;
}
