#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cout.tie(NULL);cout.tie(NULL)
const int MAXN = 258;
const long long MOD = 1e9+7, PR=257;
int n,m,freq[MAXN][MAXN][30], odd_counter[MAXN][MAXN], alc[2*MAXN];
long long hsh[MAXN][MAXN], poten[30], gp[2*MAXN], tgp, gr[MAXN], tgr;
char mat[MAXN][MAXN];
bool ok[MAXN];

inline long long manacher(){
    tgp = 0;
    for(int i=0; i<tgr; i++){
        gp[tgp] = -1; tgp++;
        gp[tgp] = gr[i]; tgp++;
    }
    gp[tgp] = -1; tgp++;
    
    int k=-1;
    for(int i=0; i<tgp; i++){
        int ip = 2*k - i;
        int dst = (k!=-1) ? k + alc[k] - i : 0;
        if(k!=-1 && dst > 0 && alc[ip] < dst){
            alc[i] = alc[ip];
        }else{
            int x;
            if(k!=-1 && dst > 0)
                x = dst;
            else
                x = 0;
            while(i-x>0 && i+x<tgp-1 && gp[i-x-1]==gp[i+x+1])
                x++;
            alc[i] = x;
            k = i;
        }
    }
    long long cnt = 0;
    for(int i=0; i<tgp; i++){
        if(i%2==0){//asterisco
            cnt += alc[i]/2;
        }else{//real
            cnt += (alc[i]+1)/2;
        }
    }
    return cnt;
}

int main(){
    fastio;
    poten[0] = 1;
    for(int i=1; i<30; i++)poten[i] = (PR*poten[i-1])%MOD;

    cin>>n>>m;
    for(int i=0; i<n; i++){
        string s; cin>>s;
        for(int j=0; j<m; j++){
            mat[i][j] = s[j];
        }
    }
    long long ans = 0;
    for(int c1=0; c1<m; c1++){
        for(int c2=c1; c2<m; c2++){//fixa as duas colunas
            tgr = 0;
            for(int li=0; li<n; li++){//passar por todas as windows das linhas
                int novo = mat[li][c2] - 'a';

                if(freq[c1][li][novo]%2==0)odd_counter[c1][li]++;//vai ficar impar
                else odd_counter[c1][li]--;//vai deixar de ser impar

                freq[c1][li][novo]++;
                hsh[c1][li]  = (hsh[c1][li] + poten[novo])%MOD;

                ok[li] = (odd_counter[c1][li] <= 1);//me diz se linha consegue virar palindromo

                if(!ok[li] && tgr){
                    ans += manacher();//quebra grupo aqui
                    tgr = 0;
                }
                if(ok[li]){
                    gr[tgr] = hsh[c1][li]; tgr++;
                }
            }
            if(tgr)ans += manacher();
            tgr = 0;
        }
    }
    cout<<ans<<endl;
}
