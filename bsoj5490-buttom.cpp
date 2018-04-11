#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=105;

#define inf INT_MAX/2

int n,f[maxn][3];
vector<int> edges[maxn];

void TreeDp(int Now,int fa) {
	f[Now][0]=0,f[Now][1]=inf,f[Now][2]=1;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		TreeDp(Next,Now);
		int tmp0=f[Now][0],tmp1=f[Now][1];
		f[Now][0]=min(min(tmp0+f[Next][1],tmp1+f[Next][2]),inf);
		f[Now][1]=min(min(tmp0+f[Next][2],tmp1+f[Next][1]),inf);
		f[Now][2]=min(f[Now][2]+f[Next][0],inf);
	}
	edges[Now].clear();
}

int main() {
	while(true) {
		n=Get_Int();
		if(!n)break;
		for(int i=1; i<n; i++) {
			int x=Get_Int(),y=Get_Int();
			edges[x].push_back(y);
			edges[y].push_back(x);
		}
		TreeDp(1,0);
		printf("%d\n",min(f[1][1],f[1][2]));
	}
	return 0;
}