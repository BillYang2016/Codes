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

const int maxn=3000005;

LL n,p,inv[maxn];

int main() {
	n=Get_Int();
	p=Get_Int();
	inv[1]=1;
	for(int i=1; i<=n; i++) {
		if(i!=1)inv[i]=(p-p/i)*inv[p%i]%p;
		printf("%lld\n",inv[i]);
	}
	return 0;
} 
