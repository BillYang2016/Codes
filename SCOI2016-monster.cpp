#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1000005;

struct Point {
	LL x,y;
	Point(LL x=0,LL y=0):x(x),y(y) {}
	Point operator - (const Point &b) {return Point(b.x-x,b.y-y);}
	bool operator < (const Point &b) const {return x<b.x||(x==b.x&&y<b.y);}
} p[maxn],S[maxn];

typedef Point Vector;

LL Cross(Vector a,Vector b) {return a.x*b.y-b.x*a.y;}
double Slope(Point a,Point b) {return 1.0*(b.y-a.y)/(b.x-a.x);}
double Optimalk(Point p) {return -sqrt(1.0*p.y/p.x);}
double Cal(Point p,double k) {return k>=0?1e18:p.x+p.y-p.x*k-p.y/k;}

int n,top=0;
double ans=1e18;

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		p[i].x=Get_Int();
		p[i].y=Get_Int();
	}
	sort(p+1,p+n+1);
	for(int i=1; i<=n; i++) {
		while(top>1&&Cross(S[top-1]-S[top],S[top-1]-p[i])>=0)top--;
		S[++top]=p[i];
	}
	if(top==1) {printf("%0.4lf\n",Cal(S[1],Optimalk(S[1])));return 0;}
	double r=Slope(S[1],S[2]),k=Optimalk(S[1]);
	if(k>=r)ans=min(ans,Cal(S[1],k));
	else ans=min(ans,Cal(S[1],r));
	double l=Slope(S[top-1],S[top]);k=Optimalk(S[top]);
	if(k<=l)ans=min(ans,Cal(S[top],k));
	else ans=min(ans,Cal(S[top],l));
	for(int i=2; i<top; i++) {
		l=Slope(S[i-1],S[i]),r=Slope(S[i],S[i+1]),k=Optimalk(S[i]);
		if(k>=l&&k<=r)ans=min(ans,Cal(S[i],k));
		else ans=min(ans,min(Cal(S[i],l),Cal(S[i],r)));
	}
	printf("%0.4lf\n",ans);
	return 0;
}