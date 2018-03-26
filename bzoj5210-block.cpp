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

const int maxn=200005;

int n,m,step=0,root[maxn],pos[maxn],father[maxn],Depth[maxn],Size[maxn],Son[maxn],Top[maxn],Dfn[maxn];
LL f[maxn],val[maxn];
vector<int> edges[maxn],chain[maxn],tops;

void Dfs1(int Now,int fa,int depth) {
	father[Now]=fa;
	Depth[Now]=depth;
	Size[Now]=1;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dfs1(Next,Now,depth+1);
		Size[Now]+=Size[Next];
		if(Size[Son[Now]]<Size[Next])Son[Now]=Next;
	}
}

void Dfs2(int Now,int top) {
	Top[Now]=top;
	Dfn[Now]=++step;
	chain[top].push_back(Now);
	if(Now==top)tops.push_back(top);
	if(Son[Now])Dfs2(Son[Now],top);
	for(int Next:edges[Now]) {
		if(Next==father[Now]||Next==Son[Now])continue;
		Dfs2(Next,Next);
	}
}

bool cmp(int x,int y) {return Depth[x]>Depth[y];}

struct Heap {
	priority_queue<LL> add,del;
	void push(LL x) {add.push(x);}
	void erase(LL x) {del.push(x);}
	LL top() {
		while(!del.empty()&&add.top()==del.top())add.pop(),del.pop();
		return !add.empty()?add.top():0;
	}
} g[maxn];

struct Tag {
	LL a,b,c,d;
	Tag(LL a=0,LL b=0,LL c=0,LL d=0):a(a),b(b),c(c),d(d) {}
	LL f() {return max(max(a,c),0ll);}
	LL g() {return max(max(b,d),0ll);}
	Tag operator + (const Tag &y) const {
		Tag ans;
		ans.a=a+y.a;
		ans.b=max(a+y.b,b);
		ans.c=max(max(c+y.a,y.c),0ll);
		ans.d=max(max(max(c+y.b,d),y.d),0ll);
		return ans;
	}
};

struct Segment_Tree {
	struct Tree {
		int left,right;
		int lson,rson;
		Tag tag;
		Tree(int l=0,int r=0):left(l),right(r) {lson=rson=0;}
	} tree[maxn<<2];
#define ls tree[index].lson
#define rs tree[index].rson
	void build(int &index,int Left,int Right,int top) {
		if(!index)index=++step;
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			int x=chain[top][Left-1];
			tree[index].tag=Tag(f[x]+val[x],f[x]+val[x],0,g[x].top());
			pos[x]=Left;
			return;
		}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid,top);
		build(rs,mid+1,Right,top);
		push_up(index);
	}
	void push_up(int index) {tree[index].tag=tree[rs].tag+tree[ls].tag;}
	void modify(int index,int tar,Tag v) {
		if(tar<tree[index].left||tar>tree[index].right)return;
		if(tree[index].left==tree[index].right) {tree[index].tag=v;return;}
		modify(ls,tar,v);
		modify(rs,tar,v);
		push_up(index);
	}
	Tag query(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].tag;
		return query(rs,Left,Right)+query(ls,Left,Right);
	}
} st;

LL get_f(int x) {return st.query(root[Top[x]],pos[x],chain[Top[x]].size()).f();}
LL get_g(int x) {return st.query(root[Top[x]],pos[x],chain[Top[x]].size()).g();}

void Modify(int x,int v) {
	val[x]=v;
	for(int t; father[t=Top[x]]; x=father[t]) {
		Tag last=st.tree[root[t]].tag;
		st.modify(root[t],pos[x],Tag(f[x]+val[x],f[x]+val[x],0,g[x].top()));
		f[father[t]]+=-last.f()+st.tree[root[t]].tag.f();
		g[father[t]].erase(last.g()),g[father[t]].push(st.tree[root[t]].tag.g());
	}
	st.modify(root[Top[x]],pos[x],Tag(f[x]+val[x],f[x]+val[x],0,g[x].top()));
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)val[i]=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	Dfs1(1,0,1);
	Dfs2(1,1);
	sort(tops.begin(),tops.end(),cmp);
	for(int x:tops) {
		st.build(root[x],1,chain[x].size(),x);
		if(father[x]) {
			f[father[x]]+=st.tree[root[x]].tag.f();
			g[father[x]].push(st.tree[root[x]].tag.g());
		}
	}
	while(m--) {
		int opt=' ';
		while(!isalpha(opt))opt=getchar();
		int x=Get_Int();
		if(opt=='M')Modify(x,Get_Int());
		else printf("%lld\n",get_g(x));
	}
	return 0;
}