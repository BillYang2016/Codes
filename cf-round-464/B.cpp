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

int ans1,k;
LL n,ans2,Max=0;

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=1; i<=k; i++) {
		LL x=Get_Int(),tmp=n/x;
		if(tmp*x>=Max) {
			ans1=i;
			ans2=tmp;
			Max=tmp*x;
		}
	}
	printf("%d %I64d\n",ans1,ans2);
	return 0;
}