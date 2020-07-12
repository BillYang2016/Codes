#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=200005;

int n,h,len[maxn],mid[maxn];

int main() {
	n=Get_Int();
	h=Get_Int();
	int lastr=0;
	for(int i=1; i<=n; i++) {
		int l=Get_Int(),r=Get_Int();
		if(i==1)lastr=l;
		len[i]=len[i-1]+r-l;
		mid[i]=mid[i-1]+l-lastr;
		lastr=r;
	}
	int ans=0;
	for(int i=1; i<=n; i++) {
		int r=lower_bound(mid+1,mid+n+1,mid[i]+h)-mid-1;
		ans=max(ans,len[r]-len[i-1]+h);
	}
	printf("%d\n",ans);
	return 0;
}