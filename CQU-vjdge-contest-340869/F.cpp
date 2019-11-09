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

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=50005;

int n,m,a[maxn];

struct Segment_Tree {
	struct Tree {
		int left,right,max,min;
		Tree() {}
		Tree(int l,int r):left(l),right(r),max(0),min(0) {}
	} tree[maxn<<2];
	#define ls index<<1
	#define rs (index<<1)+1
	void push_up(int index) {
		tree[index].max=max(tree[ls].max,tree[rs].max);
		tree[index].min=min(tree[ls].min,tree[rs].min);
	}
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {tree[index].max=tree[index].min=a[Left];return;}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	int query_max(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].max;
		return max(query_max(ls,Left,Right),query_max(rs,Left,Right));
	}
	int query_min(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return INT_MAX;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].min;
		return min(query_min(ls,Left,Right),query_min(rs,Left,Right));
	}
} st;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	st.build(1,1,n);
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		printf("%d\n",st.query_max(1,x,y)-st.query_min(1,x,y));
	}
	return 0;
}