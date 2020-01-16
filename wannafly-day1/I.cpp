#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=80005,maxc=maxn*20*20;

vector<int> roots;
int n,m,top=0,S[maxc];

namespace Value_Tree {
	struct Tree {
		int ls,rs,size;
		void clear() {ls=rs=size=0;}
		Tree() {clear();}
	} tree[maxc];
	int size=0;
	int newnode() {return !top?++size:S[top--];}
	void remove(int index) {S[++top]=index;tree[index].clear();}
	int insert(int index,int left,int right,int val,int delta) {
		if(!index)index=newnode();
		tree[index].size+=delta;
		if(left==right)return index;
		int mid=(left+right)>>1;
		if(val<=mid)tree[index].ls=insert(tree[index].ls,left,mid,val,delta);
		else tree[index].rs=insert(tree[index].rs,mid+1,right,val,delta);
		return index;
	}
	int insert(int root,int val,int delta=1) {return insert(root,1,n,val,delta);}
	int merge(int l,int r) { //将左右合并并可持久化
		if(l==0&&r==0)return l;
		int index=newnode();
		tree[index].size=tree[l].size+tree[r].size;
		tree[index].ls=merge(tree[l].ls,tree[r].ls);
		tree[index].rs=merge(tree[l].rs,tree[r].rs);
		return index;
	}
	int merge2(int l,int r,int del=0) { //将右边并入左边并删除右边
		if(r==0)return l;
		if(l==0)l=newnode();
		tree[l].size+=tree[r].size;
		tree[l].ls=merge2(tree[l].ls,tree[r].ls,del);
		tree[l].rs=merge2(tree[l].rs,tree[r].rs,del);
		if(del)remove(r);
		if(!del&&tree[l].size==0) {remove(l);return 0;} //虚空子树不能删0结点，因为有负的贡献
		return l;
	}
	void recycle(int index) {
		if(!index)return;
		remove(index);
		recycle(tree[index].ls);
		recycle(tree[index].rs);
	}
	int query(int left,int right,int val) {
		if(left==right)return left;
		int mid=(left+right)>>1;
		int lsize=0;
		for(int rt:roots)lsize+=tree[tree[rt].ls].size;
		if(lsize>=val) {
			for(int &rt:roots)rt=tree[rt].ls;
			return query(left,mid,val);
		} else {
			for(int &rt:roots)rt=tree[rt].rs;
			return query(mid+1,right,val-lsize);
		}
	}
}

int a[maxn];

namespace Segment_Tree {
	struct Tree {
		int left,right,max,cnt,sec,lazy,root;
		Tree(int l=0,int r=0):left(l),right(r),max(0),cnt(0),sec(0),lazy(INT_MAX),root(0) {}
	} tree[maxn<<2];
	#define ls index<<1
	#define rs (index<<1)|1
	void push_up(int index) {
		if(tree[ls].max>tree[rs].max) {
			tree[index].max=tree[ls].max;
			tree[index].sec=max(tree[rs].max,tree[ls].sec);
			tree[index].cnt=tree[ls].cnt;
		} else if(tree[ls].max<tree[rs].max) {
			tree[index].max=tree[rs].max;
			tree[index].sec=max(tree[ls].max,tree[rs].sec);
			tree[index].cnt=tree[rs].cnt;
		} else {
			tree[index].max=tree[ls].max;
			tree[index].sec=max(tree[ls].sec,tree[rs].sec);
			tree[index].cnt=tree[ls].cnt+tree[rs].cnt;
		}
	}
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			tree[index].max=a[Left];
			tree[index].cnt=1;
			tree[index].root=Value_Tree::insert(tree[index].root,a[Left]);
			return;
		}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		tree[index].root=Value_Tree::merge(tree[ls].root,tree[rs].root);
		push_up(index);
	}
	void modify(int index,int val) {
		if(tree[index].max<=val)return;
		tree[index].root=Value_Tree::insert(tree[index].root,tree[index].max,-tree[index].cnt);
		tree[index].root=Value_Tree::insert(tree[index].root,val,tree[index].cnt);
		tree[index].max=val;
		tree[index].lazy=val;
	}
	void push_down(int index) {
		if(tree[index].lazy==INT_MAX)return;
		modify(ls,tree[index].lazy);
		modify(rs,tree[index].lazy);
		tree[index].lazy=INT_MAX;
	}
	int modify(int index,int Left,int Right,int val) {
		if(Left>tree[index].right||Right<tree[index].left||tree[index].max<val)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right&&tree[index].sec<val) {
			int root=Value_Tree::insert(0,tree[index].max,-tree[index].cnt); //建立虚空树以便更新祖先信息
			root=Value_Tree::insert(root,val,tree[index].cnt);
			modify(index,val);
			return root;
		}
		push_down(index);
		int root=Value_Tree::merge2(modify(ls,Left,Right,val),modify(rs,Left,Right,val),1);
		tree[index].root=Value_Tree::merge2(tree[index].root,root);
		push_up(index);
		return root;
	}
	void query(int index,int Left,int Right) {
		if(Left>tree[index].right||Right<tree[index].left)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {
			roots.push_back(tree[index].root);
			return;
		}
		push_down(index);
		query(ls,Left,Right);
		query(rs,Left,Right);
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	Segment_Tree::build(1,1,n);
	for(int i=1; i<=m; i++) {
		int opt=Get_Int(),l=Get_Int(),r=Get_Int(),v=Get_Int();
		if(opt==1)Value_Tree::recycle(Segment_Tree::modify(1,l,r,v));
		else {
			roots.clear();
			Segment_Tree::query(1,l,r);
			printf("%d\n",Value_Tree::query(1,n,v));
		}
	}
	return 0;
}