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
	if(fabs(x)<eps)return 0;
	return x>eps?1:-1;
}

struct Point {
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y) {}
	Point operator - (const Point& b) {
		return Point(b.x-x,b.y-y);
	}
	bool operator < (const Point& b) const {
		return dcmp(x-b.x)<0||(dcmp(x-b.x)==0&&y<b.y);
	}
} p[maxn];

typedef Point Vector;

double Cross(Vector a,Vector b) { //叉积
	return a.x*b.y-b.x*a.y;
}

double Dot(Vector a,Vector b) { //点积
	return a.x*b.x+a.y*b.y;
}

struct Group {
	int Left,Right,size;
	vector<Point>Up,Down;
	Group(int l=0,int r=0):Left(l),Right(r),size(r-l+1) {
		Up=Down=vector<Point>();
	}
	void Scan() {
		for(int i=Right; i>=Left; i--) {
			while(Down.size()>=2&&dcmp(Cross(Down[Down.size()-2]-Down.back(),Down[Down.size()-2]-p[i]))>=0)Down.pop_back();
			Down.push_back(p[i]);
		}
		for(int i=Left; i<=Right; i++) {
			while(Up.size()>=2&&dcmp(Cross(Up[Up.size()-2]-Up.back(),Up[Up.size()-2]-p[i]))>=0)Up.pop_back();
			Up.push_back(p[i]);
		}
		if(!Up.empty())Up.push_back(Point(Up.back().x+eps,-INT_MAX));
		if(!Down.empty())Down.push_back(Point(Down.back().x-eps,INT_MAX));
	}
	void build() {
		sort(p+Left,p+Right+1);
		Up.clear();
		Down.clear();
		Scan();
	}
	bool query(Point q) {
		Point ans;
		if(q.y<0) {
			int left=0,right=Up.size()-2;
			while(left<=right) {
				int mid=(left+right)>>1;
				if(dcmp(Dot(Up[mid]-Up[mid+1],q))>=0)right=mid-1;
				else left=mid+1;
			}
			ans=Up[left];
		} else {
			int left=0,right=Down.size()-2;
			while(left<=right) {
				int mid=(left+right)>>1;
				if(dcmp(Dot(Down[mid+1]-Down[mid],q))<=0)right=mid-1;
				else left=mid+1;
			}
			ans=Down[left];
		}
		return dcmp(2*q.x*ans.x+2*q.y*ans.y-(q.x*q.x+q.y*q.y))>=0;
	}
};

vector<Group>G;

int n=0,tot=0;

void insert(Point New) {
	p[++n]=New;
	G.push_back(Group(n,n));
	while(G.size()>=2&&G.back().size==G[G.size()-2].size) {
		G.pop_back();
		G.back()=Group(G.back().Left,n);
	}
	G.back().build();
}

bool query(Point q) {
	if(!n)return 0;
	bool flag=1;
	for(auto& g:G) {
		flag=g.query(q);
		if(!flag)break;
	}
	if(flag)tot++;
	return flag;
}

int main() {
	int t=Get_Int();
	for(int i=1; i<=t; i++) {
		int opt=Get_Int();
		double x,y;
		scanf("%lf%lf",&x,&y);
		x+=tot,y+=tot;
		if(!opt)insert(Point(x,y));
		else puts(query(Point(x,y))?"Yes":"No");
	}
	return 0;
}