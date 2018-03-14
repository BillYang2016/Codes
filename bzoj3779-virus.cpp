#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,K=20;

int First[maxn],Last[maxn],M[maxn];
int n,q,root=1,step=0,Depth[maxn],p[maxn][K];
vector<int> edges[maxn];

struct Segment_Tree {
	struct Tree {
		int left,right;
		LL sum,lazy;
		Tree(int l=0,int r=0):left(l),right(r) {sum=lazy=0;}
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {tree[index].sum=Depth[M[Left]];return;}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void push_up(int index) {
		tree[index].sum=tree[ls].sum+tree[rs].sum;
	}
	void modify(int index,int v) {
		tree[index].sum+=v*(tree[index].right-tree[index].left+1);
		tree[index].lazy+=v;
	}
	void push_down(int index) {
		if(!tree[index].lazy)return;
		modify(ls,tree[index].lazy);
		modify(rs,tree[index].lazy);
		tree[index].lazy=0;
	}
	void modify(int index,int Left,int Right,int v) {
		if(Left>tree[index].right||Right<tree[index].left)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {modify(index,v);return;}
		push_down(index);
		modify(ls,Left,Right,v);
		modify(rs,Left,Right,v);
		push_up(index);
	}
	LL query(int index,int Left,int Right) {
		if(Left>tree[index].right||Right<tree[index].left)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].sum;
		push_down(index);
		return query(ls,Left,Right)+query(rs,Left,Right);
	}
} st;

#undef ls
#undef rs

int From(int x,int y) {for(int i=K-1; i>=0; i--)if(Depth[p[x][i]]>Depth[y])x=p[x][i];return x;}

struct Link_Cut_Tree {
	struct Tree {
		int father,child[2];
		bool rev;
	} tree[maxn];
	stack<int> S;
#define fa(x) tree[x].father
#define ls(x) tree[x].child[0]
#define rs(x) tree[x].child[1]
#define rev(x) tree[x].rev
	bool isroot(int x) {
		return ls(fa(x))!=x&&rs(fa(x))!=x;
	}
	bool checkson(int x) {
		return rs(fa(x))==x;
	}
	void rev_tag(int index) {tree[index].rev^=1;swap(ls(index),rs(index));}
	void push_down(int index) {
		if(!rev(index))return;
		rev_tag(ls(index)),rev_tag(rs(index));
		rev(index)=0;
	}
	void rotate(int x) {
		int father=fa(x),grand=fa(father),side=checkson(x);
		if(!isroot(father))tree[grand].child[checkson(father)]=x;
		tree[father].child[side]=tree[x].child[side^1];
		fa(tree[father].child[side])=father;
		fa(father)=x;
		tree[x].child[side^1]=father;
		fa(x)=grand;
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
	void update(int x,int delta) {
		if(!x)return;
		x=pre(x);
		if(First[x]<=First[root]&&Last[root]<=Last[x]) {
			int y=From(root,x);
			if(First[y]-1>=1)st.modify(1,1,First[y]-1,delta);
			if(Last[y]+1<=n)st.modify(1,Last[y]+1,n,delta);
		} else st.modify(1,First[x],Last[x],delta);
	}
	void access(int index) {
		for(int son=0; index; son=index,index=fa(index)) {
			splay(index);
			if(rs(index))update(rs(index),1);
			if(son)update(son,-1);
			rs(index)=son;
		}
	}
	void reverse(int index) {
		access(index);
		splay(index);
		rev_tag(index);
	}
	int pre(int x) {
		push_down(x);
		while(ls(x))x=ls(x),push_down(x);
		return x;
	}
} lct;

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

void Dfs(int Now,int fa,int depth) {
	First[Now]=++step;
	M[step]=Now;
	Depth[Now]=depth;
	lct.tree[Now].father=fa;
	p[Now][0]=fa;
	for(int i=1; i<K; i++)p[Now][i]=p[p[Now][i-1]][i-1];
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dfs(Next,Now,depth+1);
	}
	Last[Now]=step;
}

double Query(int x) {
	if(x==root)return 1.0*st.query(1,1,n)/n;
	if(First[x]<=First[root]&&Last[root]<=Last[x]) {
		int y=From(root,x);
		LL ans=0,num=0;
		if(First[y]-1>=1)ans+=st.query(1,1,First[y]-1),num+=First[y]-1;
		if(Last[y]+1<=n)ans+=st.query(1,Last[y]+1,n),num+=n-Last[y];
		return 1.0*ans/num;
	}
	return 1.0*st.query(1,First[x],Last[x])/(Last[x]-First[x]+1);
}

int main() {
	n=Get_Int();
	q=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	Dfs(1,0,1);
	st.build(1,1,n);
	while(q--) {
		char opt[10];
		scanf("%s",opt);
		if(opt[2]=='L')lct.access(Get_Int());
		else if(opt[2]=='C') {int x=Get_Int();lct.reverse(x);root=x;}
		else printf("%0.7lf\n",Query(Get_Int()));
	}
	return 0;
}