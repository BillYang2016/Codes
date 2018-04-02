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

struct Edge {
	int from,to;
	Edge(int x,int y):from(x),to(y) {}
};

struct Stack {
	int x,y,fx,fy;
	Stack(int x=0,int y=0,int fx=0,int fy=0):x(x),y(y),fx(fx),fy(fy) {}
} S[maxn];

int n,m,top=0,father[maxn];
bool Dist[maxn],Ans[maxn];

int Get_Father(int x) {return father[x]<0?x:Get_Father(father[x]);}
int Get_Dist(int x) {return father[x]<0?0:Get_Dist(father[x])^Dist[x];}

bool Merge(const Edge &e) {
	int fx=Get_Father(e.from),fy=Get_Father(e.to),dx=Get_Dist(e.from),dy=Get_Dist(e.to);
	if(fx==fy)return dx==dy; //找到奇环
	if(father[fx]>father[fy])swap(fx,fy);
	S[++top]=Stack(fx,fy,father[fx],father[fy]);
	father[fx]+=father[fy];
	father[fy]=fx;
	Dist[fy]=1^dx^dy;
	return 0;
}

void Return(int tmp) {
	while(top>tmp) {
		int x=S[top].x,y=S[top].y;
		father[x]=S[top].fx;
		father[y]=S[top].fy;
		Dist[x]=Dist[y]=0;
		top--;
	}
}

struct Segment_Tree {
	struct Tree {
		int left,right;
		vector<Edge> p;
		Tree(int l=0,int r=0):left(l),right(r) {p=vector<Edge>();}
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right)return;
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
	}
	void insert(int index,int Left,int Right,const Edge &e) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {tree[index].p.push_back(e);return;}
		insert(ls,Left,Right,e);
		insert(rs,Left,Right,e);
	}
	void dfs(int index) {
		int tmp=top;
		bool bj=0;
		for(Edge e:tree[index].p)if(Merge(e)) {bj=1;break;}
		if(bj) {Return(tmp);return;}
		if(tree[index].left!=tree[index].right)dfs(ls),dfs(rs);
		else Ans[tree[index].left]=1;
		Return(tmp);
	}
} st;

int main() {
	n=Get_Int();
	m=Get_Int();
	int T=Get_Int();
	st.build(1,0,T);
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),s=Get_Int(),t=Get_Int()-1;
		st.insert(1,s,t,Edge(x,y));
	}
	for(int i=1; i<=n; i++)father[i]=-1;
	st.dfs(1);
	for(int i=0; i<T; i++)puts(Ans[i]?"Yes":"No");
	return 0;
}