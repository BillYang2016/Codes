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

LL n;
int d,b,a[100005];

int main() {
	n=Get_Int();
	d=Get_Int();
	b=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	LL sum=0;
	int cnt=0,mid=(n+1)>>1;
	for(int i=1,j=1; i<=mid; i++) {
		for(; j<=min(n,i+1ll*i*d); j++)sum+=a[j];
		if(sum>=b)sum-=b;
		else cnt++;
	}
	int ans=cnt;
	cnt=sum=0;
	for(int i=n,j=n; i>mid; i--) {
		for(; j>=max(0ll,i-1ll*(n-i+1)*d); j--)sum+=a[j];
		if(sum>=b)sum-=b;
		else cnt++;
	}
	printf("%d\n",max(ans,cnt));
	return 0;
}