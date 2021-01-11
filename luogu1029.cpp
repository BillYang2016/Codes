#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

LL x,y;

int main() {
	x=Get_Int();
	y=Get_Int();
	int cnt=0;
	for(LL i=x; i<=y; i+=x) {
		if(x*y%i)continue;
		LL j=x*y/i;
		LL gcd=__gcd(i,j);
		if(gcd==x)cnt++;
	}
	printf("%d\n",cnt);
	return 0;
}