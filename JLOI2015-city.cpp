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

inline const LL Get_Int() {
	LL num=0,bj=1;
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

const int maxn=200005;

struct Tree {
	int l,r,dist;
	LL val,mul,add;
	Tree(int x=0):l(0),r(0),dist(0),val(x),mul(1),add(0) {}
} tree[maxn];

struct LeftSideTree {
	int n;
#define ls tree[index].l
#define rs tree[index].r
#define a(x) tree[x].val
#define dist(x) tree[x].dist
	int merge(int x,int y) {
		if(!x||!y)return x+y;
		if(a(x)>a(y))swap(x,y);
		tree[x].r=merge(tree[x].r,y);
		if(dist(tree[x].r)>dist(tree[x].l))swap(tree[x].l,tree[x].r);
		if(!rson[x])dist(x)=0;
		else dist(x)=dist(tree[x].r)+1;
		return x;
	}
	void update(int index,LL mul,LL add) {
		if(!index||(mul==1&&add==0))return;
		a(index)=a(index)*mul+add;
		tree[index].add=tree[index].add*mul+add;
		tree[index].mul*=mul;
	}
	void push_down(int index) {
		update(ls,tree[index].mul,tree[index].add);
		update(rs,tree[index].mul,tree[index].add);
		tree[index].mul=1,tree[index].add=0;
	}
	int pop(int index) {
		push_down(index);
		int tmp=merge(lson[index],rson[index]);
		lson[x]=rson[x]=0;
		return tmp;
	}
} heap;

void Dfs(int Now,int depth) {
	Depth[Now]=depth;
	for(int Next:edges[Now]) {
		Dfs(Next,depth+1);
		root[Now]=heap.merge(root[Now],root[Next]);
	}
	while(root[Now]&&tree[root[Now]].val<a[Now]) {
		Depth[Now]++;
		Die[root[Now]]=Now;
		heap.pop(root[Now]);
	}
	if(a[Now])heap.update(root[Now],v[Now],0);
	else heap.update(root[Now],1,v[Now]);
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=1; i<=n; i++) {
		int x=Get_Int();
		AddEdge(x,i);
		a[i]=Get_Int();
		v[i]=Get_Int();
	}
	for(int i=1; i<=m; i++) {
		tree[i]=Tree(Get_Int());
		from[i]=Get_Int();
		root[from[i]]=heap.merge(root[from[i]],i);
	}
	Dfs(1,1);
	for(int i=1; i<=n; i++)printf("%d\n",Depth[i]);
	for(int i=1; i<=m; i++)printf("%d\n",Depth[from[i]]-Depth[Die[i]]);
	return 0;
} 
