#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=300005;

multiset<int> S;

void insert(int x) {S.insert(x);}
void erase(int x) {S.erase(S.find(x));} //可重 

struct LeftSideTree {
	struct Tree {
		int ls,rs,fa,dist;
		int val,lazy;
		Tree(int l=0,int r=0,int v=0):ls(l),rs(r),val(v) {fa=dist=val=lazy=0;}
	} tree[maxn];
	void add(int x,int v) {
		tree[x].val+=v;
		tree[x].lazy+=v;
	}
	void push_down(int x) {
		if(!tree[x].lazy)return;
		if(tree[x].ls)add(tree[x].ls,tree[x].lazy);
		if(tree[x].rs)add(tree[x].rs,tree[x].lazy);
		tree[x].lazy=0;
	}
	int st[maxn],cnt;
	void push_all(int x) {
		while(x)st[++cnt]=x,x=tree[x].fa;
		while(cnt)push_down(st[cnt--]);
	}
	int merge(int x,int y) {
		if(!x||!y)return x+y;
		if(tree[x].val<tree[y].val)swap(x,y);
		push_down(x);
		tree[x].rs=merge(tree[x].rs,y);
		tree[tree[x].rs].fa=x;
		if(tree[tree[x].rs].dist>tree[tree[x].ls].dist)swap(tree[x].ls,tree[x].rs);
		tree[x].dist=tree[x].rs?tree[tree[x].rs].dist+1:0;
		return x;
	}
	int get_root(int x) {while(tree[x].fa)x=tree[x].fa;return x;}
	int top(int x) {return tree[get_root(x)].val;}
	int del(int x) {
		int now=merge(tree[x].ls,tree[x].rs),fa=tree[x].fa;
		tree[x].ls=tree[x].rs=tree[x].fa=0;
		if(x==tree[fa].ls)tree[fa].ls=now;
		else tree[fa].rs=now;
		tree[now].fa=fa;
		return get_root(now);
	}
	void modify(int x,int val) {
		push_all(x);
		erase(top(x));
		tree[x].val+=val;
		insert(tree[merge(x,del(x))].val);
	}
	void modify_all(int x,int val) {
		x=get_root(x);
		add(x,val);
		erase(tree[x].val-val);
		insert(tree[x].val);
	}
} heap;

int n,q,lazy=0;

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		int x=Get_Int();
		heap.tree[i].val=x;
		S.insert(x);
	}
	q=Get_Int();
	while(q--) {
		char opt1=' ';
		while(!isalpha(opt1))opt1=getchar();
		if(opt1=='A') {
			int opt2=Get_Int(),x=Get_Int();
			if(opt2==1)heap.modify(x,Get_Int());
			else if(opt2==2)heap.modify_all(x,Get_Int());
			else lazy+=x;
		} else if(opt1=='F') {
			int opt2=Get_Int();
			if(opt2==1) {
				int x=Get_Int();
				heap.push_all(x);
				printf("%d\n",heap.tree[x].val+lazy);
			} else if(opt2==2)printf("%d\n",heap.top(Get_Int())+lazy);
			else printf("%d\n",*--S.end()+lazy);
		} else {
			int x=Get_Int(),y=Get_Int();
			int fx=heap.get_root(x),fy=heap.get_root(y);
			if(fx==fy)continue;
			if(heap.merge(fx,fy)==fx)erase(heap.tree[fy].val);
			else erase(heap.tree[fx].val);
		}
	}
	return 0;
}