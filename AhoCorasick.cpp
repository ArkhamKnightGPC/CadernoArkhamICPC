#include<bits/stdc++.h>
using namespace std;
const int ALF = 30, MAXN = 1e3+9;
struct vertex{
	int filhos[ALF];
	int nend;
	int p;
	char pch;
	int link;
	int automaton[ALF];
	vertex(int pi, char pchi){
		p = pi; pch = pchi;
		nend = 0; link = -1;
		for(int i=0; i<ALF; i++){
			filhos[i] = -1;
			automaton[i] = -1;
		}
	}
};
int n,m;
string t, p;
vector<vertex> trie;
vector<int> s_nend;

void add_string(string s){
	int v = 0;
	for(int i=0; i<(int)s.size(); i++){
		int c = s[i] - 'a';
		if(trie[v].filhos[c] == -1){//create new node
			trie[v].filhos[c] = trie.size();
			trie.push_back(vertex(v, s[i]));
			s_nend.push_back(-1);
		}
		v = trie[v].filhos[c];
	}
	trie[v].nend++;
}

int go(int v, char ch);

int get_link(int v){
	if(trie[v].link == -1){//compute suffix link
		if(v==0 || trie[v].p==0)
			trie[v].link = 0;//special case
		else
			trie[v].link = go(get_link(trie[v].p), trie[v].pch);
	}
	return trie[v].link;
}

int go(int v, char ch){
	int c = ch-'a';
	if(trie[v].automaton[c] == -1){//compute automaton transition
		if(trie[v].filhos[c] != -1)//we found transition
			trie[v].automaton[c] = trie[v].filhos[c];
		else//follow suffix link and try again
			trie[v].automaton[c] = (v == 0) ? 0 : go(get_link(v), ch);
	}
	return trie[v].automaton[c];
}
int dp[MAXN][MAXN]; char opt[MAXN][MAXN];
int soma_nend(int v){
	return (s_nend[v] == -1) ? s_nend[v] = trie[v].nend + soma_nend(get_link(v)) : s_nend[v];
}
int fazdp(int idx, int v){//position in text t, state in automaton
	if(idx == (int)t.size())
		return dp[idx][v] = 0;
	if(dp[idx][v] != -1)return dp[idx][v];
	int ret = -1;
	if(t[idx] == '?'){
		for(char ch='a'; ch<='z'; ch++){
			int aux = soma_nend(go(v,ch)) + fazdp(idx+1, go(v,ch));
			if(aux > ret){
				opt[idx][v] = ch;
				ret = aux;
			}
		}
	}else{
		ret = soma_nend(go(v,t[idx])) + fazdp(idx+1, go(v,t[idx]));
		opt[idx][v] = t[idx];
	}
	return dp[idx][v] = ret;
}
int main(){
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	int tc; cin>>tc;
	while(tc--){
		cin>>n>>m>>t;
		trie.clear(); s_nend.clear();
		for(int i=0; i<MAXN; i++){
			for(int j=0; j<MAXN; j++){
				dp[i][j] = -1;
			}
		}
		trie.push_back(vertex(-1, '$'));//raiz
		s_nend.push_back(0);
		for(int i=0; i<m; i++){
			cin>>p; add_string(p);
		}
		cout << fazdp(0,0) << endl;
		int v = 0;
		for(int i=0; i<n; i++){
			cout << opt[i][v];
			v = go(v, opt[i][v]);
		}
		cout<<endl;
	}
}
