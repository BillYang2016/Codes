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
 
const int maxn=1505,maxm=1505;
const double eps=1e-6;
 
int dcmp(double x) {
	if(fabs(x)<=eps)return 0;
	return x>eps?1:-1;
}
 
struct Simplex {
	int n,m;
	double a[maxn][maxm];
	void init(int m,int n) { //Matrix a : m rows,n lines
		this->n=m;
		this->m=n;
	}
	void pivot(int in,int out) {
		for(int i=0; i<=m; i++) //reset constraint "out"
			if(i!=in)a[out][i]/=-a[out][in];
		a[out][in]=1/a[out][in];
		for(int i=0; i<=n; i++) { //recalculate other constraints 
			if(i==out||dcmp(a[i][in])==0)continue;
			double t=a[i][in];
			a[i][in]=0;
			for(int j=0; j<=m; j++)a[i][j]+=t*a[out][j];
		}
	}
	double Solve() {
		while(true) {
			int in=0,out=0;
			double Min=1e18;
			for(int i=1; i<=m; i++)
				if(dcmp(a[0][i])>0) {
					in=i;
					break;
				}
			if(!in)return a[0][0];
			for(int i=1; i<=n; i++)
				if(dcmp(a[i][in])<0&&a[i][0]/-a[i][in]<Min) {
					Min=a[i][0]/-a[i][in];
					out=i;
				}
			if(!out)throw ; //unbounded
			pivot(in,out);
		}
	}
} fst;

int N,M,k;
int n,m;

int id(int x,int y) {return (x-1)*M+y;}

int main() {
	N=Get_Int();
	M=Get_Int();
	k=Get_Int();
	n=N*M;
	fst.init(n,k);
	for(int i=1; i<=n; i++)fst.a[i][0]=1;
	for(int i=1; i<=k; i++) {
		int x=Get_Int(),y=Get_Int(),xx=Get_Int(),yy=Get_Int(),w=Get_Int();
		fst.a[id(x,y)][i]=fst.a[id(xx,yy)][i]=-1;
		fst.a[0][i]=w;
	}
	printf("%lld\n",(long long)(fst.Solve()));
	return 0;
}