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

const int maxn=45,mod=1e9+7;

void add(LL &x,LL v) {x=x+v>=mod?x+v-mod:x+v;}

int n,m,lim;
LL a[maxn][maxn],v[maxn],f[maxn],g[maxn],Hash[maxn],Hashr[maxn],C[maxn][maxn];

int Gauss(int n) {
	LL ans=1;
	int bj=1;
	for(int i=1; i<=n; i++) {
		for(int j=i+1; j<=n; j++) {
			LL A=a[i][i],B=a[j][i];
			while(B) {
				LL t=A/B;
				A%=B;
				swap(A,B);
				for(int k=i; k<=n; k++)a[i][k]=(a[i][k]-a[j][k]*t%mod+mod)%mod;
				for(int k=i; k<=n; k++)swap(a[i][k],a[j][k]);
				bj*=-1;
			}
		}
		ans=ans*a[i][i]%mod;
	}
	return (ans*bj+mod)%mod;
}

void AddEdge(int x,int y) {
	a[x][x]++,a[y][y]++;
	a[x][y]--,a[y][x]--;
}

LL Cal(int num) {
	memset(a,0,sizeof(a));
	for(int i=1; i<=num; i++)
		for(int j=m+1; j<=n; j++)AddEdge(i,j);
	for(int i=num+1; i<=n; i++)
		for(int j=i+1; j<=n; j++)AddEdge(i,j);
	return Gauss(n-1);
}

#define pii pair<int,LL>

void Dfs(int now,int end,int cnt,int val,vector<pii> &a) {
	if(val>lim)return;
	if(now==end) {a.push_back(pii(val,cnt));return;}
	Dfs(now+1,end,cnt,val,a);
	Dfs(now+1,end,cnt+1,val+v[now],a);
}

vector<pii> L,R;

int main() {
	n=Get_Int();
	lim=Get_Int();
	for(int i=1; i<=n; i++)v[i]=Get_Int(),m+=v[i]!=-1;
	sort(v+1,v+n+1,greater<int>());
	for(int i=0; i<=m; i++)g[i]=Cal(i);
	for(int i=0; i<=m; i++) {
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	for(int i=m; i>=0; i--) {
		f[i]=g[i];
		for(int j=i+1; j<=m; j++)add(f[i],mod-C[m-i][j-i]*f[j]%mod);
	}
	Dfs(1,m/2+1,0,0,L);
	Dfs(m/2+1,m+1,0,0,R);
	sort(L.begin(),L.end()),sort(R.begin(),R.end());
	for(pii x:R)Hashr[x.second]++;
	int j=R.size()-1;
	for(int i=1; i<=L.size(); i++) {
		pii x=L[i-1];
		while(~j&&x.first+R[j].first>lim)Hashr[R[j--].second]--;
		for(int k=0; k<=n-m/2; k++)add(Hash[x.second+k],Hashr[k]);
	}
	LL ans=0;
	for(int i=0; i<=m; i++)add(ans,f[i]*Hash[m-i]%mod);
	printf("%lld\n",ans);
	return 0;
}