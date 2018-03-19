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

const int maxn=55;
const double eps=1e-9,pi=acos(-1),inf=1e8;

int dcmp(double x) {return fabs(x)<=eps?0:(x>eps?1:-1);}

struct Point {
	double x,y,z;
	Point(double x=0,double y=0,double z=0):x(x),y(y),z(z) {}
	Point operator + (const Point &a) {return Point(x+a.x,y+a.y,z+a.z);}
	Point operator - (const Point &a) {return Point(x-a.x,y-a.y,z-a.z);}
	Point operator * (double a) {return Point(x*a,y*a,z*a);}
	Point operator / (double a) {return Point(x/a,y/a,z/a);}
	double length() {return sqrt(x*x+y*y+z*z);}
	void tozero() {double len=length();x/=len,y/=len,z/=len;}
};

typedef Point Vector;

double Dot(Vector a,Vector b) {return a.x*b.x+a.y*b.y+a.z*b.z;}
double Angle(Vector a,Vector b) {return acos(Dot(a,b)/a.length()/b.length());}

struct Line { //directed line
	Point p;
	Vector v;
	Line() {}
	Line(Point p,Vector v):p(p),v(v) {}
};

double dist1(Line l,Point p) {return (l.p-p).length()*sin(Angle(p-l.p,l.v));}
double dist2(Line l,Point p) {return (l.p-p).length()*cos(Angle(p-l.p,l.v));}

struct Circle:Point {
	double r;
	int id;
	Circle(double x=0,double y=0,double z=0,double r=0,int id=0):Point(x,y,z),r(r),id(id) {}
} c[maxn];

bool Intersect(Line l,Circle p) {
	return dcmp(dist1(l,p)-p.r)<=0&&dcmp(Angle(l.v,p-l.p)-pi/2)<0;
}

double distance(Line l,Circle p) {
	if(!Intersect(l,p))return inf;
	double d1=dist1(l,p),d2=dist2(l,p);
	double d3=!dcmp(p.r-d1)?0:sqrt(p.r*p.r-d1*d1);
	return d2-d3;
}

Line bounce(Line l,Circle p) {
	Point xyj=l.p+l.v*distance(l,p);
	double ang=Angle(l.v,p-xyj);
	Vector ans=l.p-xyj;
	Vector v=xyj-p;v.tozero();
	v=v*Dot(v,ans);
	Vector delta=v-ans;
	l.p=xyj;
	l.v=ans+delta*2;
	l.v.tozero();
	return l;
}

int n;
Line l;

bool cmp(Circle a,Circle b) {return distance(l,a)<distance(l,b);}

int main() {
	n=Get_Int();
	double x,y,z,r,x0,y0,z0,x1,y1,z1;
	for(int i=1; i<=n; i++) {
		scanf("%Lf%Lf%Lf%Lf",&x,&y,&z,&r);
		c[i]=Circle(x,y,z,r,i);
	}
	scanf("%Lf%Lf%Lf%Lf%Lf%Lf",&x0,&y0,&z0,&x1,&y1,&z1);
	l=Line(Point(x0,y0,z0),Point(x1,y1,z1)-Point(x0,y0,z0));
	l.v.tozero();
	vector<int> ans;
	while(ans.size()<=10) {
		sort(c+1,c+n+1,cmp);
		if(distance(l,c[1])>=inf/2)break;
		ans.push_back(c[1].id);
		l=bounce(l,c[1]);
	}
	for(int i=0; i<min((int)ans.size(),10); i++)printf("%d ",ans[i]);
	if(ans.size()>10)puts("etc.");
	return 0;
}