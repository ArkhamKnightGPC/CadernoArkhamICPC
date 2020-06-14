#include<bits/stdc++.h>
using namespace std;
struct node{
    int pai; char pch;
    int link;
    int adj[30], nxt[30];
    bool fim;
    node(int p, char pc){
        pch = pc; pai = p;
        link = -1; fim = false;
        for(int i=0; i<30; i++){adj[i] = -1; nxt[i]=-1;}
    }
    node(){}
};
const int MAXN = 1e5+7;
vector<node> trie;
map<char, int> mp;
string s1,s2;
vector<int> dp[MAXN];
void add_string(string s){
    int vert = 0;
    for(char ch : s){
        int c = mp[ch];
        if(trie[vert].adj[c] == -1){
            int novo = trie.size();
            trie.push_back(node(vert, ch));
            trie[vert].adj[c] = novo;
        }
        vert = trie[vert].adj[c];
    }
    trie[vert].fim = true;
}
int go(int vert, char ch);
int get_link(int vert){
    if(trie[vert].link != -1)return trie[vert].link;
    if(vert==0 || trie[vert].pai==0)
        trie[vert].link = 0;
    else
        trie[vert].link = go(get_link(trie[vert].pai), trie[vert].pch);
    return trie[vert].link;
}
int go(int vert, char ch){
    int c = mp[ch];
    if(trie[vert].nxt[c] != -1)return trie[vert].nxt[c];
    if(trie[vert].adj[c] != -1)
        trie[vert].nxt[c] = trie[vert].adj[c];
    else
        trie[vert].nxt[c] = (vert==0) ? 0 : go(get_link(vert), ch);
    return trie[vert].nxt[c];
}
int fazdp(int pos, int vi){
    if(pos == s1.size())return 0;//acabou string, vai pra casa
    if(dp[pos][vi] != -1)return dp[pos][vi];
    int ret = 0;
    if(s1[pos] != '?'){//normal letter
        int nv = go(vi, s1[pos]);
        if(trie[nv].fim)ret = max(ret, 1 + fazdp(pos+1, nv));
        else ret = max(ret, fazdp(pos+1, nv));
    }else{
        for(char c='a'; c<='z'; c++){
            int nv = go(vi, c);
            if(trie[nv].fim)ret = max(ret, 1 + fazdp(pos+1, nv));
            else ret = max(ret, fazdp(pos+1, nv));
        }
    }
    return dp[pos][vi] = ret;
}
int main(){
    for(char c='a'; c<='z'; c++)mp[c] = c-'a';
    mp['?'] = 'z' - 'a' + 1;
    cin >> s1 >> s2;
    trie.push_back(node(-1, '$'));//raiz
    add_string(s2);
    //hora de dimensionar tabela de dp
    for(int i=0; i<(int)s1.size(); i++){
        for(int j=0; j<=(int)s2.size(); j++){
            dp[i].push_back(-1);
        }
    }
    int ans = fazdp(0, 0);
    cout<<ans<<endl;
}
