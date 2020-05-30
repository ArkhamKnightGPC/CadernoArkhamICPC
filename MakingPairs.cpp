#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define ll long long
#define ld lond double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pld pair<ld,ld>
const int MAXN = 1e3+7, LIM=1e6+7;
const ll INF = 1e12+7;
vector<pll> it[MAXN], jt[MAXN];//li chao trees (dynamic segment trees, one for each row and one for each column)
vector<int> fe_i[MAXN], fd_i[MAXN], fe_j[MAXN], fd_j[MAXN];
int n; ll a[MAXN],sa[MAXN],b[MAXN],sb[MAXN], dp[MAXN][MAXN];
ll val(pll reta, ll x){return reta.first*x + reta.second;}
int create_i(pll reta, int id){
    int novo = (int)it[id].size();
    it[id].push_back(reta);
    fe_i[id].push_back(-1); fd_i[id].push_back(-1);
    return novo;
}
int create_j(pll reta, int id){
    int novo = (int)jt[id].size();
    jt[id].push_back(reta);
    fe_j[id].push_back(-1); fd_j[id].push_back(-1);
    return novo;
}
void upt_i(int idx, int l, int r, int id, pll reta){
    int mid = (l+r)/2;
    ll atual = val(it[id][idx], mid);
    ll novo = val(reta, mid);
    if(novo > atual){
        swap(it[id][idx], reta);//voce toma o lugar da reta
        if(fe_i[id][idx] != -1){
            upt_i(fe_i[id][idx], l, mid, id, reta);
        }else if(l != r){
            int aux = create_i(reta, id);
            fe_i[id][idx] = aux;
        }
    }else{
        if(fd_i[id][idx] != -1)
            upt_i(fd_i[id][idx], mid+1, r, id, reta);
        else if(l != r){
            int aux = create_i(reta, id);
            fd_i[id][idx] = aux;
        }
    }
}
void upt_j(int idx, int l, int r, int id, pll reta){
    int mid = (l+r)/2;
    ll atual = val(jt[id][idx], mid);
    ll novo = val(reta, mid);
    if(novo > atual){//se sou maior aq, sou maior na direita tambem
        swap(jt[id][idx], reta);//voce toma o lugar da reta
        if(fe_j[id][idx] != -1)
            upt_j(fe_j[id][idx], l, mid, id, reta);
        else if(l != r){
            int aux = create_j(reta, id);
            fe_j[id][idx] = aux;
        }
    }else{//se sou menor aqui, sou menor na esquerda tambem
        if(fd_j[id][idx] != -1)
            upt_j(fd_j[id][idx], mid+1, r, id, reta);
        else if(l != r){
            int aux = create_j(reta, id);
            fd_j[id][idx] = aux;
        }
    }
}
ll query_i(int idx, int l, int r, int id, int x){
    ll ret = val(it[id][idx], x);
    int mid = (l+r)/2;
    if(x <= mid){
        if(fe_i[id][idx] != -1)ret = max(ret, query_i(fe_i[id][idx], l, mid, id, x));
    }else{
        if(fd_i[id][idx] != -1)ret = max(ret, query_i(fd_i[id][idx], mid+1, r, id, x));
    }
    return ret;
}
ll query_j(int idx, int l, int r, int id, int x){
    ll ret = val(jt[id][idx], x);
    int mid = (l+r)/2;
    if(x <= mid){
        if(fe_j[id][idx] != -1)ret = max(ret, query_j(fe_j[id][idx], l, mid, id, x));
    }else{
        if(fd_j[id][idx] != -1)ret = max(ret, query_j(fd_j[id][idx], mid+1, r, id, x));
    }
    return ret;
}
int main(){
    fastio; cin>>n;
    for(int i=1; i<=n; i++){
        cin>>a[i]; sa[i] = sa[i-1] + a[i];
    }
    sa[n+1] = sa[n];//a[n+1] = 0
    for(int i=1; i<=n; i++){
        cin>>b[i]; sb[i] = sb[i-1] + b[i];
    }
    sb[n+1] = sb[n];//b[n+1] = 0
    for(int i=0; i<MAXN; i++){
        dp[i][0] = -sa[i]*sa[i];
        dp[0][i] = -sb[i]*sb[i];
        int raiz = create_i({2*sb[0], dp[i][0] - sb[0]*sb[0]}, i);//should have j=0
        raiz = create_j({2*sa[0], dp[0][i] - sa[0]*sa[0]}, i);
    }
    for(int i=1; i<=n+1; i++){
        for(int j=1; j<=n+1; j++){
            //calcular dp[i][j]
            ll cand1 = a[i]*b[j] - sa[i-1]*sa[i-1] + query_j(0, 0, LIM, j-1, sa[i-1]);
            ll cand2 = a[i]*b[j] - sb[j-1]*sb[j-1] + query_i(0, 0, LIM, i-1, sb[j-1]);
            dp[i][j] = max(cand1, cand2);
            //hora de atualizar, caso ip = i-1
            if(i-1 > 0)upt_i(0, 0, LIM, i-1, {2*sb[j], dp[i-1][j] - sb[j]*sb[j]});
            //caso jp = j-1
            if(j-1 > 0)upt_j(0, 0, LIM, j-1, {2*sa[i], dp[i][j-1] - sa[i]*sa[i]});
        }
    }
    cout << dp[n+1][n+1] << endl;
}
