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

struct President_Tree {
	struct Tree {
		int ls,rs,size;
	} tree[maxn*50];
	int size;
	int insert(int left,int right,int pre,int val) {
		int now=++size;
		tree[now]=tree[pre];
		tree[now].size++;
		if(left==right)return now;
		int mid=(left+right)>>1;
		if(val<=mid)tree[now].ls=insert(left,mid,tree[pre].ls,val);
		else tree[now].rs=insert(mid+1,right,tree[pre].rs,val);
		return now;
	}
	int query(int left,int right,int lt,int rt,int rank) {
		if(left==right)return left;
		int mid=(left+right)>>1,sum=tree[tree[rt].rs].size-tree[tree[lt].rs].size;
		if(rank<=sum)return query(mid+1,right,tree[lt].rs,tree[rt].rs,rank);
		else return query(left,mid,tree[lt].ls,tree[rt].ls,rank-sum);
	}
} pt;

struct Edge {
	int from,to,dist;
	Edge(int x,int y,int v):from(x),to(y),dist(v) {}
	bool operator < (const Edge& b) const {
		return dist<b.dist;
	}
};

struct tmp {
	int v,id;
	bool operator < (const tmp& b) const {
		return v<b.v;
	}
} b[maxn*2];

vector<Edge> edges;
int n,m,q,cnt,step,lastans,fM[maxn],root[maxn],a[maxn*2],father[maxn*2],p[maxn*2][25],Dfn[maxn*2],First[maxn*2],Last[maxn*2],lson[maxn*2],rson[maxn*2];
bool vst[maxn*2];

int Get_Father(int x) {
	if(father[x]==x)return x;
	return father[x]=Get_Father(father[x]);
}

void Sparse_Table() {
	for(int j=1; j<20; j++)
		for(int i=1; i<=cnt; i++)
			if(~p[i][j-1])p[i][j]=p[p[i][j-1]][j-1];
}

void Dfs(int Now) {
	vst[Now]=1;
	if(Now<=n)Dfn[++step]=Now;
	First[Now]=step;
	if(lson[Now])Dfs(lson[Now]);
	if(rson[Now])Dfs(rson[Now]);
	Last[Now]=step;
}

int main() {
	cnt=n=Get_Int();
	m=Get_Int();
	q=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		edges.push_back(Edge(x,y,v));
	}
	sort(edges.begin(),edges.end());
	for(int i=1; i<=2*n; i++)father[i]=i;
	memset(p,-1,sizeof(p));
	for(auto e:edges) {
		int fx=Get_Father(e.from),fy=Get_Father(e.to);
		if(fx!=fy) {
			p[fx][0]=p[fy][0]=father[fx]=father[fy]=++cnt;
			lson[cnt]=fx,rson[cnt]=fy;
			a[cnt]=e.dist;
		}
	}
	Sparse_Table();
	for(int i=1; i<=n; i++) {
		b[i].v=a[i];
		b[i].id=i;
	}
	sort(b+1,b+n+1);
	for(int i=1; i<=n; i++) { //离散化
		fM[i]=a[b[i].id];
		a[b[i].id]=i;
	}
	for(int i=cnt; i>=1; i--)
		if(!vst[i])Dfs(i);
	for(int i=1; i<=n; i++)root[i]=pt.insert(1,n,root[i-1],a[Dfn[i]]);
	while(q--) {
		if(lastans==-1)lastans=0;
		int x=Get_Int()^lastans,y=Get_Int()^lastans,k=Get_Int()^lastans;
		for(int i=19; i>=0; i--)
			if(~p[x][i]&&a[p[x][i]]<=y)x=p[x][i];
		int l=First[x]+1,r=Last[x];
		if(pt.tree[root[r]].size-pt.tree[root[l-1]].size<k)lastans=-1;
		else lastans=fM[pt.query(1,n,root[l-1],root[r],k)];
		printf("%d\n",lastans);
	}
	return 0;
} 
