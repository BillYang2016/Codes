#include<bits/stdc++.h>

using namespace std;

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
		int left,right,max;
		Tree() {}
		Tree(int l,int r,int m):left(l),right(r),max(m) {}
	} tree[maxn<<2];
	#define ls index<<1
	#define rs (index<<1)+1
	void push_up(int index) {tree[index].max=max(tree[ls].max,tree[rs].max);}
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right,0);
		if(Left==Right) {tree[index].max=a[Left];return;}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void modify(int index,int pos,int val) {
		if(tree[index].left==tree[index].right) {tree[index].max=val;return;}
		if(pos<=tree[ls].right)modify(ls,pos,val);
		else modify(rs,pos,val);
		push_up(index);
	}
	int query(int index,int Left,int Right) {
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].max;
		int Max=0;
		if(Left<=tree[ls].right)Max=max(Max,query(ls,Left,Right));
		if(Right>=tree[rs].left)Max=max(Max,query(rs,Left,Right));
		return Max;
	}
} st;

int main() {
	ios::sync_with_stdio(false);
	while(scanf("%d%d",&n,&m)!=EOF) {
		for(int i=1; i<=n; i++)a[i]=Get_Int();
		st.build(1,1,n);
		for(int i=1; i<=m; i++) {
			char opt=getchar();
			int x=Get_Int(),y=Get_Int();
			if(opt=='Q')printf("%d\n",st.query(1,x,y));
			else st.modify(1,x,y);
		}
	}
	return 0;
}