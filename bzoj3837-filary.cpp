#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

void Prime_Table(int n) {
	for(int i=2; i<=n; i++) {
		if(!vst[i]) {vst[i]=1;Prime[++cnt]=i;lp[i]=cnt;}
		for(int j=1; j<=cnt&&i*Prime[j]<=n; j++) {
			vst[i*Prime[j]]=1;
			lp[i*Prime[j]]=j;
			if(i%Prime[j]==0)break;
		}
	}
}

int main() {
	Prime_Table(10000000);
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int t=1; t<=4; t++) {
		int x=a[rand()%n+1];
		for(int i=1; i<=n; i++) {
			b[i]=abs(v[i]-x);
			if(!b[i])sum[0]++;
		}
		int k=0;
		for(int i=1; i<=n; i++) {
			int tmp=c[i];
			while(tmp>1) {

			}
		}
	}
	return 0;
}