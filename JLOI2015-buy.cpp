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

const int maxn=505;
const double eps=1e-5;

int dcmp(double x) {
	if(fabs(x)<=eps)return 0;
	return x>eps?1:-1;
}

struct Thing {
	int val,id;
	bool operator < (const Thing& b) const {
		return val<b.val;
	}
} b[maxn];

int n,m,sum=0,ans=0;
double a[maxn][maxn];

struct Linear_Bases {
	double b[maxn][maxn];
	bool add(int id) {
		for(int j=m; j>=1; j--)
			if(dcmp(a[id][j])) {
				if(dcmp(b[j][j])) { //存在基
					double t=a[id][j]/b[j][j];
					for(int k=1; k<=m; k++)a[id][k]-=b[j][k]*t;
					continue;
				}
				copy(a[id]+1,a[id]+m+1,b[j]+1);
				return true;
			}
		return false;
	}
} lb;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			scanf("%lf",&a[i][j]);
	for(int i=1; i<=n; i++) {
		b[i].val=Get_Int();
		b[i].id=i;
	}
	sort(b+1,b+n+1);
	for(int i=1; i<=n; i++)
		if(lb.add(b[i].id)) {
			sum++;
			ans+=b[i].val;
		}
	printf("%d %d\n",sum,ans);
	return 0;
} 
