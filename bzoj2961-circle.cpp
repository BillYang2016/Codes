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

const double eps=1e-8;
const int maxn=500005;

int dcmp(double x) {
	if(fabs(x)<=eps)return 0;
	if(x>eps)return 1;
	return -1;
}

struct Point {
	int opt;
	double x,y,k;
	int id;
	Point(double _x=0.0,double _y=0.0):x(_x),y(_y),opt(-1),k(0),id(0) {}
	Point operator - (const Point& a) {
		return Point(a.x-x,a.y-y);
	}
	bool operator < (const Point& b) const {
		return k<b.k;
	}
} p[maxn],tmp[maxn];

int n;
bool Ans[maxn],Q[maxn];

bool cmp(const Point& a,const Point& b) { //水平序
	return dcmp(a.x-b.x)<0||(dcmp(a.x-b.x)==0&&a.y<b.y);
}

typedef Point Vector;

double Cross(Vector a,Vector b) { //叉积
	return a.x*b.y-b.x*a.y;
}

double Slope(Point a,Point b) {
	if(dcmp(a.x-b.x)==0) {
		if(dcmp(b.y-a.y)>0)return 1e16;
		else return -1e16;
	}
	return (b.y-a.y)/(b.x-a.x);
}

void CDQBinary(int Left,int Right) {
	if(Left==Right)return;
	int mid=(Left+Right)>>1;
	int lpos=Left,rpos=mid+1;
	for(int i=Left; i<=Right; i++)
		if(p[i].id<=mid)tmp[lpos++]=p[i];
		else tmp[rpos++]=p[i];
	for(int i=Left; i<=Right; i++)p[i]=tmp[i];
	CDQBinary(Left,mid);
	static deque<Point>Down,Up;
	Down.clear();
	Up.clear();
	for(int i=mid; i>=Left; i--) { //维护左子区间下凸包
		if(p[i].opt==1)continue;
		while(Down.size()>=2&&dcmp(Cross(Down[Down.size()-2]-Down.back(),Down[Down.size()-2]-p[i]))>=0)Down.pop_back();
		Down.push_back(p[i]);
	}
	for(int i=Left; i<=mid; i++) { //维护左子区间上凸包
		if(p[i].opt==1)continue;
		while(Up.size()>=2&&dcmp(Cross(Up[Up.size()-2]-Up.back(),Up[Up.size()-2]-p[i]))>=0)Up.pop_back();
		Up.push_back(p[i]);
	}
	if(!Up.empty())Up.push_back(Point(Up.back().x+eps,-INT_MAX));
	if(!Down.empty())Down.push_back(Point(Down.back().x-eps,INT_MAX));
	for(int i=Right; i>=mid+1; i--)
		if(p[i].opt&&Ans[p[i].id]) {
			while(Down.size()>=2&&dcmp(Slope(Down[1],Down.front())-p[i].k)>0)Down.pop_front(); //利用下凸包计算右区间询问
			while(Up.size()>=2&&dcmp(Slope(Up.front(),Up[1])-p[i].k)>0)Up.pop_front(); //利用上凸包计算右区间询问
			if(!Down.empty())Ans[p[i].id]&=dcmp(2*p[i].x*Down.front().x+2*p[i].y*Down.front().y-(p[i].x*p[i].x+p[i].y*p[i].y))>=0;
			if(!Up.empty())Ans[p[i].id]&=dcmp(2*p[i].x*Up.front().x+2*p[i].y*Up.front().y-(p[i].x*p[i].x+p[i].y*p[i].y))>=0;
		}
	CDQBinary(mid+1,Right);
	merge(p+Left,p+mid+1,p+mid+1,p+Right+1,tmp,cmp); //水平序
	int tot=0;
	for(int i=Left; i<=Right; i++)p[i]=tmp[tot++];
}

int main() {
	n=Get_Int();
	bool flag=0;
	for(int i=1; i<=n; i++) {
		p[i].opt=Get_Int();
		scanf("%lf%lf",&p[i].x,&p[i].y);
		p[i].id=i;
		if(!p[i].opt) {
			p[i].k=p[i].y/p[i].x;
			flag=1;
		} else { 
			Q[i]=1;
			Ans[i]=flag;
			p[i].k=-p[i].x/p[i].y;
		}
	}
	sort(p+1,p+n+1);
	CDQBinary(1,n);
	for(int i=1; i<=n; i++)
		if(Q[i])puts(Ans[i]?"Yes":"No");
	return 0;
}