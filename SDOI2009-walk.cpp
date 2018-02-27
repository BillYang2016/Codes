#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;

typedef long long LL;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=125,mod=45989;

struct Matrix {
	LL n,m,a[maxn][maxn];
	Matrix(LL n,LL m) {
		init(n,m);
	}
	Matrix(LL n,LL m,char E) { //单位矩阵
		init(n,m);
		for(int i=1; i<=n; i++)a[i][i]=1;
	}
	void init(LL n,LL m) {
		this->n=n;
		this->m=m;
		memset(a,0,sizeof(a));
	}
	LL* operator [] (const LL x) {
		return a[x];
	}
	Matrix operator * (Matrix& b) {
		Matrix c(n,b.m);
		for(int i=1; i<=n; i++)
			for(int j=1; j<=b.m; j++)
				for(int k=1; k<=m; k++)
					c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
		return c;
	}
	void operator *= (Matrix& b) {
		*this=*this*b;
	}
	Matrix operator ^ (LL b) {
		Matrix ans(n,m,'e'),a=*this;
		while(b>0) {
			if(b&1)ans=ans*a;
			a*=a;
			b>>=1;
		}
		return ans;
	}
};

struct Edge {
	int from,to,id;
};

LL n,m,len,s,t,from[maxn],to[maxn],ans=0;
vector<Edge>edges[maxn];

int inv(int id) {
	if(id&1)return id+1;
	return id-1;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	len=Get_Int();
	s=Get_Int()+1;
	t=Get_Int()+1;
	for(int i=1; i<=m; i++) {
		int x=Get_Int()+1,y=Get_Int()+1;
		AddEdge(x,y,2*i-1);
		AddEdge(y,x,2*i);
		from[2*i-1]=x;
		to[2*i-1]=y;
		from[2*i]=y;
		to[2*i]=x;
	}
	Matrix M(2*m,2*m);
	for(int i=1; i<=2*m; i++) {
		int Now=to[i];
		for(Edge& e:edges[Now]) {
			int Next=e.to;
			if(Next==from[i])continue;
			M[i][e.id]=1;
		}
	}
	M=M^len;
	for(Edge& out:edges[s])
		for(Edge& in:edges[t])
			ans=(ans+M[out.id][inv(in.id)])%mod;
	printf("%lld\n",ans);
	return 0;
} 
