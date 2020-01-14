#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef long long LL;

const int maxn=5005;
const LL p=998244353;

struct Node {
	LL l,r,inv;
	bool operator < (const Node &b) {return l+r<b.l+b.r;}
} a[maxn];

int n;
LL ans,inv2=(p+1)/2;

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%p)if(b&1)sum=sum*a%p;
	return sum;
}

LL inv(LL a) {return Quick_Pow(a,p-2);}

void add(LL &x,LL v) {x=(x+v)%p;}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		a[i].l=Get_Int();
		a[i].r=Get_Int();
		a[i].inv=inv(a[i].r-a[i].l+1);
	}
	sort(a+1,a+n+1);
	for(int i=1; i<=n; i++)
		for(int j=i+1; j<=n; j++) {
			if(a[i].r<=a[j].l)continue;
			if(a[i].l<=a[j].l&&a[j].r>a[i].r)add(ans,a[i].inv*a[j].inv%p*(a[i].r-a[j].l)%p*(a[i].r-a[j].l+1)%p*inv2%p);
			else if(a[i].l>a[j].l&&a[j].r>a[i].r)add(ans,a[i].inv*a[j].inv%p*((a[i].r-a[i].l+1)*(a[i].l-a[j].l)%p+(a[i].r-a[i].l+1)*(a[i].r-a[i].l)%p*inv2%p)%p);
			else add(ans,a[i].inv*a[j].inv%p*(2*a[i].r-a[j].l-a[j].r)%p*(a[j].r-a[j].l+1)%p*inv2%p);
		}
	printf("%lld\n",ans);
	return 0;
}