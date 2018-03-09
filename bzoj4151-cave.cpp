#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=300005;

int n,m,a[maxn],b[maxn],d[maxn],father[maxn],dist[maxn];
vector<int> edges[maxn];

void Dfs(int Now,int fa,int depth) {
	dist[Now]=depth;
	father[Now]=fa;
	for(int Next:edges[Now])if(Next!=fa)Dfs(Next,Now,depth+1);
}

void Solve() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	for(int i=1; i<=m; i++) {
		a[i]=Get_Int();
		b[i]=Get_Int();
		d[i]=Get_Int();
	}
	int root=1;
	for(int times=1; times<=2; times++) {
		Dfs(root,0,0);
		int Max=0,id=0;
		for(int i=1; i<=m; i++) {
			int t=(dist[a[i]]+dist[b[i]]-d[i]+1)/2;
			if(t>Max)Max=t,id=a[i];
		}
		if(!Max) {
			printf("TAK %d\n",root);
			return;
		}
		root=id;
		for(int i=1; i<=dist[id]-Max; i++)root=father[root];
	}
	puts("NIE");
}

void Clear() {
	for(int i=1; i<=n; i++)edges[i].clear();
}

int main() {
	int t=Get_Int();
	while(t--) {
		Clear();
		Solve();
	}
	return 0;
}