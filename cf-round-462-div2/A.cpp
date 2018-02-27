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

const int maxn=55;

int n,m;
LL Max=-LLONG_MAX,Sec=-LLONG_MAX,a[maxn],b[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=1; i<=m; i++)b[i]=Get_Int();
	for(int i=1; i<=n; i++) {
		LL sum=-LLONG_MAX;
		for(int j=1; j<=m; j++)sum=max(sum,a[i]*b[j]);
		if(sum>Max) {
			Sec=Max;
			Max=sum;
		} else Sec=max(Sec,sum);
	}
	printf("%I64d\n",Sec);
	return 0;
}