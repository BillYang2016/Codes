#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=405,p=998244353,x=1;

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%p)if(b&1)sum=sum*a%p;
	return sum;
}

LL inv(LL x) {return Quick_Pow(x,p-2);}

LL A[maxn][maxn<<1],B[maxn][maxn];
char a[maxn][maxn],b[maxn][maxn];

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

int n;

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)scanf("%s",a[i]+1);
	for(int i=1; i<=n; i++)scanf("%s",b[i]+1);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++) {
			if(a[i][j]=='1'&&b[i][j]=='1') {
				A[i][j]=-x;
				A[i][i]+=x;
				B[i][j]=p-1;
				B[i][i]+=1;
			} else if(a[i][j]=='1') {
				A[i][j]=-1;
				A[i][i]+=1;
			}
		}
	n--;
	for(int i=1; i<=n; i++)A[i][n+1]=0;
	for(int i=1; i<=n; i++)A[i][i+n]=1;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=(n<<1); j++)A[i][j]=(A[i][j]+p)%p;
	LL r=Gauss_Jordan(n,n<<1),ans=0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)ans=(ans+A[i][j+n]*B[i][j]%p)%p;
	printf("%lld\n",ans*r%p);
	return 0;
}