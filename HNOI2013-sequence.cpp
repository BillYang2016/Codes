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

inline const LL Get_Int() {
	LL num=0,bj=1;
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

LL n,k,m,p;

LL Quick_Pow(LL a,LL b) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%p)if(b&1)ans=ans*a%p;
	return ans;
}

int main() {
	n=Get_Int();
	k=Get_Int();
	m=Get_Int();
	p=Get_Int();
	printf("%lld\n",((n%p*Quick_Pow(m,k-1)%p-(k-1)*Quick_Pow(m,k-2)%p*(m*(m+1)/2%p)%p)%p+p)%p);
	return 0;
} 
