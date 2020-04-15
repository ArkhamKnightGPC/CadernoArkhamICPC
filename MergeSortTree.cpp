//SPOJ MKTHNUM
#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define pii pair<int,int>
#define vi vector<int>
#define fe 2*idx
#define fd fe+1
#define mid (l+r)/2
const int MAXN = 1e5+7;
int n,m,aux[MAXN];
pii v[MAXN];
vi tree[4*MAXN];
void build(int idx, int l, int r){
    if(l==r){
        tree[idx].push_back(v[l].second);
        return;
    }
    build(fe, l, mid); build(fd, mid+1, r);
    int pe=0, pd=0;
    while(pe < tree[fe].size() && pd < tree[fd].size()){
        if(tree[fe][pe] <= tree[fd][pd]){
            tree[idx].push_back(tree[fe][pe]); pe++;
        }else{
            tree[idx].push_back(tree[fd][pd]); pd++;
        }
    }
    while(pe < tree[fe].size()){
        tree[idx].push_back(tree[fe][pe]); pe++;
    }
    while(pd < tree[fd].size()){
        tree[idx].push_back(tree[fd][pd]); pd++;
    }
}
int kth(int idx, int l, int r, int a, int b, int k){
    if(l==r)return tree[idx][0];
    //quantos caras do intervalo [a,b] tem no filho esquerdo ?
    //2 buscas binarias (primeiro cara >= a     e     ultimo cara <=b)
    int bl=0, br=tree[fe].size()-1;
    while(bl != br){
        int bm = (bl+br)/2;
        if(tree[fe][bm] < a)bl=bm+1;
        else br=bm;
    }
    int bbl=0, bbr=tree[fe].size()-1;
    while(bbl != bbr){
        int bbm = (bbl+bbr+1)/2;
        if(tree[fe][bbm] > b)bbr=bbm-1;
        else bbl = bbm;
    }
    if(tree[fe][bl]>=a && tree[fe][bbl]<=b){
        int cnt = bbl-bl+1;
        if(cnt >= k){
            return kth(fe,l,mid,a,b,k);
        }else{
            return kth(fd,mid+1,r,a,b,k-cnt);
        }
    }else{//nao tem ninguem do intervalo na esquerda
        return kth(fd, mid+1, r, a, b, k);
    }
}
int main(){
    fastio;
    cin>>n>>m;
    for(int i=0; i<n; i++){
        cin>>aux[i];
        v[i] = {aux[i], i};
    }
    sort(v, v+n);
    build(1, 0, n-1);
    while(m--){
        int a,b,k; cin>>a>>b>>k;
        a--; b--;
        cout<<aux[kth(1,0,n-1,a,b,k)]<<endl;
    }
}
