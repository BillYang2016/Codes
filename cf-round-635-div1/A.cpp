#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=200005;

int n,k,f[maxn],Depth[maxn],Size[maxn];
vector<int> edges[maxn];

void Dfs(int Now,int fa) {
	Size[Now]=1;
	Depth[Now]=Depth[fa]+1;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dfs(Next,Now);
		Size[Now]+=Size[Next];
	}
	f[Now]=Depth[Now]-Size[Now];
}

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	Dfs(1,0);
	sort(f+1,f+n+1,greater<int>());
	long long ans=0;
	for(int i=1; i<=k; i++)ans+=f[i];
	printf("%lld\n",ans);
	return 0;
}