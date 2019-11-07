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

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=200005;

int n,m,a[maxn];

struct Segment_Tree {
	struct Tree {
		int left,right;
		LL sum,lazy;
		Tree() {}
		Tree(int l,int r,LL s):left(l),right(r),sum(s),lazy(0) {}
	} tree[maxn<<2];
	#define ls index<<1
	#define rs (index<<1)+1
	void add(int index,LL val) {
		tree[index].sum+=val*(tree[index].right-tree[index].left+1);
		tree[index].lazy+=val;
	}
	void push_up(int index) {tree[index].sum=tree[ls].sum+tree[rs].sum;}
	void push_down(int index) {
		LL &lazy=tree[index].lazy;
		if(!lazy)return;
		add(ls,lazy);
		add(rs,lazy);
		lazy=0;
	}
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right,0);
		if(Left==Right) {tree[index].sum=a[Left];return;}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void add(int index,int Left,int Right,int val) {
		if(Left<=tree[index].left&&Right>=tree[index].right) {add(index,val);return;}
		push_down(index);
		if(Left<=tree[ls].right)add(ls,Left,Right,val);
		if(Right>=tree[rs].left)add(rs,Left,Right,val);
		push_up(index);
	}
	LL query(int index,int Left,int Right) {
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].sum;
		push_down(index);
		LL sum=0;
		if(Left<=tree[ls].right)sum+=query(ls,Left,Right);
		if(Right>=tree[rs].left)sum+=query(rs,Left,Right);
		return sum;
	}
} st;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	st.build(1,1,n);
	for(int i=1; i<=m; i++) {
		char opt=getchar();
		int x=Get_Int(),y=Get_Int();
		if(opt=='Q')printf("%lld\n",st.query(1,x,y));
		else st.add(1,x,y,Get_Int());
	}
	return 0;
}