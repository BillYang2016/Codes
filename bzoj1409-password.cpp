#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int mod;

struct Matrix {
	const static int maxn=2;
	int n,m;
	int a[maxn][maxn];
	Matrix(int n=0,int m=0,bool f=0):n(n),m(m) {
		memset(a,0,sizeof(a));
		for(int i=0; i<n; i++)a[i][i]=f;
	}
	int* operator [] (const int x) {return a[x];}
	Matrix operator * (Matrix b) {
		Matrix c(n,b.m);
		for(int i=0; i<n; i++)
			for(int j=0; j<b.m; j++)
				for(int k=0; k<m; k++)c[i][j]=(c[i][j]+1ll*a[i][k]*b[k][j])%mod;
		return c;
	}
	Matrix operator ^ (int k) {
		Matrix a=*this,c(n,m,1);
		for(; k; k>>=1,a=a*a)if(k&1)c=c*a;
		return c;
	}
};

const int maxn=50005;

int vst[maxn],pr[maxn],cnt=0;

void Prime_Sieve(int n) {
	for(int i=2; i<=n; i++) {
		if(!vst[i])pr[++cnt]=i;
		for(int j=1; j<=cnt&&i*pr[j]<=n; j++) {
			vst[i*pr[j]]=1;
			if(i%pr[j]==0)break;
		}
	}
}

int Euler_Phi(int x) {
	int ans=x;
	for(int i=1; i<=cnt&&pr[i]<=sqrt(x); i++) {
		if(x%pr[i])continue;
		while(x%pr[i]==0)x/=pr[i];
		ans=ans/pr[i]*(pr[i]-1);
	}
	if(x>1)ans=ans/x*(x-1);
	return ans;
}

int Quick_Pow(int a,int b,int mod) {
	int ans=1;
	for(; b; b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;
	return ans%mod;
}

int n,p,q;

int main() {
	Prime_Sieve(50000);
	int t=Get_Int();
	p=Get_Int();
	while(t--) {
		n=Get_Int();
		q=Get_Int();
		mod=Euler_Phi(q);
		Matrix A(1,2),B(2,2);
		A[0][0]=1;
		B[0][0]=B[0][1]=B[1][0]=1;
		A=A*(B^(n-1));
		printf("%d\n",Quick_Pow(p,A[0][0],q));
	}
	return 0;
}