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

const int maxn=1005,maxm=4005,mod=998244353;

int n,m,Core,Min,Size[maxn],Maxson[maxn],a[maxn];
LL f[maxn][maxm],ans[maxm];
bool vst[maxn];
vector<int> edges[maxn],d[maxm];

void Get_Size(int Now,int father) {
	Size[Now]=1;
	Maxson[Now]=0;
	for(int Next:edges[Now]) {
		if(Next==father||vst[Next])continue;
		Get_Size(Next,Now);
		Size[Now]+=Size[Next];
		Maxson[Now]=max(Maxson[Now],Size[Next]);
	}
}

void Get_Core(int Now,int father,int num) {
	Maxson[Now]=max(Maxson[Now],Size[num]-Size[Now]);
	if(Maxson[Now]<Min) {
		Min=Maxson[Now];
		Core=Now;
	}
	for(int Next:edges[Now]) {
		if(Next==father||vst[Next])continue;
		Get_Core(Next,Now,num);
	}
}

int tmp[maxm];

void Dfs(int Now,int fa,int v) {
	if(v>m)return;
	for(int i=1; i<=m; i++)f[Now][i]=0;
	f[Now][a[Now]]=1;
	for(int Next:edges[Now]) {
		if(vst[Next]||Next==fa)continue;
		Dfs(Next,Now,v*a[Next]);
		for(int j=1; j<=m; j++)tmp[j]=f[Now][j];
		for(int j=a[Now]; j<=m; j+=a[Now])
			for(int k:d[j/a[Now]])tmp[j]=(tmp[j]+f[Now][j/k]*f[Next][k]%mod)%mod;
		for(int j=1; j<=m; j++)f[Now][j]=tmp[j];
	}
}

void Solve(int Now) {
	Min=n;
	Get_Size(Now,0);
	Get_Core(Now,0,Now);
	Now=Core;
	vst[Now]=1;
	Dfs(Now,0,a[Now]);
	for(int i=1; i<=m; i++)ans[i]=(ans[i]+f[Now][i])%mod;
	for(int Next:edges[Now]) {
		if(vst[Next])continue;
		Solve(Next);
	} 
}

void AddEdge(int x,int y) {edges[x].push_back(y);edges[y].push_back(x);}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=2; i<=n; i++)AddEdge(Get_Int(),i);
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=1; i<=m; i++)
		for(int j=1; j<=i; j++)if(i%j==0)d[i].push_back(j);
	Solve(1);
	for(int i=1; i<=m; i++)printf("%lld\n",ans[i]);
	return 0;
}