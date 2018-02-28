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

using namespace std;

typedef long long LL;

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

int n,q,step=0,root[maxn],pos[maxn],father[maxn],Depth[maxn],Size[maxn],Son[maxn],Top[maxn],Dfn[maxn];
LL f[maxn],val[maxn];
vector<int> edges[maxn],chain[maxn],tops;

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

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
	if(!Son[Now])f[Now]=val[Now];
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

struct Tag {
	LL a,b;
	Tag(LL a=0,LL b=LLONG_MAX/4):a(a),b(b) {}
	LL val() {return min(a,b);}
	Tag operator + (const Tag & y) const {
		return Tag(y.a+a,min(y.b+a,b)); //!!!
	}
};

struct Segment_Tree {
	struct Tree {
		int left,right;
		int lson,rson;
		Tag tag;
		Tree(int l=0,int r=0):left(l),right(r),lson(0),rson(0),tag(Tag()) {}
	} tree[maxn<<2];
#define ls tree[index].lson
#define rs tree[index].rson
	void build(int &index,int Left,int Right,int top) {
		if(!index)index=++step;
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			tree[index].tag=Tag(f[chain[top][Left-1]],val[chain[top][Left-1]]);
			pos[chain[top][Left-1]]=Left;
			return;
		}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid,top);
		build(rs,mid+1,Right,top);
		push_up(index);
	}
	void push_up(int index) {
		tree[index].tag=tree[ls].tag+tree[rs].tag;
	}
	void modify(int index,int target,Tag v) {
		if(target<tree[index].left||target>tree[index].right)return;
		if(tree[index].left==tree[index].right) {
			tree[index].tag=v;
			return;
		}
		modify(ls,target,v);
		modify(rs,target,v);
		push_up(index);
	}
	Tag query(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return Tag();
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].tag;
		return query(ls,Left,Right)+query(rs,Left,Right);
	}
} st;

bool cmp(int x,int y) {
	return Depth[x]>Depth[y];
}

LL get_f(int x) {
	return st.query(root[Top[x]],pos[x],chain[Top[x]].size()).val();
}

void Modify(int x,int v) {
	vector<LL> last;
	int tmp=x,posl=0;
	for(int t; father[t=Top[x]]; x=father[t])last.push_back(st.tree[root[t]].tag.val());
	x=tmp;
	val[x]+=v;
	if(!Son[x])f[x]+=v;
	for(int t; father[t=Top[x]]; x=father[t]) {
		st.modify(root[t],pos[x],Tag(f[x],val[x]));
		f[father[t]]+=-last[posl++]+st.tree[root[t]].tag.val();
	}
	st.modify(root[Top[x]],pos[x],Tag(f[x],val[x]));
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)val[i]=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y);
		AddEdge(y,x);
	}
	Dfs1(1,0,1);
	Dfs2(1,1);
	sort(tops.begin(),tops.end(),cmp);
	for(int x:tops) {
		st.build(root[x],1,chain[x].size(),x);
		if(father[x])f[father[x]]+=st.tree[root[x]].tag.val();
	}
	q=Get_Int();
	while(q--) {
		char opt=' ';
		while(!isalpha(opt))opt=getchar();
		int x=Get_Int();
		if(opt=='Q')printf("%lld\n",get_f(x));
		else Modify(x,Get_Int());
	}
	return 0;
}