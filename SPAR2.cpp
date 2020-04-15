/* Merge Sort Tree
   Codechef SPAR2 */
#include<bits/stdc++.h>
using namespace std;
#define vd vector<double>
#define fe 2*idx
#define fd fe+1
#define mid (l+r)/2
const int MAXN = 1e5+7;
const double INF=1e9+7, R2=sqrt(2.0);
int n,q;
double v[MAXN];
vd tree[4*MAXN];

void build(int idx, int l, int r){
    if(l==r){
        tree[idx].push_back(v[l]);
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
double query1(int idx, int l, int r, int a, int b, double val){//maior cara no intervalo [a,b] <= val
    if(l>b || r<a)return -INF;
    if(l>=a && r<=b){//busca binaria
        int bl=0, br=tree[idx].size()-1;
        while(bl != br){
            int bm = (bl+br+1)/2;
            if(tree[idx][bm] > val)br = bm-1;
            else bl = bm;
        }
        if(tree[idx][bl] <= val)return tree[idx][bl];
        return -INF;
    }
    return max(query1(fe,l,mid,a,b,val), query1(fd,mid+1,r,a,b,val));
}
double query2(int idx, int l, int r, int a, int b, double val){//menor cara no intervalo [a,b] >= val
    if(l>b || r<a)return INF;
    if(l>=a && r<=b){//busca binaria
        int bl=0, br=tree[idx].size()-1;
        while(bl != br){
            int bm = (bl+br)/2;
            if(tree[idx][bm] < val)bl = bm+1;
            else br = bm;
        }
        if(tree[idx][bl] >= val)return tree[idx][bl];
        return INF;
    }
    return min(query2(fe,l,mid,a,b,val), query2(fd,mid+1,r,a,b,val));
}
int main(){
    scanf("%d %d", &n, &q);
    for(int i=0; i<n; i++){
        scanf("%lf", &v[i]);
    }
    build(1,0,n-1);
    while(q--){
        int a,b; double c;
        scanf("%d %d %lf", &a, &b, &c);
        a--; b--;

        //area eh maxima quando L = sqrt(2)*c
        //vamos pegar maior L <= R2*c e menor L >= R2*c e comparar as areas
        double cand1 = query1(1,0,n-1,a,b,R2*c);
        double cand2 = query2(1,0,n-1,a,b,R2*c);
        if(cand2 > 2*c)cand2 = INF;//nao obedece desigualdade triangular
        
        double max_area = 0;
        double ans = -1;
        if(cand1 > 0){//considerar cand1
            double per = (c+c+cand1)/2.0;
            double area = sqrt(per*(per-c)*(per-c)*(per-cand1));
            if(area > max_area){max_area=area; ans=cand1;}
        }
        if(cand2 <= 2*c){
            double per = (c+c+cand2)/2.0;
            double area = sqrt(per*(per-c)*(per-c)*(per-cand2));
            if(area > max_area){max_area=area; ans=cand2;}         
        }
        printf("%.0lf\n", ans);
    }
}
