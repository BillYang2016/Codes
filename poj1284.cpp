#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<ctime>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int Phi(int x) {
	int ans=x;
	for(int i=2; i<=x; i++)if(x%i==0) {
		ans-=ans/i;
		while(x%i==0)x/=i;
	}
	return ans;
}

int n;

int main() {
	while(~scanf("%d",&n))printf("%d\n",Phi(n-1));
	return 0;
}