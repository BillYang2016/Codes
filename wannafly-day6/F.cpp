#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=5005;

bitset<maxn> a[maxn];

LL n,A,B,C,D,P;

int main() {
	n=Get_Int();
	A=Get_Int();
	B=Get_Int();
	C=Get_Int();
	P=Get_Int();
	D=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)if(i!=j)a[i][j]=(A*(i+j)*(i+j)+B*(i-j)*(i-j)+C)%P>D;
	LL cnt=0;
	for(int i=1; i<=n; i++) {
		LL cnt1=a[i].count();
		cnt+=cnt1*(n-1-cnt1);
	}
	printf("%lld\n",n*(n-1)*(n-2)/6-cnt/2);
	return 0;
}