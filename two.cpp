#include<bits/stdc++.h>
using namespace std;

vector<vector<long long int>> edgelist;

void addEdge(long long int x,long long int y,long long int weight)
{
    edgelist.push_back({weight,x,y});
}
 
long long int find_set(long long int i,long long int parent[])
{
    if(parent[i]==i)
        return i;
    return find_set(parent[i],parent);
}

void union_set(long long int x,long long int y,long long int parent[],long long int rank[])
{
    long long int s1 = find_set(x,parent);
    long long int s2 = find_set(y,parent);

    if(s1!=s2)
    {
        if(rank[s1]<rank[s2])
        {
            parent[s1]=s2;
            rank[s2]+=rank[s1];
        }
        else
        {
            parent[s1]=s2;
            rank[s2]+=rank[s1];
        }
    }
}

void mst(long long int vertices)
{
   long long int parent[vertices];
   long long int rank[vertices];
   long long int ans=0;
   for(long long int i=0;i<vertices;i++)
   {
       parent[i]=i;
       rank[i]=0;
   }
   sort(edgelist.begin(),edgelist.end());
   for(auto edge: edgelist)
   {
       long long int weight = edge[0];
       long long int x = edge[1];
       long long int y = edge[2];
       if(find_set(x,parent)!=find_set(y,parent))
       {
           union_set(x,y,parent,rank);
           ans+=weight;
       }
   }
   cout<<"Weight of a MST: "<<ans;
}

int main()
{
    long long int vertices,edges;
    cin>>vertices>>edges;
    for(long long int i=0;i<edges;i++)
    {
        long long int x,y,weight;
        cin>>x>>y>>weight;
        addEdge(x-1,y-1,weight);
    }
    mst(vertices);
}