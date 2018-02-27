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
#include<set>

using namespace std;

typedef long long LL;

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

const int maxn=100005;

struct Point {
	LL x,y;
	mutable double k;
	Point(LL x=0,LL y=0,LL k=0):x(x),y(y),k(k) {}
	bool operator < (const Point& b) const {
		if(b.y==1e15)return k<b.k;
		return x<b.x||(x==b.x&&y<b.y);
	}
};

struct Convex_Hull: set<Point> {
	bool bad(iterator it) {
		if(next(it)==end()||it==begin())return false;
		return (double)(it->y-prev(it)->y)*(next(it)->x-prev(it)->x)>=(double)(next(it)->y-prev(it)->y)*(it->x-prev(it)->x);
	}
	void compute(iterator it) {
		if(next(it)==end())it->k=1e15;
		else it->k=(double)(next(it)->y-it->y)/(next(it)->x-it->x);
	}
	void add(Point x) {
		if(find(x)!=end())return;
		auto it=insert(x).first;
		if(bad(it)) {
			erase(it);
			return;
		}
		while(it!=begin()&&bad(prev(it)))erase(prev(it));
		while(next(it)!=end()&&bad(next(it)))erase(next(it));
		compute(it);
		if(it!=begin())compute(prev(it));
	}
	LL query(double k) {
		if(empty())return 1e15;
		auto it=lower_bound(Point(0,1e15,-k));
		return k*it->x+it->y;
	}
} S[maxn];

LL a[maxn],b[maxn],f[maxn];
int n,Size[maxn],Belong[maxn],cnt=0;
vector<int> edges[maxn];

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

void Dfs(int Now,int fa) {
	Size[Now]=1;
	if(edges[Now].size()==1&&fa) {
		f[Now]=0;
		Belong[Now]=++cnt;
		S[cnt].add(Point(b[Now],0));
		return; 
	}
	int son=0;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dfs(Next,Now);
		Size[Now]+=Size[Next];
		if(Size[Next]>Size[son])son=Next;
	}
	Belong[Now]=Belong[son];
	for(int Next:edges[Now]) {
		if(Next==son||Next==fa)continue;
		for(auto it:S[Belong[Next]])S[Belong[Now]].add(it);
		S[Belong[Next]].clear();
	}
	f[Now]=S[Belong[Now]].query(a[Now]);
	S[Belong[Now]].add(Point(b[Now],f[Now]));
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=1; i<=n; i++)b[i]=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y);
		AddEdge(y,x);
	}
	Dfs(1,0);
	for(int i=1; i<=n; i++)printf("%I64d ",f[i]);
	return 0;
}