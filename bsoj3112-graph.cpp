#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,maxm=maxn<<1,K=63,mod=1e9+7;

void add(LL &x,LL v) {x=x+v>=mod?x+v-mod:x+v;}

struct Linear_Bases {
	LL b[K+1],cnt,sum;
	Linear_Bases() {fill(b,b+K+1,0);cnt=sum=0;}
	void add(LL num) {
		for(int j=K; j>=0; j--)if(num>>j&1) {
			if(b[j]) {num^=b[j];continue;}
			cnt++;
			b[j]=num;
			break;
		}
	}
	void cal() {for(int i=0; i<=K; i++)sum|=b[i];}
} lb[maxn];

struct Edge {
	int from,to;
	LL dist;
	Edge(int x=0,int y=0,LL v=0):from(x),to(y),dist(v) {}
} edges[maxm];

int n,m,father[maxn];
LL sum[maxn],Pow[K+2],cnt[maxn][K+1][2];

int Get_Father(int x) {
	if(father[x]==x)return x;
	int fa=Get_Father(father[x]);
	sum[x]^=sum[father[x]];
	return father[x]=fa;
}

LL C2(LL x) {return x*(x-1)/2%mod;}

int main() {
	Pow[0]=1;
	for(int i=1; i<=K+1; i++)Pow[i]=(Pow[i-1]<<1)%mod;
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)father[i]=i;
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		LL v=Get_Int();
		edges[i]=Edge(x,y,v);
		int fx=Get_Father(x),fy=Get_Father(y);
		if(fx!=fy)father[fx]=fy,sum[fx]=sum[x]^sum[y]^v;
	}
	for(int i=1; i<=n; i++)Get_Father(i);
	for(int i=1; i<=m; i++) {
		int x=edges[i].from,y=edges[i].to;
		if(sum[x]^sum[y]^edges[i].dist)lb[father[x]].add(sum[x]^sum[y]^edges[i].dist);
	}
	for(int i=1; i<=n; i++)if(father[i]==i)lb[i].cal();
	for(int i=1; i<=n; i++)for(int j=0; j<=K; j++)cnt[father[i]][j][sum[i]>>j&1]++;
	LL ans=0;
	for(int k=0; k<=K; k++) {
		LL now=0;
		for(int i=1; i<=n; i++)if(father[i]==i) {
			if(lb[i].sum>>k&1)add(now,C2(cnt[i][k][0]+cnt[i][k][1])*Pow[lb[i].cnt-1]%mod);
			else add(now,cnt[i][k][0]*cnt[i][k][1]%mod*Pow[lb[i].cnt]%mod);
		}
		add(ans,now*Pow[k]%mod);
	}
	printf("%lld\n",ans);
	return 0;
}