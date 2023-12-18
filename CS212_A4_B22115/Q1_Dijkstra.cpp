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
    f(i, n) cout << v[i] <<" ";
    cout << endl;
}
int main()
{
    unordered_map<ll,vector<pair<ll,ll>>> m;
    ll vert = nxt();
    ll edg = nxt();
    // {node,wt}
    f(i,edg){
        ll a = nxt();
        ll b = nxt();
        ll wt = nxt();
        m[a].push_back({b,wt});
    }

    // Print Map

    // for(auto i:m){
    //     cout<<i.first<<" --> ";
    //     for(auto k:i.second){
    //         cout<<k.first<<" "<<k.second<<", ";
    //     }
    //     cout<<endl;
    // }

    set<pair<ll,ll>> s;
    // {node,wt}
    s.insert({0,0});

    // distance vector
    vector<ll> parent(vert,-2);
    parent[0] = -1;

    vector<ll> dist(vert,1e9);

    while(!s.empty()){
        auto it = *(s.begin());
        s.erase(s.begin());
        for(auto adj: m[it.first]){
            if(adj.second + it.second < dist[adj.first]){

                if(parent[it.first] == adj.first) {
                    cout<<-1<<endl;
                    cout<<" Negative cycle exist Can't get answer ";
                    return 0;
                }

                parent[adj.first] = it.first;

                if(dist[adj.first] != 1e9){
                    auto adj_pair = s.find({adj.first,dist[adj.first]});
                    s.erase(adj_pair);
                }

                dist[adj.first] = adj.second + it.second;
                s.insert({adj.first,dist[adj.first]});
            }
        }
    }
    cout<<1<<endl;
    cout<<endl;
    for(ll i = 1;i<vert;i++){
        cout<<" From src 0 to reach "<<i<<" Shortest distance = "<<dist[i]<<endl;
    }

}

// Test case 1
// 7 8
// 0 1 -7
// 0 2 -1
// 1 3 5
// 2 3 3
// 2 4 5
// 3 5 3
// 4 5 3
// 5 6 2

// Test 2
// 4 5
// 0 1 -2
// 1 2 -2
// 0 3 -1 
// 3 2 -5
// 2 1 -3