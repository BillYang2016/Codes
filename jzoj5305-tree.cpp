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

const int maxn=100005,maxp=10000005;

int n,size,core,Size[maxn],cnt;
LL p,a[maxn];
bool vst[maxn];
vector<int> edges[maxn];

void Get_Size(int Now,int fa) {
	Size[Now]=1;
	for(int Next:edges[Now]) {
		if(Next==fa||vst[Next])continue;
		Get_Size(Next,Now);
		Size[Now]+=Size[Next];
	}
}

void Get_Root(int Now,int fa) {
	bool bj=1;
	for(int Next:edges[Now]) {
		if(Next==fa||vst[Next])continue;
		Get_Root(Next,Now);
		if(Size[Next]>size/2)bj=0;
	}
	if(Size[Now]<size/2)bj=0;
	if(bj)core=Now;
}

struct State {
	LL sum,max;
	State(LL s=0,LL m=0):sum(s),max(m) {}
	bool operator < (const State &b) const {return max<b.max;}
} b[maxn];

LL f[maxp],ans=0;
int g[maxp];

void Get_Sum(int Now,int fa) {
	int last=cnt;
	for(int Next:edges[Now]) {
		if(Next==fa||vst[Next])continue;
		b[++cnt]=State((b[last].sum+a[Next])%p,max(b[last].max,a[Next]));
		Get_Sum(Next,Now);
	}
}

void Solve(int Now) {
	Get_Size(Now,Now);
	size=Size[Now];
	Get_Root(Now,Now);
	Now=core;
	cnt=0;
	for(int Next:edges[Now]) {
		if(vst[Next])continue;
		b[++cnt]=State((a[Now]+a[Next])%p,max(a[Now],a[Next]));
		int tmp=cnt;
		Get_Sum(Next,Now);
		sort(b+tmp,b+cnt+1);
		for(int i=tmp; i<=cnt; i++) { //来自同一子树不合法 
			int now=(p-((b[i].sum-b[i].max)%p+p)%p)%p;
			if(g[now]==Next)ans-=f[now];
			now=(b[i].sum-a[Now]%p+p)%p;
			if(g[now]!=Next)g[now]=Next,f[now]=0;
			f[now]++;
		}
	}
	sort(b+1,b+cnt+1);
	g[0]=Now,f[0]=1;
	for(int i=1; i<=cnt; i++) {
		int now=(p-((b[i].sum-b[i].max)%p+p)%p)%p;
		if(g[now]==Now)ans+=f[now];
		now=(b[i].sum-a[Now]%p+p)%p;
		if(g[now]!=Now)g[now]=Now,f[now]=0;
		f[now]++;
	}
	vst[Now]=1;
	for(int Next:edges[Now]) {
		if(vst[Next])continue;
		Solve(Next);
	}
}

int main() {
	n=Get_Int();
	p=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	Solve(1);
	printf("%lld\n",ans+n);
	return 0;
}