#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=205;

typedef long long LL;

LL n,p,C[maxn][maxn];

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%p)if(b&1)sum=sum*a%p;
	return sum;
}

int main() {
	n=Get_Int();
	p=Get_Int();
	C[0][0]=1;
	for(int i=1; i<=2*n; i++) {
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%p;
	}
	LL sum=0;
	for(int i=0; i<n; i++)sum=(sum+Quick_Pow(2,n-i-1)*C[2*i][i]%p)%p;
	printf("%lld\n",(C[2*n][n]-sum+p)%p);
	return 0;
}