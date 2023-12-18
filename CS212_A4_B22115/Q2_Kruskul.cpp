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
bool compare(vector<ll> &a, vector<ll> &b)
{
    return a[2] < b[2];
}

ll parentf(vector<ll> &parent, ll node)
{
    if (parent[node] == node)
        return node;

    return parent[node] = parentf(parent, parent[node]);
}

void UnionSets(vector<ll> &parent, vector<ll> &rank, ll a, ll b)
{
    ll u = parentf(parent, a);
    ll v = parentf(parent, b);

    if (rank[u] == rank[v])
    {
        parent[u] = v;
        rank[v]++;
    }
    else if (rank[u] > rank[v])
        parent[v] = u;
    else
        parent[u] = v;
}

int main()
{
    ll n = nxt();
    ll edg = nxt();
    ll k = nxt();

    // We know for all road to connect each other with min cost we need MST
    //  Final graph == MST ==> n-1 edges finally
    // hence atleast cost = sum(n-1) = n-1 when all roads are converted to 1

    if (k < n - 1)
    {
        cout << -1 << endl;
        cout << "Answer Not possible" << endl;
        return 0;
    }

    vector<vector<ll>> v;
    vector<vector<ll>> mst;
    vector<pair<ll, ll>> modified_road;

    vector<ll> parent(n + 1), rank(n + 1, 0);

    f(i, n + 1) parent[i] = i;

    f(i, edg)
    {
        // {a,b,wt}
        v.push_back({nxt(), nxt(), nxt()});
    }
    sort(all(v), compare);

    // Worst case when all roads to be changes in final ans --> n-1 roads
    ll ans = n - 1;

    for (auto i : v)
    {
        ll v1 = i[0], v2 = i[1], wt = i[2];

        if (parentf(parent, v1) != parentf(parent, v2))
        {
            UnionSets(parent, rank, parentf(parent, v1), parentf(parent, v2));
            mst.push_back(i);

            // if final ans had 4 edge after this 3 more edges left to evaluate hence n--;
            n--;
            // Reduce current wt from k so we can analyze that if current road need to be made super road or not
            k -= i[2];

            // if k >= n-1 means we don't need to modify this road as either we can make the rest n-1 edges 1, or their orginal value
            if (k >= n - 1)
            {
                ans = n - 1; // ans--;
            }
            else
                modified_road.push_back({v1, v2});
        }
    }
    // if there were more than 1 connected componentes/ Disconnected graph
    // Ex {2,2,wt} then n will not get reduce thereby will be > 1
    if (n > 1)
    {
        cout << -1 << endl;
        cout << "Answer Not possible" << endl;
        return 0;
    }

    cout <<"No. of Super roads made = "<< ans << endl;
    cout << "Super Road is Made Between : ";
    for (auto i : modified_road)
    {
        cout << i.first << " - " << i.second << ", ";
    }
    cout << endl;
}