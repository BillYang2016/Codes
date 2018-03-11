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

int n,m,Color[maxn];
vector<int> edges[maxn];

bool bj=1;

void Dfs(int Now,int color) {
	Color[Now]=color;
	for(int Next:edges[Now]) {
		if(!Color[Next])Dfs(Now,color^1);
		else if(Color[Next]!=(color^1))bj=0;
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	Dfs(1,0);
	while(m--) {
		int x=Get_Int(),y=Get_Int();
		if(bj==0||Color[x]!=Color[y])puts("Yes");
		else puts("No");
	}
	return 0;
}