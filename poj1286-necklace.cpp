#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

LL n;

int main() {
	while(scanf("%lld",&n)&&~n) {
		if(n==0) {puts("0");continue;}
		LL sum=0;
		for(LL i=1; i<=n; i++)sum+=pow(3ll,__gcd(n,i));
		if(n&1)sum+=n*pow(3ll,(n+1)/2);
		else sum+=n/2*(pow(3ll,n/2+1)+pow(3ll,n/2));
		printf("%lld\n",sum/(n<<1));
	}
	return 0;
}