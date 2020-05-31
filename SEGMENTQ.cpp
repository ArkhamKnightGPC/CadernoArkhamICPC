#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+7;
#define fe 2*idx
#define fd fe+1
#define mid (l+r)/2
vector<int> segm[MAXN];//segm[i] = list of nodes for segment i
vector<int> node[4*MAXN];//node[i] = list of segments for node i
int leaf[MAXN];//leaf[i] = node of segment tree correponding to leaf i
int tree[4*MAXN];//tree[node] = how many marked points in node interval
int lgt[4*MAXN];//lgt[node] = length of interval of node
int act[MAXN];//act[seg] = how many nodes are activated for segment seg
int n, q, seg_counter=0;
void build(int idx, int l, int r){
    lgt[idx] = r-l+1;
    if(l==r){leaf[l] = idx;return;}
    build(fe, l, mid); build(fd, mid+1, r);
}
int query(int idx, int l, int r, int ql, int qr){
    if(l>qr || r<ql)return 0;
    if(l>=ql && r<=qr)return tree[idx];
    return query(fe, l, mid, ql, qr) + query(fd, mid+1, r, ql, qr);
}
void upt(int idx, int l, int r, int ql, int qr){
    if(l>qr || r<ql)return;
    if(l>=ql && r<=qr){
        segm[seg_counter].push_back(idx);
        if(tree[idx]==lgt[idx])act[seg_counter]++;//this part of new segment is already activated
        node[idx].push_back(seg_counter);
        return;
    }
    upt(fe, l, mid, ql, qr); upt(fd, mid+1, r, ql, qr);
}
int query2(int idx){
    tree[idx]++;
    int ret = 0;
    if(tree[idx] == lgt[idx]){//this interval just got activated
        for(int i=0; i<(int)node[idx].size(); i++){
            int seg_i = node[idx][i];
            act[seg_i]++;
            if(act[seg_i] == segm[seg_i].size())ret++;//all intervals in segment just became activated
        }
    }
    if(idx > 1)return ret + query2(idx/2);//go to parent
    return ret;
}
int main(){
    scanf("%d %d", &n, &q);
    build(1, 1, n);
    while(q--){
        int tp; scanf("%d", &tp);
        if(tp==0){
            int li,ri; scanf("%d %d", &li, &ri);
            int aux = query(1, 1, n, li, ri);
            if(aux < ri-li+1){//new segment
                seg_counter++;
                upt(1, 1, n, li, ri);
            }
        }else{
            int p; scanf("%d", &p);
            int aux = query(1, 1, n, p, p);
            if(aux==0)printf("%d\n", query2(leaf[p]));
            else printf("0\n");//was already marked
            fflush(stdout);
        }
    }
}
