#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=50005;
const double eps=1e-8;

int dcmp(double x) {
	if(fabs(x)<=eps)return 0;
	return x>eps?1:-1;
}

struct Point {
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
	Point operator + (const Point &a) {return Point(x+a.x,y+a.y);}
	Point operator - (const Point &a) {return Point(a.x-x,a.y-y);} //attention reversed!
	Point operator * (double a) {return Point(x*a,y*a);}
	Point operator / (double a) {return Point(x/a,y/a);}
	bool operator < (const Point &b) const {return x<b.x||(x==b.x&&y<b.y);}
	double length() {return sqrt(x*x+y*y);}
};

typedef Point Vector;

double Cross(const Vector& a,const Vector& b) {return a.x*b.y-b.x*a.y;}
double Dot(Vector a,Vector b) {return a.x*b.x+a.y*b.y;}

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

Point p[maxn],a[maxn],Ans[4];
int n;
double ans=1e18;

double Rotating_Calipers() {
	a[n+1]=a[1];
	int l=2,r=2,u=2;
	for(int i=1; i<=n; i++) {
		Vector x=a[i]-a[i+1];
		while(dcmp(Dot(x,a[i]-a[r+1])-Dot(x,a[i]-a[r]))>=0)r=r%n+1;
		while(dcmp(Cross(x,a[i]-a[u+1])-Cross(x,a[i]-a[u]))>=0)u=u%n+1;
		if(i==1)l=u; //初值
		while(dcmp(Dot(x,a[i]-a[l+1])-Dot(x,a[i]-a[l]))<=0)l=l%n+1;
		double wid=(abs(Dot(x,a[i]-a[l]))+Dot(x,a[i]-a[r]))/x.length(),hei=Cross(x,a[i]-a[u])/x.length();
		if(ans>wid*hei) {
			ans=wid*hei;
			Ans[0]=a[i]+x*(Dot(x,a[i]-a[r])/(Dot(x,x)));
			Ans[1]=Ans[0]+(Ans[0]-a[r])*(hei/(Ans[0]-a[r]).length());
			Ans[2]=Ans[1]+(Ans[1]-a[u])*(wid/(Ans[1]-a[u]).length());
			Ans[3]=Ans[2]+(Ans[2]-a[l])*(hei/(Ans[2]-a[l]).length());
		}
	}
	return ans;
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)scanf("%lf%lf",&p[i].x,&p[i].y);
	sort(p+1,p+n+1);
	n=ConvexHull(n,p,a);
	printf("%0.5lf\n",Rotating_Calipers());
	int fir=0;
	for(int i=1; i<=3; i++)if(Ans[i].y<Ans[fir].y||(Ans[i].y==Ans[fir].y&&Ans[i].x<Ans[fir].x))fir=i;
	for(int i=0; i<4; i++)printf("%0.5lf %0.5lf\n",Ans[(fir+i)%4].x,Ans[(fir+i)%4].y);
	return 0;
}