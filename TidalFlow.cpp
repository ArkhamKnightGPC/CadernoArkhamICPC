//SPOJ FASTFLOW
#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define vi vector<int>
#define pb push_back
#define ll long long
const int MAXV = 5e3 + 7, MAXE = 3e4 + 7;
const ll INF = 1e16 + 7;
 
struct aresta{
    int orig;//vertice origem
    int ido;//indice da aresta na lista de adjacencia do vertice origem
    int dest;//vertice destino
    int idr;//indice da aresta reversa na lista de adjacencia do vertice destino
    ll cap;//capacidade residual da aresta
    aresta(int oo, int io, int dd, int ir, ll cc){
        orig=oo; ido=io; dest=dd; idr=ir; cap=cc;
    }
    aresta(){}
};
 
int n, d[MAXV];
ll h[MAXV], armazenado[MAXV], promessa[MAXE], cumpri[MAXE];
vector<aresta> adjList[MAXV];
aresta level[MAXE];
bool ok[MAXV];//ok[v] = true <=> ja calculamos distancia na bfs
int ptl;//aponta onde proxima aresta da bfs vai em level
 
void add_aresta(int u, int v, ll w){
    //posicao da aresta nova na adjList de u e v
    int uptr = (int)adjList[u].size();
    int vptr = (int)adjList[v].size();
    aresta uv = aresta(u, uptr, v, vptr, w);
    //caso direcionado aresta vu = aresta(v, vptr, u, uptr, 0);
    //caso nao direcionado
    aresta vu = aresta(v, vptr, u, uptr, w);
    adjList[u].pb(uv); adjList[v].pb(vu);
}
 
void bfs(int s, int t){//vamos calcular level graph
    for(int i=1; i <= n; i++){
        d[i] = MAXV;
        ok[i] = false;
    }
    d[s] = 0; ok[s] = true;
    ptl = 0;
    queue<int> q; q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int i=0; i < (int)adjList[u].size(); i++){
            aresta atual = adjList[u][i];
            if(atual.cap == 0)continue;//ignora arestas saturadas
            if(ok[atual.dest]){//ja passamos por esse cara antes
                if(d[atual.dest] == d[u] + 1){//essa aresta vai pro level graph
                    level[ptl] = atual;
                    ptl++;
                }
            }else{//se nao passamos, d ainda eh INF
                ok[atual.dest] = true;
                d[atual.dest] = d[u] + 1;//essa aresta vai pro level graph
                level[ptl] = atual;
                ptl++;
                q.push(atual.dest);
            }
        }
    }
    //note que temos uma ordenacao topologica do level graph para fazer dp
}
ll tidalcycle(int s, int t){
    bfs(s, t);
    //High Tide (calcular estimativa inicial de flow)
    for(int i=1; i<=n; i++)h[i] = 0;
    h[s] = INF;//upper bound otimista
    for(int i=0; i < ptl; i++){
        aresta atual = level[i];
        promessa[i] = min(atual.cap, h[atual.orig]);
        h[atual.dest] += promessa[i];
    }
    //Low Tide (hora de refinar a estimativa)
    for(int i=1; i<=n; i++)armazenado[i] = 0;
    armazenado[t] = h[t];//vamos tentar mandar esse fluxo de volta para source
    for(int i=ptl-1; i>=0; i--){
        aresta atual = level[i];
        //quanto fluxo eu consigo mandar de volta nessa aresta ?
        promessa[i] = min(promessa[i], min(armazenado[atual.dest], h[atual.orig] - armazenado[atual.orig]));
        //armazenado[dest] == quanto ainda esta sobrando para ser mandado de volta
        //h[orig] - armazenado[orig] == promessa inicial - quanto nao mandei da promessa == quanto ja mandei da promessa
        armazenado[atual.dest] -= promessa[i];//acabamos de tirar flow daqui para mandar de volta
        armazenado[atual.orig] += promessa[i];//acabamos de mandar flow de volta para aqui
    }
    //Erosao (hora de cumprir as nossas promessas)
    for(int i=1; i<=n; i++)cumpri[i] = 0;
    //cumpri[i] = quanto flow ainda preciso tirar de i para cumprir a promessa
    cumpri[s] = armazenado[s];
    for(int i=0; i<ptl; i++){
        aresta atual = level[i];
        promessa[i] = min(promessa[i], cumpri[atual.orig]);
        cumpri[atual.orig] -= promessa[i];
        cumpri[atual.dest] += promessa[i];
        adjList[atual.orig][atual.ido].cap -= promessa[i];
        adjList[atual.dest][atual.idr].cap += promessa[i];
    }
    return cumpri[t];
}
ll maxflow(int s, int t){
    ll augment = 0;
    ll flow = 0;
    do{
        augment = tidalcycle(s, t);
        flow += augment;
    }while(augment > 0);
    return flow;
}
int main(){
    int m;
    scanf("%d %d", &n, &m);
    for(int i=1; i<=m; i++){
        int u,v,w; scanf("%d %d %d", &u, &v, &w);
        add_aresta(u, v, w);
    }
    printf("%lld\n", maxflow(1, n));
} 
