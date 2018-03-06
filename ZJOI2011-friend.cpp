#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

LL Cal(LL x) {return x*(x+1)/2;}

struct Treap {
	struct Tree {
		int child[2],size;
		LL val,sum,lazy;
	} tree[maxn];
#define ls tree[index].child[0]
#define rs tree[index].child[1]
	void build(int &index,int Left,int Right) {
		if(Left>Right)return;
		int mid=(Left+Right)>>1;
		index=mid;
		build(ls,Left,mid-1);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void push_up(int index) {
		tree[index].size=1;
		tree[index].sum=0;
		if(ls) {
			tree[index].size+=tree[ls].size;
			tree[index].sum+=tree[ls].sum+Cal(tree[ls].size)*(tree[ls].val-tree[index].val);
		}
		if(rs) {
			tree[index].size+=tree[rs].size;
			tree[index].sum+=tree[rs].sum+Cal(tree[rs].size)*(tree[rs].val-tree[index].val);
		}
	}
	void modify(int index,int val) {
		tree[index].val+=val;
		tree[index].lazy+=val;
	}
	void push_down(int index) {
		if(!tree[index].lazy)return;
		if(ls)modify(ls,tree[index].lazy);
		if(rs)modify(rs,tree[index].lazy);
		tree[index].lazy=0;
		push_up(index);
	}
	void rotate(int &index,int side) {
		int son=tree[index].child[side];
		tree[index].child[side]=tree[son].child[side^1];
		tree[son].child[side^1]=index;
		push_up(index);
		push_up(son);
		index=son;
	}
	void reset(int &index,int tar) {
		push_down(index);
		if(tar==tree[ls].size+1) {
			tree[index].val=0;
			push_up(index);
			return;
		}
		if(tar<tree[ls].size+1)reset(ls,tar),rotate(index,0);
		else reset(rs,tar-tree[ls].size-1),rotate(index,1);
	}
} treap;

int n,m,p,root;
LL ans=0;
vector<int> edges[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	p=Get_Int();
	for(int i=1; i<=p; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[x].push_back(y);
	}
	ans=Cal(n)*Cal(m);
	treap.build(root,1,m);
	for(int i=1; i<=n; i++) {
		treap.modify(root,1);
		for(int j:edges[i])treap.reset(root,j);
		ans-=treap.tree[root].sum+Cal(treap.tree[root].size)*treap.tree[root].val;
	}
	printf("%lld\n",ans);
	return 0;
}