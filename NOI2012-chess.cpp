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

struct Segment_Tree_in {
	struct Tree {
		int ls,rs;
		int left,right;
		LL val;
		Tree(int l=0,int r=0,LL x=0):left(l),right(r),val(x),ls(0),rs(0) {}
	} tree[maxn*16];
	int size;
#define ls tree[index].ls
#define rs tree[index].rs
	void build(int Left,int Right,LL* a) {
		int index=++size;
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			tree[index].val=a[Left];
			return;
		}
		ls=build(Left,mid,a);
		rs=build(mid+1,Right,a);
		push_up(now);
	}
	void push_up(int index) {
		tree[index].val=__gcd(tree[ls].val,tree[rs].val);
	}
	void modify(int index,int target,LL val) {
		if(target>tree[index].right||target<tree[index].left)return;
		if(tree[index].left==tree[index].right) {
			tree[index].val+=val;
			return;
		}
		modify(ls,target,val);
		modify(rs,target,val);
		push_up(index);
	}
	LL query(int index,int Left,int Right) {
		if(Left>tree[index].right||Right<tree[index].left)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].val;
		return __gcd(query(ls,Left,Right),query(rs,Left,Right));
	}
	int merge(int x,int y) {
		int index=++size;
		if(x==y) {
			tree[index].val=__gcd(tree[x].val,tree[y].val);
			return;
		}
		ls=merge(tree[x].ls,tree[y].ls);
		rs=merge(tree[x].rs,tree[y].rs);
		push_up(index);
	}
} stin;

struct Segment_Tree_out {
	struct Tree {
		int left,right,root;
		Tree(int l=0,int r=0,int x=0):left(l),right(r),root(x) {}
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			stin.build(tree[index].root,1,n,a[Left]);
			return;
		}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		tree[index].root=stin.merge(tree[ls].root,tree[rs].root);
	}
	void push_up(int index,int target) {
		LL l=stin.query(tree[ls].root,target,target),r=stin.query(tree[rs].root,target,target),last=stin.query(tree[index].root,target,target);
		stin.modify(tree[index].root,target,__gcd(l,r)-last);
	}
	void modify(int index,int xtarget,int ytarget,LL val) {
		if(xtarget>tree[index].right||xtarget<tree[index].left)return 0;
		if(tree[index].left==tree[index].right) {
			stin.modify(tree[index].root,ytarget,val);
			return;
		}
		modify(ls,xtarget,ytarget,val);
		modify(rs,xtarget,ytarget,val);
		push_up(index,ytarget);
	}
	LL query(int index,int xl,int xr,int yl,int yr) {
		if(Left>tree[index].right||Right<tree[index].left)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right)return stin.query(tree[index].root,yl,yr);
		return __gcd(query(ls,xl,xr,yl,yr),query(rs,xl,xr,yl,yr));
	}
} st;

int main() {
	n=Get_Int();
	m=Get_Int();
	x=Get_Int();
	y=Get_Int();
	q=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			a[i][j]=Get_Int();
	for(int i=1; i<=n; i++) { //横向差分
		for(int j=1; j<y; j++)a[i][j]-=a[i][j+1];
		for(int j=m; j>y; j--)a[i][j]-=a[i][j-1];
	}
	for(int j=1; j<=m; j++) { //纵向差分
		for(int i=1; i<x; i++)a[i][j]-=a[i+1][j];
		for(int i=n; i>x; i--)a[i][j]-=a[i-1][j];
	}
	st.build(1,1,m);
	for(int i=1; i<=q; i++) {
		int opt=Get_Int()
		if(opt==0) {
			int x1=x-Get_Int(),y1=y-Get_Int(),x2=x+Get_Int(),y2=y+Get_Int();
			LL ans=st.query(1,x1,x2,y1,y2);
			printf("%lld\n",abs(ans));
		} else {
			int x1=Get_Int(),y1=Get_Int(),x2=Get_Int(),y2=Get_Int();
			if(x1<=x&&y1<=y&&x1-1>=1&&y1-1>=1)
		}
	}
	return 0;
} 
