#include<bits/stdc++.h>

using namespace std;

struct Point {
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y) {}
	double length() {return sqrt(x*x+y*y);}
	Point operator - (const Point b) const {return Point(x-b.x,y-b.y);}
} p;

struct Circle : Point {
	double r;
	Circle(double _x=0,double _y=0,double _r=0):Point(_x,_y),r(_r) {}
	Point getPoint(const double &a) const {return Point(x+r*cos(a),y+r*sin(a));} //以圆心为原点，a为极角，对应的圆上的点
} c1,c2,ic1,ic2;

const double R=1;

double sqr(double x) {return x*x;}

double Cross(const Point &a,const Point &b) {return a.x*b.y-b.x*a.y;}

double dist(const Point &a,const Point &b) {return (a-b).length();}

Point Root(const Point &p,const Point &st,const Point &ed) { //求垂足
	double u=(sqr(ed.x-st.x)+sqr(ed.y-st.y));
	u=((ed.x-st.x)*(ed.x-p.x)+(ed.y-st.y)*(ed.y-p.y))/u;
	return Point(u*st.x+(1-u)*ed.x,u*st.y+(1-u)*ed.y);
}

double DistanceToLine(const Point &p,const Point &a,const Point &b) {Point v1=a-b,v2=a-p;return fabs(Cross(v1,v2))/v1.length();}

Circle inv(const Circle &c) { //不过中心圆的反演->不过中心圆
	double d=dist(c,p),s=sqr(R)/(d-c.r),t=sqr(R)/(d+c.r);
	double r=(s-t)/2;
	return Circle(p.x+(c.x-p.x)/d*(t+r),p.y+(c.y-p.y)/d*(t+r),r);
}

Circle inv(const Point &a,const Point &b) { //不过中心直线反演->过中心圆
	Point w=Root(p,a,b); //垂足
	double r=sqr(R)/DistanceToLine(p,a,b)/2,d=DistanceToLine(p,a,b);
	return Circle(p.x+r/d*(w.x-p.x),p.y+r/d*(w.y-p.y),r);
}

vector<Point> st,ed;

const double eps=1e-10;

int sgn(double x) {return (x>eps)-(x<-eps);}

bool sameSide(const Point &a,const Point &b,const Point &s,const Point &t) {return sgn(Cross(s-a,t-a))==sgn(Cross(s-b,t-b));}

void getTangents(const Circle &a,const Circle &b) {
	st.clear();ed.clear();
	double base=atan2(b.y-a.y,b.x-a.x),d=dist(a,b),ang=acos((a.r-b.r)/d);
	st.push_back(a.getPoint(base-ang));ed.push_back(b.getPoint(base-ang));
	if(!sameSide(p,a,st.back(),ed.back()))st.pop_back(),ed.pop_back();
	st.push_back(a.getPoint(base+ang));ed.push_back(b.getPoint(base+ang));
	if(!sameSide(p,a,st.back(),ed.back()))st.pop_back(),ed.pop_back();
}

int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		scanf("%lf%lf%lf%lf%lf%lf",&c1.x,&c1.y,&c1.r,&c2.x,&c2.y,&c2.r);
		scanf("%lf%lf",&p.x,&p.y);
		ic1=inv(c1);ic2=inv(c2);
		getTangents(ic1,ic2);
		printf("%d\n",st.size());
		for(int i=0; i<st.size(); i++) {
			Circle c=inv(st[i],ed[i]);
			printf("%lf %lf %lf\n",c.x,c.y,c.r);
		}
	}
	return 0;
}