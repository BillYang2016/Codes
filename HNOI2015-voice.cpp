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

const int maxn=100005,maxm=200005,p=1000000007;

int n,m,s,t,InDegree[maxn];
LL a[maxn],f[maxn],ans=1,inv[maxm];
vector<int> edges[maxn];

void topsort() {
	queue<int> Q;
	f[t]=ans;
	Q.push(1);
	while(!Q.empty()) {
		int Now=Q.front();
		Q.pop();
		f[Now]=f[Now]*inv[a[Now]]%p;
		for(int Next:edges[Now]) {
			f[Next]=(f[Next]+f[Now])%p;
			if(--InDegree[Next]==0)Q.push(Next);
		}
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	s=Get_Int();
	t=Get_Int();
	inv[1]=1;
	for(int i=2; i<=n; i++)inv[i]=(p-p/i)*inv[p%i]%p;
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[x].push_back(y);
		InDegree[y]++;
		a[y]++;
	}
	a[t]++;
	for(int i=2; i<=n; i++)ans=ans*a[i]%p;
	if(t==1) {printf("%lld\n",ans);return 0;}
	topsort();
	printf("%lld\n",(ans-f[s]+p)%p);
	return 0;
}