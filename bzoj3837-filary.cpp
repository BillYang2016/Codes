#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,maxv=10000005,maxp=1000005;

int n,a[maxn],b[maxn],Prime[maxv],lp[maxv],g[maxp],sum[maxp];
bool vst[maxv];

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
			int x=b[i];
			while(x>1) {
				int p=lp[x];
				sum[p]++;
				g[p]=__gcd(g[p],c[i]);
				if(k<sum[p]+sum[0])k=sum[p]+sum[0],m=0;
				else if(k==sum[p]+sum[0])m=max(m,g[p]);
				while(x%Prime[p]==0)x/=Prime[p];
			}
		}
		for(int i=1; i<=n; i++) { //clear
			int x=b[i];
			while(x>1) {
				int p=lp[x];
				sum[p]=g[p]=0;
				sum[p]++;
				while(x%Prime[p]==0)x/=Prime[p];
			}
		}
	}
	printf("%d %d\n",k,m);
	return 0;
}