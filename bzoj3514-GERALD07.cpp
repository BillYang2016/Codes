#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=400005;

int n,m,q,type,tot=0,del[maxn];

struct Tree {
	int child[2],fa;
	bool rev;
	int val,minid;
	Tree(int v=0,int id=0):val(v),minid(id) {child[0]=child[1]=fa=rev=0;}
};

struct Link_Cut_Tree {
	Tree tree[maxn];
	int top,S[maxn];
#define fa(x) tree[x].fa
#define ls(x) tree[x].child[0]
#define rs(x) tree[x].child[1]
#define rev(x) tree[x].rev
	bool isroot(int x) {return ls(fa(x))!=x&&rs(fa(x))!=x;}
	bool checkson(int x) {return rs(fa(x))==x;}
	void reverse(int x) {swap(ls(x),rs(x));rev(x)^=1;}
	void push_down(int x) {
		if(!rev(x))return;
		reverse(ls(x)),reverse(rs(x));
		rev(x)=0;
	}
	void push_up(int x) {
		tree[x].minid=x;
		if(tree[tree[ls(x)].minid].val<tree[tree[x].minid].val)tree[x].minid=tree[ls(x)].minid;
		if(tree[tree[rs(x)].minid].val<tree[tree[x].minid].val)tree[x].minid=tree[rs(x)].minid;
	}
	void rotate(int x) {
		int f=fa(x),g=fa(f),side=checkson(x);
		if(!isroot(f))tree[g].child[checkson(f)]=x;
		tree[f].child[side]=tree[x].child[!side],fa(tree[f].child[side])=f;
		fa(f)=x,tree[x].child[!side]=f;
		fa(x)=g;
		push_up(f),push_up(x);
	}
	void splay(int x) {
		S[++top]=x;
		for(int i=x; !isroot(i); i=fa(i))S[++top]=fa(i);
		while(top)push_down(S[top--]);
		for(int f; !isroot(x); rotate(x)) {
			f=fa(x);
			if(!isroot(f))rotate(checkson(x)==checkson(f)?f:x);
		}
	}
	void access(int x) {
		for(int son=0; x; son=x,x=fa(x)) {
			splay(x);
			rs(x)=son;
			push_up(x);
		}
	}
	void make_root(int x) {access(x);splay(x);reverse(x);}
	void split(int x,int y) {make_root(x);access(y);splay(y);}
	void link(int x,int y) {make_root(x);fa(x)=y;} //y->x
	void cut(int x,int y) {split(x,y);ls(y)=fa(x)=0;}
	int get_root(int x) {
		access(x);
		splay(x);
		while(ls(x))x=ls(x);
		return x;
	}
} lct;

struct President_Tree {
	struct Tree {
		int ls,rs,size;
	} tree[maxn*20];
	int size;
#define mid ((left+right)>>1)
	void insert(int &now,int pre,int left,int right,int val) {
		tree[now=++size]=tree[pre];
		tree[now].size++;
		if(left==right)return;
		if(val<=mid)insert(tree[now].ls,tree[pre].ls,left,mid,val);
		else insert(tree[now].rs,tree[pre].rs,mid+1,right,val);
	}
	int query(int left,int right,int lt,int rt,int tar) {
		if(right==tar)return tree[rt].size-tree[lt].size;
		if(tar<=mid)return query(left,mid,tree[lt].ls,tree[rt].ls,tar);
		return tree[tree[rt].ls].size-tree[tree[lt].ls].size+query(mid+1,right,tree[lt].rs,tree[rt].rs,tar);
	}
} pt;

struct Edge {
	int from,to;
	Edge(int x=0,int y=0):from(x),to(y) {}
} edges[maxn];

int root[maxn],ans=0;

int main() {
	n=Get_Int();
	m=Get_Int();
	q=Get_Int();
	type=Get_Int();
	for(int i=0; i<=n; i++)lct.tree[i]=Tree(INT_MAX,i);
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[i]=Edge(x,y);
	}
	tot=n;
	for(int i=1; i<=m; i++) {
		Edge &e=edges[i];
		if(e.from==e.to) {del[i]=i;continue;}
		if(lct.get_root(e.from)==lct.get_root(e.to)) {
			lct.split(e.from,e.to);
			int id=lct.tree[e.to].minid;
			del[i]=lct.tree[id].val;
			lct.cut(edges[del[i]].from,id),lct.cut(id,edges[del[i]].to);
		}
		tot++;
		lct.tree[tot]=Tree(i,tot);
		lct.link(e.from,tot),lct.link(tot,e.to);
	}
	for(int i=1; i<=m; i++)pt.insert(root[i],root[i-1],0,m,del[i]);
	for(int i=1; i<=q; i++) {
		int l=Get_Int()^(type*ans),r=Get_Int()^(type*ans);
		printf("%d\n",ans=n-pt.query(0,m,root[l-1],root[r],l-1));
	}
	return 0;
}