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

struct Edge {int from,to,dist;};
int n,k,Size[maxn],core;
bool vst[maxn];
vector<Edge> edges[maxn];

void Get_Root(int Now,int fa,int all) {
	Size[Now]=1;
	bool bj=1;
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(Next==fa||vst[Next])continue;
		Get_Root(Next,Now,all);
		Size[Now]+=Size[Next];
		if(Size[Next]>all/2)bj=0;
	}
	if(Size[Now]<all/2)bj=0;
	if(bj)core=Now;
}

struct node {
	int p,d;
	node(int p=0,int d=0):p(p),d(d) {}
};

vector<node> vec[maxn];

int cnt=0;

void Dfs(int Now,int fa,int dist,int top) {
	vec[Now].push_back(node(top,dist));
	cnt++;
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(Next==fa||vst[Next])continue;
		Dfs(Next,Now,dist+e.dist,top);
	}
}

void build(int Now) {
	vst[Now]=1;
	vec[Now].push_back(node(Now,0));
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(vst[Next])continue;
		cnt=0;
		Dfs(Next,Now,e.dist,Now);
		Size[Next]=cnt;
	}
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(vst[Next])continue;
		Get_Root(Next,0,Size[Next]);
		build(core);
	}
}

int count(vector<int> &a,int b) {return upper_bound(a.begin(),a.end(),b)-a.begin();}

vector<int> val1[maxn],val2[maxn];

int count(int Now,int d) {
	int ans=0,last=0;
	for(auto x:vec[Now]) {
		ans+=count(val1[x.p],d-x.d);
		if(last)ans-=count(val2[last],d-x.d);
		last=x.p;
	}
	return ans;
}

void Solve(int Now) {
	int Left=0,Right=INT_MAX/2;
	while(Left<=Right) {
		int mid=(Left+Right)>>1;
		if(count(Now,mid)>=k)Right=mid-1;
		else Left=mid+1;
	}
	printf("%d\n",Left);
}

void AddEdge(int x,int y,int v) {edges[x].push_back((Edge) {x,y,v});}

int main() {
	n=Get_Int();
	k=Get_Int()+1;
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		AddEdge(x,y,v);
		AddEdge(y,x,v);
	}
	Get_Root(1,0,n);
	build(core);
	for(int i=1; i<=n; i++) {
		reverse(vec[i].begin(),vec[i].end());
		int last=0;
		for(auto &x:vec[i]) {
			val1[x.p].push_back(x.d);
			if(last)val2[last].push_back(x.d);
			last=x.p;
		}
	}
	for(int i=1; i<=n; i++) {
		sort(val1[i].begin(),val1[i].end());
		sort(val2[i].begin(),val2[i].end());
	}
	for(int i=1; i<=n; i++)Solve(i);
	return 0;
}