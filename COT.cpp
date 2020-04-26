/* SPOJ COT
    Persistent Segment Tree
*/
#include<bits/stdc++.h>
using namespace std;
#define mid (li+ri)/2
const int SZ=2e7+7, MAXN=2e5+7, MAXL=25;
int l[SZ], r[SZ], tree[SZ], raiz[MAXN], a[MAXN], b[MAXN], freq[MAXN], n, q, node_counter=0;
vector<int> G[MAXN];
int ent[MAXN], sai[MAXN], pai[MAXN], anc[MAXN][MAXL], t=0;
map<int,int> m,mr;
int newleaf(int val){
    int p = ++node_counter;
    l[p] = 0; r[p] = 0;
    tree[p] = val;
    return p;
}
int newparent(int lef, int rig){
    int p = ++node_counter;
    l[p] = lef; r[p] = rig;
    tree[p] = tree[lef] + tree[rig];
    return p;
}
int build(int li, int ri){
    if(li==ri)return newleaf(0);
    return newparent(build(li,mid), build(mid+1, ri));
}
int build_prev(int rprev, int pos, int li, int ri){
    if(li==ri)return newleaf(freq[li]);
    if(pos<=mid)return newparent(build_prev(l[rprev],pos,li,mid), r[rprev]);
    return newparent(l[rprev], build_prev(r[rprev],pos,mid+1,ri));
}
void dfs(int u, int p){
    ent[u] = ++t;
    freq[a[u-1]]++;
    raiz[u] = build_prev(raiz[p], a[u-1], 0, n-1);
    for(int i=0; i<(int)G[u].size(); i++){
        int viz = G[u][i];
        if(viz==p)continue;
        pai[viz] = u;
        dfs(viz,u);
    }
    freq[a[u-1]]--;
    sai[u] = t;
}
bool eh_anc(int x, int y){
    return ent[x]<=ent[y] && sai[x]>=sai[y];
}
int lca(int x, int y){
    if(eh_anc(x,y))return x;
    for(int j=MAXL-1; j>=0; j--)
        if(!eh_anc(anc[x][j], y))
            x = anc[x][j];
    return pai[x];
}
int lcaxy;
int query(int r1, int r2, int r3, int k, int li, int ri){
    if(li==ri)return li;
    int cnt = tree[l[r1]] - tree[l[r3]] + tree[l[r2]] - tree[l[r3]];
    if(a[lcaxy-1]>=li && a[lcaxy-1]<=mid)cnt++;
    if(cnt < k)return query(r[r1],r[r2],r[r3],k-cnt,mid+1,ri);
    return query(l[r1],l[r2],l[r3],k,li,mid);
}
int main(){
    scanf("%d %d", &n, &q);
    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b, b+n);
    int aux = 0;
    for(int i=0; i<n; i++){
        if(i>0 && b[i]==b[i-1])continue;
        m[b[i]] = aux;
        mr[aux] = b[i];
        aux++;
    }
    for(int i=1; i<n; i++){
        int x,y; scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i=0; i<n; i++)a[i] = m[a[i]];
    raiz[0] = build(0, n-1);
    pai[1] = 1;
    dfs(1, 0);
    for(int i=1; i<=n; i++)anc[i][0] = pai[i];
    for(int j=1; j<MAXL; j++)
        for(int i=1; i<=n; i++)
            anc[i][j] = anc[anc[i][j-1]][j-1];
    while(q--){
        int x,y,k;
        scanf("%d %d %d", &x, &y, &k);
        lcaxy = lca(x, y);
        int ans = mr[query(raiz[x],raiz[y],raiz[lcaxy],k,0,n-1)];
        printf("%d\n",ans);
    }
}
