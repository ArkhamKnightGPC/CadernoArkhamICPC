clude<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
const int MAXN = 5e4+7, UNMATCHED=-1;
vector<int> G[MAXN];
int matchA[MAXN], matchB[MAXN];
bool mrk[MAXN];
 
bool Kuhn(int u){
	for(int i=0; i<(int)G[u].size(); i++){
		int v = G[u][i];
		if(mrk[v])continue;
		mrk[v]=true;
		if(matchB[v]==UNMATCHED || Kuhn(matchB[v])){
			matchB[v] = u;
			matchA[u] = v;
			return true;
		}
	}
	return false;
}
 
int main(){
	int n,m,p; scanf("%d %d %d", &n, &m, &p);
	for(int i=0; i<p; i++){
		int ai,bi; scanf("%d %d", &ai, &bi);
		G[ai].push_back(bi);
	}
	memset(matchA, UNMATCHED, sizeof matchA);
	memset(matchB, UNMATCHED, sizeof matchB);
	int matching = 0;
	bool aux = true;
	while(aux){
		memset(mrk, false, sizeof mrk);
		aux = false;
		for(int i=1; i<=n; i++){
			if(matchA[i]==UNMATCHED && Kuhn(i)){
				matching++;
				aux = true;
			}
		}
	}
	printf("%d", matching);
} 
