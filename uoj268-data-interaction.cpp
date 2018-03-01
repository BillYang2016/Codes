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
#define pii pair<LL,LL>
#define mp make_pair

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

const int maxn=100005;

struct Heap {
	priority_queue<LL> add,del;
	void insert(LL x) {add.push(x);}
	void erase(LL x) {del.push(x);}
	LL top() {
		while(!del.empty()&&add.top()==del.top())add.pop(),del.pop();
		return !add.empty()?add.top():0;
	}
	pii get() {
		LL fir=top(),sec=0;
		if(fir==0)return mp(0,0);
		erase(fir);
		sec=top();
		insert(fir);
		return mp(fir,sec);
	}
} f[maxn],ans;

int n,m,step=0,father[maxn],Depth[maxn],Size[maxn],Son[maxn],Top[maxn],Dfn[maxn],M[maxn];
LL a[maxn];
vector<int> edges[maxn];

struct Segment_Tree {
	struct Tree {
		int left,right;
		int lson,rson;
		LL lazy,lmax,rmax,sum,ans;
		Tree(int l=0,int r=0):left(l),right(r) {lson=rson=lazy=lmax=rmax=sum=ans=0;}
	} tree[maxn<<2];
	int size;
#define ls tree[index].lson
#define rs tree[index].rson
	void build(int &index,int Left,int Right) {
		if(!index)index=++size;
		tree[index]=Tree(Left,Right);
		//cout<<index<<"..."<<Left<<" "<<Right<<endl;
		if(Left==Right)return;
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
	}
	void push_up(int index) {
		tree[index].sum=tree[ls].sum+tree[rs].sum;
		tree[index].lmax=max(tree[ls].lmax+tree[rs].sum,tree[rs].lmax);
		tree[index].rmax=max(tree[ls].rmax,tree[ls].sum+tree[rs].rmax);
		tree[index].ans=max(max(tree[ls].ans,tree[rs].ans),tree[ls].lmax+tree[rs].rmax);
	}
	void modify_b(int index,int val) {
		tree[index].lazy+=val;
		tree[index].lmax+=val;
		tree[index].ans+=val;
	}
	void push_down(int index) {
		if(!tree[index].lazy)return;
		modify_b(ls,tree[index].lazy);
		modify_b(rs,tree[index].lazy);
		tree[index].lazy=0;
	}
	void modify_b(int index,int Left,int Right,int val) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {
			modify_b(index,val);
			return;
		}
		push_down(index);
		modify_b(ls,Left,Right,val);
		modify_b(rs,Left,Right,val);
		push_up(index);
	}
	void modify_a(int index,int pos,pii val) {
		if(pos<tree[index].left||pos>tree[index].right)return;
		if(tree[index].left==tree[index].right) {
			tree[index].sum=a[M[pos]];
			tree[index].lmax=tree[index].sum+tree[index].lazy+val.first;
			tree[index].rmax=tree[index].sum+val.first;
			tree[index].ans=tree[index].sum+tree[index].lazy+val.first+val.second;
			return;
		}
		push_down(index);
		modify_a(ls,pos,val);
		modify_a(rs,pos,val);
		push_up(index);
	}
} st;

int root[maxn];
LL last[maxn];

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
	M[step]=Now;
	if(Son[Now])Dfs2(Son[Now],top);
	else st.build(root[top],Dfn[top],Dfn[Now]),ans.insert(0);
	for(int Next:edges[Now]) {
		if(Next==Son[Now]||Next==father[Now])continue;
		Dfs2(Next,Next);
		f[Now].insert(0);
	}
}

struct Query {
	int x,y,v;
} q[maxn];

void update_ans(int x) {
	if(last[x]==st.tree[root[x]].ans)return;
	ans.erase(last[x]);
	ans.insert(last[x]=st.tree[root[x]].ans);
}

void Modify(Query q,int bj) {
	int x=q.x,y=q.y,v=q.v*bj;
	for(int t; (t=Top[x])!=Top[y]; x=father[t]) {
		if(Depth[Top[x]]<Depth[Top[y]])swap(x,y),t=Top[x];
		st.modify_b(root[t],Dfn[t],Dfn[x],v);
		update_ans(t);
	}
	if(Dfn[x]>Dfn[y])swap(x,y);
	st.modify_b(root[Top[x]],Dfn[x]+1,Dfn[y],v);
	update_ans(Top[x]);
	a[x]+=v;
	for(int t; father[t=Top[x]]; x=father[t]) {
		LL last=st.tree[root[t]].rmax;
		st.modify_a(root[t],Dfn[x],f[x].get());
		update_ans(t);
		LL now=st.tree[root[t]].rmax;
		if(now!=last)f[father[t]].erase(last),f[father[t]].insert(now);
	}
	st.modify_a(root[Top[x]],Dfn[x],f[x].get());
	update_ans(Top[x]);
}

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y);
		AddEdge(y,x);
	}
	Dfs1(1,0,1);
	Dfs2(1,1);
	for(int i=1; i<=m; i++) {
		char opt=' ';
		while(opt!='+'&&opt!='-')opt=getchar();
		if(opt=='+') {
			q[i].x=Get_Int();
			q[i].y=Get_Int();
			q[i].v=Get_Int();
			Modify(q[i],1);
		} else Modify(q[Get_Int()],-1);
		printf("%lld\n",ans.top());
	}
	return 0;
}