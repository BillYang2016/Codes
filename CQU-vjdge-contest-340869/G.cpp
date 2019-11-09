#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn=100005;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int n,m;
LL a[maxn];

struct Segment_Tree {
	struct Tree {
		int left,right;
		LL sum;
		Tree() {}
		Tree(int l,int r):left(l),right(r),sum(0) {}
	} tree[maxn<<2];
	#define ls index<<1
	#define rs (index<<1)+1
	void push_up(int index) {tree[index].sum=tree[ls].sum+tree[rs].sum;}
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {tree[index].sum=a[Left];return;}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void sqrt(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(tree[index].sum<=tree[index].right-tree[index].left+1)return;
		if(tree[index].left==tree[index].right) {tree[index].sum=LL(std::sqrt(tree[index].sum));return;}
		sqrt(ls,Left,Right);
		sqrt(rs,Left,Right);
		push_up(index);
	}
	LL query(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].sum;
		return query(ls,Left,Right)+query(rs,Left,Right);
	}
} st;

int main() {
	int t=0;
	while(scanf("%d",&n)!=EOF) {
		printf("Case #%d:\n",++t);
		for(int i=1; i<=n; i++)a[i]=Get_Int();
		st.build(1,1,n);
		m=Get_Int();
		for(int i=1; i<=m; i++) {
			int opt=Get_Int(),x=Get_Int(),y=Get_Int();
			if(x>y)swap(x,y);
			if(!opt)st.sqrt(1,x,y);
			else printf("%lld\n",st.query(1,x,y));
		}
		putchar('\n');
	}
	return 0;
}