/* Energia Seletiva IOI 2016
    Reachability Tree (construir sobre Min Spanning Tree)
vamos de precisar de binary lifting, saindo de u qual primeira aresta ancestral com peso > query na reachability tree*/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 7e5+7, MAXL=25, INF = 1e9+7;
struct nst{
    int x,y,w;
    nst(int xx, int yy, int ww){
        x=xx; y=yy; w=ww;
    }
    nst(){}
};
bool comp(nst n1, nst n2){
    return n1.w < n2.w;
}
int n,m,val[MAXN], pai[MAXN], node_counter, anc[MAXN][MAXL], peso[MAXN][MAXL];
vector<nst> arestas;
inline int raiz(int xi){return (xi==pai[xi]) ? xi : pai[xi]=raiz(pai[xi]);}
inline void unite(int xi, int yi, int wi){
    //we are creating a new node with x and y as children
    node_counter++;
    int new_node = node_counter;
    pai[new_node] = new_node; anc[new_node][0] = new_node;
    anc[xi][0] = new_node; anc[yi][0] = new_node;//binary lifting in reachability tree
    peso[xi][0] = wi; peso[yi][0] = wi;
    val[new_node] = val[xi] + val[yi];
    pai[xi] = new_node; pai[yi] = new_node;
}
int main(){
    scanf("%d %d", &n, &m);
    for(int j=0; j<MAXL; j++){
        for(int i=0; i<MAXN; i++){
            peso[i][j] = INF;
        }
    }
    for(int i=1; i<=n; i++){
        pai[i] = i;
        scanf("%d", &val[i]);
    }
    for(int i=0; i<m; i++){
        int xi,yi,wi; scanf("%d %d %d", &xi, &yi, &wi);
        arestas.push_back(nst(xi,yi,wi));
    }
    sort(arestas.begin(), arestas.end(), comp);
    node_counter = n;
    for(int i=0; i<m; i++){
        int xi = raiz(arestas[i].x);
        int yi = raiz(arestas[i].y);
        if(xi == yi)continue;
        int wi = arestas[i].w;
        unite(xi, yi, wi);
    }
    for(int j=1; j<MAXL; j++){
        for(int i=1; i<=node_counter; i++){
            anc[i][j] = anc[anc[i][j-1]][j-1];
            peso[i][j] = peso[anc[i][j-1]][j-1];
        }
    }
    int q; scanf("%d", &q);
    int last = 0;
    for(int i=0; i<q; i++){
        int xi, ki;
        scanf("%d %d", &xi, &ki);
        ki += last;
        for(int j=MAXL-1; j>=0; j--){
            if(peso[xi][j] <= ki){//ta de boa pode pular
                xi = anc[xi][j];
            }
        }
        last = val[xi];
        printf("%d\n", last);
    }
}
