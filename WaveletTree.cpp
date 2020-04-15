/*  Wavelet Tree 
    SPOJ MKTHNUM  */
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+7, INF=1e9+7, MAXX = 4e5+7;
int n, q, a[MAXN], b[MAXN],cnt = 1, m_esq, m_dir, atual_esq, atual_dir, esq, dir;
vector<int> val[MAXX], pref[MAXX];
map<int, int> M, Mrev;
int fe[MAXX], fd[MAXX];
 
void build(int idx, int vl, int vr){
    if(vl == vr)return;
    int tam = val[idx].size();
    int m_pai = (vl + vr)/2;
    for(int i=0; i<tam; i++){
        int aux = val[idx][i];
        if(aux <= m_pai){
            if(fe[idx] == 0){
                fe[idx] = cnt++;
                m_esq = (vl + m_pai)/2;
                atual_esq = 0;
                esq = fe[idx];
            }
            val[esq].push_back(aux);
            if(aux <= m_esq)atual_esq++;
            pref[esq].push_back(atual_esq);
        }else{
            if(fd[idx] == 0){
                fd[idx] = cnt++;
                m_dir = (m_pai + 1 + vr)/2;
                atual_dir = 0;
                dir = fd[idx];
            }
            val[dir].push_back(aux);
            if(aux <= m_dir)atual_dir++;
            pref[dir].push_back(atual_dir);
        }
    }
    if(fe[idx] != 0)build(fe[idx], vl, m_pai);
    if(fd[idx] != 0)build(fd[idx], m_pai+1, vr);
    return;
}
 
int query(int idx, int vl, int vr, int ql, int qr, int qk){
    if(vl == vr)return vl;
    int mid = (vl + vr)/2;
 
    int cnt_left = pref[idx][qr];
    if(ql > 0)cnt_left -= pref[idx][ql-1];
    int cnt_right = qr - ql + 1 - cnt_left;
    if(cnt_left >= qk){
        int nl = (ql > 0) ? pref[idx][ql-1] : 0;
        int nr = nl + cnt_left - 1;
        return query(fe[idx], vl, mid, nl, nr, qk);
    }else{
        int nl = (ql>0) ? ql - pref[idx][ql-1] : 0;
        int nr = nl + cnt_right - 1;
        return query(fd[idx], mid+1, vr, nl, nr, qk - cnt_left);
    }
}
 
int main(){
    scanf("%d %d", &n, &q);
    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b, b+n);
    int xx = 0;
    for(int i=0; i<n; i++){
        if(i>0 && b[i]==b[i-1])continue;
        xx++;
        M[b[i]] = xx;
        Mrev[xx] = b[i];
    }
    int raiz = 0;
    int md = (1 + xx)/2;
    int atual = 0;
    for(int i=0; i<n; i++){
        a[i] = M[a[i]];
        val[raiz].push_back(a[i]);
        if(a[i] <= md)atual++;
        pref[raiz].push_back(atual);
    }
    build(raiz, 1, xx);
 
    while(q--){
        int ql, qr, qk;
        scanf("%d %d %d", &ql, &qr, &qk);
        ql--; qr--;
        printf("%d\n", Mrev[query(raiz, 1, xx, ql, qr, qk)]);
    }
}  
