#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=20005,K=30;

struct Edge {
	int from,to,dist;
	Edge(int x=0,int y=0,int v=0):from(x),to(y),dist(v) {}
};

struct St {
	int u,v,dist;
	St(int x=0,int y=0,int va=0):u(x),v(y),dist(va) {}
};

vector<Edge> edges[maxn],tree[maxn];
vector<int> Circle[maxn];
stack<St> S;

int step=0,Lowlink[maxn],Dfn[maxn],BCC=0,New,Length[maxn],f[maxn],Belong[maxn],vst[maxn],Square[maxn];
int n,m,q,father[maxn],Depth[maxn],Dist[maxn],p[maxn][K];

void AddEdge(int x,int y,int v) {edges[x].push_back(Edge(x,y,v));}

void AddEdge2(int x,int y,int v) {tree[x].push_back(Edge(x,y,v));}

void Dfs(int Now,int fa,int depth) {
	father[Now]=fa;
	Depth[Now]=depth;
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(Next==fa)continue;
		Dist[Next]=Dist[Now]+e.dist;
		Dfs(Next,Now,depth+1);
	}
}

void Sparse_Table() {
	for(int i=1; i<=New; i++)p[i][0]=father[i];
	for(int j=1; j<K; j++)
		for(int i=1; i<=New; i++)p[i][j]=p[p[i][j-1]][j-1];
}

int LCA(int a,int b) {
	if(Depth[a]<Depth[b])swap(a,b);
	for(int i=K-1; i>=0; i--)if(Depth[a]-(1<<i)>=Depth[b])a=p[a][i];
	if(a==b)return a;
	for(int i=K-1; i>=0; i--)if(p[a][i]!=p[b][i])a=p[a][i],b=p[b][i];
	return p[a][0];
}

void Tarjan(int Now,int fa) {
	step++;
	Lowlink[Now]=Dfn[Now]=step;
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(!Dfn[Next]) {
			S.push(St(Now,Next,e.dist));
			Tarjan(Next,Now);
			Lowlink[Now]=min(Lowlink[Now],Lowlink[Next]);
			if(Dfn[Now]<Lowlink[Next])AddEdge2(Now,Next,e.dist),S.pop();
			else if(Dfn[Now]==Lowlink[Next]) { //构成点双连通分量
				BCC++;
				AddEdge2(Now,++New,0);
				Square[New]=1;
				while(!S.empty()) {
					int u=S.top().u,v=S.top().v,dist=S.top().dist;S.pop();
					Length[BCC]+=dist;
					f[u]=f[v]+dist;
					if(u!=Now)Belong[u]=BCC,Circle[New].push_back(u);
					if(u==Now&&v==Next)break;
				}
				for(int Next:Circle[New])AddEdge2(New,Next,min(abs(f[Next]-f[Now]),Length[BCC]-abs(f[Next]-f[Now])));
			}
		} else if(Next!=fa&&Lowlink[Now]>Dfn[Next]) {
			Lowlink[Now]=Dfn[Next];
			S.push(St(Now,Next,e.dist));
		}
	}
}

void Dfs2(int Now,int fa,int depth) {
	father[Now]=fa;
	Depth[Now]=depth;
	for(Edge& e:tree[Now]) {
		int Next=e.to;
		if(Next==fa)continue;
		Dist[Next]=Dist[Now]+e.dist;
		Dfs2(Next,Now,depth+1);
	}
}

int LCA(int a,int b,int& x,int& y) {
	if(Depth[a]<Depth[b])swap(a,b);
	for(int i=K-1; i>=0; i--)if(Depth[a]-(1<<i)>=Depth[b])a=p[a][i];
	x=y=b;
	if(a==b)return a;
	for(int i=K-1; i>=0; i--)if(p[a][i]!=p[b][i])a=p[a][i],b=p[b][i];
	x=a,y=b;
	return p[a][0];
}

int main() {
	n=Get_Int();
	m=Get_Int();
	q=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		AddEdge(x,y,v);
		AddEdge(y,x,v);
	}
	New=n;
	if(m==n-1) {
		Dfs(1,-1,1);
		Sparse_Table();
		for(int i=1; i<=q; i++) {
			int x=Get_Int(),y=Get_Int();
			int lca=LCA(x,y);
			printf("%d\n",Dist[x]+Dist[y]-2*Dist[lca]);
		}
	} else {
		Tarjan(1,0);
		Dfs2(1,-1,1);
		Sparse_Table();
		for(int i=1; i<=q; i++) {
			int x=Get_Int(),y=Get_Int(),_x,_y;
			int lca=LCA(x,y,_x,_y);
			if(!Square[lca])printf("%d\n",Dist[x]+Dist[y]-2*Dist[lca]);
			else {
				int tmp=Dist[x]-Dist[_x]+Dist[y]-Dist[_y];
				tmp+=min(abs(f[_y]-f[_x]),Length[Belong[_x]]-abs(f[_y]-f[_x]));
				printf("%d\n",tmp);
			}
		}
	}
	return 0;
}