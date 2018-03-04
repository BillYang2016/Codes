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

inline const LL Get_Int() {
	LL num=0,bj=1;
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

const int maxn=5000005;

struct Station {
	double x,r,k,v;
	Station(double x=0,double r=0,double v=0):x(x),r(r),v(v) {if(r)k=1.0/(2.0*sqrt(r));}
} a[maxn];

struct Point {
	double x,y;
	int id;
	Point(double x=0,double y=0,int id=0):x(x),y(y),id(id) {}
	Point operator - (const Point &b) const {
		return Point(b.x-x,b.y-y);
	}
} p[maxn],S[maxn];

typedef Point Vector;

double Cross(Vector a,Vector b) {
	return a.x*b.y-b.x*a.y;
}

double Slope(Point a,Point b) {
	return (b.y-a.y)/(b.x-a.x);
}

int top=0;

int Binary(int x) {
	if(top==1)return S[1].id;
	if(Slope(S[1],S[2])>=a[x].k)return S[1].id;
	int Left=2,Right=top;
	while(Left<=Right) {
		int mid=(Left+Right)>>1;
		if(Slope(S[mid-1],S[mid])<=a[x].k)Left=mid+1;
		else Right=mid-1;
	}
	return S[Right].id;
}

LL n,x;
double f[maxn];

int main() {
	n=Get_Int();
	x=Get_Int();
	for(int i=1; i<=n; i++) {
		double x=Get_Int(),r=Get_Int(),v=Get_Int();
		a[i]=Station(x,r,v);
	}
	f[n]=a[n].v,p[n]=Point(-a[n].x,f[n],n);
	S[++top]=p[n];
	for(int i=n-1; i>=1; i--) {
		int j=Binary(i);
		f[i]=f[j]+(a[j].x-a[i].x)/(2.0*sqrt(a[i].r))+a[i].v;
		if(x-a[i].x<=a[i].r)f[i]=min(f[i],a[i].v);
		p[i]=Point(-a[i].x,f[i],i);
		while(top>1&&Cross(S[top-1]-S[top],S[top-1]-p[i])<=0)top--;
		S[++top]=p[i];
	}
	printf("%0.3lf\n",f[1]);
	return 0;
}