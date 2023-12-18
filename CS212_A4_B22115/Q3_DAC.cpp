#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()
#define f(i, n) for (ll i = 0; i < (n); i++)
#define fr(i, n) for (ll i = (n)-1; i >= 0; i--)
#define fex(i, s, n) for (ll i = s; i < (n); i++)
#define fexr(i, s, n) for (ll i = (n)-1; i >= s; i--)
inline ll nxt()
{
    ll x;
    cin >> x;
    return x;
}
void print(vector<ll> v, ll n)
{
    f(i, n) cout << v[i] + 1;
    cout << endl;
}
int main()
{
    ll n = nxt();
    ll edg = nxt();

    unordered_map<ll,vector<ll>> m;
    vector<ll> indeg(n+1,0);
    f(i,edg){
        ll a = nxt();
        ll b = nxt();
        m[b].push_back(a);
        indeg[a]++;
    }

    queue<ll> q;
    f(i,n+1){
        if(indeg[i] == 0) q.push(i);
    }
    if(q.empty()){
        cout<<-1<<endl;
        cout<<"They can't complete HW as all are dependent on one another";
    }

    vector<ll> topo;
    vector<bool> visited(n+1,0);

    while(!q.empty()){
        ll node = q.front();
        q.pop();
        visited[node] = 1;
        topo.push_back(node);

        for(auto adj:m[node]){
            indeg[adj]--;
            if(!visited[adj] && indeg[adj] == 0) q.push(adj);
        }
    }
    if(topo.size() != n + 1){
        cout<<-1<<endl;
        cout<<"They can't complete HW as all are dependent on one another";        
    }
    else {
        cout<<1<<endl;
        cout<<"They can complete HW";   
    }
}