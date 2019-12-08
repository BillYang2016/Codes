#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=50005;

struct Edge {int from,to,dist;};

struct HeapNode {
	int d,u;
	bool operator < (HeapNode a) const {return d>a.d;}
};

struct Prim {
	int n,ans,dist[maxn];
	vector<Edge> edges;
	vector<int> G[maxn];
	bool vst[maxn];
	void init(int n) {this->n=n;}
	void AddEdge(int from,int to,int dist) {
		edges.push_back((Edge) {from,to,dist});
		int m=edges.size();
		G[from].push_back(m-1);
	}
	int main(int s) {
		for(int i=1; i<=n; i++)dist[i]=INT_MAX;
		priority_queue<HeapNode> Q;
		Q.push((HeapNode) {
			0,s
		});
		dist[s]=0;
		while(!Q.empty()) {
			HeapNode Now=Q.top();
			Q.pop();
			if(vst[Now.u])continue;
			vst[Now.u]=1;
			ans+=dist[Now.u];
			for(int id:G[Now.u]) {
				Edge& e=edges[id];
				int Next=e.to,v=e.dist;
				if(!vst[Next]&&v<dist[Next]) {
					dist[Next]=v;
					Q.push((HeapNode) {
						dist[Next],Next
					});
				}
			}
		}
		return ans;
	}
} prim;

int n,m,a[205][205];

int id(int x,int y) {return (x-1)*m+y;}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)a[i][j]=Get_Int();
	prim.init(n*m);
	for(int i=1; i<n; i++)
		for(int j=1; j<=m; j++) {
			prim.AddEdge(id(i,j),id(i+1,j),-a[i][j]*a[i+1][j]);
			prim.AddEdge(id(i+1,j),id(i,j),-a[i][j]*a[i+1][j]);
		}
	for(int j=1; j<m; j++)
		for(int i=1; i<=n; i++) {
			prim.AddEdge(id(i,j),id(i,j+1),-a[i][j]*a[i][j+1]);
			prim.AddEdge(id(i,j+1),id(i,j),-a[i][j]*a[i][j+1]);
		}
	printf("%d\n",-prim.main(1));
	return 0;
}