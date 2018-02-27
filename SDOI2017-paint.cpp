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
#include<stack>
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

struct Segment_Tree {
	struct Tree {
		int left,right;
		int max,lazy;
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void push_up(int index) {
		tree[index].max=max(tree[ls].max,tree[rs].max);
	}
	void modify(int index,int v) {
		tree[index].max+=v;
		tree[index].lazy+=v;
	}
	void push_down(int index) {
		if(!tree[index].lazy)return;
		modify(ls,tree[index].lazy);
		modify(rs,tree[index].lazy);
		tree[index].lazy=0;
	}
	void modify(int index,int Left,int Right,int v) {
		if(Left>tree[index].right||Right<tree[index].left)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {
			modify(index,v);
			return;
		}
		push_down(index);
		modify(ls,Left,Right,v);
		modify(rs,Left,Right,v);
		push_up(index);
	}
	int query(int index,int Left,int Right) {
		if(Left>tree[index].right||Right<tree[index].left)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].max;
		push_down(index);
		return query(ls,Left,Right)+query(rs,Left,Right);
	}
} st;

#undef ls
#undef rs

int First[maxn],Last[maxn];

struct Link_Cut_Tree {
	struct Tree {
		int father,child[2];
		bool rev;
	} tree[maxn];
#define fa(x) tree[x].father
#define ls(x) tree[x].child[0]
#define rs(x) tree[x].child[1]
#define rev(x) tree[x].rev
	bool isroot(int x) {
		return ls(fa(x))!=x&&rs(fa(x))!=x;
	}
	bool checkson(int x) {
		return rs(fa(x))==x;
	}
	void rotate(int x) {
		int father=fa(x),grand=fa(x),side=checkson(x);
		if(!isroot(father))tree[grand].child[checkson(father)]=x;
		tree[father].child[side]=tree[x].child[side^1];
		fa(tree[father].child[side])=father;
		fa(father)=x;
		tree[x].child[side^1]=father;
		fa(x)=grand;
	}
	void splay(int index) {
		for(int father; !isroot(index); rotate(index)) {
			father=fa(index);
			if(!isroot(father))rotate(checkson(index)==checkson(father)?father:index);
		}
	}
	void access(int index) {
		for(int son=0; index; son=index,index=fa(index)) {
			splay(index);
			if(rs(index)) {
				int l=pre(rs(index));
				st.modify(1,First[l],Last[l],1);
			}
			if(son) {
				int l=pre(son);
				st.modify(1,First[l],Last[l],-1);
			}
			rs(index)=son;
		}
	}
	int pre(int x) {
		while(ls(x))x=ls(x);
		return x;
	}
} lct;

int n,q,step=0,Depth[maxn],p[maxn][25];
vector<int>edges[maxn];

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

void Dfs(int Now,int fa,int depth) {
	First[Now]=++step;
	Depth[Now]=depth;
	if(~fa)lct.tree[Now].father=fa;
	p[Now][0]=fa;
	for(int i=1; i<=20; i++)
		if(~p[Now][i-1])p[Now][i]=p[p[Now][i-1]][i-1];
		else break;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dfs(Next,Now,depth+1);
	}
	Last[Now]=step;
	st.modify(1,First[Now],Last[Now],1);
}

int LCA(int x,int y) {
	if(Depth[x]<Depth[y])swap(x,y);
	int k=20;
	for(int i=k; i>=0; i--)
		if(Depth[x]-(1<<i)>=Depth[y])x=p[x][i];
	if(x==y)return y;
	for(int i=k; i>=0; i--)
		if(~p[x][i]&&p[x][i]!=p[y][i]) {
			x=p[x][i];
			y=p[y][i];
		}
	return p[y][0];
}

int main() {
	memset(p,-1,sizeof(p));
	n=Get_Int();
	q=Get_Int();
	for(int i=1; i<=n; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y);
		AddEdge(y,x);
	}
	Dfs(1,-1,1);
	while(q--) {
		int opt=Get_Int();
		if(opt==1)lct.access(Get_Int());
		else if(opt==2) {
			int x=Get_Int(),y=Get_Int();
			int lca=LCA(x,y);
			printf("%d\n",st.query(1,First[x],First[x])+st.query(1,First[y],First[y])-2*st.query(1,First[lca],First[lca])+1);
		} else {
			int x=Get_Int();
			printf("%d\n",st.query(1,First[x],Last[x]));
		}
	}
	return 0;
} 
