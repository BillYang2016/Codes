#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn=405,p=998244353;

int n;
LL A[maxn][maxn],tmp[maxn],B[maxn];

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%p)if(b&1)sum=sum*a%p;
	return sum;
}

LL inv(LL x) {return Quick_Pow(x,p-2);}

LL Gauss_Jordan(int n,int m) {
	LL r=1;
	for(int i=1; i<=n; i++) {
		int row=i;
		for(; row<=n; row++)if(A[row][i])break;
		if(row>n)continue;
		if(row!=i) {
			for(int j=1; j<=m; j++)swap(A[i][j],A[row][j]);
			r=(p-r)%p;
		}
		r=r*A[i][i]%p;
		LL t=inv(A[i][i]);
		for(int j=1; j<=m; j++)A[i][j]=A[i][j]*t%p;
		for(int j=1; j<=n; j++)
			if(j!=i) {
				t=A[j][i];
				for(int k=1; k<=m; k++)A[j][k]=(A[j][k]-t*A[i][k]%p+p)%p;
			}
	}
	return r;
}

int main() {
	while(scanf("%d",&n)!=EOF) {
		memset(A,0,sizeof(A));
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++) {
				scanf("%lld",&A[i][j]);
				A[i][j]=(A[i][j]+p)%p;
			}
		for(int i=1; i<=n; i++)A[i][i+n]=1;
		Gauss_Jordan(n,n<<1);
		for(int i=1; i<=n; i++) {
			scanf("%lld",&B[i]);
			B[i]=(B[i]+p)%p;
		}
		LL ans=0;
		for(int i=1; i<=n; i++) {
			tmp[i]=0;
			for(int j=1; j<=n; j++)tmp[i]=(tmp[i]+B[j]*A[i][j+n]%p)%p;
			ans=(ans+tmp[i]*B[i]%p)%p;
		}
		printf("%lld\n",ans);
	}
	return 0;
}