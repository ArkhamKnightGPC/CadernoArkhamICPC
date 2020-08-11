#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define ll long long
const ll MOD = 163577857;
const int MAXN = 50007, MAXK=107, MAXL = 32;
int n, h, x, k, pos[MAXN], a[MAXK], c[MAXK];
ll R[MAXK][MAXK][MAXL];//powers of Recurrent Matrix R^(2^w) 0<=w<MAXL

ll cur[MAXK], prv[MAXK];
ll get_prefix_sum(int idx){
    if(idx <= k){//i know all these a values
        ll ret = 0;
        for(int i=1; i<=idx; i++)ret = (ret+a[i])%MOD;
        return ret;
    }
    idx -= k;//i need matrix exponentiation for bigger values
    ll aux = 0;//a[1]+...+a[k]
    for(int i=1; i<=k; i++){
        cur[i] = a[k-i+1];//BASE matrix a[k],...,a[1],pref_sum
        prv[i] = cur[i];
        aux += a[i];
    }
    cur[k+1] = aux%MOD;
    prv[k+1] = cur[k+1];

    for(int i=MAXL-1; i>=0; i--){
        if((idx&(1<<i)) == 0)continue;
        for(int j=1; j<=k+1; j++){
            cur[j] = 0;
            for(int g=1; g<=k+1; g++){
                cur[j] = (cur[j] + R[j][g][i]*prv[g])%MOD;
            }
        }
        for(int j=1; j<=k+1; j++)prv[j] = cur[j];
    }
    return cur[k+1];
}
ll fastxp(ll x, ll ep){
    if(ep==0)return 1LL;
    if(ep%2==1)return (x*fastxp(x, ep-1))%MOD;
    ll aux = fastxp(x, ep/2);
    return (aux*aux)%MOD;
}

int main(){
    cin >> n >> h >> x >> k;
    for(int i=1; i<=n; i++)cin >> pos[i];
    for(int i=1; i<=k; i++)cin >> a[i];
    for(int i=1; i<=k; i++)cin >> c[i];
    //precomputation of R^(2^w)

    //Base case w=0: R^1
    for(int i=1; i<=k; i++)R[1][i][0] = c[i];//first line
    for(int i=2; i<=k; i++)//next (k-1)lines
        R[i][i-1][0] = 1;
    for(int i=1; i<=k; i++)R[k+1][i][0] = c[i];//last line -> prefix sum
    R[k+1][k+1][0] = 1;

    //Recurrence R^(2^w) = R^(2^(w-1)) squared
    for(int w=1; w<MAXL; w++)
        for(int i=1; i<=k+1; i++)
            for(int j=1; j<=k+1; j++)
                for(int g=1; g<=k+1; g++)
                    R[i][j][w] = (R[i][j][w] + R[i][g][w-1]*R[g][j][w-1])%MOD;

    ll s = get_prefix_sum(h)%MOD;//sum of all a[i]
    //cout<<"LET ME SEE "<<s<<endl;
    ll q = fastxp(s, MOD-2);
    ll p = 0;
    for(int i=1; i<=n; i++){
        //Probability building i is in range
        int j = pos[i] - x;
        ll sm;
        if(j < 1){
            j += h;
            sm = s - (get_prefix_sum(j) - get_prefix_sum(pos[i]));
        }else{
            sm = get_prefix_sum(pos[i]) - get_prefix_sum(j);
        }
        sm = sm%MOD;
        //cout<<"for "<<i<<" i got "<<sm<<endl;
        p = (p + sm)%MOD;
    }
    //cout<<"LOOK MAN "<<p<<endl;
    ll ans = (p*q)%MOD;
    if(ans < 0)ans+=MOD;
    cout << ans << endl;
}
