#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=200005;
const double eps=1e-8;

int dcmp(double x) {return fabs(x)<=eps?0:x>eps?1:-1;}

struct Point {
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
	Point operator + (const Point &a) const {return Point(x+a.x,y+a.y);}
	Point operator - (const Point &a) const {return Point(a.x-x,a.y-y);}
	Point operator * (double a) const {return Point(x*a,y*a);}
	Point operator / (double a) const {return Point(x/a,y/a);}
};

typedef Point Vector;

double Cross(const Vector &a,const Vector &b) {return a.x*b.y-b.x*a.y;}

struct Line {
	Point p;
	Vector v;
	double ang;
	Line() {}
	Line(Point p,Vector v):p(p),v(v) {ang=atan2(v.y,v.x);}
	bool operator < (const Line &b) const {return ang<b.ang;}
};

bool OnLeft(Line L,Point p) {return dcmp(Cross(L.v,L.p-p))>=0;}

Point GetIntersection(Line a,Line b) {
	Vector u=a.p-b.p;
	double t=Cross(u,b.v)/Cross(a.v,b.v);
	return a.p+a.v*t;
}

double Area(Point a,Point b,Point c) {return Cross(a-b,a-c);}

double Area(int n,Point *p) {
	double ans=0;
	for(int i=2; i<n; i++)ans+=Area(p[1],p[i],p[i+1]);
	return ans/2;
}

int Unique(int n,Line *L) {
	int cnt=1;
	for(int i=2; i<=n; i++) {
		if(dcmp(L[cnt].ang-L[i].ang))L[++cnt]=L[i];
		else if(OnLeft(L[cnt],L[i].p))L[cnt]=L[i];
	}
	return cnt;
}

int HalfplaneIntersection(int n,Line *L,Point *poly) {
	sort(L+1,L+n+1);
	n=Unique(n,L);
	int first=1,last=1;
	static Point p[maxn];
	static Line q[maxn+5];
	q[last]=L[1];
	for(int i=2; i<=n; i++) {
		while(first<last&&!OnLeft(L[i],p[last-1]))last--;
		while(first<last&&!OnLeft(L[i],p[first]))first++;
		q[++last]=L[i];
		if(first<last)p[last-1]=GetIntersection(q[last-1],q[last]);
	}
	while(first<last&&!OnLeft(q[first],p[last-1]))last--;
	if(last-first<=1)return 0;
	p[last]=GetIntersection(q[last],q[first]);
	int m=0;
	for(int i=first; i<=last; i++)poly[++m]=p[i];
	return m;
}

int n,cnt=0;
Point p[maxn],ans[maxn];
Line L[maxn];

int main() {
	n=Get_Int();
	for(int i=0; i<n; i++) {
		p[i].x=Get_Int();
		p[i].y=Get_Int();
	}
	p[n]=p[0];
	for(int i=0; i<n; i++)L[++cnt]=Line(p[i],p[i]-p[i+1]);
	for(int i=1; i<n; i++) {
		double a=p[1].y-p[0].y-p[i+1].y+p[i].y,b=p[0].x-p[1].x-p[i].x+p[i+1].x,c=p[1].x*p[0].y-p[0].x*p[1].y-p[i+1].x*p[i].y+p[i].x*p[i+1].y;
		if(dcmp(b))L[++cnt]=Line(Point(0,-c/b),Vector(b,-a));
		else if(dcmp(a))L[++cnt]=Line(Point(-c/a,0),Vector(0,-a));
	}
	int tot=HalfplaneIntersection(cnt,L,ans);
	printf("%0.4lf\n",Area(tot,ans)/Area(n,p));
	return 0;
}