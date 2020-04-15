/* Codechef Generous Raju
   Heavy Light + Merge Sort Tree */
#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define fe 2*idx
#define fd fe+1
#define mid (l+r)/2
const int MAXN = 1e5+7, MAXL=25;
int n,q,val[MAXN],sz[MAXN],ancestral[MAXN][MAXL],nivel[MAXN],ent[MAXN],sai[MAXN],t=0;
int chain[MAXN], pai_chain[MAXN], chain_counter=0, hld[MAXN];
vector<int> G[MAXN], tree[4*MAXN];

void pre_dfs(int u, int p){
    ancestral[u][0] = p;
    sz[u] = 1;
    for(int i=0; i<(int)G[u].size(); i++){
        int viz = G[u][i];
        if(viz==p)continue;
        nivel[viz] = nivel[u] + 1;
        pre_dfs(viz, u);
        sz[u] += sz[viz];
    }
}
void dfs(int u, int p){
    t++; ent[u] = t;
    hld[t] = u;
    int bigchild = -1;
    for(int i=0; i<(int)G[u].size(); i++){
        int viz = G[u][i];
        if(viz==p)continue;
        if(2*sz[viz] >= sz[u])bigchild=viz;
    }
    if(bigchild != -1){
        chain[bigchild] = chain[u];
        dfs(bigchild, u);
    }
    for(int i=0; i<(int)G[u].size(); i++){
        int viz = G[u][i];
        if(viz==p || viz==bigchild)continue;
        chain[viz] = ++chain_counter;
        pai_chain[chain_counter] = viz;
        dfs(viz, u);
    }
    sai[u] = t;
}
void build(int idx, int l, int r){
    if(l==r){
        tree[idx].push_back(val[hld[l]]);//valor do vertice na posicao l da dfs ordering
        return;
    }
    build(fe,l,mid); build(fd,mid+1,r);
    int pe=0,pd=0;
    while(pe < tree[fe].size() && pd < tree[fd].size()){
        if(tree[fe][pe] < tree[fd][pd]){
            tree[idx].push_back(tree[fe][pe]); pe++;
        }else{
            tree[idx].push_back(tree[fd][pd]); pd++;
        }
    }
    while(pe < tree[fe].size()){
        tree[idx].push_back(tree[fe][pe]); pe++;
    }
    while(pd < tree[fd].size()){
        tree[idx].push_back(tree[fd][pd]); pd++;
    }
}
bool eh_anc(int x, int y){
    return ent[x]<=ent[y] && sai[x]>=sai[y];
}
int lca(int x, int y){
    if(eh_anc(x, y))return x;
    for(int j=MAXL-1; j>=0; j--)
        if(!eh_anc(ancestral[x][j],y))x = ancestral[x][j];
    return ancestral[x][0];
}
int query_tree(int idx, int l, int r, int ql, int qr, int vl, int vr){
    if(l>qr || r<ql)return 0;
    if(l>=ql && r<=qr){//2 buscas binarias
        //menor cara >= vl    e    maior cara <= vr
        int bl=0, br=tree[idx].size()-1;
        while(bl != br){
            int bm = (bl+br)/2;
            if(tree[idx][bm] < vl)bl = bm+1;
            else br = bm;
        }
        int bbl=0, bbr=tree[idx].size()-1;
        while(bbl != bbr){
            int bbm = (bbl+bbr+1)/2;
            if(tree[idx][bbm] > vr)bbr = bbm-1;
            else bbl = bbm;
        }
        if(tree[idx][bl]>=vl && tree[idx][bbl]<=vr)return bbl-bl+1;
        return 0;
    }
    return query_tree(fe,l,mid,ql,qr,vl,vr) + query_tree(fd,mid+1,r,ql,qr,vl,vr);
}
int query(int x, int y, int l, int r){//quantos nos no caminho subindo de x a y(sem contar y) tem valor em [l,r] ?
    int ret = 0;
    while(x != y){//vamos subir chains !!
        int cx = chain[x];
        int px = pai_chain[cx];
        if(nivel[px] > nivel[y]){//vamos subir a chain inteira
            ret += query_tree(1, 1, n, ent[px], ent[x], l, r);
            x = ancestral[px][0];
        }else{//x e y estao na mesma chain (quero saber ate filho de aux)
            if(ent[y]+1 <= ent[x])ret += query_tree(1, 1, n, ent[y]+1, ent[x], l, r);
            x = y;//para fechar loop
        }
    }
    return ret;
}
int main(){
    fastio; cin>>n>>q;
    for(int i=1; i<=n; i++)cin>>val[i];
    for(int i=1; i<n; i++){
        int x,y; cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    pre_dfs(1, 1);
    for(int j=1; j<MAXL; j++)
        for(int i=1; i<=n; i++)
            ancestral[i][j] = ancestral[ancestral[i][j-1]][j-1];
    chain[1] = ++chain_counter;
    pai_chain[chain_counter] = 1;
    dfs(1, 1);
    build(1,1,n);
    int last = 0;
    while(q--){
        int x,y,a,b,l,r;
        cin>>a>>b>>l>>r;
        x = (a^last)%n + 1;
        y = (b^last)%n + 1;
        int aux = lca(x, y);
        int ans = query(x, aux, l, r) + query(y, aux, l, r);
        if(val[aux]>=l && val[aux]<=r)ans++;
        cout << ans << endl;
        last = ans;
    }
}
