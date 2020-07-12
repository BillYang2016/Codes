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

int n,q,a[maxn];

int main() {
	scanf("%d%d",&n,&q);
	for(int i=1; i<=n; i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1; i<=q; i++) {
		int x;
		scanf("%d",&x);
		int Left=1,Right=n;
		while(Left<=Right) {
			int mid=(Left+Right)>>1;
			if(a[mid]<=x)Left=mid+1;
			else Right=mid-1;
		}
		int l=Right,r=Right+1;
		if(l<1)l=1;
		if(r>n)r=n;
		if(abs(a[l]-x)>=abs(a[r]-x))printf("%d\n",a[r]);
		else printf("%d\n",a[l]);
	}
	return 0;
}