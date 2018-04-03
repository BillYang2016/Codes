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

const int maxn=85,mod=1e9+7;

int n,k;

struct poly {
	int a[maxn];
	poly() {memset(a,0,sizeof(a));}
	int& operator [] (int x) {return a[x];}
	poly operator + (poly b) {
		poly ans;
		for(int i=0; i<=k; i++)ans[i]=(a[i]+b[i])%mod;
		return ans;
	}
	poly operator * (int v) {
		poly ans;
		for(int i=0; i<=k; i++)ans[i]=1ll*a[i]*v%mod;
		return ans;
	}
	poly operator * (poly b) {
		poly ans;
		for(int i=0; i<=k; i++)
			for(int j=0; j<=i; j++)
				ans[i]=(ans[i]+1ll*a[j]*b[i-j])%mod;
		return ans;
	}
};

LL M[maxn][maxn];
bool a[maxn][maxn];

int Gauss(int n) { //高斯消元计算行列式
	LL ans=1;
	int bj=1;
	for(int i=1; i<=n; i++) {
		for(int j=i+1; j<=n; j++) {
			LL A=M[i][i],B=M[j][i];
			while(B) {
				LL t=A/B;
				A%=B;
				swap(A,B);
				for(int k=i; k<=n; k++)M[i][k]=(M[i][k]-M[j][k]*t%mod+mod)%mod;
				for(int k=i; k<=n; k++)swap(M[i][k],M[j][k]);
				bj*=-1;
			}
		}
		ans=ans*M[i][i]%mod;
	}
	return (ans*bj+mod)%mod;
}

void AddEdge(int x,int y,int v) {
	M[x][x]+=v,M[y][y]+=v;
	M[x][y]-=v,M[y][x]-=v;
}

int Cal(int x) {
	memset(M,0,sizeof(M));
	for(int i=1; i<=n; i++)
		for(int j=i+1; j<=n; j++)
			AddEdge(i,j,a[i][j]?1:x);
	return Gauss(n-1);
}

LL Quick_Pow(LL a,LL b) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;
	return ans;
}

LL x[maxn],y[maxn];

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=2; i<=n; i++) {
		int x=Get_Int()+1;
		a[x][i]=1;
	}
	for(int i=1; i<=n; i++)x[i]=i,y[i]=Cal(i); //点值
	poly ans;
	for(int i=1; i<=n; i++) {
		poly f;f[0]=1;
		LL down=1;
		for(int j=1; j<=n; j++)if(j!=i) {
			poly tmp;tmp[0]=-x[j],tmp[1]=1;
			f=f*tmp;
			down=down*(x[i]-x[j])%mod;
		}
		f=f*Quick_Pow(down,mod-2);
		ans=ans+f*y[i];
	}
	int Ans=0;
	for(int i=0; i<=k; i++)Ans=(Ans+ans[i])%mod;
	printf("%d\n",(Ans+mod)%mod);
	return 0;
}