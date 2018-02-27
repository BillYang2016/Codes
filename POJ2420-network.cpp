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
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const double pi=acos(-1),START_T=50000,END_T=1e-4,DELTA=0.95,P=0.1;
const int maxn=1005,DIV=20000;

struct Point {
	double x,y;
} p[maxn];
int n,Length,Height;

double Dist(Point a,Point b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double get_sum(Point x) {
	double sum=1e18;
	for(int i=1; i<=n; i++)sum=min(sum,Dist(p[i],x));
	return sum;
}

Point Anneal() {
	Point ansp=p[1];
	double t=START_T,ans=get_sum(ansp);
	while(t>END_T) {
		bool bj=1;
		while(bj) {
			bj=0;
			for(int i=0; i<4; i++) {
				double ang=2*pi*(rand()%DIV)/DIV;
				Point now;
				now.x=ansp.x+cos(ang)*t;
				now.y=ansp.y+sin(ang)*t;
				if(now.x<0||now.y<0||now.x>Length||now.y>Height)continue;
				double sum=get_sum(now);
				if(sum>ans||exp(-t/START_T)<P) {
					ans=sum;
					ansp=now;
					bj=1;
				}
			}
		}
		t=t*DELTA;
	}
	return ansp;
}

int main() {
	srand(999599);
	int t=Get_Int();
	while(t--) {
		Length=Get_Int();
		Height=Get_Int();
		n=Get_Int();
		for(int i=1; i<=n; i++) {
			p[i].x=Get_Int();
			p[i].y=Get_Int();
		}
		Point p=Anneal();
		printf("The safest point is (%0.1lf, %0.1lf).\n",p.x,p.y);
	}
	return 0;
} 
