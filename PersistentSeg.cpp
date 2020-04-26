/*SPOJ MKTHNUM
   Persistent Segment Tree */
#include<bits/stdc++.h>
using namespace std;
#define mid (li+ri)/2
const int SZ = 2e7+7, MAXN = 1e5+7;
int l[SZ], r[SZ], tree[SZ], raiz[SZ], node_counter=0, n, q, a[MAXN], b[MAXN], freq[MAXN];
map<int,int> m, mr;
 
inline int newleaf(int val){
    int p = ++node_counter;
    l[p] = 0; r[p] = 0;
    tree[p] = val;
    return p;
}
 
inline int newparent(int lef, int rig){
    int p = ++node_counter;
    l[p] = lef; r[p] = rig;
    tree[p] = tree[lef] + tree[rig];
    return p;
}
 
int build(int li, int ri){
    if(li==ri)return newleaf(0);
    return newparent(build(li, mid), build(mid+1, ri));
}
 
int build_prev(int rprev, int pos, int li, int ri){
    if(li == ri)return newleaf(freq[li]);
    if(pos <= mid)//right stays the same
        return newparent(build_prev(l[rprev], pos, li, mid), r[rprev]);
    else
        return newparent(l[rprev], build_prev(r[rprev], pos, mid+1, ri));
}
int query(int r1, int r2, int k, int li, int ri){
    if(li==ri)return li;
    int cnt = tree[l[r2]] - tree[l[r1]];//how many if we go left ?
    if(cnt < k)//not enough
        return query(r[r1], r[r2], k-cnt, mid+1, ri);
    else
        return query(l[r1], l[r2], k, li, mid);
}
int main(){
    scanf("%d %d", &n, &q);
    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b, b+n);
    int aux = 0;
    for(int i=0; i<n; i++){
        if(i>0 && b[i]==b[i-1])continue;
        m[b[i]] = aux;
        mr[aux] = b[i];
        aux++;
    }
    raiz[0] = build(0, n-1);
    for(int i=1; i<=n; i++){
        a[i-1] = m[a[i-1]];
        freq[a[i-1]]++;
        raiz[i] = build_prev(raiz[i-1], a[i-1], 0, n-1);//equal to raiz[i-1] except in position a[i-1]
    }
    while(q--){
        int ql,qr,qk;
        scanf("%d %d %d", &ql, &qr, &qk);
        int ans = mr[query(raiz[ql-1], raiz[qr], qk, 0, n-1)];
        printf("%d\n", ans);
    }   
}  
