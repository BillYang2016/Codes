#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int mod=2007;

int Pow[105];

int main() {
	Pow[0]=1;
	for(int i=1; i<=100; i++)Pow[i]=Pow[i-1]*5%mod;
	int t=Get_Int();
	while(t--) {
		int n=Get_Int();
		printf("%d\n",4*n%mod*Pow[n-1]%mod);
	}
	return 0;
}