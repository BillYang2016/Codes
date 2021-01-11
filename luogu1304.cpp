#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=10005;

int vst[maxn],Prime[maxn],cnt=0;

void Prime_Sieve(int n) {
	for(int i=2; i<=n; i++) {
		if(!vst[i])Prime[++cnt]=i;
		for(int j=1; j<=cnt&&i*Prime[j]<=n; j++) {
			vst[i*Prime[j]]=1;
			if(i%Prime[j]==0)break;
		}
	}
}

int n;

int main() {
	n=Get_Int();
	Prime_Sieve(n);
	for(int i=4; i<=n; i+=2)
		for(int j=1; j<=cnt&&Prime[j]<i; j++)if(!vst[i-Prime[j]]) {
			printf("%d=%d+%d\n",i,Prime[j],i-Prime[j]);
			break;
		}
	return 0;
}