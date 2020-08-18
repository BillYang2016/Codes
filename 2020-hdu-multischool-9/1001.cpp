#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=500005;

typedef long long LL;

LL n,Size[maxn],f[maxn],ans=0;
vector<int> edges[maxn];

void Dfs(int Now) {
	Size[Now]=1;
	for(int Next:edges[Now]) {
		Dfs(Next);
		Size[Now]+=Size[Next];
	}
}

void Dfs2(int Now) {
	ans+=Size[Now];
	for(int Next:edges[Now]) {
		f[Next]=f[Now]+n-Size[Next];
		Dfs2(Next);
	}
}

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		ans=0;
		for(int i=1; i<=n; i++)edges[i].clear();
		for(int i=2; i<=n; i++)edges[Get_Int()].push_back(i);
		f[1]=0;
		Dfs(1);
		Dfs2(1);
		LL Max=0;
		for(int i=1; i<=n; i++)Max=max(Max,f[i]);
		printf("%lld\n",Max+ans);
	}
	return 0;
}