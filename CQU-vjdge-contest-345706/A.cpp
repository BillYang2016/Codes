#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

int t,n,m,sum[maxn];

int main() {
	t=Get_Int();
	while(t--) {
		n=Get_Int();
		m=Get_Int();
		for(int i=1; i<=n; i++)sum[i]=sum[i-1]+Get_Int();
		int j=0,ans=0x7fffffff/2;
		for(int i=1; i<=n; i++) {
			while(sum[i]-sum[j]>=m)j++;
			if(j&&sum[i]-sum[j-1]>=m)ans=min(ans,i-j+1);
		}
		printf("%d\n",ans==0x7fffffff/2?0:ans);
	}
	return 0;
}