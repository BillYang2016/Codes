#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const double eps=1e-5,pi=acos(-1);

int dcmp(double x) {return fabs(x)<=eps?0:x>eps?1:-1;}

struct Point {
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
	Point operator + (const Point &a) {return Point(x+a.x,y+a.y);}
	Point operator - (const Point &a) {return Point(x-a.x,y-a.y);}
	Point operator * (double a) {return Point(x*a,y*a);}
	Point operator / (double a) {return Point(x/a,y/a);}
	bool operator < (const Point &b) const {return x<b.x||(x==b.x&&y<b.y);}
	bool operator == (Point b) {return dcmp(x-b.x)==0&&dcmp(y-b.y)==0;}
	double length() {return sqrt(x*x+y*y);}
	Point rotate(double rad) {return Point(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));} //anticlockwise
	Point normal(Point a) {return Point(-a.y/a.length(),a.x/a.length());} //normal vector
};

typedef Point Vector; //only for code convenience

double Cross(const Vector& a,const Vector& b) {return a.x*b.y-b.x*a.y;}
double Dot(Vector a,Vector b) {return a.x*b.x+a.y*b.y;}
double Angle(Vector a,Vector b) {return acos(Dot(a,b)/a.length()/b.length());}
double Area(Point a,Point b,Point c) {return Cross(a-b,a-c);}

Point GetLineIntersection(Point P,Vector v,Point Q,Vector w) {return P+v*(Cross(Q-P,w)/Cross(v,w));}
bool Segment_Intersection(Point a1,Point a2,Point b1,Point b2) {return dcmp(Cross(a1-a2,a1-b1))*dcmp(Cross(a1-a2,a1-b2))<=0&&dcmp(Cross(b1-b2,b1-a1))*dcmp(Cross(b1-b2,b1-a2))<=0;} //if segments (a1->a2,b1->b2) are intersected

Vector rev(Vector a,Vector b) { //a关于b法向量对称
	if(dcmp(Dot(a,b))==0)return a*-1; //平行
	double ang=Angle(a,b);
	if(dcmp(ang-pi/2)>0)return (a*-1).rotate(2*pi-2*Angle(a,b.rotate(pi/2))); //钝角
	else return (a*-1).rotate(2*Angle(a,b.rotate(pi/2))); //锐角
}

#define pii pair<Point,Point>

Point Q[5],w[5];

double Collide(Point &P,Vector &v) {
	for(int id=0; id<3; id++) {
		if(dcmp(Cross(v,w[id]))==0)continue;
		Point i=GetLineIntersection(P,v,Q[id],w[id]);
		if(Dot(i-P,v)<=eps)continue;
		if(!Segment_Intersection(P,i,Q[id],Q[(id+1)%3]))continue;
		double t=(P-i).length()/v.length();
		P=i;
		v=rev(v,w[id]);
		return t;
	}
	return 0;
}

vector<pii> vec;
double Time[1000005];

int main() {
	int t=Get_Int();
	while(t--) {
		vec.clear();
		double L=Get_Int(),x=Get_Int(),y=Get_Int(),vx=Get_Int(),vy=Get_Int(),k=Get_Int();
		Vector v=Vector(vx,vy);
		Point p=Point(x,y);
		Q[0]=Point(L/2,0);w[0]=Vector(-1,0);
		Q[1]=Point(-L/2,0);w[1]=Vector(1,sqrt(3));
		Q[2]=Point(0,L/2*sqrt(3));w[2]=Vector(1,-sqrt(3));
		int cnt=0;
		double t=0,stt=Collide(p,v);
		k--;
		while(cnt<=k) {
			bool flag=0;
			for(auto it:vec)if(dcmp((it.first-p).x)==0&&dcmp((it.first-p).y)==0&&dcmp((it.second-v).x)==0&&dcmp((it.second-v).y)==0) {flag=1;break;}
			if(flag)break;
			vec.push_back(pii(p,v));
			int tmpt=t;
			t+=Collide(p,v);
			Time[++cnt]=t;
			cout<<p.x<<" "<<p.y<<"..."<<v.x<<" "<<v.y<<"---"<<t-tmpt<<endl;
		}
		t=t*((int)k/cnt)+Time[(int)k%cnt]+stt;
		printf("%.8lf\n",t);
	}
	return 0;
}