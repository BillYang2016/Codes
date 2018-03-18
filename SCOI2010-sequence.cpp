#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

struct Tag {
	int sum,lmax,rmax,max;
	Tag() {sum=lmax=rmax=max=0;}
	bool operator == (const Tag &b) const {return sum==b.sum&&lmax==b.lmax&&rmax==b.rmax&&max==b.max;}
};

struct Tree {
	int left,right;
	Tag tag[2];
	int lazy;
	bool rev;
	Tree(int l=0,int r=0):left(l),right(r) {lazy=-1;rev=0;}
	Tree operator + (const Tree &b) const {
		if(tag[0]==Tag()&&tag[1]==Tag())return b;
		if(b.tag[0]==Tag()&&b.tag[1]==Tag())return *this;
		int l=left,r=b.right;
		Tree ans=Tree(l,r);
		for(int i=0; i<=1; i++) {
			ans.tag[i].sum=tag[i].sum+b.tag[i].sum;
			ans.tag[i].lmax=tag[i].lmax;
			if(ans.tag[i].lmax==right-left+1)ans.tag[i].lmax+=b.tag[i].lmax;
			ans.tag[i].rmax=b.tag[i].rmax;
			if(ans.tag[i].rmax==b.right-b.left+1)ans.tag[i].rmax+=tag[i].rmax;
			ans.tag[i].max=max({tag[i].max,b.tag[i].max,tag[i].rmax+b.tag[i].lmax});
		}
		return ans;
	}
};

int n,m,a[maxn];

struct Segment_Tree {
	Tree tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
#define tag(x,i) tree[x].tag[i]
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			for(int i=0; i<=1; i++)tag(index,i).sum=tag(index,i).lmax=tag(index,i).rmax=tag(index,i).max=a[Left]==i?1:0;
			return;
		}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void push_up(int index) {tree[index]=tree[ls]+tree[rs];}
	void modify(int index,int val) {
		tree[index].lazy=val;
		for(int i=0; i<=1; i++)tag(index,i).sum=tag(index,i).lmax=tag(index,i).rmax=tag(index,i).max=val==i?(tree[index].right-tree[index].left+1):0;
	}
	void reverse(int index) {
		tree[index].rev^=1;
		swap(tag(index,0),tag(index,1));
		if(~tree[index].lazy) {tree[index].lazy^=1;tree[index].rev=0;}
	}
	void push_down(int index) {
		if(~tree[index].lazy) {
			modify(ls,tree[index].lazy);
			modify(rs,tree[index].lazy);
			tree[index].lazy=-1;
			tree[index].rev=0;
		}
		if(tree[index].rev) {
			reverse(ls);
			reverse(rs);
			tree[index].rev=0;
		}
	}
	void modify(int index,int Left,int Right,int val) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {modify(index,val);return;}
		push_down(index);
		modify(ls,Left,Right,val);
		modify(rs,Left,Right,val);
		push_up(index);
	}
	void reverse(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {reverse(index);return;}
		push_down(index);
		reverse(ls,Left,Right);
		reverse(rs,Left,Right);
		push_up(index);
	}
	int query_sum(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tag(index,1).sum;
		push_down(index);
		return query_sum(ls,Left,Right)+query_sum(rs,Left,Right);
	}
	Tree query_max(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right) {
			return tree[index];
		}
		push_down(index);
		Tree l=query_max(ls,Left,Right),r=query_max(rs,Left,Right);
		return l+r;
	}
} st;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	st.build(1,1,n);
	while(m--) {
		int opt=Get_Int(),x=Get_Int()+1,y=Get_Int()+1;
		if(opt<=1)st.modify(1,x,y,opt);
		else if(opt==2)st.reverse(1,x,y);
		else if(opt==3)printf("%d\n",st.query_sum(1,x,y));
		else printf("%d\n",st.query_max(1,x,y).tag[1].max);
	}
	return 0;
}