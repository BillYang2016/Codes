#include<bits/stdc++.h>

using namespace std;

typedef long long LL; 

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1000005;

int vst[maxn],p[maxn],u[maxn],cnt=0;

void Mobius_Table(int n) {
	u[1]=1;
	for(int i=2; i<=n; i++) {
		if(!vst[i]) {p[++cnt]=i;u[i]=-1;}
		for(int j=1; j<=cnt&&i*p[j]<=n; j++) {
			vst[i*p[j]]=1;
			if(i%p[j]==0) {u[i*p[j]]=0;break;}
			u[i*p[j]]=-u[i];
		}
	}
}

LL Cal(int n,int m) {
	LL ans=0;
	for(int b=1; b<=m; b++) {
		int up=n/b;
		for(int i=b+1,last; i<(b<<1)&&i<=up; i=last+1) {
			last=min((b<<1)-1,up/(up/i));
			ans+=1ll*(last-i+1)*(up/i);
		}
	}
	return ans;
}

int n,m;

int main() {
	n=Get_Int();
	m=sqrt(n);
	Mobius_Table(m);
	LL ans=0;
	for(int d=1; d<=m; d++)ans+=u[d]*Cal(n/d/d,m/d);
	printf("%lld\n",ans);
	return 0;
}