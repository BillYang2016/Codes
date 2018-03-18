#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const double eps=1e-8;

struct Point {
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
} a,b,c,d;

double P,Q,R;

Point getp(Point a,Point b,double k) {return Point(a.x+(b.x-a.x)*k,a.y+(b.y-a.y)*k);}
double dist(Point a,Point b) {return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
double Cal(Point _a,Point _d) {return dist(a,_a)/P+dist(d,_d)/Q+dist(_a,_d)/R;}

double Cal(Point p) {
	double Left=0,Right=1;
	while(Right-Left>eps) {
		double lmid=Left+(Right-Left)/3,rmid=Right-(Right-Left)/3;
		Point lp=getp(c,d,lmid),rp=getp(c,d,rmid);
		if(Cal(p,lp)<Cal(p,rp))Right=rmid;
		else Left=lmid;
	}
	return Cal(p,getp(c,d,(Left+Right)/2));
}

int main() {
	a.x=Get_Int(),a.y=Get_Int();
	b.x=Get_Int(),b.y=Get_Int();
	c.x=Get_Int(),c.y=Get_Int();
	d.x=Get_Int(),d.y=Get_Int();
	P=Get_Int(),Q=Get_Int(),R=Get_Int();
	double Left=0,Right=1;
	while(Right-Left>eps) {
		double lmid=Left+(Right-Left)/3,rmid=Right-(Right-Left)/3;
		Point lp=getp(a,b,lmid),rp=getp(a,b,rmid);
		if(Cal(lp)<Cal(rp))Right=rmid;
		else Left=lmid;
	}
	printf("%0.2lf\n",Cal(getp(a,b,(Left+Right)/2)));
	return 0;
}