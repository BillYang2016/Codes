#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=200005,K=30;

struct Linear_Bases {
	int b[K+1];
	Linear_Bases() {fill(b,b+K+1,0);}
	void add(int num) {
		for(int j=K; j>=0; j--)if(num>>j&1) {
			if(b[j]) {num^=b[j];continue;}
			b[j]=num;
			break;
		}
	}
};

struct Stack {
	int x,y,fx,fy;
	Stack(int x=0,int y=0,int fx=0,int fy=0):x(x),y(y),fx(fx),fy(fy) {}
} S[maxn];

struct Edge {
	int from,to,dist;
	Edge(int x=0,int y=0,int v=0):from(x),to(y),dist(v) {}
} edges[maxn<<1];

struct Query {int x,y;} Q[maxn];
int top=0,father[maxn],sum[maxn];

int Get_Father(int x) {return father[x]<0?x:Get_Father(father[x]);}
int Get_Dist(int x) {return father[x]<0?sum[x]:sum[x]^Get_Dist(father[x]);}

void Merge(int x,int y,int v,Linear_Bases &lb) {
	int fx=Get_Father(x),fy=Get_Father(y);
	if(fx!=fy) {
		if(father[fx]<father[fy])swap(fx,fy);
		S[++top]=Stack(fx,fy,father[fx],father[fy]);
		father[fy]+=father[fx];
		father[fx]=fy;
		sum[fx]=Get_Dist(x)^Get_Dist(y)^v;
	} else lb.add(Get_Dist(x)^Get_Dist(y)^v);
}

void Return(int tmp) {
	while(top>tmp) {
		father[S[top].x]=S[top].fx;
		father[S[top].y]=S[top].fy;
		sum[S[top].x]=0;
		top--;
	}
}

struct Segment_Tree {
	struct Tree {
		int left,right;
		vector<int> p;
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index].left=Left,tree[index].right=Right;
		if(Left==Right)return;
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
	}
	void insert(int index,int Left,int Right,int id) {
		if(Right<tree[index].left||Left>tree[index].right||Left>Right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {tree[index].p.push_back(id);return;}
		insert(ls,Left,Right,id);
		insert(rs,Left,Right,id);
	}
	void dfs(int index,Linear_Bases lb) {
		int tmp=top;
		for(int id:tree[index].p)Merge(edges[id].from,edges[id].to,edges[id].dist,lb);
		if(tree[index].left==tree[index].right) {
			int x=Q[tree[index].left].x,y=Q[tree[index].left].y,v=Get_Dist(x)^Get_Dist(y);
			for(int i=K; i>=0; i--)if((v^lb.b[i])<v)v^=lb.b[i];
			printf("%d\n",v);
		} else dfs(ls,lb),dfs(rs,lb);
		Return(tmp);
	}
} st;

int n,m,q,cnt=0,tot=0,s[maxn<<1],t[maxn<<1];
map<int,map<int,int> > M;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		edges[++cnt]=Edge(x,y,v);
		s[M[x][y]=M[y][x]=cnt]=1,t[cnt]=-1;
	}
	q=Get_Int();
	while(q--) {
		int opt=Get_Int(),x=Get_Int(),y=Get_Int();
		if(opt==1) {
			int v=Get_Int();
			edges[++cnt]=Edge(x,y,v);
			s[M[x][y]=M[y][x]=cnt]=tot+1,t[cnt]=-1;
		} else if(opt==2) {
			t[M[x][y]]=tot;
			M[x].erase(y),M[y].erase(x);
		} else Q[++tot].x=x,Q[tot].y=y;
	}
	st.build(1,1,tot);
	for(int i=1; i<=cnt; i++)st.insert(1,s[i],~t[i]?t[i]:tot,i);
	for(int i=1; i<=n; i++)father[i]=-1;
	Linear_Bases lb;
	if(tot)st.dfs(1,lb);
	return 0;
}