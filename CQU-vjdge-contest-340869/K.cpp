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
		int left,right,sum,lazy;
		Tree(int l=0,int r=0):left(l),right(r),sum(0),lazy(-1) {}
	} tree[maxn<<2];
	#define ls index<<1
	#define rs (index<<1)+1
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right)return;
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
	}
	int opp(int index) {return tree[index].right-tree[index].left+1-tree[index].sum;}
	void modify(int index,int val) {
		tree[index].lazy=val;
		tree[index].sum=(tree[index].right-tree[index].left+1)*val;
	}
	void push_down(int index) {
		int &lazy=tree[index].lazy;
		if(lazy==-1)return;
		modify(ls,lazy);
		modify(rs,lazy);
		lazy=-1;
	}
	void push_up(int index) {tree[index].sum=tree[ls].sum+tree[rs].sum;}
	void modify(int index,int Left,int Right,int val) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {modify(index,val);return;}
		push_down(index);
		modify(ls,Left,Right,val);
		modify(rs,Left,Right,val);
		push_up(index);
	}
	int rank_k(int index,int k) { //第k个没有花的花瓶位置
		if(tree[index].left==tree[index].right)return tree[index].left;
		push_down(index);
		if(k<=opp(ls))return rank_k(ls,k);
		else return rank_k(rs,k-opp(ls));
	}
	int query(int index,int Left,int Right) {
		if(Left>tree[index].right||Right<tree[index].left)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right)return opp(index);
		push_down(index);
		return query(ls,Left,Right)+query(rs,Left,Right);
	}
} st;

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		m=Get_Int();
		st.build(1,1,n);
		for(int i=1; i<=m; i++) {
			int opt=Get_Int(),x=Get_Int()+1,y=Get_Int();
			if(opt==1) {
				int sum=st.query(1,1,x-1);
				int rest=st.opp(1)-sum;
				if(rest==0)puts("Can not put any one.");
				else {
					int Left=st.rank_k(1,sum+1),Right;
					if(rest<=y)Right=st.rank_k(1,st.opp(1));
					else Right=st.rank_k(1,sum+y);
					st.modify(1,Left,Right,1);
					printf("%d %d\n",Left-1,Right-1);
				}
			} else {
				y++;
				printf("%d\n",y-x+1-st.query(1,x,y));
				st.modify(1,x,y,0);
			}
		}
		putchar('\n');
	}
	return 0;
}