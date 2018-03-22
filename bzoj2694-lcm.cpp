#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=10000005;

int n,m,cnt=0,p[maxn],g[maxn];
bool vst[maxn];

void Sieve(int n) {
	g[1]=1;
	for(int i=2; i<=n; i++) {
		if(!vst[i]) {p[++cnt]=i;g[i]=i-i*i;}
		for(int j=1; j<=cnt&&i*p[j]<=n; j++) {
			vst[i*p[j]]=1;
			if(i%p[j]==0) {
				g[i*p[j]]=i%(p[j]*p[j])==0?0:-g[i/p[j]]*p[j]*p[j]*p[j];
				break;
			}
			g[i*p[j]]=g[i]*g[p[j]];
		}
	}
	for(int i=2; i<=n; i++)g[i]+=g[i-1];
}

int f(int x) {return x*(x+1)/2;}

int main() {
	Sieve(10000000);
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		m=Get_Int();
		int ans=0;
		for(int i=1,next=0; i<=min(n,m); i=next+1) {
			next=min(n/(n/i),m/(m/i));
			ans+=(g[next]-g[i-1])*f(n/i)*f(m/i);
		}
		printf("%d\n",ans&((1<<30)-1));
	}
	return 0;
}