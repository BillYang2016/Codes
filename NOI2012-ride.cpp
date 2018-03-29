#include<bits/stdc++.h>

using namespace std;

#define double long double

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=10005;
const double eps=1e-12;

int n;
double Eu,v[maxn],v0[maxn],s[maxn],k[maxn];

double Cal(double lambda) {
	double sum=0;
	for(int i=1; i<=n; i++) {
		double Left=fmax(0,v0[i]),Right=INT_MAX;
		while(Right-Left>eps) {
			double mid=(Left+Right)/2;
			if(2*lambda*mid*mid*k[i]*(mid-v0[i])>=-1)Left=mid;
			else Right=mid;
		}
		v[i]=(Left+Right)/2;
		sum+=k[i]*(v[i]-v0[i])*(v[i]-v0[i])*s[i];
	}
	return sum;
}

int main() {
	n=Get_Int();
	scanf("%Lf",&Eu);
	for(int i=1; i<=n; i++)scanf("%Lf%Lf%Lf",&s[i],&k[i],&v0[i]);
	double Left=INT_MIN,Right=0;
	while(Right-Left>eps) {
		double mid=(Left+Right)/2;
		if(Cal(mid)<=Eu)Left=mid;
		else Right=mid;
	}
	double mid=(Left+Right)/2;
	Cal(mid);
	double ans=0;
	for(int i=1; i<=n; i++)ans+=s[i]/v[i];
	printf("%0.8Lf\n",ans);
	return 0;
}