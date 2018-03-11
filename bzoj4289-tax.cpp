#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
#define pii pair<LL,int>
#define mp make_pair

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=400005;

struct Edge {
	int to,dist;
};

vector<Edge> edges,edges2[maxn];
vector<int> in[maxn],out[maxn];
LL dist[maxn];
int n,m,S,T;
bool vst[maxn];

void AddEdge(int x,int y,int v) {
	edges.push_back((Edge) {y,v});
	edges.push_back((Edge) {x,v});
	int cnt=edges.size();
	out[x].push_back(cnt-2),in[y].push_back(cnt-2);
	out[y].push_back(cnt-1),in[x].push_back(cnt-1);
}

bool cmp(int x,int y) {
	return edges[x].dist<edges[y].dist;
}

void build(int x) {
	vector<int> st;
	for(int id:out[x])st.push_back(id);
	sort(st.begin(),st.end(),cmp);
	for(int i=0; i<(int)st.size()-1; i++) {
		edges2[st[i]].push_back((Edge) {st[i+1],edges[st[i+1]].dist-edges[st[i]].dist});
		edges2[st[i+1]].push_back((Edge) {st[i],0});
	}
	for(int id:in[x])edges2[id].push_back((Edge) {id^1,edges[id].dist});
}

void Dijkstra() {
	fill(dist,dist+T+1,LLONG_MAX/2);
	priority_queue<pii,vector<pii>,greater<pii> > Q;
	Q.push(mp(dist[S]=0,S));
	while(!Q.empty()) {
		int Now=Q.top().second;
		Q.pop();
		if(vst[Now])continue;
		vst[Now]=1;
		for(Edge& e:edges2[Now]) {
			int Next=e.to;
			if(dist[Now]+e.dist<dist[Next]) {
				dist[Next]=dist[Now]+e.dist;
				Q.push(mp(dist[Next],Next));
			}
		}
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		AddEdge(x,y,v);
	}
	S=2*m+1,T=2*m+2;
	for(int id:out[1])edges2[S].push_back((Edge) {id,edges[id].dist});
	for(int id:in[n])edges2[id].push_back((Edge) {T,edges[id].dist});
	for(int i=1; i<=n; i++)build(i);
	Dijkstra();
	printf("%lld\n",dist[T]);
	return 0;
}