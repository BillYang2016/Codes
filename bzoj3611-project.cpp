#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1000005,K=20;

struct Edge {
	int from,to,dist;
	Edge(int x=0,int y=0,int v=0):from(x),to(y),dist(v) {}
};

vector<Edge> T[maxn];
vector<int> edges[maxn];

typedef long long LL;

int root,k,step=0,Depth[maxn],First[maxn],Last[maxn],p[maxn][K],a[maxn];
LL Min[maxn],Max[maxn],Size[maxn],ans1,ans2,ans3;
bool vst[maxn];

void Dfs(int Now,int fa) {
	Depth[Now]=Depth[fa]+1;
	First[Now]=++step;
	p[Now][0]=fa;
	for(int i=1; i<K; i++)p[Now][i]=p[p[Now][i-1]][i-1];
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dfs(Next,Now);
	}
	Last[Now]=step;
}

int LCA(int a,int b) {
	if(Depth[a]<Depth[b])swap(a,b);
	for(int i=K-1; i>=0; i--)if(Depth[a]-(1<<i)>=Depth[b])a=p[a][i];
	if(a==b)return a;
	for(int i=K-1; i>=0; i--)if(p[a][i]!=p[b][i])a=p[a][i],b=p[b][i];
	return p[a][0];
}

void AddEdge(int x,int y) {edges[x].push_back(y);}

void AddTreeEdge(int x,int y,int v) {T[x].push_back(Edge(x,y,v));}

bool cmp(int a,int b) {return First[a]<First[b];}

void build(vector<int> &a) {
	int tmp=a.size();
	sort(a.begin(),a.end(),cmp);
	for(int i=0; i<tmp-1; i++)a.push_back(LCA(a[i],a[i+1]));
	sort(a.begin(),a.end(),cmp);
	auto it=unique(a.begin(),a.end());
	a.erase(it,a.end());
	static int S[maxn];
	int top=0;
	root=S[++top]=a[0];
	for(int i=1; i<a.size(); i++) {
		int now=a[i];
		while(top>=1) {
			if(First[now]>=First[S[top]]&&First[now]<=Last[S[top]]) {
				AddTreeEdge(S[top],now,Depth[now]-Depth[S[top]]);
				break;
			}
			top--;
		}
		if(S[top]!=now)S[++top]=now;
	}
}

void TreeDp(int Now) {
	Size[Now]=vst[Now];
	Min[Now]=vst[Now]?0:LLONG_MAX/3;
	Max[Now]=vst[Now]?0:-LLONG_MAX/3;
	for(Edge &e:T[Now]) {
		int Next=e.to;
		TreeDp(Next);
		Size[Now]+=Size[Next];
		ans1+=Size[Next]*(k-Size[Next])*e.dist;
		ans2=min(ans2,Min[Now]+Min[Next]+e.dist);
		ans3=max(ans3,Max[Now]+Max[Next]+e.dist);
		Min[Now]=min(Min[Now],Min[Next]+e.dist);
		Max[Now]=max(Max[Now],Max[Next]+e.dist);
	}
	T[Now].clear();
}

int n;
vector<int> t;

int main() {
	n=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y);
		AddEdge(y,x);
	}
	Dfs(1,0);
	int T=Get_Int();
	while(T--) {
		k=Get_Int();
		t.clear();
		for(int i=1; i<=k; i++) {
			a[i]=Get_Int();
			t.push_back(a[i]);
			vst[a[i]]=1;
		}
		build(t);
		ans1=0;
		ans2=LLONG_MAX/3;
		ans3=-LLONG_MAX/3;
		TreeDp(root);
		for(int i=1; i<=k; i++)vst[a[i]]=0;
		printf("%lld %lld %lld\n",ans1,ans2,ans3);
	}
	return 0;
}