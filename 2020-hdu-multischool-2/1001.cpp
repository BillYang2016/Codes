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

int n,m,a[maxn],Max=0;
bool vst[maxn];
vector<int> edges[maxn];

void Dfs(int Now) {
	Max=max(Max,a[Now]);
	vst[Now]=1;
	for(int Next:edges[Now]) {
		if(vst[Next])continue;
		Dfs(Next);
	}
}

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		m=Get_Int();
		for(int i=1; i<=n; i++) {
			a[i]=Get_Int();
			vst[i]=0;
			edges[i].clear();
		}
		for(int i=1; i<=m; i++) {
			int x=Get_Int(),y=Get_Int();
			edges[x].push_back(y);
			edges[y].push_back(x);
		}
		long long ans=0;
		for(int i=1; i<=n; i++)if(!vst[i]) {
			Max=0;
			Dfs(i);
			ans+=Max;
		}
		printf("%lld\n",ans);
	}
	return 0;
}