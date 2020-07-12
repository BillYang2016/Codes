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

int n,Degree[maxn],Deep[maxn],Min,Max,sum=0,root;
bool f[maxn][2];
vector<int> edges[maxn];

void TreeDp(int Now,int fa) {
	if(Degree[Now]==1)f[Now][0]=1,Deep[Now]=0;
	int cnt=0;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		TreeDp(Next,Now);
		if((f[Now][0]&&f[Next][0])||(f[Now][1]&&f[Next][1]))Min=3;
		Deep[Now]=max(Deep[Now],Deep[Next]+1);
		if(Deep[Next]==0)cnt++;
		f[Now][0]=f[Now][0]|f[Next][1];
		f[Now][1]=f[Now][1]|f[Next][0];
	}
	if(cnt>0)sum+=cnt-1;
}

int main() {
	n=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[x].push_back(y);
		edges[y].push_back(x);
		Degree[x]++;
		Degree[y]++;
	}
	for(int i=1; i<=n; i++)if(Degree[i]>1) {root=i;break;}
	Min=1;
	TreeDp(root,0);
	Max=n-1-sum;
	printf("%d %d\n",Min,Max);
	return 0;
}