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

struct Segment_Tree {
	struct Tree {
		int left,right,min;
		Tree(int l,int r):left(l),right(r),min(INT_MAX) {}
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right,int* a) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			tree[index].min=a[Left];
			return;
		}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid,a);
		build(rs,mid+1,Right,a);
		push_up(index);
	}
	void push_up(int index) {
		tree[index].min=min(tre[ls].min,tree[rs].min);
	}
	void modify(int index,int Left,int Right,int val) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&&Right>=tree[index].right) {
			tree[index].min=tree[index].lazy=val;
			return;
		}
		push_down(index);
		modify(ls,Left,Right,val);
		modify(rs,Left,Right,val);
		push_up(index);
	}
	int query(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return INT_MAX;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].min;
		return min(query(ls,Left,Right),query(rs,Left,Right));
	}
} st;

void Modify(int x,int y,int val) {
	int t1=Top[x],t2=Top[y];
	while(t1!=t2) {
		if(Depth[t1]<Depth[t2]) {
			swap(x,y);
			swap(t1,t2);
		}
		st.modify(1,Dfn[t1],Dfn[x],val);
		x=father[t1];
		t1=Top[x];
	}
	if(Depth[x]>Depth[y])swap(x,y);
	st.modify(1,Dfn[x],Dfn[y]);
}

int LCA(int x,int y,int& z) {
	int t1=Top[x],t2=Top[y];
	while(t1!=t2) {
		if(Depth[t1]<Depth[t2]) {
			swap(t1,t2);
			swap(x,y);
		}
		x=father[t1];
		z=t1;
		t1=Top[x];
	}
	if(Depth[x]>Depth[y])swap(x,y);
	if(x!=y)z=Son[x];
	return x;
}

int n,a[maxn],Depth[maxn],Size[maxn],Son[maxn],p[maxn][19],Dfn[maxn],step,root;
vector<int>edges[maxn];

void Dfs1(int Now,int fa,int depth) {
	Depth[Now]=depth;
	Size[Now]=1;
	father[Now]=fa;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dfs1(Next,Now,depth+1);
		Size[Now]+=Size[Next];
		if(Size[Next]>Size[Son[Now]])Son[Now]=Son[Next];
	}
}

void Dfs2(int Now,int top) {
	Top[Now]=top;
	Dfn[Now]=++step;
	if(Son[Now])Dfs2(Son[Now],top);
	for(int Next:edges[Now]) {
		if(Next==father[Now]||Next==Son[Now])continue;
		Dfs2(Next,Next);
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y);
		AddEdge(y,x);
	}
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	root=Get_Int();
	Dfs1(root,0,1);
	Dfs2(root,root);
	for(int i=1; i<=m; i++) {
		int opt=Get_Int();
		if(opt==1)root=Get_Int();
		else if(opt==2) {
			int x=Get_Int(),y=Get_Int();
			Modify(x,y,Get_Int());
		} else {
			int x=Get_Int(),z=0;
			int lca=LCA(x,root,z);
			if(lca!=x)printf("%d\n",st.query(1,Dfn[x],Dfn[x]+Size[x]-1));
			else printf("%d\n",st.query(1,1,n)-st.query(1,Dfn[z],Dfn[z]+Size[z]-1));
		}
	}
	return 0;
} 
