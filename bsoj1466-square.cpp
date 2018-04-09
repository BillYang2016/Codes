#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

struct Point {
	int x,y;
	Point(int x=0,int y=0):x(x),y(y) {}
	Point operator - (const Point &a) {return Point(a.x-x,a.y-y);}
	bool operator < (const Point &b) const {return x<b.x||(x==b.x&&y<b.y);}
};

typedef Point Vector;

int Cross(const Vector& a,const Vector& b) {return a.x*b.y-b.x*a.y;}
int dist(const Point &a,const Point &b) {return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);}

int ConvexHull(int n,Point *p,Point *ans) {
	sort(p+1,p+n+1);
	int top=0;
	for(int i=1; i<=n; i++) {
		while(top>1&&Cross(ans[top]-ans[top-1],p[i]-ans[top-1])<=0)top--;
		ans[++top]=p[i];
	}
	int k=top;
	for(int i=n-1; i>=1; i--) {
		while(top>k&&Cross(ans[top]-ans[top-1],p[i]-ans[top-1])<=0)top--;
		ans[++top]=p[i];
	}
	if(n>1)top--;
	return top;
}

int Rotating_Calipers(int n,Point *p) {
	int ans=0;
	p[n+1]=p[1];
	for(int i=1,j=1; i<=n; i++) {
		while(dist(p[j+1],p[i])>=dist(p[j],p[i]))j=j%n+1;
		ans=max(ans,dist(p[i],p[j]));
	}
	return ans;
}

int n,cnt=0;
Point p[maxn<<2],ans[maxn<<2];

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		cnt=0;
		for(int i=1; i<=n; i++) {
			int x=Get_Int(),y=Get_Int(),a=Get_Int();
			p[++cnt]=Point(x,y);
			p[++cnt]=Point(x+a,y);
			p[++cnt]=Point(x,y+a);
			p[++cnt]=Point(x+a,y+a);
		}
		cnt=ConvexHull(cnt,p,ans);
		printf("%d\n",Rotating_Calipers(cnt,ans));
	}
	return 0;
}