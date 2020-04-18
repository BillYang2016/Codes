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

LL n,sum=0;

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)sum+=Get_Int();
	printf("%lld\n",sum-n*(n-1)/2);
	return 0;
}