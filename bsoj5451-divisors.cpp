#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=5005,mod=1<<30;

int cnt=0,p[maxn],d[maxn],u[maxn],mds[maxn],mind[maxn],simp[maxn],f[maxn];
bool vst[maxn];

void Sieve(int n) {
	d[1]=u[1]=mind[1]=simp[1]=1;
	for(int i=2; i<=n; i++) {
		if(!vst[i]) {
			p[++cnt]=i;
			mds[i]=1,d[i]=2;
			mind[i]=simp[i]=i;
			u[i]=-1;
		}
		for(int j=1; j<=cnt&&i*p[j]<=n; j++) {
			vst[i*p[j]]=1;
			mind[i*p[j]]=p[j];
			if(i%p[j]==0) {
				mds[i*p[j]]=mds[i]+1;
				d[i*p[j]]=d[i]/(mds[i]+1)*(mds[i]+2);
				simp[i*p[j]]=simp[i];
				u[i*p[j]]=0;
				break;
			}
			mds[i*p[j]]=1;
			d[i*p[j]]=d[i]*d[p[j]];
			simp[i*p[j]]=simp[i]*p[j];
			u[i*p[j]]=-u[i];
		}
	}
	for(int i=1; i<=n; i++)f[i]=f[i-1]+d[i];
}

int Gcd[maxn][maxn];

int gcd(int a,int b) {
	if(Gcd[a][b])return Gcd[a][b];
	return Gcd[a][b]=!b?a:gcd(b,a%b);
}

int A,B,C,M[maxn*maxn];

int Dfs(int x,int y,int d) {
	if(d>C)return 0;
	if(x==1&&y==1)return u[d]*f[C/d];
	else if(x>1)return Dfs(x/mind[x],y,d)+Dfs(x/mind[x],y,d*mind[x]);
	else return Dfs(x,y/mind[y],d)+Dfs(x,y/mind[y],d*mind[y]);
}

int main() {
	Sieve(5000);
	A=Get_Int();
	B=Get_Int();
	C=Get_Int();
	int ans=0;
	for(int x=1; x<=A; x++)
		for(int y=1; y<=B; y++) {
			if(gcd(simp[x],simp[y])!=1)continue;
			int T=simp[x]*simp[y];
			if(!M[T])M[T]=Dfs(x,y,1);
			ans+=(A/x)*(B/y)*M[T];
		}
	printf("%d\n",ans&(mod-1));
	return 0;
}