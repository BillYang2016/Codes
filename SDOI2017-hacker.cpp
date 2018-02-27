#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>

using namespace std;

typedef long long LL;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=50005,maxm=50005,maxk=20005,K=15,N=2000005;

struct Edge {
	int from,to,dist,pos;
} edges[maxm];

vector<int> In[maxn],Out[maxn],trie[maxn];
int n,m,k,step=0,cnt=0,Depth[maxk],First[maxk],Last[maxk],p[maxk][K];
LL Dist[maxn];

void AddEdge(int x,int y) {
	trie[x].push_back(y);
}

void Dfs(int Now,int fa,int depth) {
	Depth[Now]=depth;
	First[Now]=++step;
	p[Now][0]=fa;
	for(int i=1; i<K; i++)
		if(~p[Now][i-1])p[Now][i]=p[p[Now][i-1]][i-1];
		else break;
	for(int Next:trie[Now]) {
		if(Next==fa)continue;
		Dfs(Next,Now,depth+1);
	}
	Last[Now]=step;
}

int LCA(int a,int b) {
	if(Depth[a]<Depth[b])swap(a,b);
	for(int i=K-1; i>=0; i--)
		if(Depth[a]==Depth[b])break;
		else if(Depth[a]-(1<<i)>=Depth[b])a=p[a][i];
	if(a==b)return a;
	for(int i=K-1; i>=0; i--)
		if(~p[a][i]&&p[a][i]!=p[b][i]) {
			a=p[a][i];
			b=p[b][i];
		}
	return p[a][0];
}

struct Graph {
	vector<Edge> edges[N];
	void AddEdge(int x,int y,int v) {
		edges[x].push_back((Edge) {x,y,v});
	}
	void clear(int n) {
		for(int i=1; i<=n; i++)edges[i].clear();
	}
#define pii pair<LL,int>
#define mp make_pair
	LL dist[N];
	bool vst[N];
	void dijkstra(int n) {
		priority_queue<pii,vector<pii>,greater<pii> > Q;
		for(int i=1; i<=n; i++)dist[i]=LLONG_MAX/2,vst[i]=0;
		for(int x:Out[1]) {
			dist[x]=0;
			Q.push(mp(0,x));
		}
		while(!Q.empty()) {
			int Now=Q.top().second;
			Q.pop();
			if(vst[Now])continue;
			vst[Now]=1;
			for(Edge& e:edges[Now]) {
				int Next=e.to;
				if(dist[Next]>dist[Now]+e.dist) {
					dist[Next]=dist[Now]+e.dist;
					Q.push(mp(dist[Next],Next));
				}
			}
		}
		clear(n);
	}
} newG;

