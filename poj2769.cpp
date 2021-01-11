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

const int maxn=1000005,maxm=100005;

bool vst[maxm];
int n,a[maxn];

bool Check(int mod) {
	memset(vst,0,sizeof(vst));
	for(int i=1; i<=n; i++) {
		if(vst[a[i]%mod])return false;
		vst[a[i]%mod]=1;
	}
	return true;
}

int main() {
	int t=Get_Int();
	for(int i=1; i<=t; i++) {
		n=Get_Int();
		for(int j=1; j<=n; j++)a[j]=Get_Int();
		for(int j=n; ; j++)if(Check(j)) {printf("%d\n",j);break;}
	}
	return 0;
}