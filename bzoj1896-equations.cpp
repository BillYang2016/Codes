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

const double eps=1e-6;
 
int dcmp(double x) {
	if(fabs(x)<=eps)return 0;
	return x>eps?1:-1;
}
 
struct Simplex {
	int n,m;
	double a[maxn][maxm];
	void init(int m,int n) { //a矩阵m行n列 
		this->n=m;
		this->m=n;
	}
	bool find() {
		while(true) {
			int in=0,out=0;
			for(int i=1; i<=n; i++)
				if(dcmp(a[i][0])<0&&(!out||(g()&1)))out=i;
			if(!out)break;
			for(int j=1; j<=m; j++)
				if(dcmp(a[out][j])>0&&(!in||(g()&1)))in=j;
			if(!in)return false; //无解
			pivot(in,out);
		}
		return true;
	}
	void pivot(int in,int out) {
		for(int i=0; i<=m; i++) //重置out约束 
			if(i!=in)a[out][i]/=-a[out][in];
		a[out][in]=1/a[out][in];
		for(int i=0; i<=n; i++) { //重新计算其他约束 
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

int main() {

	return 0;
}