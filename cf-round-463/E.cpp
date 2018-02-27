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

const int maxn=5005,mod=1e9+7;

int n,k;
LL S[maxn][maxn],ans=0;

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

int main() {
	n=Get_Int();
	k=Get_Int();
	S[0][0]=1;
	for(int i=1; i<=k; i++)
		for(int j=1; j<=i; j++)S[i][j]=(S[i-1][j]*j%mod+S[i-1][j-1])%mod;
	LL nowf=1;
	for(int j=0; j<=min(n,k); j++) {
		ans=(ans+S[k][j]*nowf%mod*Quick_Pow(2,n-j)%mod)%mod;
		nowf=nowf*(n-j)%mod;
	}
	printf("%I64d\n",ans);
	return 0;
}