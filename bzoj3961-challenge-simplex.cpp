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

const int maxn=4005,maxm=1605;
 
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

int n,A,B,t=0,rows=0,num_must=0,Max=0,ans;
char map[45][45];

void Clear() {
	ans=-1;
	num_must=Max=0;
}

int id(int x,int y) {
	return (x-1)*n+y;
}

int main() {
	srand(99995999);
	while(true) {
		n=Get_Int();
		A=Get_Int();
		B=Get_Int();
		if(n+A+B==0)break;
		Clear();
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++) {
				char ch=' ';
				while(ch!='.'&&ch!='/'&&ch!='C')ch=getchar();
				map[i][j]=ch;
				if(ch=='C')num_must++;
			}
		for(int i=1; i<=n; i++) {
			int sum1=0,sum2=0;
			for(int j=1; j<=n; j++) {
				sum1+=map[i][j]=='C';
				sum2+=map[j][i]=='C';
			}
			Max=max(Max,max(sum1,sum2));
		}
		for(int lim=Max; lim<=n; lim++) {
			for(int i=0; i<=rows; i++)
				for(int j=1; j<=n*n; j++)
					fst.a[i][j]=0;
			rows=0;
			for(int i=1; i<=n; i++)
				for(int j=1; j<=n; j++) {
					if(map[i][j]=='/') {
						rows++;
						fst.a[rows][id(i,j)]=-1;
					} else if(map[i][j]=='C') {
						rows++;
						fst.a[rows][id(i,j)]=1;
						fst.a[rows][0]=-1;
					}
					rows++;
					fst.a[rows][id(i,j)]=-1;
					fst.a[rows][0]=1;
				}
			for(int i=1; i<=n; i++) {
				rows++;
				for(int j=1; j<=n; j++) {
					fst.a[rows][id(i,j)]--;
					fst.a[rows][id(j,i)]++;
				}
				rows++;
				for(int j=1; j<=n; j++) {
					fst.a[rows][id(i,j)]++;
					fst.a[rows][id(j,i)]--;
				}
			}
			for(int i=1; i<=n; i++) {
				rows++;
				for(int j=1; j<=n; j++)fst.a[rows][id(i,j)]=-1;
				fst.a[rows][0]=lim;
			}
			for(int i=1; i<=n*n; i++)fst.a[0][i]=1;
			fst.init(rows,n*n);
			if(!fst.find())continue;
			int cnt=fst.Solve();
			if(cnt*A>=lim*B)ans=max(ans,cnt-num_must);
		}
		if(~ans)printf("Case %d: %d\n",++t,ans);
		else printf("Case %d: impossible\n",++t);
	}
	return 0;
}