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
		int left,right;
		double sumx,sumy,sumxx,sumxy;
		bool reset;
		double lazyx,lazyy;
		Tree(int l=0,int r=0,double x=0,double y=0):left(l),right(r),sumx(x),sumy(y),sumxx(x*x),sumxy(x*y) {
			reset=lazyx=lazyy=0;
		}
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
#define len (tree[index].right-tree[index].left+1)
	void build(int index,int Left,int Right,double *x,double *y) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			tree[index]=Tree(Left,Right,x[Left],y[Left]);
			return;
		}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid,x,y);
		build(rs,mid+1,Right,x,y);
		push_up(index);
	}
	void push_up(int index) {
		tree[index].sumx=tree[ls].sumx+tree[rs].sumx;
		tree[index].sumy=tree[ls].sumy+tree[rs].sumy;
		tree[index].sumxx=tree[ls].sumxx+tree[rs].sumxx;
		tree[index].sumxy=tree[ls].sumxy+tree[rs].sumxy;
	}
	void add(int index,double deltax,double deltay) {
		tree[index].sumxx+=tree[index].sumx*deltax*2+deltax*deltax*len;
		tree[index].sumxy+=tree[index].sumx*deltay+tree[index].sumy*deltax+deltax*deltay*len;
		tree[index].sumx+=deltax*len;
		tree[index].sumy+=deltay*len;
		tree[index].lazyx+=deltax;
		tree[index].lazyy+=deltay;
	}
	double sum_pow(int x) {
		return (double)x*(x+1)*(2*x+1)/6;
	}
	void reset(int index) {
		tree[index].sumx=tree[index].sumy=double(tree[index].left+tree[index].right)*len/2;
		tree[index].sumxx=tree[index].sumxy=sum_pow(tree[index].right)-sum_pow(tree[index].left-1);
		tree[index].lazyx=tree[index].lazyy=0;
		tree[index].reset=1;
	}
	void push_down(int index) {
		if(tree[index].left==tree[index].right)return;
		if(tree[index].reset) {
			reset(ls);
			reset(rs);
			tree[index].reset=0;
		}
		if(tree[index].lazyx||tree[index].lazyy) {
			add(ls,tree[index].lazyx,tree[index].lazyy);
			add(rs,tree[index].lazyx,tree[index].lazyy);
			tree[index].lazyx=tree[index].lazyy=0;
		}
	}
	void add(int index,int Left,int Right,double deltax,double deltay) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {
			add(index,deltax,deltay);
			return;
		}
		push_down(index);
		add(ls,Left,Right,deltax,deltay);
		add(rs,Left,Right,deltax,deltay);
		push_up(index);
	}
	void reset(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {
			reset(index);
			return;
		}
		push_down(index);
		reset(ls,Left,Right);
		reset(rs,Left,Right);
		push_up(index);
	}
	double query(int index,int Left,int Right,int opt) {
		if(Right<tree[index].left||Left>tree[index].right)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right) {
			if(opt==1)return tree[index].sumx;
			if(opt==2)return tree[index].sumy;
			if(opt==3)return tree[index].sumxx;
			return tree[index].sumxy;
		}
		push_down(index);
		return query(ls,Left,Right,opt)+query(rs,Left,Right,opt);
	}
} st;

int n,m;
double x[maxn],y[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)scanf("%lf",&x[i]);
	for(int i=1; i<=n; i++)scanf("%lf",&y[i]);
	st.build(1,1,n,x,y);
	while(m--) {
		int opt=Get_Int(),l=Get_Int(),r=Get_Int();
		if(opt==1) {
			double x=st.query(1,l,r,1),y=st.query(1,l,r,2),xx=st.query(1,l,r,3),xy=st.query(1,l,r,4);
			printf("%0.8lf\n",(xy-x*y/(r-l+1))/(xx-x*x/(r-l+1)));
		} else {
			int deltax=Get_Int(),deltay=Get_Int();
			if(opt==3)st.reset(1,l,r);
			st.add(1,l,r,deltax,deltay);
		}
	}
	return 0;
} 
