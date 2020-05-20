#include<bits/stdc++.h>
using namespace std;
typedef struct node* pnode;
typedef struct node{
    pnode l,r;
    int Hk, sz, val, lz;
    bool rev;
    node(int v){
        l=r=NULL; Hk = rand(); sz=1; val=v; lz=0; rev=false;
    }
}node;
inline int get_sz(pnode &t){return t ? t->sz : 0;}
inline void upt_sz(pnode &t){if(t)t->sz = get_sz(t->l) + 1 + get_sz(t->r);}
inline void refresh(pnode &t){
    if(t){
        if(t->lz == 0)return;
        t->val += t->lz;
        if(t->l)
            t->l->lz += t->lz;
        if(t->r)
            t->r->lz += t->lz;
        t->lz = 0;
    }
}
inline void refresh_rev(pnode &t){
    if(t && t->rev){
        swap(t->l, t->r);
        if(t->l)
            t->l->rev ^= true;
        if(t->r)
            t->r->rev ^= true;
        t->rev = false;
    }
}
void split(pnode t, pnode &l, pnode &r, int pos, int add){
    refresh(t); refresh_rev(t); upt_sz(t);
    if(!t){l=r=NULL; return;}
    int cur_pos = add + get_sz(t->l);
    if(cur_pos <= pos){
        split(t->r, t->r, r, pos, cur_pos + 1); l = t;
    }else{
        split(t->l, l, t->l, pos, add); r = t;
    }
    refresh(t); refresh_rev(t); upt_sz(t);
}
void merge(pnode &t, pnode l, pnode r){
    refresh(l); refresh_rev(l); upt_sz(l);
    refresh(r); refresh_rev(r); upt_sz(r);
    if(!l){t=r; return;}
    if(!r){t=l; return;}
    if(l->Hk >= r->Hk){
        merge(l->r, l->r, r); t = l;
    }else{
        merge(r->l, l, r->l); t = r;
    }
    refresh(t); refresh_rev(t); upt_sz(t);
}
void in_order(pnode t){
    refresh(t); refresh_rev(t); upt_sz(t);
    if(!t)return;
    in_order(t->l);
    char ci = (t->val)%('z'-'a'+1) + 'a';
    cout<<ci;
    in_order(t->r);
}
int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    string s; cin>>s;
    pnode t = NULL;
    for(int i=0; i<(int)s.size(); i++){
        int si = s[i]-'a';
        pnode novo = new node(si);
        merge(t, t, novo);
    }
    /*int li,ri; cin>>li>>ri;
    li--; ri--;
    pnode p1=NULL; split(t, p1, t, li-1, 0);
    pnode p2=NULL; split(t, t, p2, ri-li, 0);
    in_order(p1);cout<<endl;
    in_order(t); cout<<endl;
    in_order(p2); return 0;*/
    int q; cin>>q;
    while(q--){
        int tp; cin>>tp;
        if(tp==1){
            int li,ri,pi; cin>>li>>ri>>pi;
            li--; ri--;
            pnode p1=NULL; split(t, p1, t, li-1, 0);
            pnode p2=NULL; split(t, t, p2, ri-li, 0);
            pnode p3=NULL; merge(p3, p1, p2);
            pnode p4=NULL; split(p3, p3, p4, pi-1, 0);
            merge(t, p3, t);//paste
            merge(t, t, p4);
        }else if(tp==2){
            int li,ri,ci; cin>>li>>ri>>ci;
            li--; ri--;
            pnode p1=NULL; split(t, p1, t, li-1, 0);
            pnode p2=NULL; split(t, t, p2, ri-li, 0);
            refresh(t); refresh_rev(t); upt_sz(t);
            t->lz += ci;
            refresh(t); refresh_rev(t); upt_sz(t);
            merge(t, t, p2);
            merge(t, p1, t);
        }else{
            int li,ri; cin>>li>>ri;
            li--; ri--;
            pnode p1=NULL; split(t, p1, t, li-1, 0);
            pnode p2=NULL; split(t, t, p2, ri-li, 0);
            refresh(t); refresh_rev(t); upt_sz(t);
            t->rev ^= true;
            refresh(t); refresh_rev(t); upt_sz(t);
            merge(t, t, p2);
            merge(t, p1, t);
        }
    }
    in_order(t);
}
