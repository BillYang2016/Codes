#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<ctime>

using namespace std;

typedef unsigned long long LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

LL Quick_Pow(LL a,LL b,LL p) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%p)if(b&1)sum=sum*a%p;
	return sum;
}

bool Check(LL n) {
	for(int i=2; 1ull*i*i<=n; i++)if(n%i==0)return false;
	return true;
}

int main() {
	while(true) {
		LL p=Get_Int(),a=Get_Int();
		if(p+a==0)break;
		if(Check(p))puts("no");
		else {
			if(Quick_Pow(a,p,p)==a)puts("yes");
			else puts("no");
		}
	}
	return 0;
} 