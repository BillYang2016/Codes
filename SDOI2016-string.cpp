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

typedef unsigned long long LL;

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

const int maxn=1000005,BASE=31;

int t,n,m,size,Size[maxn],root,precnt[maxn],succnt[maxn],a[maxn],pre[maxn],suc[maxn],Depth[maxn];
LL Pow[maxn],preh[maxn],such[maxn],ans=0;
bool vst[maxn];
char s[maxn];
vector<int> edges[maxn],pren,sucn;

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

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
	if(bj)root=Now;
}

void Cal(int Now,int fa,int depth,LL ha) {
	Depth[Now]=depth;
	if(preh[depth]==ha&&a[Now]==pre[1])pren.push_back(Now);
	if(such[depth]==ha&&a[Now]==suc[1])sucn.push_back(Now);
	for(int Next:edges[Now]) {
		if(Next==fa||vst[Next])continue;
		Cal(Next,Now,depth+1,ha*BASE+a[Next]);
	}
}

void Solve(int Now) {
	Get_Size(Now,0);
	size=Size[Now];
	Get_Root(Now,0);
	Now=root;
	for(int i=1; i<=m; i++)precnt[i]=succnt[i]=0;
	if(a[Now]==pre[1])precnt[1]=1;
	if(a[Now]==suc[1])succnt[1]=1;
	for(int Next:edges[Now]) {
		if(vst[Next])continue;
		pren.clear(),sucn.clear();
		Cal(Next,Now,1,a[Next]);
		for(int x:pren) {
			int pos=m-Depth[x]%m;
			if(pos==0)pos=m;
			ans+=succnt[pos];
		}
		for(int x:sucn) {
			int pos=m-Depth[x]%m;
			if(pos==0)pos=m;
			ans+=precnt[pos];
		}
		for(int x:pren) {
			int pos=Depth[x]%m+1;
			if(a[Now]==pre[pos])precnt[pos]++;
		}
		for(int x:sucn) {
			int pos=Depth[x]%m+1;
			if(a[Now]==suc[pos])succnt[pos]++;
		}
	}
	vst[Now]=1;
	for(int Next:edges[Now]) {
		if(vst[Next])continue;
		size=Size[Next];
		if(size<m)continue;
		Solve(Next);
	}
}

int main() {
	Pow[0]=1;
	for(int i=1; i<maxn; i++)Pow[i]=Pow[i-1]*BASE;
	t=Get_Int();
	while(t--) {
		memset(vst,0,sizeof(vst));
		for(int i=1; i<=n; i++)edges[i].clear();
		ans=0;
		n=Get_Int();
		m=Get_Int();
		scanf("%s",s+1);
		for(int i=1; i<=n; i++)a[i]=s[i]-'A'+1;
		for(int i=1; i<n; i++) {
			int x=Get_Int(),y=Get_Int();
			AddEdge(x,y);
			AddEdge(y,x);
		}
		scanf("%s",s+1);
		for(int i=1; i<=m; i++)pre[i]=s[i]-'A'+1,suc[i]=s[m-i+1]-'A'+1;
		for(int i=1; i<=n; i++)preh[i]=preh[i-1]+pre[(i-1)%m+1]*Pow[i-1],such[i]=such[i-1]+suc[(i-1)%m+1]*Pow[i-1];
		size=n;
		Solve(1);
		printf("%lld\n",ans);
	}
	return 0;
}