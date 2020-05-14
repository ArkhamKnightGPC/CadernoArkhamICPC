#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
const int MAXN = 1e5+8, root = 0;
string t, pi;
int node_counter = 0, link[MAXN], k, filhos[MAXN][130];
bool ans[MAXN];//se achou ou nao
vector<int> nend[MAXN];//nend[i] = quem sao as strings que acabam no vertice i
bool mrk[MAXN];//se eu ja marquei nend[i] nao vou marcar de novo

int id_pattern=1;
void add(int idx, int pos){//node in trie, position in string
    if(pos == pi.size()){//acabou
        nend[idx].push_back(id_pattern);
        return;
    }
    if(filhos[idx][pi[pos]] == 0){//nao existe aresta para descer(precisamos criar novo vertice)
        node_counter++;
        filhos[idx][pi[pos]] = node_counter;
        //agora vamos calcular suffix link
        if(idx == 0){
            link[node_counter] = 0;//pai eh raiz
        }else{
            int cand = idx;
            bool achou = false;
            while(cand != 0 && !achou){
                if(filhos[cand][pi[pos] - 'a'] == 0)cand = link[cand];
                else achou = true;
            }
            link[node_counter] = cand;
        }
    }
    add(filhos[idx][pi[pos]], pos+1);
}
void go(int idx, int pos){//estamos iterando pelo texto, procurando padroes
    if(pos==t.size())return;//acabou o texto
    if(!mrk[idx]){//marcar padroes encontrados
        mrk[idx] = true;
        for(int i=0; i<(int)nend[idx].size(); i++)ans[nend[idx][i]] = true;
    }
    int cand = idx;//para que vertice vamos
    bool achou = true;
    while(filhos[cand][t[pos]] == 0){
        if(cand == 0){achou = false; break;}
        cand = link[cand];
    }
    if(achou)go(filhos[cand][t[pos]], pos+1);
    else go(0, pos+1);
}
int main(){
    fastio; cin>>t;
    cin>>k;
    for(; id_pattern<=k; id_pattern++){
        cin >> pi;
        add(0, 0);
    }
    go(0, 0);
    for(int i=1; i<=k; i++){
        if(ans[i])cout<<"Y\n";
        else cout<<"N\n";
    }
}
