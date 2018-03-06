#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	return (x-'0')*bj;
}

const int mod=1000000007;

struct Matrix {
	const static int n=2;
	LL a[2][2];
	Matrix(int f=0) {memset(a,0,sizeof(a));for(int i=0; i<n; i++)a[i][i]=f;}
	LL* operator [] (const int x) {
		return a[x];
	}
	Matrix operator + (Matrix b) {
		Matrix c;
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)c[i][j]=a[i][j]+b[i][j]>=mod?a[i][j]+b[i][j]-mod:a[i][j]+b[i][j];
		return c;
	}
	void operator += (Matrix b) {
		*this=*this+b;
	}
	Matrix operator * (Matrix b) {
		Matrix c;
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++) {
				for(int k=0; k<n; k++)c[i][j]+=a[i][k]*b[k][j];
				c[i][j]%=mod;
			}
		return c;
	}
	Matrix operator ^ (LL k) {
		Matrix a=*this,c=1;
		for(; k; k>>=1,a=a*a)if(k&1)c=c*a;
		return c;
	}
};

const int maxn=1005;

int n,a[maxn];
Matrix f[maxn];

int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	f[n+1]=1;
	for(int i=n; i>=1; i--) {
		Matrix A,tmp=1;
		A[0][0]=A[1][0]=A[0][1]=1;
		for(int j=i; j<=n; j++) {
			tmp=(tmp^10)*(A^a[j]);
			f[i]+=f[j+1]*tmp;
		}
	}
	printf("%lld\n",f[1][1][1]%mod);
	return 0;
}
