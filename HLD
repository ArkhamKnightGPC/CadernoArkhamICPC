//SPOJ QTREE
//HLD eh so uma dfs chique !!
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define v first
#define w second
const int MAXN = 1e4+7, MAXL = 15, INF=1e9+7;
int n, tc, ent[MAXN], sai[MAXN], paiCaminho[MAXN], tree[4*MAXN], ancestral[MAXN][MAXL], pai[MAXN], peso[MAXN], sz[MAXN], nodeCounter, noEnt[MAXN], nivel[MAXN];
int a[MAXN], b[MAXN], c[MAXN];
vector<pii> G[MAXN][21];

void dfs(int u, int p){
	sz[u] = 1;
	for(int i=0; i<(int)G[u][tc].size(); i++){
		pii viz = G[u][tc][i];
		if(viz.v == p)continue;
		peso[viz.v] = viz.w;
		pai[viz.v] = u;
		nivel[viz.v] = nivel[u] + 1;
		dfs(viz.v, u);
		sz[u] += sz[viz.v];
	}
}
void hld(int u, int p){
	ent[u] = ++nodeCounter;	noEnt[nodeCounter] = u;
	int bigchild = -1;
	for(int i=0; i<(int)G[u][tc].size(); i++){
		pii viz = G[u][tc][i];
		if(viz.v == p)continue;
		if(2*sz[viz.v] >= sz[u])bigchild = viz.v;
	}
	if(bigchild != -1){//continua mesmo caminho
		paiCaminho[bigchild] = paiCaminho[u];
		hld(bigchild, u);
	}
	for(int i=0; i<(int)G[u][tc].size(); i++){
		pii viz = G[u][tc][i];
		if(viz.v == p || viz.v == bigchild)continue;
		//comeco de outro caminho
		paiCaminho[viz.v] = viz.v;
		hld(viz.v, u);
	}
	sai[u] = nodeCounter;
}
void build(int idx, int l, int r){
	if(l==r){
		tree[idx] = peso[noEnt[l]];//quem eh o no com tempo de entrada igual a l
		return;
	}
	int fe = 2*idx;
	int fd = fe+1;
	int mid = (l+r)/2;
	build(fe, l, mid);
	build(fd, mid+1, r);
	tree[idx] = max(tree[fe], tree[fd]);
}
void upt(int idx, int l, int r, int pos, int val){
	if(l==r){
		tree[idx] = val;
		return;
	}
	int fe = 2*idx;
	int fd = fe+1;
	int mid = (l+r)/2;
	if(pos <= mid)upt(fe, l, mid, pos, val);
	else upt(fd, mid+1, r, pos, val);
	tree[idx] = max(tree[fe], tree[fd]);
}
int query(int idx, int l, int r, int ql, int qr){
	if(l>qr || r<ql)return -INF;
	if(l>=ql && r<=qr)return tree[idx];
	int fe = 2*idx;
	int fd = fe+1;
	int mid = (l+r)/2;
	return max(query(fe, l, mid, ql, qr), query(fd, mid+1, r, ql, qr));
}
inline bool ehAncestral(int u1, int u2){//u1 eh ancestral de u2 ?
	return ent[u1]<=ent[u2] && sai[u1]>=sai[u2];
}
inline int lca(int u1, int u2){
	if(ehAncestral(u1, u2))return u1;
	for(int j=MAXL-1; j>=0; j--){
		if(!ehAncestral(ancestral[u1][j], u2)){
			u1 = ancestral[u1][j];
		}
	}
	return pai[u1];
}
inline int queryHLD(int u1, int u2){//quero subir de u1 ate u2
	int ret = -INF;
	while(nivel[paiCaminho[u1]] > nivel[u2]){
		ret = max(ret, query(1, 1, n, ent[paiCaminho[u1]], ent[u1]));
		u1 = pai[paiCaminho[u1]];
	}
	if(ent[u1]>ent[u2])ret = max(ret, query(1, 1, n, ent[u2]+1, ent[u1]));//agora os dois estao no mesmo caminho
	//note que nao queremos considerar o peso do lca !!!
	//essa aresta nao esta no caminho
	return ret;
}


int main(){
	scanf("%d", &tc);
	while(tc--){
		scanf("%d", &n);
		for(int i=1; i<n; i++){
			scanf("%d %d %d", &a[i], &b[i], &c[i]);
			G[a[i]][tc].push_back({b[i],c[i]});
			G[b[i]][tc].push_back({a[i],c[i]});
		}
		
		nodeCounter = 0;
		peso[1] = -INF; pai[1] = 1;
		dfs(1, 1);
		
		for(int i=1; i<=n; i++){
			ancestral[i][0] = pai[i];
		}
		for(int j=1; j<MAXL; j++){
			for(int i=1; i<=n; i++){
				ancestral[i][j] = ancestral[ancestral[i][j-1]][j-1];
			}
		}
		
		paiCaminho[1] = 1;
		hld(1, 1);
		build(1, 1, n);
		
		bool flag = true;
		while(flag){
		
			char prim; scanf(" %c", &prim);
			char ultimo;
			if(prim=='Q')ultimo='Y';
			else ultimo='E';
			
			char ci;
			do{
				scanf("%c", &ci);
			}while(ci != ultimo);
			
			if(prim == 'D'){
				flag = false;
			}else if(prim == 'C'){
				int i, ti; scanf("%d %d", &i, &ti);
				c[i] = ti;
				int filho = (pai[a[i]] == b[i]) ? a[i] : b[i];
				upt(1, 1, n, ent[filho], ti);
			}else{
				int u1, u2; scanf("%d %d", &u1, &u2);
				int aux = lca(u1, u2);			
				printf("%d\n", max(queryHLD(u1,aux), queryHLD(u2,aux)));
			}
		}
	}
}
