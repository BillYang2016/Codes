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

int n,m,a[maxn],b[maxn],ans=0;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)a[i]=a[i-1]+Get_Int();
	for(int i=1; i<=m; i++)b[i]=b[i-1]+Get_Int();
	int i=1,j=1,lasti=0,lastj=0;
	while(i<=n&&j<=m) {
		if(a[i]-a[lasti]==b[j]-b[lastj]) {
			ans++;
			lasti=i,lastj=j;
			i++,j++;
		} else if(a[i]-a[lasti]<b[j]-b[lastj])i++;
		else j++;
	}
	printf("%d\n",ans);
	return 0;
}