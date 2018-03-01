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

typedef long long LL;

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

const int maxn=1005,maxm=1<<10;
const int mod=1e9+7,inv2=5e8+4;

struct FastWalshTransform {
	int n;
	void init(int n) {
		this->n=n;
	}
	void transform(LL *a,LL mul) {
		for(int len=2; len<=n; len<<=1) {
			int mid=len>>1;
			for(LL *p=a; p!=a+n; p+=len)
				for(int i=0; i<mid; i++) {
					LL x=p[i],y=p[mid+i];
					p[i]=(x+y)*mul%mod;
					p[mid+i]=(x-y+mod)*mul%mod;
				}
		}
	}
	void fwt(LL *a) {
		transform(a,1);
	}
	void ufwt(LL *a) {
		transform(a,inv2);
	}
} wtf;

int t,n,m;
LL a[maxn],f[maxn][maxm],e[maxm][maxm],ans[maxm];
vector<int> edges[maxn];

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

void TreeDp(int Now,int fa) {
	for(int i=0; i<m; i++)f[Now][i]=e[a[Now]][i];
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		TreeDp(Next,Now);
		for(int i=0; i<m; i++)f[Now][i]=f[Now][i]*(f[Next][i]+e[0][i])%mod;
	}
	for(int i=0; i<m; i++)ans[i]=(ans[i]+f[Now][i])%mod;
}

void Clear() {
	for(int i=1; i<=n; i++) {
		edges[i].clear();
		for(int j=1; j<=m; j++)f[i][j]=0;
	}
	for(int i=0; i<m; i++)ans[i]=0;
}

int main() {
	t=Get_Int();
	while(t--) {
		Clear();
		n=Get_Int();
		m=Get_Int();
		int t=1;
		while(t<m)t<<=1;
		wtf.init(t);
		for(int i=0; i<m; i++) {
			fill(e[i],e[i]+m,0);
			e[i][i]=1;
			wtf.fwt(e[i]);
		}
		for(int i=1; i<=n; i++)a[i]=Get_Int();
		for(int i=1; i<n; i++) {
			int x=Get_Int(),y=Get_Int();
			AddEdge(x,y);
			AddEdge(y,x);
		}
		TreeDp(1,0);
		wtf.ufwt(ans);
		for(int i=0; i<m; i++)printf("%lld%c",ans[i],i==m-1?'\n':' ');
	}
	return 0;
}