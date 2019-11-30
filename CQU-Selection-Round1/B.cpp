#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

int n,w,a[maxn],sum[maxn];

int main() {
	n=Get_Int();
	w=Get_Int();
	int m=0;
	for(int i=1; i<=n; i++) {
		int x=Get_Int(),y=Get_Int();
		a[x]+=y;
		m=max(m,x);
	}
	for(int i=1; i<=m; i++)sum[i]=sum[i-1]+a[i];
	int ans=0;
	for(int i=1; i+w-1<=m; i++)ans=max(ans,sum[i+w-1]-sum[i-1]);
	printf("%d\n",ans);
	return 0;
}