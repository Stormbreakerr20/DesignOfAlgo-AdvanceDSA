#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

class trieNode{
    public:
    vector<trieNode*> children;
    char data;
    bool terminal;
    int freq = 0;

    trieNode(char d){
        this->data = d;
        for(int i=0;i<26;i++) children.push_back(NULL);
        this->terminal = false;
        this->freq = 0;
    }
};
class Trie{
    public:
    trieNode* root;

    Trie(){
        this->root = new trieNode('\0');
    }

    // Time Comp = O(length of string)
    void insert(string s){
        insertf(root,s);
    }
    void insertf(trieNode* root,string s){
        if(s.length() == 0) {
            root->terminal = true;
            root->freq++;
            return;
        }

        trieNode* child;
        char toinsert = s[0] - 'a';
        if(root->children[toinsert]){
            child = root->children[toinsert];
        }
        else{
            child = new trieNode(s[0]);
            root->children[toinsert] = child;
        }

        insertf(child,s.substr(1));
    }
    // Time Comp = O(length of string)
    bool search(string s){
        return searchf(root,s);
    }
    bool searchf(trieNode* root,string s){
        if(s.length() == 0) {
            return root->terminal;
        }

        trieNode* child;
        char tosearch = s[0] - 'a';
        if(root->children[tosearch]) child = root->children[tosearch];
        else return false;

        return searchf(child,s.substr(1));
    }
    // O(N*L) ==> N = Number of words, L = length of longest word
    void Suggestion(string s,vector<pair<int,string>> &store){
        Suggestionf(root,s,s,store);
    }
    void Suggestionf(trieNode* root,string s,string word,vector<pair<int,string>> &store){
        if(root->terminal) {
            store.push_back({root->freq,word});
        }
        if(s.length() != 0 && !root->children[s[0] - 'a']) return;
        if(s.length() != 0) {
            Suggestionf(root->children[s[0] - 'a'],s.substr(1),word,store);
            return;
        }
        bool found = 0;
        for(int i = 0;i<26;i++){
            if(root->children[i]){
                word.push_back(root->children[i]->data);
                Suggestionf(root->children[i],s,word,store);
                word.pop_back();
                found = 1;
            }
        }
        if(!found) return;
        
    }
};

bool compare(pair<int,string>&a,pair<int,string>&b){
    return a.first > b.first;
}

int main()
{
    Trie* trie = new Trie();

    int n;
    cin>>n;

    while(n--) {
        string s;
        cin>>s;
        trie->insert(s);
    }
    string freq;
    cin>>freq;

    vector<pair<int,string>> store;
    
    trie->Suggestion(freq,store);
    if(store.size() == 0) {
        cout<<"No Suggestions found";
        return 0;
    }

    sort(all(store),compare);
    cout<<endl<<"Suggestions : "<<endl;
    
    for(auto i:store) cout<<i.second<<endl;
}