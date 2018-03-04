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

const int maxn=105;

struct Point {
	LL x,y;
	Point(LL x=0,LL y=0):x(x),y(y) {}
	bool operator < (const Point &b) const {
		return x<b.x||(x==b.x&&y<b.y);
	}
} tmp[maxn];

struct Circle:Point {
	LL v;
	Circle(LL x=0,LL y=0,LL v=0):Point(x,y),v(v) {}
} c[maxn];

LL n,m,R,f[maxn][maxn][maxn];
vector<Point> p;
vector<Circle> up,down;

bool inCircle(Point a,Point b) {
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)<=R*R;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	R=Get_Int();
	for(int i=1; i<=n; i++)tmp[i].x=Get_Int(),tmp[i].y=Get_Int();
	for(int i=1; i<=m; i++) {
		c[i].x=Get_Int(),c[i].y=Get_Int(),c[i].v=Get_Int();
		if(c[i].y>R)up.push_back(c[i]);
		else down.push_back(c[i]);
	}
	for(int i=1; i<=n; i++) {
		bool bj=0;
		for(int j=1; j<=m; j++)
			if(inCircle(tmp[i],c[j])) {
				bj=1;
				break;
			}
		if(bj)p.push_back(tmp[i]);
	}
	p.push_back(Point()),up.push_back(Circle()),down.push_back(Circle());
	sort(p.begin(),p.end());
	sort(up.begin(),up.end());
	sort(down.begin(),down.end());
	memset(f,0x3f,sizeof(f));
	f[0][0][0]=0;
	for(int i=0; i<p.size(); i++)
		for(int j=0; j<up.size(); j++)
			for(int k=0; k<down.size(); k++) {
				Point nowp=p[i+1];
				if((j&&inCircle(nowp,up[j]))||(k&&inCircle(nowp,down[k])))f[i+1][j][k]=min(f[i+1][j][k],f[i][j][k]);
				for(int l=j+1; l<up.size(); l++)if(inCircle(nowp,up[l]))f[i+1][l][k]=min(f[i+1][l][k],f[i][j][k]+up[l].v);
				for(int l=k+1; l<down.size(); l++)if(inCircle(nowp,down[l]))f[i+1][j][l]=min(f[i+1][j][l],f[i][j][k]+down[l].v);
			}
	LL ans=LLONG_MAX;
	for(int i=0; i<up.size(); i++)
		for(int j=0; j<down.size(); j++)
			ans=min(ans,f[p.size()-1][i][j]);
	printf("%d\n%lld\n",p.size()-1,ans);
	return 0;
}