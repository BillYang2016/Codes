#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=50005;

int n,a[maxn];

struct Segment_Tree {
	struct Tree {
		int left,right,sum;
		Tree() {}
		Tree(int l,int r,int s):left(l),right(r),sum(s) {}
	} tree[maxn<<2];
	#define ls index<<1
	#define rs (index<<1)+1
	void push_up(int index) {tree[index].sum=tree[ls].sum+tree[rs].sum;}
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right,0);
		if(Left==Right) {tree[index].sum=a[Left];return;}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void add(int index,int pos,int val) {
		if(tree[index].left==tree[index].right) {tree[index].sum+=val;return;}
		if(pos<=tree[ls].right)add(ls,pos,val);
		else add(rs,pos,val);
		push_up(index);
	}
	int query(int index,int Left,int Right) {
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].sum;
		int sum=0;
		if(Left<=tree[ls].right)sum+=query(ls,Left,Right);
		if(Right>=tree[rs].left)sum+=query(rs,Left,Right);
		return sum;
	}
} st;

int main() {
	int t=Get_Int();
	for(int k=1; k<=t; k++) {
		printf("Case %d:\n",k);
		n=Get_Int();
		for(int i=1; i<=n; i++)a[i]=Get_Int();
		st.build(1,1,n);
		char opt=getchar();
		while(opt!='E') {
			int x=Get_Int(),y=Get_Int();
			if(opt=='Q')printf("%d\n",st.query(1,x,y));
			else if(opt=='A')st.add(1,x,y);
			else st.add(1,x,-y);
			opt=getchar();
		}
	}
	return 0;
}