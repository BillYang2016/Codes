#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

LL sum[200*200+5];

int main() {
	int t=Get_Int();
	while(t--) {
		int a=Get_Int(),b=Get_Int(),m=Get_Int();
		for(int i=1; i<=a*b; i++)sum[i]=sum[i-1]+(i%a%b!=i%b%a);
		while(m--) {
			LL l=Get_Int(),r=Get_Int();
			LL ans=(r-l)/(a*b)*sum[a*b];
			if(l%(a*b)<=r%(a*b))ans+=sum[r%(a*b)]-sum[l%(a*b)-1];
			else ans+=sum[r%(a*b)]+sum[a*b]-sum[l%(a*b)-1];
			printf("%lld ",ans);
		}
		putchar('\n');
	}
	return 0;
}