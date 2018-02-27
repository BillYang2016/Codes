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

const int maxn=605,maxm=360005;
const double eps=1e-8;

double dcmp(double x) {
	if(fabs(x)<=eps)return 0;
	if(x>eps)return 1;
	return -1;
}

struct Point {
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y) {}
	Point operator + (const Point& a) const {
		return Point(x+a.x,y+a.y);
	}
	Point operator - (const Point& a) const {
		return Point(a.x-x,a.y-y);
	}
	Point operator / (double a) const {
		return Point(x/a,y/a);
	}
} p[maxn],lim,st;

typedef Point Vector;

double Cross(const Vector& a,const Vector& b) {
	return a.x*b.y-b.x*a.y;
}

vector<int> edges[maxn];

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

struct Line {
	Point p;
	Vector v;
	double ang;
	int id;
	Line() {}
	Line(Point p,Vector v,int x):p(p),v(v),id(x) {
		ang=atan2(v.y,v.x);
	}
	bool operator < (const Line& L) const {
		return ang<L.ang;
	}
};

bool OnLeft(Line L,Point p) { 
	return dcmp(Cross(L.v,L.p-p))>0;
}

Point GetIntersection(Line a,Line b) {
	Vector u=a.p-b.p;
	double t=Cross(u,b.v)/Cross(a.v,b.v);
	return a.p+a.v*t;
}

void HalfplaneIntersection(int n,Line* L,int s) {
	sort(L+1,L+n+1);
	int first=1,last=1;
	static Point p[n+5];
	static Line q[n+5];
	q[last]=L[1];
	for(int i=2; i<=n; i++) {
		while(first<last&&!OnLeft(L[i],p[last-1]))last--;
		while(first<last&&!OnLeft(L[i],p[first]))first++;
		q[++last]=L[i];
		if(fabs(Cross(q[last].v,q[last-1].v))<eps) { 
			last--;
			if(!OnLeft(L[i],p[last-1]))q[last]=L[i];
		}
		if(first<last)p[last-1]=GetIntersection(q[last-1],q[last]);
	}
	while(first<last&&!OnLeft(q[first],p[last-1]))last--;
	if(last-first<=1)return;
	for(int i=first; i<=last; i++)AddEdge(s,q[i].id);
	if(!S) {
		bool bj=1;
		for(int i=first; i<=last; i++)
			if(!OnLeft(q[i],st)) {
				bj=0;
				break;
			}
		if(bj)S=s;
	}
}

int cnt=0;
Line L[maxm];

void build(int s) {
	cnt=0;
	for(int i=1; i<=n; i++)
		if(i!=s) {
			Point mid=(p[s]+p[i])/2;
			Vector pos=Vector(-mid.y,pos.x);
			L[++cnt]=Line(mid,pos,i);
		}
	L[++cnt]=Line(Point(0,0),Vector(0,-1),0);
	L[++cnt]=Line(Point(0,lim.y),Vector(-1,0),0);
	L[++cnt]=Line(lim,Vector(0,1),0);
	L[++cnt]=Line(Point(lim.x,0),Vector(1,0),0);
	HalfplaneIntersection(cnt,L,s);
}

#define mp make_pair
#define pii pair<int,int>

int Dist[maxn];
bool vst[maxn];

void Dijkstra(int s) {
	for(int i=0; i<=n; i++)Dist[0]=INT_MAX,vst[i]=0;
	priority_queue<pii> Q;
	Dist[s]=0;
	Q.push(mp(0,s));
	while(!Q.empty()) {
		int Now=Q.top().second;
		Q.pop();
		if(vst[Now])continue;
		vst[Now]=1;
		for(int Next:edges[Now])
			if(Dist[Next]>Dist[Now]+1) {
				Dist[Next]=Dist[Now]+1;
				Q.push(mp(Dist[Next],Next));
			}
	}
}

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		lim.x=Get_Int(),lim.y=Get_Int();
		st.x=Get_Int(),st.y=Get_Int();
		for(int i=1; i<=n; i++) {
			p[i].x=Get_Int(),p[i].y=Get_Int();
			edges[i].clear();
		}
		S=0;
		for(int i=1; i<=n; i++)build(i);
		Dijkstra(S);
		printf("%d\n",Dist[0]);
	}
	return 0;
} 
