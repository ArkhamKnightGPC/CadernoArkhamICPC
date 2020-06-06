#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
const int MAXN = 5e5+9, INF=1e9+7;
int n,m,q,a[MAXN],ans[MAXN],sz[MAXN],nodes[MAXN],node_counter=0, distCentroidToColor[MAXN], distToCentroid[MAXN];
vector<pii> queries[MAXN];//query[v] stores all queries where vi = v
vector<int> G[MAXN];
bool mrk_centroid[MAXN];
void inicializa_sub(int u, int p){
    nodes[++node_counter] = u;//nodes in current part of decomposition
    sz[u] = 1;
    for(int i=0; i<(int)G[u].size(); i++){
        int viz = G[u][i];
        if(viz==p || mrk_centroid[viz])continue;
        inicializa_sub(viz, u);
        sz[u] += sz[viz];
    }
}
int find_centroid(int u, int p){
    for(int i=0; i<(int)G[u].size(); i++){
        int viz = G[u][i];
        if(viz==p || mrk_centroid[viz])continue;
        if(sz[viz] > sz[u]/2)return find_centroid(viz, u);
    }
    return u;
}
void dfs_centroid(int u, int p, int nivel){
    distToCentroid[u] = nivel;
    distCentroidToColor[a[u]] = min(distCentroidToColor[a[u]], nivel);
    for(int i=0; i<(int)G[u].size(); i++){
        int viz = G[u][i];
        if(viz==p || mrk_centroid[viz])continue;
        dfs_centroid(viz, u, nivel + 1);
    }
}
void decompose(int u, int p){
    node_counter = 0;
    inicializa_sub(u, u);
    int centroid = find_centroid(u, u);
    mrk_centroid[centroid] = true;
    for(int i=1; i<=node_counter; i++)
        distCentroidToColor[a[nodes[i]]] = INF;
    dfs_centroid(centroid, centroid, 0);
    for(int i=1; i<=node_counter; i++){
        int node = nodes[i];
        for(int j=0; j<(int)queries[node].size(); j++){
            int id_query = queries[node][j].second;
            int color = queries[node][j].first;
            ans[id_query] = min(ans[id_query], distCentroidToColor[color] + distToCentroid[node]);
        }
    }
    for(int i=1; i<=node_counter; i++)
        distCentroidToColor[a[nodes[i]]] = INF;
    for(int i=0; i<(int)G[centroid].size(); i++){
        int viz = G[centroid][i];
        if(mrk_centroid[viz])continue;
        decompose(viz, centroid);
    }
}
int main(){
    scanf("%d %d", &n, &m);
    for(int i=1; i<=n; i++)scanf("%d", &a[i]);
    for(int i=1; i<n; i++){
        int xi,yi; scanf("%d %d", &xi, &yi);
        G[xi].push_back(yi); G[yi].push_back(xi);
    }
    scanf("%d", &q);
    for(int i=1; i<=q; i++){
        int vi,ci; scanf("%d %d", &vi, &ci);
        queries[vi].push_back({ci, i});
        ans[i] = INF;
    }
    decompose(1, 0);
    for(int i=1; i<=q; i++){
        printf("%d\n", ans[i]);
    }
}
