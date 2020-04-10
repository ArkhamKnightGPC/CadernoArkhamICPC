//BRIDGE TREE
#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define pii pair<int,int>
const int MAXN = 3e5 + 7, UNVISITED = 0, MAXL=25;
/*Dado um grafo nao direcionado com arestas de peso ou 0 ou 1
  responder para (A,B): existe algum caminho de A a B sem repetir arestas 
  que contem pelo menos uma aresta de peso 1 ?
*/
vector<pii> G[MAXN], Gc[MAXN];//grafo dado e grafo das Bridge Components
int n, m, t=1, dfs_num[MAXN], dfs_low[MAXN], dfs_parent[MAXN];
int cc=0, componente[MAXN];
set<pii> bridges;
bool tem[MAXN], tem_aresta_pai[MAXN];
/*tem[i] = true => Bridge component i tem aresta com peso 1
*/
void achar_bridges(int u){
    dfs_num[u] = dfs_low[u] = t++;
    for(int i=0; i < (int)G[u].size(); i++){
        pii viz = G[u][i];
        if(dfs_num[viz.first] == UNVISITED){
            dfs_parent[viz.first] = u;
            achar_bridges(viz.first);
            if(dfs_low[viz.first] > dfs_num[u]){
                //cout<<"BRIDGE "<<u<<" "<<viz.first<<endl;
                bridges.insert({u,viz.first});
                bridges.insert({viz.first,u});
            }
            dfs_low[u] = min(dfs_low[u], dfs_low[viz.first]);
        }else if(viz.first != dfs_parent[u]){
            dfs_low[u] = min(dfs_low[u], dfs_num[viz.first]);
        }
    }
}
void marca_comp(int u, int p){
    componente[u] = cc;
    for(int i=0; i<(int)G[u].size(); i++){
        pii viz = G[u][i];
        if(bridges.find({u, viz.first}) != bridges.end()){//eh bridge, nao usa
            if(componente[viz.first] != 0){
                Gc[cc].push_back({componente[viz.first], viz.second});
                Gc[componente[viz.first]].push_back({cc, viz.second});
            }
        }else{
            if(viz.second == 1)tem[cc] = true;
            if(componente[viz.first] == 0)marca_comp(viz.first, u);
        }
    }
}
int pai_comp[MAXN][MAXL],nivel_comp[MAXN],ent_comp[MAXN], sai_comp[MAXN];
void dfs_comp(int u, int p){
    ent_comp[u] = ++t;
    for(int i=0; i<(int)Gc[u].size(); i++){
        pii viz = Gc[u][i];
        if(viz.first == p)continue;
        pai_comp[viz.first][1] = u;
        tem_aresta_pai[viz.first] = (viz.second==1);
        nivel_comp[viz.first] = nivel_comp[u] + 1;
        dfs_comp(viz.first, u);
    }
    sai_comp[u] = ++t;
}
bool eh_anc(int u, int v){
    return ent_comp[u]<=ent_comp[v] && sai_comp[u]>=sai_comp[v];
}
int lca_comp(int u, int v){
    if(eh_anc(u,v))return u;
    for(int j=MAXL-1; j>=0; j--)
        if(!eh_anc(pai_comp[u][j], v))u = pai_comp[u][j];
    return pai_comp[u][1];
}
int main(){
    fastio; cin>>n>>m;
    for(int i=0; i<m; i++){
        int xi,yi,zi;
        cin>>xi>>yi>>zi;
        G[xi].push_back({yi, zi});
        G[yi].push_back({xi, zi});
    }
    achar_bridges(1);
    for(int i=1; i<=n; i++){
        if(componente[i] == 0){//bora marcar a componente e montar Gc
            cc++; marca_comp(i, 0);
            pai_comp[cc][0] = cc;
        }
    }
    pai_comp[1][1] = 1;
    t=0; dfs_comp(1, 1);//vamos explorar as componentes (marcar pais e niveis)

    for(int j=2; j<MAXL; j++)
        for(int i=1; i<=n; i++)
            pai_comp[i][j] = pai_comp[pai_comp[i][j-1]][j-1];

    int a,b; cin>>a>>b;
    a = componente[a];
    b = componente[b];
    //cout<<"COMPONENTE "<<a<<" "<<b<<endl;
    int aux = lca_comp(a, b);
    //cout<<"LCA "<<aux<<endl;
    bool ans = tem[aux];
    while(a != aux){
        ans |= tem[a];
        ans |= tem_aresta_pai[a];
        a = pai_comp[a][1];
    }
    while(b != aux){
        ans |= tem[b];
        ans |= tem_aresta_pai[b];
        b = pai_comp[b][1];
    }
    if(ans)cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
}
