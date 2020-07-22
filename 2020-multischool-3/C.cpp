#include<bits/stdc++.h>

using namespace std;

const int maxn=25;
const double eps=1e-2;

int dcmp(double x) {return fabs(x)<=eps?0:x>eps?1:-1;}

struct Point {
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
	Point operator - (const Point &a) {return Point(a.x-x,a.y-y);} //attention reversed!
	bool operator < (const Point &b) const {return x<b.x||(x==b.x&&y<b.y);}
	double length() {return sqrt(x*x+y*y);}
} a[maxn],ans[maxn];

typedef Point Vector;

double Cross(const Vector& a,const Vector& b) {return a.x*b.y-b.x*a.y;}

double Dist(Point a,Point b) {return (a-b).length();}

int ConvexHull(int n,Point* p,Point* ans) {
	sort(p+1,p+n+1);
	int top=0;
	for(int i=1; i<=n; i++) {
		while(top>1&&dcmp(Cross(ans[top]-ans[top-1],p[i]-ans[top-1]))<=0)top--;
		ans[++top]=p[i];
	}
	int k=top;
	for(int i=n-1; i>=1; i--) {
		while(top>k&&dcmp(Cross(ans[top]-ans[top-1],p[i]-ans[top-1]))<=0)top--;
		ans[++top]=p[i];
	}
	if(n>1)top--;
	return top;
}

int n;

int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		n=20;
		for(int i=1; i<=n; i++)scanf("%lf%lf",&a[i].x,&a[i].y);
		n=ConvexHull(n,a,ans);
		for(int i=1; i<=n; i++) {
			double d1=Dist(ans[i],ans[i%n+1]),d2=Dist(ans[i%n+1],ans[i%n+2]);
			if(dcmp(d1-9)==0&&dcmp(d2-8)==0) {puts("right");break;}
			if(dcmp(d1-8)==0&&dcmp(d2-9)==0) {puts("left");break;}
		}
	}
	return 0;
}