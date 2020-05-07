/* SPOJ DYNACON
 Dynamic Connectivity */
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
const int MAXN = 1e5+7, MAXQ=1e5+7, sqn=700;
int n,q;
int ti[MAXQ],xi[MAXQ],yi[MAXQ], pai[MAXN], h[MAXN];
bool tem_query[MAXQ];
vector<pii> mods_pai, mods_h;

inline int raiz(int x){
    return (pai[x]==x) ? x : pai[x]=raiz(pai[x]);
}
inline void join(int x, int y){
    x=raiz(x); y=raiz(y);
    if(x==y)return;
    if(h[x] > h[y])swap(x, y);
    pai[x] = y;
    if(h[x]==h[y])h[y]++;
}
inline int raiz_brute(int x){
    return (pai[x]==x) ? x : raiz_brute(pai[x]);
}
inline void join_brute(int x, int y){
    x=raiz_brute(x); y=raiz_brute(y);
    if(x==y)return;
    if(h[x] > h[y])swap(x,y);
    mods_pai.push_back({x, pai[x]});//vamos trocar de volta depois
    pai[x] = y;
    if(h[x] == h[y]){
        mods_h.push_back({y, h[y]});//vamos trocar de volta(importante disfazer mudancas do final para o comeco)
        h[y]++;
    }
}
int main(){
    scanf("%d %d", &n, &q);
    for(int i=0; i<q; i++){
        char c[6]; scanf(" %s", c);
        scanf("%d %d", &xi[i], &yi[i]);
        if(xi[i] > yi[i])swap(xi[i],yi[i]);
        if(c[0]=='a'){
            ti[i] = 0;
        }else if(c[0]=='r'){
            ti[i] = 1;
        }else{
            ti[i] = 2;
            tem_query[i/sqn]=true;
        }
    }
    
    for(int i=0; sqn*i < q; i++){
        if(!tem_query[i])continue;
        //vamos processar bloco i
        for(int j=1; j<=n; j++){
            pai[j] = j;//reset para reconstruir grafo
            h[j] = 1;
        }
        set<pii> arestas_ativadas, arestas_ativadas_dentro;
        int ini=sqn*i, fim=min(q-1,ini+sqn-1);//limites do bloco
        for(int j=0; j<ini; j++){
            if(ti[j] == 0){
                arestas_ativadas.insert({xi[j], yi[j]});
            }else if(ti[j] == 1){
                arestas_ativadas.erase({xi[j], yi[j]});               
            }
        }
        for(int j=ini; j<=fim; j++){
            if(ti[j]!=2 && arestas_ativadas.find({xi[j], yi[j]})!=arestas_ativadas.end()){
                arestas_ativadas.erase({xi[j], yi[j]});
                arestas_ativadas_dentro.insert({xi[j], yi[j]});
            }
        }
        //agora temos conjunto de arestas ativadas antes do bloco (E) cujo status nao muda durante bloco
        //vamos adicionar elas no grafo
        for(set<pii>::iterator it = arestas_ativadas.begin(); it!=arestas_ativadas.end(); ++it){
            int xa = (*it).first; int ya = (*it).second;
            join(xa, ya);
        }
        for(int j=ini; j<=fim; j++){
            //que arestas novas vamos ativar ate o j
            if(ti[j]==0){
                arestas_ativadas_dentro.insert({xi[j], yi[j]});
            }else if(ti[j]==1 && arestas_ativadas_dentro.find({xi[j],yi[j]})!=arestas_ativadas_dentro.end()){
                arestas_ativadas_dentro.erase({xi[j], yi[j]});
            }
            if(ti[j] != 2)continue;
            mods_pai.clear(); mods_h.clear();
            for(set<pii>::iterator it = arestas_ativadas_dentro.begin(); it!=arestas_ativadas_dentro.end(); ++it){//vamos ativar essas arestas brutamente para tirar depois
                int xa = (*it).first; int ya = (*it).second;
                join_brute(xa, ya);
            }
            if(raiz_brute(xi[j]) == raiz_brute(yi[j]))printf("YES\n");
            else printf("NO\n");
            //hora de desfazer mudancas
            for(int k=(int)mods_pai.size()-1; k>=0; k--){
                pai[mods_pai[k].first] = mods_pai[k].second;
            }
            for(int k=(int)mods_h.size()-1; k>=0; k--){
                h[mods_h[k].first] = mods_h[k].second;
            }
        }
    }
} 
