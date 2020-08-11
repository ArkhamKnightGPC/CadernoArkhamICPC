#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define ll long long
#define pii pair<int,int>
const ll MOD = 1e9+7;
const int MAXN = 3e3+7, LIM = 4e6+7;
int p,q,c,m;
vector<pii> s;
ll dp[MAXN], fat[LIM], inv[LIM], inv_fat[LIM];

ll fastxp(ll x, ll ep){
    if(ep==0)return 1LL;
    if(ep%2==1)return (x*fastxp(x, ep-1))%MOD;
    ll aux = fastxp(x, ep/2);
    return (aux*aux)%MOD;
}
ll compute(int x, int y){
    if(x<0 || y<0)return 0;
    ll ret = fat[x+y];
    ret = (ret*inv_fat[x])%MOD;
    ret = (ret*inv_fat[y])%MOD;
    return ret;
}
ll catalan(int x1, int y1, int x2, int y2){
    int x1p = y1 + (c-1);
    int y1p = x1 - (c-1);
    ll ret = compute(x2-x1, y2-y1) - compute(x2-x1p, y2-y1p);
    return ret%MOD;
}
int main(){
    fastio;
    fat[0] = 1; inv_fat[0] = 1;
    for(int i=1; i<LIM; i++)fat[i] = (fat[i-1]*i)%MOD;
    inv_fat[LIM-1] = fastxp(fat[LIM-1], MOD-2);
    for(int i=LIM-2; i>=1; i--)inv_fat[i] = (inv_fat[i+1]*(i+1LL))%MOD;

    cin >> p >> q >> c >> m;
    bool poss = (p >= q+c);

    for(int i=0; i<m; i++){
        int gi,bi; cin>>gi>>bi;
        if(gi>=bi+c && gi<=p && bi<=q)//abaixo da reta e dentro do nosso grid
            s.push_back({gi,bi});
        if(gi==p && bi==p)poss = false;
        if(gi<=c && bi==0)poss = false;
    }
    if(!poss){cout<<"0"<<endl; return 0;}

    s.push_back({p,q});
    sort(s.begin(), s.end());
    s.resize(unique(s.begin(), s.end()) - s.begin());

    for(int i=0; i<(int)s.size(); i++){
        dp[i] = catalan(c, 0, s[i].first, s[i].second);
        for(int j=0; j<i; j++){
            if(s[i].first < s[j].first || s[i].second < s[j].second)continue;
            ll aux = (catalan(s[j].first, s[j].second, s[i].first, s[i].second)*dp[j])%MOD;
            dp[i] = (dp[i] - aux)%MOD;
            if(dp[i] < 0)dp[i] += MOD;
        }
    }
    cout << dp[(int)s.size()-1] << endl;
}
