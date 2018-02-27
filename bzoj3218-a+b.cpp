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

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=100005;

struct Edge {
	int from,to,cap,flow;
	Edge(int x=0,int y=0,int c=0,int f=0):from(x),to(y),cap(c),flow(f) {}
};

struct Dinic {
	int n,m,s,t;
	vector<Edge>edges;
	vector<int>G[maxn];
	bool vst[maxn];
	int dist[maxn],cur[maxn];
	void init(int n) {
		this->n=n;
		edges.clear();
		for(int i=1; i<=n; i++)G[i].clear();
	}
	void AddEdge(int x,int y,int v) {
		edges.push_back(Edge(x,y,v,0));
		edges.push_back(Edge(y,x,0,0));
		m=edges.size();
		G[x].push_back(m-2);
		G[y].push_back(m-1);
	}
	bool bfs() {
		memset(vst,0,sizeof(vst));
		memset(dist,0,sizeof(dist));
		queue<int>Q;
		Q.push(t);
		vst[t]=1;
		while(!Q.empty()) {
			int Now=Q.front();
			Q.pop();
			for(int id:G[Now]) {
				Edge& e=edges[id^1];
				int Next=e.from;
				if(!vst[Next]&&e.cap>e.flow) { 
					vst[Next]=1;
					dist[Next]=dist[Now]+1;
					Q.push(Next);
				}
			}
		}
		return vst[s];
	}
	int dfs(int Now,int a) {
		if(Now==t||a==0)return a;
		int flow=0;
		for(int& i=cur[Now]; i<G[Now].size(); i++) {
			Edge& e=edges[G[Now][i]];
			int Next=e.to;
			if(dist[Now]-1!=dist[Next])continue;
			int nextflow=dfs(Next,min(a,e.cap-e.flow));
			if(nextflow>0) {
				e.flow+=nextflow;
				edges[G[Now][i]^1].flow-=nextflow;
				flow+=nextflow;
				a-=nextflow;
				if(a==0)break;
			}
		}
		return flow;
	}
	int maxflow(int s,int t) {
		this->s=s;
		this->t=t;
		int flow=0;
		while(bfs()) {
			memset(cur,0,sizeof(cur));
			flow+=dfs(s,INT_MAX);
		}
		return flow;
	}
} dinic;

int n,cnt=0,tmp[maxn],a[maxn],l[maxn],r[maxn],root[maxn],ans=0;

struct President_Tree {
	struct Tree {
		int ls,rs,id;
	} tree[maxn*30];
	int size;
	int insert(int pre,int left,int right,int id,int val) {
		int now=++size;
		tree[now]=tree[pre];
		tree[now].id=++cnt;
		if(tree[pre].id)dinic.AddEdge(tree[now].id,tree[pre].id,INT_MAX/2);
		if(left==right) {
			dinic.AddEdge(cnt,id,INT_MAX/2); 
			return now;
		}
		int mid=(left+right)>>1;
		if(val<=mid) {
			tree[now].ls=insert(tree[pre].ls,left,mid,id,val);
			dinic.AddEdge(tree[now].id,tree[tree[now].ls].id,INT_MAX/2);
		} else {
			tree[now].rs=insert(tree[pre].rs,mid+1,right,id,val);
			dinic.AddEdge(tree[now].id,tree[tree[now].rs].id,INT_MAX/2);
		}
		return now;
	}
	void query(int now,int left,int right,int Left,int Right,int p) {
		if(left>Right||right<Left)return;
		if(Left<=left&&Right>=right) {
			dinic.AddEdge(p,tree[now].id,INT_MAX/2);
			return;
		}
		int mid=(left+right)>>1;
		query(tree[now].ls,left,mid,Left,Right,p);
		query(tree[now].rs,mid+1,right,Left,Right,p);
	}
} pt;

int main() {
	n=Get_Int();
	int S=2*n+1,T=2*n+2,tot=0;
	cnt=T;
	for(int i=1; i<=n; i++) {
		tmp[++tot]=a[i]=Get_Int();
		int b=Get_Int(),w=Get_Int();
		ans+=b+w;
		tmp[++tot]=l[i]=Get_Int();
		tmp[++tot]=r[i]=Get_Int();
		int p=Get_Int();
		dinic.AddEdge(S,i,b);
		dinic.AddEdge(i,T,w);
		dinic.AddEdge(i,n+i,p);
	}
	sort(tmp+1,tmp+tot+1);
	tot=unique(tmp+1,tmp+tot+1)-tmp-1;
	for(int i=1; i<=n; i++) {
		a[i]=lower_bound(tmp+1,tmp+tot+1,a[i])-tmp;
		l[i]=lower_bound(tmp+1,tmp+tot+1,l[i])-tmp;
		r[i]=lower_bound(tmp+1,tmp+tot+1,r[i])-tmp;
	}
	for(int i=1; i<=n; i++) {
		if(i>1)pt.query(root[i-1],1,tot,l[i],r[i],n+i);
		root[i]=pt.insert(root[i-1],1,tot,i,a[i]);
		if(root[i-1])dinic.AddEdge(pt.tree[root[i]].id,pt.tree[root[i-1]].id,INT_MAX/2);
	}
	printf("%d\n",ans-dinic.maxflow(S,T));
	return 0;
} 
