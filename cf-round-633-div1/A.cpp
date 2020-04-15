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

int t,n,a[maxn];

int main() {
	t=Get_Int();
	while(t--) {
		n=Get_Int();
		for(int i=1; i<=n; i++)a[i]=Get_Int();
		int ans=0;
		for(int i=2; i<=n; i++) {
			if(a[i]>=a[i-1])continue;
			int x=a[i-1]-a[i];
			ans=max(ans,int(log2(x))+1);
			a[i]=a[i-1];
		}
		printf("%d\n",ans);
	}
	return 0;
}