#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1<<20;

struct FastMobiusTransform {
	int n,m;
	void init(int n) {
		this->n=n;
		m=1<<n;
	}
	void transform(double *a,int mul) {
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)
				if(j&(1<<i))a[j]+=a[j^(1<<i)]*mul;
	}
	void fmt(double *a) {transform(a,1);}
	void ufmt(double *a) {transform(a,-1);}
} mtf;

int n,tag=0;
double p[maxn];

int main() {
	n=Get_Int();
	mtf.init(n);
	for(int i=0; i<(1<<n); i++) {
		scanf("%lf",&p[i]);
		if(p[i])tag|=i;
	}
	if(tag!=(1<<n)-1) {puts("INF");return 0;}
	mtf.fmt(p);
	for(int i=0; i<(1<<n)-1; i++)p[i]=-1/(1-p[i]);p[(1<<n)-1]=0;
	mtf.ufmt(p);
	printf("%.10lf\n",p[(1<<n)-1]);
	return 0;
}