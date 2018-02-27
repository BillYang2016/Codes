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

const int maxn=105,maxm=105;
const double eps=1e-8;

int t,id[maxn+maxm];
double ans[maxn+maxm];

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
				if(dcmp(a[i][0])<0&&(!out||(rand()&1)))out=i;
			if(!out)break;
			for(int j=1; j<=m; j++)
				if(dcmp(a[out][j])>0&&(!in||(rand()&1)))in=j;
			if(!in)return false; //无解
			pivot(in,out);
		}
		return true;
	}
	void pivot(int in,int out) {
		swap(id[m+out],id[in]);
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
	void Solve() {
		while(true) {
			int in=0,out=0;
			double Min=1e18;
			for(int i=1; i<=m; i++)
				if(dcmp(a[0][i])>0) {
					in=i;
					break;
				}
			if(!in)break;
			for(int i=1; i<=n; i++)
				if(dcmp(a[i][in])<0&&a[i][0]/-a[i][in]<Min) {
					Min=a[i][0]/-a[i][in];
					out=i;
				}
			if(!out) {
				puts("Unbounded");
				return;
			}
			pivot(in,out);
		}
		printf("%0.8lf\n",a[0][0]);
		if(t) {
			for(int i=1; i<=n; i++)ans[id[m+i]]=a[i][0];
			for(int i=1; i<=m; i++)printf("%0.8lf ",ans[i]);
		}
	}
} fst;

int n,m;

int main() {
	srand(99995999);
	n=Get_Int();
	m=Get_Int();
	t=Get_Int();
	fst.init(m,n);
	for(int i=1; i<=n; i++)fst.a[0][i]=Get_Int();
	for(int i=1; i<=m; i++) {
		for(int j=1; j<=n; j++)
			fst.a[i][j]=-Get_Int();
		fst.a[i][0]=Get_Int();
	}
	for(int i=1; i<=n; i++)id[i]=i;
	if(!fst.find())puts("Infeasible");
	else fst.Solve();
	return 0;
}