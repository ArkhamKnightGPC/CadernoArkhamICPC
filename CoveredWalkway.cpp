#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef complex<ll> reta;
const int MAXN = 1e6+7, MAXX=1e9+7;
const ll INF = 1e16+7;

int n, node_counter=0; 
ll c, a[MAXN], dp[MAXN];
reta inicial;
//stuff we need for tree
int fe[20*MAXN], fd[20*MAXN];
reta f[20*MAXN];

int create(){
    node_counter++;
    fe[node_counter] = -1; fd[node_counter] = -1;
    f[node_counter] = inicial;
    return node_counter;
}
ll valor(reta r, ll x){return r.real()*x + r.imag();}
void inserir(int node, int l, int r, reta nova){
    int mid = (l+r)/2;
    ll valor_atual = valor(f[node], mid);
    ll valor_novo = valor(nova, mid);
    if(valor_atual < valor_novo){
        if(fd[node] == -1)fd[node] = create();
        inserir(fd[node], mid+1, r, nova);
    }else{
        swap(f[node], nova);
        if(nova == inicial)return;
        if(fe[node] == -1)fe[node] = create();
        inserir(fe[node], l, mid, nova);
    }
}

ll query(int node, int l, int r, int x){
    if(node == -1)return INF;
    ll valor_node = valor(f[node], x);
    int mid = (l+r)/2;
    if(x<=mid)return min(valor_node, query(fe[node], l, mid, x));
    return min(valor_node, query(fd[node], mid+1, r, x));
}

int main(){
    inicial.real(0); inicial.imag(INF);
    scanf("%d %lld", &n, &c);
    int raiz = create();

    scanf("%lld", &a[1]);
    dp[1] = c;

    for(int i=2; i<=n; i++){
        scanf("%lld", &a[i]);
        //inserir reta (-2*a[i] , dp[i-1] + a[i]^2)
        reta ri; ri.real(-2*a[i]); ri.imag(dp[i-1] + a[i]*a[i]);
        inserir(raiz, 1, MAXX, ri);
        dp[i] = min( c + (a[i]-a[1])*(a[i]-a[1]) , c + a[i]*a[i] + query(raiz, 1, MAXX, a[i]));
    }
    printf("%lld", dp[n]);
}
