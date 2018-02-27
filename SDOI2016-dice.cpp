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

inline const int Get_Int() {
	int num=0,bj=1;
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

const int maxn=105;
const double pi=acos(-1);

struct Point {
	double x,y,z;
	Point(double x=0,double y=0,double z=0):x(x),y(y),z(z) {}
	Point operator + (const Point& b) {
		return Point(x+b.x,y+b.y,z+b.z);
	}
	void operator += (const Point& b) {
		*this=*this+b;
	}
	Point operator - (const Point& b) {
		return Point(x-b.x,y-b.y,z-b.z);
	}
	void operator -= (const Point& b) {
		*this=*this-b;
	}
	Point operator * (double c) {
		return Point(x*c,y*c,z*c);
	}
	void operator *= (double c) {
		*this=*this*c;
	}
	Point operator / (double c) {
		return Point(x/c,y/c,z/c);
	}
	void operator /= (double c) {
		*this=*this/c;
	}
	double length() {
		return sqrt(x*x+y*y+z*z);
	}
} p[maxn];

typedef Point Vector;

double Dot(Vector a,Vector b) {
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

Vector Cross(Vector a,Vector b) {
	return Vector(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}

double Triple(Vector a,Vector b,Vector c) {
	return Dot(a,Cross(b,c));
}

double Cal(Vector a,Vector b,Vector c) {
	Vector u=Cross(a,b),v=Cross(a,c);
	return acos(Dot(u,v)/u.length()/v.length());
}

int n,f,F[maxn][maxn];

int main() {
	n=Get_Int();
	f=Get_Int();
	for(int i=1; i<=n; i++) {
		double x,y,z;
		scanf("%lf%lf%lf",&x,&y,&z);
		p[i]=Point(x,y,z);
	}
	for(int i=1; i<=f; i++) {
		F[i][0]=Get_Int();
		for(int j=1; j<=F[i][0]; j++)F[i][j]=Get_Int();
	}
	double vol=0;
	Vector ctr;
	for(int i=1; i<=f; i++)
		for(int j=2; j<F[i][0]; j++) {
			Vector ci=p[F[i][1]]+p[F[i][j]]+p[F[i][j+1]];
			double vi=Triple(p[F[i][1]],p[F[i][j]],p[F[i][j+1]]);
			vol+=vi;
			ctr+=ci*vi;
		}
	ctr/=vol*4;
	for(int i=1; i<=n; i++)p[i]-=ctr;
	for(int i=1; i<=f; i++) {
		double ans=0;
		for(int j=2; j<F[i][0]; j++)ans+=Cal(p[F[i][j]],p[F[i][j-1]],p[F[i][j+1]]);
		ans+=Cal(p[F[i][F[i][0]]],p[F[i][F[i][0]-1]],p[F[i][1]])+Cal(p[F[i][1]],p[F[i][F[i][0]]],p[F[i][2]]);
		printf("%0.7lf\n",(ans-(F[i][0]-2)*pi)/(4*pi));
	}
	return 0;
}