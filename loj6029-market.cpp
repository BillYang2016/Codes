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

int div_down(int x,int y) {
	if(x<0)return (x+1)/y-1;
	return x/y;
}

struct Segment_Tree {
	struct Tree {
		int left,right;
		int max,min,lazy;
		LL sum;
		Tree(int l=0,int r=0,int v=0):left(l),right(r),max(v),min(v),lazy(0),sum(v) {}
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right,int* a) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			tree[index]=Tree(Left,Right,a[Left]);
			return;
		}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid,a);
		build(rs,mid+1,Right,a);
		push_up(index);
	}
	void push_up(int index) {
		tree[index].max=max(tree[ls].max,tree[rs].max);
		tree[index].min=min(tree[ls].min,tree[rs].min);
		tree[index].sum=tree[ls].sum+tree[rs].sum;
	}
	void push_down(int index) {
		if(!tree[index].lazy)return;
		modify(ls,tree[index].lazy);
		modify(rs,tree[index].lazy);
		tree[index].lazy=0;
	}
	void modify(int index,LL val) {
		tree[index].sum+=val*(tree[index].right-tree[index].left+1);
		tree[index].lazy+=val;
		tree[index].max+=val;
		tree[index].min+=val;
	}
	void add(int index,int Left,int Right,int val) {
		if(Left>tree[index].right||Right<tree[index].left)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {
			modify(index,val);
			return;
		}
		push_down(index);
		add(ls,Left,Right,val);
		add(rs,Left,Right,val);
		push_up(index);
	}
	void div(int index,int Left,int Right,int val) {
		if(Left>tree[index].right||Right<tree[index].left)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {
			int delta1=tree[index].max-div_down(tree[index].max,val),delta2=tree[index].min-div_down(tree[index].min,val);
			if(delta1==delta2) {
				modify(index,-delta1);
				return;
			}
		}
		push_down(index);
		div(ls,Left,Right,val);
		div(rs,Left,Right,val);
		push_up(index);
	}
	int query_min(int index,int Left,int Right) {
		if(Left>tree[index].right||Right<tree[index].left)return INT_MAX;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].min;
		push_down(index);
		return min(query_min(ls,Left,Right),query_min(rs,Left,Right));
	}
	LL query_sum(int index,int Left,int Right) {
		if(Left>tree[index].right||Right<tree[index].left)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].sum;
		push_down(index);
		return query_sum(ls,Left,Right)+query_sum(rs,Left,Right);
	}
} st;

int n,m,a[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	st.build(1,1,n,a);
	while(m--) {
		int opt=Get_Int(),l=Get_Int()+1,r=Get_Int()+1;
		if(opt==1)st.add(1,l,r,Get_Int());
		else if(opt==2)st.div(1,l,r,Get_Int());
		else if(opt==3)printf("%d\n",st.query_min(1,l,r));
		else printf("%lld\n",st.query_sum(1,l,r));
	}
	return 0;
} 
