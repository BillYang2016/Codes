#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int mod=1e8+7;

int Quick_Pow(int a,int b) {
	int ans=1;
	for(; b; b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;
	return ans;
}

int main() {
	int t=Get_Int();
	while(t--) {
		int x=Get_Int();
		printf("%d\n",Quick_Pow(x+1,x-1));
	}
	return 0;
}