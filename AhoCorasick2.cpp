#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int ALF=30, MAXM=1e3+37;
struct node{
    int adj[ALF];
    int transition[ALF];
    int pai;
    char pch;
    ll val;
    int link;
    ll tot_val;
    node(int p, char pc){
        pai = p; pch = pc;
        link = -1; val = 0; tot_val = -1;
        for(int i=0; i<ALF; i++){
            adj[i] = -1;
            transition[i] = -1;
        }
    }
};
vector<node> trie;
inline void add_string(string s, ll bi){
    int v = 0;//root
    for(int i=0; i<(int)s.size(); i++){
        if(trie[v].adj[s[i]-'a'] == -1){//need to create node
            trie[v].adj[s[i]-'a'] = trie.size();
            trie.push_back(node(v, s[i]));
        }
        v = trie[v].adj[s[i]-'a'];
    }
    trie[v].val += bi;
}
int go(int v, int c);
inline int get_link(int v){
    if(trie[v].link != -1)return trie[v].link;
    if(v==0 || trie[v].pai==0){
        trie[v].link = 0;//special case
    }else{
        trie[v].link = go(get_link(trie[v].pai), trie[v].pch-'a');
    }
    return trie[v].link;
}
inline int go(int v, int c){
    if(trie[v].transition[c] != -1)return trie[v].transition[c];
    if(trie[v].adj[c] != -1){
        trie[v].transition[c] = trie[v].adj[c];
    }else{
        trie[v].transition[c] = (v==0) ? 0 : go(get_link(v), c);
    }
    return trie[v].transition[c];
}
inline ll get_val(int v){
    if(trie[v].tot_val != -1)return trie[v].tot_val;
    trie[v].tot_val = trie[v].val + get_val(get_link(v));
    return trie[v].tot_val;
}
ll ansb[MAXM];//starting and ending at b
int bsz; string a,b;
int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int tc; cin>>tc;
    while(tc--){
        trie.clear();
        for(int i=0; i<MAXM; i++)ansb[i] = 0;
        trie.push_back(node(-1, '$'));//raiz
        trie[0].tot_val = 0;
        cin>>a>>b;
        bsz = b.size();
        int n; cin>>n;
        int tot_sz=0;
        for(int i=0; i<n; i++){
            string si; ll bi;
            cin>>si>>bi; tot_sz+=si.size();
            add_string(si, bi);
        }
        int pref = 0;
        ll pt_pref = 0, pt_tot=0;
        for(int i=0; i<(int)b.size(); i++){
            int cur = 0;
            ansb[i] = 0;
            for(int k=max(0, i-25); k<(int)b.size(); k++){
                cur = go(cur, b[k]-'a');
                if(k >= i)ansb[i] += get_val(cur);
            }
        }
        for(int i=0; i<a.size(); i++){
            pref = go(pref, a[i]-'a');
            pt_pref += get_val(pref);//end in A
            for(int k=0; k<b.size(); k++){
                int cur = pref;
                ll cur_pt = 0;
                for(int j=0; j<=24 && k+j<b.size(); j++){//end in B[k...k+24]
                    cur = go(cur, b[k+j]-'a');
                    cur_pt += get_val(cur);
                }
                //ans[k+25] = end in B[k+25...]
                pt_tot = max(pt_tot, pt_pref + cur_pt + ansb[k+25]);
            }
        }
        cout<<pt_tot<<endl;
    }
}
