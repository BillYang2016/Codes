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

map<int,map<int,int> > M;
vector<int> edges[maxn];
int n,a[3],f[maxn],ans=0;

void Solve(int a,int x,int y) {
	if(M.count(x)&&M[x].count(y)) {
		int b=M[x][y];
		edges[a].push_back(b);
		edges[b].push_back(a);
	} else M[x][y]=a;
}

void TreeDp(int Now,int fa) {
	f[Now]=1;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		TreeDp(Next,Now);
		ans=max(ans,f[Now]+f[Next]);
		f[Now]=max(f[Now],f[Next]+1);
	}
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n-2; i++) {
		a[0]=Get_Int(),a[1]=Get_Int(),a[2]=Get_Int();
		sort(a,a+3);
		Solve(i,a[0],a[1]);
		Solve(i,a[0],a[2]);
		Solve(i,a[1],a[2]);
	}
	TreeDp(1,0);
	printf("%d\n",ans);
	return 0;
}