//SPOJ FASTFLOW
//Algoritmo de Dinic
#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define vi vector<int>
#define pb push_back
#define ll long long
const ll INF = 1e16+7;
struct Graph{//representa rede capacitada
	struct Edge{
		int v; ll u;//vertice de destino v da aresta e sua capacidade u
		Edge(int vv, ll uu){v=vv; u=uu;}
		Edge(){}
	};
	int n;
	vector<Edge> edges;
	vector<vi> adj; 
	Graph(int nn){n=nn; adj.resize(nn);}
	Graph(){}
	void add_edge(int v, int w, ll u){//insere aresta (v,w) de capacidade u
		adj[v].pb(edges.size());//guarda indice da aresta em edges
		edges.pb(Edge(w,u));
		adj[w].pb(edges.size());//aresta e reversa diferem so no ultimo bit
		edges.pb(Edge(v,u));
		//edges.pb(Edge(v,0));//aresta reversa (caso direcionado)
	}
};
vi level;//guarda nivel de cada vertice (BFS)
inline bool bfs(Graph &g, int s, int t){
	fill(level.begin(), level.end(), -1);//-1 marca vertice inalcancavel
	level[s] = 0;
	queue<int> q({s});
	while(!q.empty()){
		int v = q.front();
		if(level[v] == level[t])break;
		q.pop();
		for(int i : g.adj[v]){
			int w = g.edges[i].v;
			ll u = g.edges[i].u;
			if(level[w] == -1 && u>0){
				level[w] = level[v] + 1;
				q.push(w);
			}
		}
	}
	return level[t] != -1;//retorna se sink eh alcancavel
}
vi ptr;//utilizado para marcar arestas que ja processamos
//ptr[v] aponta para proxima aresta na lista de v a ser processada
ll augment(Graph &g, int v, int t,  ll cap){
	if(v==t)return cap;//encontramos sink
	for(int &p = ptr[v]; p<(int)g.adj[v].size(); p++){
		int i = g.adj[v][p];
		int w = g.edges[i].v;
		ll u = g.edges[i].u;
		if(level[w] == level[v] + 1 && u>0){//aresta boa! manda recursao
			ll eps = augment(g, w, t, min(cap,u));
			if(eps > 0){
				g.edges[i].u -= eps;
				g.edges[i^1].u += eps;
				return eps;
			}
		}
		//aresta nao eh boa, laco vai marcar dando p++
	}
	return 0;
}
inline ll maxflow(Graph &g, int s, int t){
	level.resize(g.n), ptr.resize(g.n);
	ll total_flow = 0, cur_flow;
	while( bfs(g,s,t) ){
		fill(ptr.begin(), ptr.end(), 0);
		do{
			cur_flow = augment(g, s, t, INF);
			total_flow += cur_flow;
			//coisa boa do dinic eh que reutiliza a mesma BFS varias vezes
		}while(cur_flow > 0);
	}
	return total_flow;
}
int main(){
	fastio;
	int n,m; cin>>n>>m;
	Graph g = Graph(n);
	while(m--){
		int v,w; ll u;
		cin>>v>>w>>u;
		v--; w--;
		//UNDIRECTED NETWORK !!
		g.add_edge(v, w, u);
	}
	cout<<maxflow(g, 0, n-1)<<endl;
}
