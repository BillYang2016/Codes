#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=300005;

LL n,k,l,d[maxn];

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		k=Get_Int();
		l=Get_Int();
		for(int i=1; i<=n; i++)d[i]=Get_Int();
		LL Left=1,Right=2*k;
		bool flag=1;
		for(int i=1; i<=n; i++) {
			if(d[i]>l) {flag=0;break;}
			LL t=l-d[i];
			Left++,Right++;
			if(Right-Left+1>2*k)Right-=Right-Left+1-2*k;
			if(Right>=4*k)Left-=2*k,Right-=2*k;
			LL left=max(1ll,2*k+1-t),right=min(2*k+1+t,4*k);
			Left=max(Left,left);
			Right=min(Right,right);
			if(Left>Right) {flag=0;break;}
			Right=max(Right,right);
			if(t>=k)Left=1,Right=2*k;
		}
		if(Right-Left+1>2*k)Right-=Right-Left+1-2*k;
		if(Right>=4*k)Left-=2*k,Right-=2*k;
		if(flag==0)puts("No");
		else puts(Right>=Left?"Yes":"No");
	}
	return 0;
}