struct Virtual_Tree {
	vector<int> vtree[N];
	int First[N],Last[N],M[N],step,uroot,droot,upos[N],dpos[N];
	void AddEdge(int x,int y) {
		vtree[x].push_back(y);
	}
	void dfs(int Now) {
		First[Now]=++step;
		M[step]=Now;
		for(int Next:vtree[Now])dfs(Next);
		Last[Now]=step;
	}
	void clear(int Now) {
		for(int Next:vtree[Now])clear(Next);
		vtree[Now].clear();
	}
	struct Tree {
		int ls,rs,left,right;
		Tree(int l=0,int r=0):left(l),right(r),ls(0),rs(0) {}
	} tree[N];
	void build(int &index,int Left,int Right,bool down) {
		index=++cnt;
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			if(!down)upos[Left]=index;
			else dpos[Left]=index;
			return;
		}
		int mid=(Left+Right)>>1;
		build(tree[index].ls,Left,mid,down);
		build(tree[index].rs,mid+1,Right,down);
		if(!down) {
			newG.AddEdge(index,tree[index].ls,0);
			newG.AddEdge(index,tree[index].rs,0);
		} else {
			newG.AddEdge(tree[index].ls,index,0);
			newG.AddEdge(tree[index].rs,index,0);
		}
	}
	void link(int index,int Left,int Right,int pos,bool down) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {
			if(!down)newG.AddEdge(pos,index,0);
			else newG.AddEdge(index,pos,0);
			return;
		}
		link(tree[index].ls,Left,Right,pos,down);
		link(tree[index].rs,Left,Right,pos,down);
	}
	void Link(int L1,int R1,int L2,int R2,int v) {
		if(L1>R1||L2>R2)return;
		link(droot,L1,R1,cnt+1,1);
		link(uroot,L2,R2,cnt+2,0);
		newG.AddEdge(cnt+1,cnt+2,v);
		cnt+=2;
	}
	void work(int root,int Now) {
		dfs(root);
		build(uroot,1,step,0),build(droot,1,step,1);
		for(int x:In[Now])newG.AddEdge(m+x,dpos[First[edges[x].pos]],0);
		for(int x:Out[Now])newG.AddEdge(upos[First[edges[x].pos]],x,0);
		for(int i=1; i<=step; i++) {
			int x=M[i];
			Link(First[x],First[x],First[x],Last[x],Depth[x]-1);
			for(int y:vtree[x]) {
				Link(First[y],Last[y],First[x],First[y]-1,Depth[x]-1);
				Link(First[y],Last[y],Last[y]+1,Last[x],Depth[x]-1);
			}
		}
		clear(root);
		step=0;
	}
} vt;

bool cmp(int x,int y) {
	return First[x]<First[y];
}

vector<int> a;
int root;

void Build(int x) {
	a.clear();
	for(int y:In[x])a.push_back(edges[y].pos);
	for(int y:Out[x])a.push_back(edges[y].pos);
	sort(a.begin(),a.end(),cmp);
	int tmp=a.size();
	for(int i=0; i<tmp-1; i++)a.push_back(LCA(a[i],a[i+1]));
	sort(a.begin(),a.end(),cmp);
	auto it=unique(a.begin(),a.end());
	a.erase(it,a.end());
	static int top=0,S[N];
	root=S[++top]=a[0];
	for(int i=1; i<a.size(); i++) {
		int now=a[i];
		while(top>=1) {
			if(First[now]>=First[S[top]]&&First[now]<=Last[S[top]]) {
				vt.AddEdge(S[top],now);
				break;
			}
			top--;
		}
		if(S[top]!=now)S[++top]=now;
	}
	vt.work(root,x);
}

void Clear() {
	for(int i=1; i<=k; i++)trie[i].clear();
	for(int i=1; i<=n; i++)In[i].clear(),Out[i].clear();
	memset(p,-1,sizeof(p));
	step=0;
}

int main() {
	int t=Get_Int();
	while(t--) {
		Clear();
		n=Get_Int();
		m=Get_Int();
		k=Get_Int();
		for(int i=1; i<=m; i++) {
			edges[i].from=Get_Int();
			edges[i].to=Get_Int();
			edges[i].dist=Get_Int();
			edges[i].pos=Get_Int();
			In[edges[i].to].push_back(i);
			Out[edges[i].from].push_back(i);
		}
		for(int i=1; i<k; i++) {
			int x=Get_Int(),y=Get_Int(),v=Get_Int();
			AddEdge(x,y);
		}
		Dfs(1,0,1);
		for(int i=1; i<=m; i++)newG.AddEdge(i,m+i,edges[i].dist);
		cnt=m<<1;
		for(int i=1; i<=n; i++)if(In[i].size()&&Out[i].size())Build(i);
		newG.dijkstra(cnt);
		for(int i=1; i<=n; i++)Dist[i]=LLONG_MAX/2;
		for(int i=1; i<=m; i++)Dist[edges[i].to]=min(Dist[edges[i].to],newG.dist[m+i]);
		for(int i=2; i<=n; i++)printf("%lld\n",Dist[i]);
	}
	return 0;
}