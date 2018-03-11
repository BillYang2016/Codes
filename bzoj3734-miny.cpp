#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,maxp=maxn+(maxn<<2);

struct Point {
	LL x,r;
	int id;
	bool operator < (const Point &b) const {
		return x<b.x;
	}
} p[maxn];

int n,Maxid,Left[maxp],Right[maxp],ans[maxn];
LL tmp[maxn];
vector<int> edges[maxp],edges2[maxp];

struct Segment_Tree {
	struct Tree {
		int left,right,id;
		Tree(int index=0,int l=0,int r=0):left(l),right(r) {
			if(l==r)id=l;
			else id=n+index;
			Left[id]=l;
			Right[id]=r;
		}
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void AddEdge(int x,int y) {
		edges[x].push_back(y);
	}
	void build(int index,int Left,int Right) {
		tree[index]=Tree(index,Left,Right);
		Maxid=max(Maxid,tree[index].id);
		if(Left==Right)return;
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		AddEdge(tree[index].id,tree[ls].id);
		AddEdge(tree[index].id,tree[rs].id);
	}
	void AddEdge(int index,int Left,int Right,int id) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {
			AddEdge(id,tree[index].id);
			return;
		}
		AddEdge(ls,Left,Right,id);
		AddEdge(rs,Left,Right,id);
	}
} st;

int step=0,top=0,BCC=0,Min[maxp],Max[maxp],InDegree[maxp],Belong[maxp],Dfn[maxp],Lowlink[maxp],Stack[maxp];
bool Instack[maxp];

void Tarjan(int Now) {
	Dfn[Now]=Lowlink[Now]=++step;
	Stack[++top]=Now;
	Instack[Now]=1;
	for(int Next:edges[Now]) {
		if(!Dfn[Next]) {
			Tarjan(Next);
			Lowlink[Now]=min(Lowlink[Now],Lowlink[Next]);
		} else if(Instack[Next])Lowlink[Now]=min(Lowlink[Now],Dfn[Next]);
	}
	if(Dfn[Now]==Lowlink[Now]) {
		int y;
		BCC++;
		do {
			y=Stack[top--];
			Instack[y]=0;
			Belong[y]=BCC;
			Min[BCC]=min(Min[BCC],Left[y]);
			Max[BCC]=max(Max[BCC],Right[y]);
		} while(y!=Now);
	}
}

void topsort() {
	queue<int> Q;
	for(int i=1; i<=BCC; i++)if(!InDegree[i])Q.push(i);
	while(!Q.empty()) {
		int Now=Q.front();
		Q.pop();
		for(int Next:edges2[Now]) {
			Min[Next]=min(Min[Next],Min[Now]);
			Max[Next]=max(Max[Next],Max[Now]);
			InDegree[Next]--;
			if(!InDegree[Next])Q.push(Next);
		}
	}
}

void Clear() {
	step=BCC=0;
	for(int i=1; i<=Maxid; i++) {
		Min[i]=INT_MAX/2;
		Max[i]=InDegree[i]=Dfn[i]=0;
		edges[i].clear();
		edges2[i].clear();
	}
	Maxid=0;
}

int main() {
	fill(Min,Min+maxp,INT_MAX/2);
	int t=Get_Int();
	while(t--) {
		Clear();
		n=Get_Int();
		for(int i=1; i<=n; i++) {
			p[i].x=Get_Int();
			p[i].r=Get_Int();
			p[i].id=i;
		}
		sort(p+1,p+n+1);
		st.build(1,1,n);
		for(int i=1; i<=n; i++)tmp[i]=p[i].x;
		for(int i=1; i<=n; i++) {
			int l=lower_bound(tmp+1,tmp+n+1,tmp[i]-p[i].r)-tmp,r=upper_bound(tmp+1,tmp+n+1,tmp[i]+p[i].r)-tmp-1;
			if(l!=r)st.AddEdge(1,l,r,i);
		}
		for(int i=1; i<=Maxid; i++)if(!Dfn[i])Tarjan(i);
		for(int Now=1; Now<=Maxid; Now++)
			for(int Next:edges[Now]) {
				if(Belong[Now]==Belong[Next])continue;
				edges2[Belong[Next]].push_back(Belong[Now]);
				InDegree[Belong[Now]]++;
			}
		topsort();
		for(int i=1; i<=n; i++)ans[p[i].id]=Max[Belong[i]]-Min[Belong[i]]+1;
		for(int i=1; i<=n; i++)printf("%d%c",ans[i],i==n?'\n':' ');
	}
	return 0;
}