#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,K=30;

int n,a[maxn],Hash[K];
long long ans=0;

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i]=a[i-1]^Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=0; j<K; j++)
			if((a[i]>>j)&1) {
				ans+=(i-Hash[j])*(1ll<<j);
				Hash[j]++;
			} else ans+=Hash[j]*(1ll<<j);
	printf("%lld\n",ans);
	return 0;
}