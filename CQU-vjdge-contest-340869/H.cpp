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

int n,m;

struct Segment_Tree {
	struct Tree {
		int left,right,min,max;
		Tree() {}
		Tree(int l,int r):left(l),right(r),min(n+1),max(0) {}
	} tree[maxn<<2];
	#define ls index<<1
	#define rs (index<<1)+1
	void push_up(int index) {
		tree[index].min=min(tree[ls].min,tree[rs].min);
		tree[index].max=max(tree[ls].max,tree[rs].max);
	}
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right)return;
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
	}
	void modify(int index,int pos,int Max,int Min) {
		if(pos>tree[index].right||pos<tree[index].left)return;
		if(tree[index].left==tree[index].right) {
			tree[index].min=Min;
			tree[index].max=Max;
			return;
		}
		modify(ls,pos,Max,Min);
		modify(rs,pos,Max,Min);
		push_up(index);
	}
	int query_min(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return n+1;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].min;
		return min(query_min(ls,Left,Right),query_min(rs,Left,Right));
	}
	int query_max(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].max;
		return max(query_max(ls,Left,Right),query_max(rs,Left,Right));
	}
} st;

int main() {
	while(scanf("%d%d",&n,&m)!=EOF) {
		stack<int> S;
		st.build(1,1,n);
		getchar();
		for(int i=1; i<=m; i++) {
			char opt=getchar();
			if(opt=='D') {
				int x=Get_Int();
				S.push(x);
				st.modify(1,x,x,x);
			} else if(opt=='Q') {
				int x=Get_Int();
				int Max=st.query_max(1,1,x),Min=st.query_min(1,x,n);
				if(Max==Min)puts("0");
				else printf("%d\n",Min-Max-1);
			} else {
				int x=S.top();
				S.pop();
				st.modify(1,x,0,n+1);
				getchar();
			}
		}
	}
	return 0;
}