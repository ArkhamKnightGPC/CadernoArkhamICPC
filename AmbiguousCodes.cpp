#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define ll long long
#define pii pair<int,int>
const int MAXN = 5e3 + 9;
const ll MOD=1e9+9;
ll pr[2] = {31, 41}, inv[2] = {838709685, 195121953};//primes for hashing
vector<ll> sufixos1, sufixos2; //hashes 1 e 2 das strings dos vertices
vector<int> tam;//tamanho da string em cada vertice
ll poten[59][2];//powers of prime for hashing
vector<pii> G[MAXN];
vector<int> carac;//nodes that represent full symbols
int dist[MAXN];//dijkstra
priority_queue<pii, vector<pii>, greater<pii> > pq;
int main(){
    fastio;
    poten[0][0]=1; poten[0][1]=1;
    for(int i=1; i<59; i++)
        for(int j=0; j<2; j++)
            poten[i][j] = (pr[j]*poten[i-1][j])%MOD;
    while(true){
        int n; cin>>n;
        if(n==0)return 0;
        carac.clear(); tam.clear(); sufixos1.clear(); sufixos2.clear();
        for(int i=0; i<MAXN; i++){
            G[i].clear();
        }
        sufixos1.push_back(0); sufixos2.push_back(0); tam.push_back(0);//0-th node is start
        sufixos1.push_back(0); sufixos2.push_back(0); tam.push_back(0);//1-st node is end
        int node_counter = 1;
        for(int i=0; i<n; i++){
            string si; cin>>si;
            ll hsh[2]; hsh[0]=0; hsh[1]=0;
            for(int j=0; j<si.size(); j++)
                for(int k=0; k<2; k++)
                    hsh[k] = (hsh[k] + poten[j][k]*si[j])%MOD;
            node_counter++;
            carac.push_back(node_counter);
            G[0].push_back({node_counter, si.size()});//we always begin inserting full symbol
            sufixos1.push_back(hsh[0]); sufixos2.push_back(hsh[1]); tam.push_back(si.size());
            //lets insert nodes for suffixes to
            for(int j=1; j<(int)si.size(); j++){
                for(int k=0; k<2; k++)
                    hsh[k] = ((hsh[k] - si[j-1])*inv[k])%MOD;
                node_counter++;
                sufixos1.push_back(hsh[0]); sufixos2.push_back(hsh[1]); tam.push_back(si.size() - j);
            }
        }
        //lets build the graph
        for(int i=0; i<n; i++){
            int id = carac[i];//caracter c
            for(int j=2; j<=node_counter; j++){//suffix s = y - x
                if(j == id)continue;
                // is s prefix of c ??
                if(tam[j] <= tam[id]){//possibly...
                    ll pref_id[2];

                    if(tam[id] > tam[j])pref_id[0] = (sufixos1[id] - poten[tam[j]][0]*sufixos1[id + tam[j]])%MOD;
                    else pref_id[0] = sufixos1[id];
                    if(pref_id[0] < 0)pref_id[0] += MOD;

                    if(tam[id] > tam[j])pref_id[1] = (sufixos2[id] - poten[tam[j]][1]*sufixos2[id + tam[j]])%MOD;
                    else pref_id[1] = sufixos2[id];
                    if(pref_id[1] < 0)pref_id[1] += MOD;

                    if(pref_id[0] == sufixos1[j] && pref_id[1] == sufixos2[j]){//s is prefix of c
                        //edge from s to c-s
                        //cout<<j<<" is a prefixx of "<<id<<endl;
                        if(tam[id] > tam[j])G[j].push_back({id+tam[j], tam[id] - tam[j]});
                        else G[j].push_back({1, 0});
                    }
                }
                // is c proper prefix of s ??
                if(tam[id] < tam[j]){//possibly...
                    ll pref_id[2];

                    pref_id[0] = (sufixos1[j] - poten[tam[id]][0]*sufixos1[j + tam[id]])%MOD;
                    if(pref_id[0] < 0)pref_id[0] += MOD;

                    pref_id[1] = (sufixos2[j] - poten[tam[id]][1]*sufixos2[j + tam[id]])%MOD;
                    if(pref_id[1] < 0)pref_id[1] += MOD;

                    if(pref_id[0]==sufixos1[id] && pref_id[1]==sufixos2[id]){//c is prefix of s
                        //edge from s to s-c
                        //cout<<id<<" is a prefix of "<<j<<endl;
                        G[j].push_back({j+tam[id], 0});
                    }
                }
            }
        }   
        //time for dijkstra
        for(int i=1; i<=node_counter; i++)dist[i] = MOD;
        dist[0] = 0; pq.push({dist[0], 0});
        while(!pq.empty()){
            pii aux = pq.top(); pq.pop();
            int vert = aux.second;
            int dv = aux.first;
            for(int i=0; i<(int)G[vert].size(); i++){
                int viz = G[vert][i].first;
                int peso = G[vert][i].second;
                if(dist[viz] > dv + peso){
                    dist[viz] = dv+peso;
                    //cout<<"RELAXEI "<<viz<<" "<<dist[viz]<<" PRED = "<<vert<<endl;
                    pq.push({dist[viz], viz});
                }
            }
        }
        if(dist[1] < MOD)cout<<dist[1]<<endl;
        else cout<<"-1"<<endl;
    }
}
