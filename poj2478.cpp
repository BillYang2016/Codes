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

const int maxn=1000005;

int vst[maxn],Prime[maxn],cnt=0; //prime
long long Phi[maxn]; //phi

void Phi_Table(int n) {
	Phi[1]=1;
	for(int i=2; i<=n; i++) {
		if(!vst[i]) {
			Prime[++cnt]=i;
			Phi[i]=i-1;
		}
		for(int j=1; j<=cnt&&i*Prime[j]<=n; j++) {
			vst[i*Prime[j]]=1;
			if(i%Prime[j]==0) {
				Phi[i*Prime[j]]=Phi[i]*Prime[j];
				break;
			}
			Phi[i*Prime[j]]=Phi[i]*Phi[Prime[j]];
		}
	}
}

int main() {
	Phi_Table(1000000);
	for(int i=3; i<=1000000; i++)Phi[i]+=Phi[i-1];
	while(true) {
		int n=Get_Int();
		if(!n)break;
		printf("%lld\n",Phi[n]);
	}
	return 0;
}