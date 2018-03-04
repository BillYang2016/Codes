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
#include<stack>

using namespace std;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=200005;

struct Tree {
	int father,child[2];
	bool rev;
	int val,sum;
};

struct Link_Cut_Tree {
	Tree tree[maxn];
	stack<int>S;
	#define fa(x) tree[x].father
	#define ls(x) tree[x].child[0]
	#define rs(x) tree[x].child[1]
	#define rev(x) tree[x].rev
	bool isroot(int index) {
		return ls(fa(index))!=index&&rs(fa(index))!=index;
	}
	bool checkson(int index) {
		return rs(fa(index))==index;
	}
	void push_down(int index) {
		if(!rev(index))return;
		swap(ls(index),rs(index));
		rev(ls(index))^=1;
		rev(rs(index))^=1;
		rev(index)=0;
	}
	void push_up(int index) {
		tree[index].sum=tree[ls(index)].sum+tree[rs(index)].sum+tree[index].val;
	}
	void rotate(int index) {
		int father=fa(index),grand=fa(father),side=checkson(index);
		if(!isroot(father))tree[grand].child[checkson(father)]=index;
		tree[father].child[side]=tree[index].child[side^1];
		fa(tree[father].child[side])=father;
		fa(father)=index;
		tree[index].child[side^1]=father;
		fa(index)=grand;
		push_up(father);
		push_up(index);
	}
	void splay(int index) {
		S.push(index);
		for(int i=index; !isroot(i); i=fa(i))S.push(fa(i));
		while(!S.empty())push_down(S.top()),S.pop();
		for(int father; !isroot(index); rotate(index)) {
			father=fa(index);
			if(!isroot(father))rotate(checkson(index)==checkson(father)?father:index);
		}
	}
	int access(int index) {
		int son=0;
		for(; index; son=index,index=fa(index))splay(index),rs(index)=son,push_up(index);
		return son;
	}
	void reverse(int index) {
		access(index);
		splay(index);
		rev(index)^=1;
	}
	void link(int x,int y) {
		reverse(x);
		fa(x)=y;
	}
	void split(int x,int y) {
		reverse(x);
		access(y);
		splay(y);
	} 
	void cut(int x,int y) { 
		split(x,y);
		ls(y)=fa(x)=0;
	}
	int query(int x,int y) {
		reverse(1);
		int sum=0;
		access(x),splay(x);sum+=tree[x].sum;
		int lca=access(y);splay(y);sum+=tree[y].sum;
		access(lca),splay(lca),sum-=2*tree[lca].sum;
		return sum;
	}
} lct;

int n,m,q=0,cnt=0,size=0,ans[maxn],id[maxn],Left[maxn],Right[maxn];

int newnode(int v) {
	lct.tree[++cnt].val=v;
	return cnt;
}

struct Option {
	int opt,x,from,to,id;
	Option(int o=0,int x=0,int f=0,int t=0,int id=0):opt(o),x(x),from(f),to(t),id(id) {}
};

vector<Option> Opt[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	id[++size]=newnode(1),Left[size]=1,Right[size]=n;
	int last=newnode(0);lct.link(last,id[1]);
	for(int i=1; i<=m; i++) {
		int opt=Get_Int();
		if(opt==0) {
			id[++size]=newnode(1),Left[size]=Get_Int(),Right[size]=Get_Int();
			lct.link(last,id[size]);
		} else if(opt==1) {
			int l=Get_Int(),r=Get_Int(),x=Get_Int();
			l=max(l,Left[x]),r=min(r,Right[x]);
			if(l>r)continue;
			int now=newnode(0);lct.link(now,last);
			Opt[l].push_back(Option(1,now,last,id[x]));
			Opt[r+1].push_back(Option(1,now,id[x],last));
			last=now;
		} else {
			int x=Get_Int(),u=Get_Int(),v=Get_Int();
			Opt[x].push_back(Option(2,x,id[u],id[v],++q));
		}
	}
	for(int i=1; i<=n; i++)
		for(auto now:Opt[i]) {
			if(now.opt==1)lct.cut(now.x,now.from),lct.link(now.x,now.to);
			else ans[now.id]=lct.query(now.from,now.to);
		}
	for(int i=1; i<=q; i++)printf("%d\n",ans[i]);
	return 0;
}