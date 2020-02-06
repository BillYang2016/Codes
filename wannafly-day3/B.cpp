#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef long long LL;

const int maxn=5005,p=1e9+7;

int n,Size[maxn];
LL f[maxn][maxn],sum[maxn][maxn],tmp[maxn],C[maxn][maxn];
vector<int> edges[maxn];

void AddEdge(int x,int y) {edges[x].push_back(y);}

void TreeDp(int Now,int fa) {
	Size[Now]=1;
	for(int i=2; i<=n; i++)f[Now][i]=0;
	f[Now][1]=1;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		TreeDp(Next,Now);
		Size[Now]+=Size[Next];
		for(int i=0; i<=Size[Now]-Size[Next]; i++)tmp[i]=f[Now][i],f[Now][i]=0;
		for(int i=1; i<=Size[Now]; i++)
			for(int j=min(i-1,Size[Next]); j>=0&&i-j<=Size[Now]-Size[Next]; j--)
				f[Now][i]=(f[Now][i]+tmp[i-j]*sum[Next][j]%p*C[i-1][i-j-1]%p)%p;
	}
	for(int i=Size[Now]; i>=0; i--)sum[Now][i]=(sum[Now][i+1]+f[Now][i])%p;
}

int main() {
	n=Get_Int();
	C[0][0]=1;
	for(int i=1; i<=n; i++) {
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%p;
	}
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y);
		AddEdge(y,x);
	}
	TreeDp(1,0);
	printf("%lld\n",sum[1][0]);
	return 0;
}