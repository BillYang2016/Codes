#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const double eps=1e-8,pi=acos(-1);

int dcmp(double x) {
	if(fabs(x)<eps)return 0;
	return x<eps?-1:1;
}

struct Point {
	double x,y;
	Point(double x0=0,double y0=0):x(x0),y(y0) {}
};

double Dist(const Point &a,const Point &b) {return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}

struct Circle {
	Point p;
	double r;
	Circle(Point _p=Point(),double r0=0):p(_p),r(r0) {}
};

int Circle_Intersection(const Circle &a,const Circle &b) { //判断圆相交状态
	double dist=Dist(a.p,b.p);
	if(dcmp(dist-(a.r+b.r))>=0)return 1; //不相交或者外切
	if(dcmp(dist-fabs(a.r-b.r))<0)return -2; //内含
	if(dcmp(dist-fabs(a.r-b.r))==0)return -1; //内切
	return 0; //相交
}

int main() {
	int t=Get_Int();
	while(t--) {
		int n=Get_Int();
		double r;
		scanf("%lf",&r);
		Circle Big=Circle(Point(0,0),r);
		double ans=2*pi*r;
		for(int i=1; i<=n; i++) {
			double x,y,r;
			scanf("%lf%lf%lf",&x,&y,&r);
			Circle Small=Circle(Point(x,y),r);
			int status=Circle_Intersection(Big,Small);
			if(status>0||status<-1)continue;
			if(status==-1) {ans+=2*pi*r;continue;}
			double dist=Dist(Big.p,Small.p);
			double alpha1=(Big.r*Big.r+dist*dist-Small.r*Small.r)/(2*Big.r*dist),alpha2=(Small.r*Small.r+dist*dist-Big.r*Big.r)/(2*Small.r*dist);
			ans+=2*acos(alpha2)*Small.r-2*acos(alpha1)*Big.r;
		}
		printf("%.8lf\n",ans);
	}
	return 0;
}