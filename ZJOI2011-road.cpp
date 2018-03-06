#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=30005;

int n,m,step=0,father[maxn],Depth[maxn],Size[maxn],Son[maxn],Top[maxn],Dfn[maxn],M[maxn];
vector<int> edges[maxn];

void Dfs1(int Now,int fa,int depth) {
	father[Now]=fa;
	Depth[Now]=depth;
	Size[Now]=1;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dfs1(Next,Now,depth+1);
		Size[Now]+=Size[Next];
		if(Size[Next]>Size[Son[Now]])Son[Now]=Next;
	}
}

void Dfs2(int Now,int top) {
	Top[Now]=top;
	Dfn[Now]=++step;
	M[step]=Now;
	if(Son[Now])Dfs2(Son[Now],top);
	for(int Next:edges[Now]) {
		if(Next==father[Now]||Next==Son[Now])continue;
		Dfs2(Next,Next);
	}
}

struct Tree {
	int left,right;
	int dist[2][2],maxx[2][2];
	Tree(int l=0,int r=0):left(l),right(r) {memset(dist,0,sizeof(dist)),memset(maxx,0,sizeof(maxx));}
	void init(int x,int y) {
		if(x==1&&y==1) {
			dist[0][0]=dist[1][1]=1;
			dist[0][1]=dist[1][0]=2;
			maxx[0][0]=maxx[0][1]=maxx[1][0]=maxx[1][1]=2;
		} else if(x==1) {
			dist[0][0]=1;
			dist[0][1]=dist[1][0]=dist[1][1]=INT_MIN/2;
			maxx[0][0]=maxx[1][0]=1;
			maxx[0][1]=maxx[1][1]=INT_MIN/2;
		} else if(y==1) {
			dist[0][0]=dist[0][1]=dist[1][0]=INT_MIN/2;
			dist[1][1]=1;
			maxx[0][0]=maxx[1][0]=INT_MIN/2;
			maxx[0][1]=maxx[1][1]=1;
		} else for(int i=0; i<=1; i++)for(int j=0; j<=1; j++)maxx[i][j]=dist[i][j]=INT_MIN/2;
	}
	friend Tree operator + (const Tree &a,const Tree &b) {
		if(a.empty())return b;
		if(b.empty())return a;
		Tree c;
		c.dist[0][0]=max({INT_MIN/2,a.dist[0][0]+b.dist[0][0],a.dist[0][1]+b.dist[1][0]});
		c.dist[0][1]=max({INT_MIN/2,a.dist[0][1]+b.dist[1][1],a.dist[0][0]+b.dist[0][1]});
		c.dist[1][0]=max({INT_MIN/2,a.dist[1][0]+b.dist[0][0],a.dist[1][1]+b.dist[1][0]});
		c.dist[1][1]=max({INT_MIN/2,a.dist[1][1]+b.dist[1][1],a.dist[1][0]+b.dist[0][1]});
		c.maxx[0][0]=max({a.maxx[0][0],a.dist[0][0]+b.maxx[0][0],a.dist[0][1]+b.maxx[0][1]});
		c.maxx[0][1]=max({a.maxx[0][1],a.dist[1][0]+b.maxx[0][0],a.dist[1][1]+b.maxx[0][1]});
		c.maxx[1][0]=max({b.maxx[1][0],b.dist[0][0]+a.maxx[1][0],b.dist[1][0]+a.maxx[1][1]});
		c.maxx[1][1]=max({b.maxx[1][1],b.dist[0][1]+a.maxx[1][0],b.dist[1][1]+a.maxx[1][1]});
		return c;
	}
	bool empty() const {
		for(int i=0; i<=1; i++)for(int j=0; j<=1; j++)if(dist[i][j]||maxx[i][j])return false;
		return true;
	}
	Tree reverse() {
		Tree a=*this;
		swap(a.maxx[0][0],a.maxx[1][0]);
		swap(a.maxx[0][1],a.maxx[1][1]);
		swap(a.dist[0][1],a.dist[1][0]);
		return a;
	}
};

int a[maxn][2];

struct Segment_Tree {
	Tree tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			tree[index].init(a[M[Left]][0],a[M[Left]][1]);
			return;
		}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void push_up(int index) {
		int l=tree[index].left,r=tree[index].right;
		tree[index]=tree[ls]+tree[rs];
		tree[index].left=l,tree[index].right=r;
	}
	void modify(int index,int target,int x,int y) {
		if(tree[index].left>target||tree[index].right<target)return;
		if(tree[index].left==tree[index].right) {
			tree[index].init(x,y);
			return;
		}
		modify(ls,target,x,y);
		modify(rs,target,x,y);
		push_up(index);
	}
	Tree query(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return Tree();
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index];
		return query(ls,Left,Right)+query(rs,Left,Right);
	}
} st;

int Query(int x,int y) {
	Tree lans,rans;
	bool bj=0;
	for(; Top[x]!=Top[y]; x=father[Top[x]]) {
		if(Depth[Top[x]]<Depth[Top[y]])swap(x,y),swap(lans,rans),bj^=1;
		lans=st.query(1,Dfn[Top[x]],Dfn[x])+lans;
	}
	if(Depth[x]>Depth[y])swap(x,y);
	else swap(lans,rans),bj^=1;
	lans=st.query(1,Dfn[x],Dfn[y])+lans;
	if(bj)swap(lans,rans);
	lans=lans.reverse()+rans;
	return max({0,lans.maxx[0][0],lans.maxx[0][1]});
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	Dfs1(1,0,1);
	Dfs2(1,1);
	for(int i=1; i<=n; i++) {
		char t[5];
		scanf("%s",t);
		if(t[0]=='.')a[i][0]=1;
		if(t[1]=='.')a[i][1]=1;
	}
	st.build(1,1,n);
	while(m--) {
		char opt=' ',t[5];
		while(!isalpha(opt))opt=getchar();
		if(opt=='C') {
			int x=Get_Int(),a=0,b=0;
			scanf("%s",t);
			if(t[0]=='.')a=1;
			if(t[1]=='.')b=1;
			st.modify(1,Dfn[x],a,b);
		} else {
			int x=Get_Int(),y=Get_Int();
			printf("%d\n",Query(x,y));
		}
	}
	return 0;
}