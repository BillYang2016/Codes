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

const int maxn=70005,maxb=250;

struct Edge {
	int from,to,dist;
	Edge(int x=0,int y=0,int v=0):from(x),to(y),dist(v) {}
} edge[maxn];

int n,m,step=0,Size[maxn],father[maxn],Depth[maxn],Son[maxn],First[maxn],Last[maxn],Top[maxn],Belong[maxn],Left[maxb],Right[maxb];
LL dist[maxn],ans=0;
vector<Edge> edges[maxn];

void Dfs1(int Now,int fa,int depth) {
	Size[Now]=1;
	father[Now]=fa;
	Depth[Now]=depth;
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(Next==fa)continue;
		dist[Next]=e.dist;
		Dfs1(Next,Now,depth+1);
		Size[Now]+=Size[Next];
		if(Size[Next]>Size[Son[Now]])Son[Now]=Next;
	}
}

void Dfs2(int Now,int top) {
	First[Now]=++step;
	Top[Now]=top;
	if(Son[Now])Dfs2(Son[Now],top);
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(Next==father[Now]||Next==Son[Now])continue;
		Dfs2(Next,Next);
	}
	Last[Now]=step+1;
}

int LCA(int x,int y) {
	for(; Top[x]!=Top[y]; x=father[Top[x]])if(Depth[Top[x]]<Depth[Top[y]])swap(x,y);
	return Depth[x]<Depth[y]?x:y;
}

struct BIT {
	LL c[maxn];
#define lowbit(x) (x&(-x))
	void add(int x,LL v) {for(int i=x; i<=n; i+=lowbit(i))c[i]+=v;}
	LL query(int x) {
		LL ans=0;
		for(int i=x; i>=1; i-=lowbit(i))ans+=c[i];
		return ans;
	}
} all;

struct Block {
	int left,right;
	BIT in;
	LL sum;
	int Size[maxn];
	void Dfs(int Now) {
		Size[Now]=(left<=Now&&right>=Now);
		for(Edge &e:edges[Now]) {
			int Next=e.to;
			if(Next==father[Now])continue;
			Dfs(Next);
			sum+=1ll*e.dist*Size[Next];
			Size[Now]+=Size[Next];
		}
		in.add(First[Now],dist[Now]*Size[Now]);
		in.add(Last[Now],-dist[Now]*Size[Now]);
	}
	void modify(int Now,LL val) {
		sum+=Size[Now]*(val-dist[Now]);
		in.add(First[Now],(val-dist[Now])*Size[Now]);
		in.add(Last[Now],(dist[Now]-val)*Size[Now]);
	}
	LL query(int Now) {return sum+(right-left+1)*all.query(First[Now])-2*in.query(First[Now]);}
} B[maxb];

LL Dist(int x,int y) {return all.query(First[x])+all.query(First[y])-2*all.query(First[LCA(x,y)]);}

LL Query(int l,int r,int x) {
	int L=Belong[l],R=Belong[r];
	LL ans=0;
	if(R-L<=1) {
		for(int i=l; i<=r; i++)ans+=Dist(i,x);
		return ans;
	}
	for(int i=l; i<=Right[L]; i++)ans+=Dist(i,x);
	for(int i=Left[R]; i<=r; i++)ans+=Dist(i,x);
	return ans+B[R-1].query(x)-B[L].query(x);
}

int main() {
	n=Get_Int();
	m=Get_Int();
	int type=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		edge[i]=Edge(x,y,v);
		edges[x].push_back(Edge(x,y,v));
		edges[y].push_back(Edge(y,x,v));
	}
	Dfs1(1,0,1);
	Dfs2(1,1);
	for(int i=1; i<n; i++)if(Depth[edge[i].from]<Depth[edge[i].to])swap(edge[i].from,edge[i].to);
	for(int i=1; i<=n; i++)all.add(First[i],dist[i]),all.add(Last[i],-dist[i]);
	int size=300,BCC=0;
	for(int i=1; i<=n; i++) {
		Belong[i]=(i-1)/size+1;
		if(!B[Belong[i]].left)B[Belong[i]].left=1,Left[Belong[i]]=i,BCC++;
		B[Belong[i]].right=Right[Belong[i]]=i;
	}
	for(int i=1; i<=BCC; i++)B[i].Dfs(1);
	while(m--) {
		char opt=' ';
		while(!isalpha(opt))opt=getchar();
		if(opt=='m') {
			int x=Get_Int()^(type*ans),y=Get_Int()^(type*ans);
			x=edge[x].from;
			for(int i=1; i<=BCC; i++)B[i].modify(x,y);
			all.add(First[x],y-dist[x]);
			all.add(Last[x],dist[x]-y);
			dist[x]=y;
		} else {
			int x=Get_Int()^(type*ans),y=Get_Int()^(type*ans),z=Get_Int()^(type*ans);
			printf("%lld\n",ans=Query(x,y,z));
			ans%=n;
		}
	}
	return 0;
}