#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
const int MAXN = 1e3+7;
int alc_par[MAXN], alc_impar[MAXN], alc[2*MAXN];
long long manacher(string s){
    string t;
    for(int i=0; i<(int)s.size(); i++){
        t += "$";
        t += s[i];
    }
    t += "$";
    int k = -1;
    for(int i=0; i<(int)t.size(); i++){
        int ip = 2*k - i;
        int dst = k + alc[k] - i;
        if(k != -1 && dst > 0 && alc[ip] < dst){
            alc[i] = alc[ip];
        }else{
            int x;
            if(k != -1 && dst > 0)
                x = dst;
            else
                x = 0;
            while(i - x > 0 && i + x < t.size()-1 && t[i-x-1]==t[i+x+1])
                x++;
            alc[i] = x;
            k = i;
        }
    }
    long long cnt = 0;
    //cout<<t<<endl;
    for(int i=0; i<(int)t.size(); i++){
        //cout<<"ALC "<<i<<" "<<alc[i]<<endl;
        if(i%2 == 0){//asterisco
            cnt += alc[i]/2;
        }else{//letra real
            cnt += (alc[i]+1)/2;
        }
    }
    return cnt;
}
int main(){
    fastio;
    int tc; cin>>tc;
    while(tc--){
        string s; cin>>s;
        long long ans = manacher(s);
        cout<<ans<<endl;
    }
}
