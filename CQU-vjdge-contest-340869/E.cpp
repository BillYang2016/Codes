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

const int maxn=100005;

int n,q,a[maxn];

struct Segment_Tree {
	struct Tree {
		int left,right,sum,lazy;
		Tree() {}
		Tree(int l,int r,int s):left(l),right(r),sum(s),lazy(0) {}
	} tree[maxn<<2];
	#define ls index<<1
	#define rs (index<<1)+1
	void modify(int index,int val) {
		tree[index].sum=val*(tree[index].right-tree[index].left+1);
		tree[index].lazy=val;
	}
	void push_up(int index) {tree[index].sum=tree[ls].sum+tree[rs].sum;}
	void push_down(int index) {
		int &lazy=tree[index].lazy;
		if(!lazy)return;
		modify(ls,lazy);
		modify(rs,lazy);
		lazy=0;
	}
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right,0);
		if(Left==Right) {tree[index].sum=1;return;}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void modify(int index,int Left,int Right,int val) {
		if(Left<=tree[index].left&&Right>=tree[index].right) {modify(index,val);return;}
		push_down(index);
		if(Left<=tree[ls].right)modify(ls,Left,Right,val);
		if(Right>=tree[rs].left)modify(rs,Left,Right,val);
		push_up(index);
	}
} st;

int main() {
	int t=Get_Int();
	for(int k=1; k<=t; k++) {
		n=Get_Int();
		st.build(1,1,n);
		q=Get_Int();
		for(int i=1; i<=q; i++) {
			int x=Get_Int(),y=Get_Int(),v=Get_Int();
			st.modify(1,x,y,v);
		}
		printf("Case %d: The total value of the hook is %d.\n",k,st.tree[1].sum);
	}
	return 0;
}