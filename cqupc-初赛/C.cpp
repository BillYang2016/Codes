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

int a[maxn],n,q;

int main() {
	scanf("%d%d",&n,&q);
	for(int i=1; i<=n; i++) {
		scanf("%d",&a[i]);
		a[i]=a[i]^a[i-1];
	}
	for(int i=1; i<=q; i++) {
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",a[r]^a[l-1]);
	}
	return 0;
}