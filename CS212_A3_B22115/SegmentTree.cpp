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
class SegmentTree
{
public:
    vector<int> tree;
    vector<int> lazytree;

    SegmentTree(vector<int> &arr)
    {
        for (int i = 0; i < 2 * arr.size() - 1; i++)
            tree.push_back(0), lazytree.push_back(0);

        CreateTree(arr, 0, arr.size() - 1, 0);
    }
    void CreateTree(vector<int> &arr, int s, int e, int pos)
    {
        if (s == e)
        {
            tree[pos] = arr[s];
            return;
        }

        int mid = s + (e - s) / 2;
        CreateTree(arr, s, mid, 2 * pos + 1);
        CreateTree(arr, mid + 1, e, 2 * pos + 2);

        tree[pos] = tree[2 * pos + 1] + tree[2 * pos + 2];
    }

    void printTree()
    {
        for (auto i : this->tree)
            cout << i << " ";
        cout << endl;
        for (auto i : this->lazytree)
            cout << i << " ";
        cout << endl;
    }

    void printArray()
    {
        for (int i = tree.size() / 2; i < tree.size(); i++)
            cout << i << " ";
        cout << endl;
    }

    void IncrementRange(vector<int> &arr, int s, int e, int low, int high, int pos, int inc)
    {
        if (s > e)
            return;
        if (this->lazytree[pos] != 0)
        {
            this->tree[pos] += this->lazytree[pos];
            if (s != e)
            {
                this->lazytree[2 * pos + 1] += this->lazytree[pos];
                this->lazytree[2 * pos + 2] += this->lazytree[pos];
            }
            this->lazytree[pos] = 0;
        }
        // No Overlap
        if (s > high || e < low)
            return;

        // Total Overlap
        if (s >= low && e <= high)
        {
            this->tree[pos] += inc;
            if (s != e)
            {
                this->lazytree[2 * pos + 1] += inc;
                this->lazytree[2 * pos + 2] += inc;
            }
            return;
        }
        // Partial Overlaps
        int mid = s + (e - s) / 2;
        IncrementRange(arr, s, mid, low, high, 2 * pos + 1, inc);
        IncrementRange(arr, mid + 1, e, low, high, 2 * pos + 2, inc);

        this->tree[pos] = this->tree[2 * pos + 1] + this->tree[2 * pos + 2];
    }

    void Get(vector<int> &arr, int s, int e, int index, int pos)
    {
        if (s > e)
            return;

        if (this->lazytree[pos] != 0)
        {
            this->tree[pos] += this->lazytree[pos];
            if (s != e)
            {
                this->lazytree[2 * pos + 1] += this->lazytree[pos];
                this->lazytree[2 * pos + 2] += this->lazytree[pos];
            }
            this->lazytree[pos] = 0;
        }
        if (s > index || e < index)
            return;
        if (s == index && e == index)
        {
            cout << this->tree[pos] << endl;
            return;
        }

        int mid = s + (e - s) / 2;
        Get(arr, s, mid, index, 2 * pos + 1);
        Get(arr, mid + 1, e, index, 2 * pos + 2);

        this->tree[pos] = this->tree[2 * pos + 1] + this->tree[2 * pos + 2];
    }

    void Update(vector<int> &arr, int s, int e, int index, int pos, int val)
    {
        if (s > e)
            return;

        if (this->lazytree[pos] != 0)
        {
            this->tree[pos] += this->lazytree[pos];
            if (s != e)
            {
                this->lazytree[2 * pos + 1] += this->lazytree[pos];
                this->lazytree[2 * pos + 2] += this->lazytree[pos];
            }
            this->lazytree[pos] = 0;
        }
        if (s > index || e < index)
            return;
        if (s == index && e == index)
        {
            this->tree[pos] = val;
            return;
        }

        int mid = s + (e - s) / 2;
        Update(arr, s, mid, index, 2 * pos + 1, val);
        Update(arr, mid + 1, e, index, 2 * pos + 2, val);

        this->tree[pos] = this->tree[2 * pos + 1] + this->tree[2 * pos + 2];
    }
};

int main()
{
    int n = nxt();
    int k = nxt();
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        v[i] = nxt();
    SegmentTree *s = new SegmentTree(v);
    while (k--)
    {
        char type;
        cin >> type;
        if (type == 'I')
        {
            int low = nxt() - 1;
            int high = nxt() - 1;
            int inc = nxt();
            s->IncrementRange(v, 0, v.size() - 1, low, high, 0, inc);
        }
        else if (type == 'G')
        {
            int index = nxt();
            s->Get(v, 0, v.size() - 1, index - 1, 0);
        }
        else if (type == 'U')
        {
            int index = nxt();
            int val = nxt();
            s->Update(v, 0, v.size() - 1, index - 1, 0, val);
        }
        else
        {
            cout << "Invalid Querey" << endl;
            break;
        }
    }
}