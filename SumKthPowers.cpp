#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define ll long long
#define pll pair<ll, ll>
const ll MOD = 1e9+7, MAXN = 1e6+7;
ll inverso_fatorial[MAXN], inverso[MAXN];
ll fastxp(ll x, ll expoente){
    if(expoente==0)return 1LL;
    if(expoente%2==1)return (x*fastxp(x, expoente-1))%MOD;
    ll ret = fastxp(x, expoente/2);
    return (ret*ret)%MOD;
}
pll euclid(ll a, ll b){
    if(a==0)return {0,1};
    pll ei = euclid(b%a, a);
    return {ei.second - (b/a)*ei.first, ei.first};
}
int main(){
    ll n,k; cin>>n>>k;
    inverso_fatorial[0] = 1; inverso_fatorial[1]=1;
    inverso[0] = 1; inverso[1] = 1;
    for(ll i=2; i<=k+1; i++){
        ll quoc = MOD/i;
        ll rem = MOD%i;
        //cout<<"OLHA "<<quoc<<" "<<rem<<endl;
        inverso[i] = - (inverso[rem]*quoc)%MOD;
        //cout<<i<<" "<<inverso[i]<<endl;
        inverso_fatorial[i] = (inverso[i]*inverso_fatorial[i-1])%MOD;
    }
    ll atual = 0;
    if(n <= k+1){
        for(ll i=1; i<=n; i++){
            atual = (atual + fastxp(i, k))%MOD;
        }
        cout<<atual<<endl;
        return 0;
    }
    ll fator = 1;
    for(ll i=n; i>=n-(k+1); i--)
        fator = (fator*i)%MOD;
    ll ans = 0;
    for(ll i=1; i<=k+1; i++){
        atual = (atual + fastxp(i, k))%MOD;
        ll sgn = (k+1-i)%2==1 ? -1 : 1;
        ll aux = ( ((euclid(n-i, MOD).first*inverso_fatorial[i])%MOD)*inverso_fatorial[k+1-i] )%MOD;
        ans = (ans + (((fator*atual)%MOD)*sgn*aux)%MOD)%MOD;
        if(ans<0)ans+=MOD;
    }
    cout<<ans<<endl;
}
