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
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=5e5+5;
const double eps=1e-6;

int n,q;
LL a[maxn],sum[maxn];
double ans=0;

bool Check(double m) {
	int Left=1,Right=n,pos=-1;
	while(Left<=Right) {
		int mid=(Left+Right)>>1;
		if(m>a[mid]) {
			pos=mid;
			Left=mid+1;
			if(m*pos-sum[pos]+m-a[n]>=0)return true;
		} else Right=mid-1;
	}
	if(~pos)return m*pos-sum[pos]+m-a[n]>=0;
	return false;
}

int main() {
	q=Get_Int();
	while(q--) {
		int opt=Get_Int();
		if(opt==1) {
			int x=Get_Int();
			a[++n]=x;
			sum[n]=sum[n-1]+x;
			double Left=0,Right=1e9;
			while(Right-Left>eps) {
				double mid=(Left+Right)/2;
				if(Check(x-mid))Left=mid;
				else Right=mid;
			}
			ans=(Left+Right)/2;
		} else printf("%0.10lf\n",ans);
	}
	return 0;
}