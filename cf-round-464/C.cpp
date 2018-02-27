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

const int maxn=200005;

int n,s,t,a[maxn],sum[maxn],Max=0,ans=INT_MAX;

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int(),sum[i]=sum[i-1]+a[i];
	for(int i=n+1; i<=2*n; i++)sum[i]=sum[i-1]+a[i-n];
	s=Get_Int();
	t=Get_Int();
	for(int i=1; i<=2*n-(t-s); i++) {
		int tmp=((s-i+1)%n+n)%n;
		if(tmp==0)tmp=n;
		if(Max<sum[i+(t-s)-1]-sum[i-1]||(Max==sum[i+(t-s)-1]-sum[i-1]&&tmp<ans)) {
			ans=tmp;
			Max=sum[i+(t-s)-1]-sum[i-1];
		}
	}
	printf("%d\n",ans);
	return 0;
}