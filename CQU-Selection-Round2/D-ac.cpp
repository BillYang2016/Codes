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

int n,a[maxn],b[maxn];

bool Check() {
	if(b[2]<0||b[3]<0)return false;
	n++;
	int sum=0;
	for(int i=1; i+3<=n; i++) {
		sum+=(b[i]>0?b[i]:0)+(b[i+3]<0?b[i+3]:0);
		if(sum<0)return false;
	}
	return true;
}

int main() {
	int T=Get_Int();
	for(int t=1; t<=T; t++) {
		n=Get_Int();
		for(int i=1; i<=n; i++) {
			a[i]=Get_Int();
			b[i]=a[i]-a[i-1];
		}
		b[n+1]=-a[n];
		if(Check())printf("Case #%d: Yes\n",t);
		else printf("Case #%d: No\n",t);
	}
	return 0;
}