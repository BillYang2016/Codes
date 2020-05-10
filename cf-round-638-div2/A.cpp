#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef long long LL;

int main() {
	int t=Get_Int();
	while(t--) {
		int n=Get_Int();
		LL sum=0;
		for(int i=1; i<(n>>1); i++)sum+=(1ll<<i);
		sum+=(1ll<<n);
		LL sum2=(1<<(n+1))-2-sum;
		printf("%lld\n",abs(sum-sum2));
	}
	return 0;
}