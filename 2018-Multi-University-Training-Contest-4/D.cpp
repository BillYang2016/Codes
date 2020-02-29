#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=105;

int n,m,a[maxn];

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		m=Get_Int();
		for(int i=1; i<=n; i++) {
			Get_Int();
			a[i]=Get_Int()+1;
		}
		sort(a+1,a+n+1);
		long long sum=1,ans=0;
		for(int i=1; i<=n; i++)
			if(sum*a[i]<=m) {
				sum*=a[i];
				ans++;
			} else break;
		printf("%lld\n",ans);
	}
	return 0;
}