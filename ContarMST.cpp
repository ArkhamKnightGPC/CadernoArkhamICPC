#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define ll long long
#define ld lond double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pld pair<ld,ld>
const int MAXN =1e6+7;
const ll MOD = 1e9+7;
int n,m,pai[MAXN];
ll ans = 1, peso=0;
vector< pair<int, pii> > arestas[MAXN];
vector<pii> mod_pai;//first eh posicao, second eh o valor que tem q colocar
int raiz(int x){return (x==pai[x]) ? x : pai[x]=raiz(pai[x]);}
int raiz_brute(int x){return (x==pai[x]) ? x : raiz_brute(pai[x]);}
void unite(int x, int y){x=raiz(x); y=raiz(y); pai[x] = y;}
void unite_brute(int x, int y){
    mod_pai.push_back({x, x});
    pai[x] = y;
}
int main(){
    fastio; cin>>n>>m;
    for(int i=1; i<=n; i++)pai[i]=i;
    for(int i=0; i<m; i++){
        int xi,yi,wi; cin>>xi>>yi>>wi;
        int id = arestas[wi].size();//first eh id da aresta para montar mask depois
        arestas[wi].push_back({id,{xi, yi}});
    }
    for(int i=0; i<MAXN; i++){
        if(arestas[i].size()==0)continue;
        set<int> masks; masks.clear();
        int qnt=0;
        do{//aplicar permutacao brute, colocar mask das arestas usadas no set e fazer rollbacks
            int mask = 0;
            for(int j=0; j<arestas[i].size(); j++){
                int ax = raiz_brute(arestas[i][j].second.first);
                int ay = raiz_brute(arestas[i][j].second.second);
                if(ax != ay){
                    mask += (1<<arestas[i][j].first);
                    unite_brute(ax, ay);
                }
            }
            if(mask != 0)masks.insert(mask);
            qnt = max(qnt, __builtin_popcount(mask));
            for(int j=mod_pai.size()-1; j>=0; j--){
                pai[mod_pai[j].first] = mod_pai[j].second;
            }
            mod_pai.clear();
        }while(next_permutation(arestas[i].begin(), arestas[i].end()));
        if(!masks.empty()){
            //cout<<"Temos "<<masks.size()<<" possibilidades para arestas de peso "<<i<<endl;
            ans = (ans*masks.size())%MOD;
            peso = peso + qnt*i;
        }
        //agora aplica pra valer
        for(int j=0; j<arestas[i].size(); j++){
            unite(arestas[i][j].second.first, arestas[i][j].second.second);
        }
    }
    cout<<peso<<" "<<ans<<endl;
}
