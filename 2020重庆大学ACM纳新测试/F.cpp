#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1005;

int t,n,a[maxn];

int main() {
	int t=Get_Int();
	for(int cnt=1; cnt<=t; cnt++) {
		n=Get_Int();
		fill(a,a+n+1,0);
		for(int i=1; i<=n; i++) {
			int x=Get_Int();
			int pos=x%n;
			while(a[pos]) {
				pos++;
				if(pos==n)pos=0;
			}
			a[pos]=x;
		}
		printf("Case #%d:\n",cnt);
		for(int i=0; i<n-1; i++)printf("%d ",a[i]);
		printf("%d\n",a[n-1]);
	}
	return 0;
}