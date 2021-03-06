#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<queue>
using namespace std;

typedef long long LL;

inline const LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

LL Quick_Pow(LL a,LL b,LL p) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%p)if(b&1)sum=sum*a%p;
	return sum;
}

const int TIMES=10; 

mt19937 g(rand());

bool Witness(LL a,LL n) {
	LL u=n-1,t=0;
	while(u%2==0)t++,u>>=1;
	LL x=Quick_Pow(a,u,n);
	if(x==1)return false;
	for(int i=1; i<=t; i++,x=x*x%n)
		if(x!=n-1&&x!=1&&x*x%n==1)return true;
	return x!=1;
}

bool Miller_Rabin(LL n) {
	if(n==2)return true;
	if(n<2||!(n&1))return false;
	srand(time(NULL));
	for(int i=1; i<=TIMES; i++)
		if(Witness(g()%(n-1)+1,n))return false;
	return true;
}

LL n;

int main() {
	while(~scanf("%lld",&n))puts(Miller_Rabin(n)?"Yes":"No");
	return 0;
} 
