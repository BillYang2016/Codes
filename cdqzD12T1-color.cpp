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
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

LL n,m,p;

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; a=a*a%p,b>>=1)if(b&1)sum=sum*a%p;
	return sum;
}

LL inv(LL a) {
	return Quick_Pow(a,p-2);
}

namespace PrimeBase {
	void solve() {
		LL sum=0,t=((m*m%p-3*m+3%p)%p+p)%p;
		for(int i=1; i<=min(p-1,n); i++) {
			int N=(n-i)/p+1;
			sum=(sum+Quick_Pow(i,m)*Quick_Pow(t,i)%p*inv(((Quick_Pow(t,p)-1+p)%p))%p*((Quick_Pow(t,p*N)-1+p)%p))%p;
		}
		printf("%lld\n",sum*Quick_Pow(2,m)%p*((m*m-m)%p)%p*inv(t)%p);
	}
}

namespace Equation {
	const int maxm=1005;
	
	LL C[maxm][maxm],f[maxm];
	
	void Get_C() {
		for(int i=0; i<=m; i++) {
			C[i][0]=C[i][i]=1;
			for(int j=1; j<i; j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%p;
		}
	}
	
	void solve() {
		Get_C();
		LL t=((m*m%p-3*m+3%p)%p+p)%p;
		f[0]=t*inv(t-1)%p*(Quick_Pow(t,n)-1)%p;
		for(int i=1; i<=m; i++) {
			LL sum=0;
			for(int j=0; j<i; j++)sum=(sum+C[i][j]*f[j]%p)%p;
			f[i]=((Quick_Pow(t,n+1)*Quick_Pow(n+1,i)%p-t-sum*t%p)%p+p)%p*inv(t-1)%p;
		}
		printf("%lld\n",f[m]*Quick_Pow(2,m)%p*((m*m-m)%p)%p*inv(t)%p);
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	p=Get_Int();
	if(m>1000)PrimeBase::solve();
	else Equation::solve();
	return 0;
} 
