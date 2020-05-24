#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define ll long long
#define ld lond double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pld pair<ld,ld>
const int MAXN = 1e4+7, SQN=250;
int n,m,x[MAXN],y[MAXN],cor[MAXN], pai_comp[MAXN] ,corp[MAXN];//cor ou eh 1 ou eh 2
int pai[MAXN];
vector<int> G[MAXN], Gc[MAXN];
bool violou; int pi;
void pre_dfs(int x, int pc){
    int c = (pc==1) ? 2 : 1;
    cor[x] = c; pai_comp[x]=pi;
    for(int i=0; i<(int)G[x].size(); i++){
        int viz = G[x][i];
        if(cor[viz] == 0)pre_dfs(viz, c);
        else if(cor[viz] == cor[x])violou = true;
    }
}
int raiz(int x){return (x==pai[x]) ? x : pai[x]=raiz(pai[x]);}
void unite(int x, int y){pai[x] = y;}
void dfs(int x, int pc){
    int c = (pc==1) ? 2 : 1;
    corp[x] = c;
    for(int i=0; i<(int)Gc[x].size(); i++){
        int viz = Gc[x][i];
        if(corp[viz]==0)dfs(viz, c);
        else if(corp[viz] == corp[x])violou = true;
    }
}
int main(){
    fastio; cin>>n>>m;
    for(int i=0; i<m; i++){
        cin>>x[i]>>y[i];
    }
    vector<int> ans;
    for(int i=0; SQN*i<m; i++){
        for(int j=1; j<=n; j++){
            G[j].clear(); cor[j] = 0;
        }
        int ini=SQN*i; int fim=min(m-1, ini+SQN-1);
        for(int j=0; j<ini; j++){
            G[x[j]].push_back(y[j]);
            G[y[j]].push_back(x[j]);
        }
        for(int j=fim+1; j<m; j++){
            G[x[j]].push_back(y[j]);
            G[y[j]].push_back(x[j]);
        }
        violou = false;
        for(int j=1; j<=n; j++){
            if(cor[j] == 0){
                pi = j;
                pre_dfs(j, 1);
            }
        }
        if(violou)continue;//ja nao ta bipartido
        set<int> pais; pais.clear();
        for(int j=ini; j<=fim; j++){
            pais.insert(pai_comp[x[j]]);
            pais.insert(pai_comp[y[j]]);
        }
        for(int j=ini; j<=fim; j++){
            for(set<int>::iterator it = pais.begin(); it!=pais.end(); ++it){
                pai[*it] = *it;
                Gc[*it].clear();
                corp[*it] = 0;
            }
            violou = false;
            //leave j out of it
            for(int k=ini; k<j; k++){
                if(cor[x[k]] != cor[y[k]]){
                    unite(raiz(pai_comp[x[k]]), raiz(pai_comp[y[k]]));
                }
            }
            for(int k=j+1; k<=fim; k++){
                if(cor[x[k]] != cor[y[k]]){
                    unite(raiz(pai_comp[x[k]]), raiz(pai_comp[y[k]]));
                }
            }
            for(int k=ini; k<j; k++){
                if(cor[x[k]] == cor[y[k]]){
                    Gc[raiz(pai_comp[x[k]])].push_back(raiz(pai_comp[y[k]]));
                    Gc[raiz(pai_comp[y[k]])].push_back(raiz(pai_comp[x[k]]));
                }
            }
            for(int k=j+1; k<=fim; k++){
                if(cor[x[k]] == cor[y[k]]){
                    Gc[raiz(pai_comp[x[k]])].push_back(raiz(pai_comp[y[k]]));
                    Gc[raiz(pai_comp[y[k]])].push_back(raiz(pai_comp[x[k]]));
                }
            }
            for(set<int>::iterator it = pais.begin(); it!=pais.end(); ++it){
                if(corp[raiz(*it)] == 0)
                    dfs(raiz(*it), 1);
            }
            if(!violou)ans.push_back(j);
        }
    }
    cout<<ans.size()<<endl;
    for(int i=0; i<(int)ans.size(); i++)
        cout<<ans[i]+1<<" ";
}
