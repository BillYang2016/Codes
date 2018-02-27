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

double START_T=30000,END_T=1e-4,DELTA=0.99;

void Anneal() {
	memset(sum,0,sizeof(sum));
	for(int i=1; i<=n; i++) {
		Group[i]=rand()%m+1;
		sum[Group[i]]+=seq[i];
	}
	for(int i=1; i<=m; i++)ans+=sqr(sum[i]-ave);
	double t=30000;
	while(t>1e-4) {
		int tmp=rand()%n+1,x=Group[tmp],y=rand()%m+1;
		if(x==y) {
			t*=DELTA;
			continue;
		}
		double tot=ans;
		tot-=sqr(sum[x]-ave)+sqr(sum[y]-ave);
		sum[x]-=a[tmp],sum[y]+=a[tmp];
		tot+=sqr(sum[x]-ave)+sqr(sum[y]-ave);
		if(tot<ans||exp(-t/1000000)<rand()%20000/20000) {
			ans=tot;
			Group[tmp]=y;
		}
		t*=DELTA;
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++) {
		a[i]=Get_Int();
		ave+=a[i];
	}
	ave/=m;
	random_shuffle(a+1,a+n+1);
	for(int i=1; i<=100; i++)Anneal();
	printf("%0.2lf\n",sqrt(ans/m));
	return 0;
} 
