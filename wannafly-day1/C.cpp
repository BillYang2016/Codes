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

const int p=998244353;

LL n,L,R;

LL get(LL L,LL R) {return (L+R)*(R-L+1)/2%p;} //等差数列求和

LL C2(LL x) {return x*(x-1)/2%p;}

LL g(LL n,LL l,LL r) {
	LL Down=n/l,Up=(n-1)/l+1,len=r-l+1;
	LL tmp=Down*get(l,r)%p;
	LL val1=(len*n%p-tmp+p)%p*C2(Up)%p,val2=(get(l,r)-n*len%p+tmp+p)%p*C2(Down)%p;
	return (val1+val2)%p;
}

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		L=Get_Int();
		R=Get_Int();
		int Next=1;
		LL ans=0;
		for(int i=L; i<=min(R,n-1); i=Next+1) {
			Next=min(R,min(n/(n/i),(n-1)/((n-1)/i)));
			ans=(ans+g(n,i,Next))%p;
		}
		printf("%lld\n",(C2(n)*(R-L+1)%p-ans+p)%p);
	}
	return 0;
}