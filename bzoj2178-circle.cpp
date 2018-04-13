#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1005;

struct Circle {double x,y,r;} a[maxn];

struct Segment {
	double l,r;
	Segment(double l=0,double r=0):l(l),r(r) {}
	bool operator < (const Segment &b) const {return l<b.l;}
} s[maxn];

int n;

const double eps=1e-8;

double dcmp(double x) {return fabs(x)<=eps?0:x>eps?1:-1;}

double sqr(double x) {return x*x;}

double f(double x) {
	int cnt=0;
	for(int i=1; i<=n; i++)if(x>=a[i].x-a[i].r&&x<=a[i].x+a[i].r)s[++cnt]=Segment(a[i].y-sqrt(sqr(a[i].r)-sqr(x-a[i].x)),a[i].y+sqrt(sqr(a[i].r)-sqr(x-a[i].x)));
	sort(s+1,s+cnt+1);
	double len=0;
	for(int i=1,j; i<=cnt; i=j) {
		double Right=s[i].r;
		for(j=i+1; j<=cnt; j++) {
			if(s[j].l>Right)break;
			Right=max(Right,s[j].r);
		}
		len+=Right-s[i].l;
	}
	return len;
}

double Cal(double Left,double Right) {return (Right-Left)/6*(f(Left)+4*f((Left+Right)/2)+f(Right));}

double Simpson(double Left,double Right,double ans) {
	double mid=(Left+Right)/2,ans1=Cal(Left,mid),ans2=Cal(mid,Right);
	if(dcmp(ans-ans1-ans2)==0)return ans;
	else return Simpson(Left,mid,ans1)+Simpson(mid,Right,ans2);
}

int main() {
	n=Get_Int();
	double Left=1e15,Right=-1e15;
	for(int i=1; i<=n; i++) {
		a[i].x=Get_Int();
		a[i].y=Get_Int();
		a[i].r=Get_Int();
		Left=min(Left,a[i].x-a[i].r);
		Right=max(Right,a[i].x+a[i].r);
	}
	printf("%0.3lf\n",Simpson(Left,Right,Cal(Left,Right)));
	return 0;
}