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

struct Circle {
	int x,y,r;
} p[5];

double Dist(double x1,double y1,double x2,double y2) {
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

bool Intersection(Circle a,Circle b) {
	return Dist(a.x,a.y,b.x,b.y)<a.r+b.r&&Dist(a.x,a.y,b.x,b.y)>abs(a.r-b.r);
}

int n;

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		p[i].x=Get_Int();
		p[i].y=Get_Int();
		p[i].r=Get_Int();
	}
	if(n==1) {
		puts("2");
		return 0;
	}
	if(n==2) {
		if(Intersection(p[1],p[2]))puts("4");
		else puts("3");
		return 0;
	}
	if(n==3) {
		if(Intersection(p[1],p[2])&&Intersection(p[2],p[3])&&Intersection(p[1],p[3])) {
			puts("8");
			return 0;
		}
		if(!Intersection(p[1],p[2])&&!Intersection(p[2],p[3])&&!Intersection(p[1],p[3])) {
			puts("4");
			return 0;
		}
		if(Intersection(p[1],p[2])&&Intersection(p[2],p[3])&&!Intersection(p[1],p[3])) {
			puts("6");
			return 0;
		}
		if(!Intersection(p[1],p[2])&&Intersection(p[2],p[3])&&Intersection(p[1],p[3])) {
			puts("6");
			return 0;
		}
		if(Intersection(p[1],p[2])&&!Intersection(p[2],p[3])&&Intersection(p[1],p[3])) {
			puts("6");
			return 0;
		}
		puts("5");
	}
	return 0;
}