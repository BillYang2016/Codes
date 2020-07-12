#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1005;
const double eps=1e-6;

struct Circle {
	int x,y,r,p;
	double dp;
	double left,right; //y轴
	int _left,_right; //x轴
	void get() {
		x=Get_Int();y=Get_Int(),r=Get_Int(),p=Get_Int();
		if(p!=1000)dp=log(1.0-1.0*p/1000);
		_left=x-r,_right=x+r;
	}
	bool operator < (const Circle &b) const {return _left<b._left||(_left==b._left&&_right<b._right);}
} a[maxn];

int n,Must[maxn<<1];
double sum[maxn<<1];

vector<Circle> now;

double f(double x) {
	vector<Circle> circles;
	vector<double> points;
	for(auto c:now)
		if(x>c._left&&x<c._right) {
			double delta=sqrt(c.r*c.r-(c.x-x)*(c.x-x));
			c.left=c.y-delta,c.right=c.y+delta;
			circles.push_back(c);
			points.push_back(c.left),points.push_back(c.right);
		}
	sort(points.begin(),points.end());
	for(int i=0; i<=points.size(); i++)Must[i]=sum[i]=0;
	for(auto c:circles) {
		int left=lower_bound(points.begin(),points.end(),c.left)-points.begin(),right=lower_bound(points.begin(),points.end(),c.right)-points.begin();
		if(c.p==1000) {
			Must[left]++;
			Must[right]--;
		} else {
			sum[left]+=c.dp;
			sum[right]-=c.dp;
		}
	}
	double ans=0;
	for(int i=0; i+1<points.size(); i++) {
		if(i)sum[i]+=sum[i-1],Must[i]+=Must[i-1];
		if(Must[i])ans+=points[i+1]-points[i];
		else ans+=(1-exp(sum[i]))*(points[i+1]-points[i]);
	}
	return ans;
}

double Cal(double Left,double Right) {return (Right-Left)/6*(f(Left)+4*f((Left+Right)/2)+f(Right));}

double Simpson(double Left,double Right,double ans,double eps) {
	double mid=(Left+Right)/2,ans1=Cal(Left,mid),ans2=Cal(mid,Right);
	if(fabs(ans-ans1-ans2)<=15*eps)return ans1+ans2+(ans1+ans2-ans)/15;
	else return Simpson(Left,mid,ans1,eps/2)+Simpson(mid,Right,ans2,eps/2);
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i].get();
	sort(a+1,a+n+1);
	double ans=0;
	int Left=a[1]._left,Right=a[1]._right;
	now.push_back(a[1]);
	for(int i=2; i<=n; i++) {
		if(a[i]._left>Right) {
			ans+=Simpson(Left,Right,Cal(Left,Right),eps);
			Left=a[i]._left;
			now.clear();
		}
		Right=max(Right,a[i]._right);
		now.push_back(a[i]);
	}
	ans+=Simpson(Left,Right,Cal(Left,Right),eps);
	printf("%.10lf\n",ans);
	return 0;
}