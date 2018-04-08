#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int mod=1e9+7,inv2=5e8+4;

typedef long long LL;

struct Matrix {
	const static int n=27;
	LL a[n][n];
	Matrix(bool f=0) {
		memset(a,0,sizeof(a));
		for(int i=0; i<n; i++)a[i][i]=f;
	}
	LL* operator [] (const int x) {return a[x];}
	Matrix operator * (Matrix b) {
		Matrix c;
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				for(int k=0; k<n; k++)c[i][j]=(c[i][j]+a[i][k]*b[k][j]%mod)%mod;
		return c;
	}
	Matrix operator ^ (LL k) {
		Matrix a=*this,c(1);
		for(; k; k>>=1,a=a*a)if(k&1)c=c*a;
		return c;
	}
} trans;

int Cal(int x) {
	Matrix now=trans;
	LL sum=(now^x)[1][26];
	LL tmp=(now^((x+1)/2))[1][26];
	return (sum+tmp)*inv2%mod;
}

int id[5][5],step=0;

int main() {
	for(int i=0; i<=4; i++)
		for(int j=0; j<=4; j++)id[i][j]=++step;
	for(int i=0; i<=4; i++)
		for(int j=0; j<=4; j++)
			for(int k=1; k<=4; k++) {
				if(j==k)continue;
				if((j==1&&k==2)||(j==2&&k==1))continue;
				if((j==3&&k==4)||(j==4&&k==3))continue;
				if((i^j^k)==0)continue;
				trans[id[i][j]][id[j][k]]=1;
				trans[id[i][j]][26]++;
			}
	trans[26][26]++;
	int L=Get_Int(),R=Get_Int();
	printf("%d\n",(Cal(R)-Cal(L-1)+mod)%mod);
	return 0;
}