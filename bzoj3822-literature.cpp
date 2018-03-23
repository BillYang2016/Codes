#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=105;

struct Line {
	double a,b,c;
	int v;
} L[maxn];

struct Point {
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
	Point operator - (const Point &a) const {return Point(x-a.x,y-a.y);}
} p[maxn],vec[maxn],p0;

typedef Point Vector;

double Cross(Vector a,Vector b) {return a.x*b.y-a.y*b.x;}
bool operator < (const Point &a,const Point &b) {return Cross(a-p0,b-p0)<0;}
bool Inplane(Line l,Point p) {return l.a*p.x+l.b*p.y<=l.c;}

Point Intersection(Line x,Line y) {
	x.c*=-1,y.c*=-1;
	double down=x.b*y.a-y.b*x.a;
	return Point((x.c*y.b-y.c*x.b)/down,(x.c*y.a-y.c*x.a)/-down);
}

int n,m,ans=0x3f3f3f3f,f[maxn],g[maxn][maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)scanf("%lf%lf%lf%d",&L[i].a,&L[i].b,&L[i].c,&L[i].v);
	for(int i=1; i<=m; i++)scanf("%lf%lf",&p[i].x,&p[i].y);
	for(int i=1; i<=n; i++) {
		bool bj=1;
		for(int j=1; j<=m; j++)if(!Inplane(L[i],p[j])) {bj=0;break;}
		if(bj)ans=min(ans,L[i].v);
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<i; j++) {
			p0=Intersection(L[i],L[j]);
			int tot=0;
			for(int k=1; k<=m; k++)if(!Inplane(L[i],p[k])&&!Inplane(L[j],p[k]))vec[++tot]=p[k];
			sort(vec+1,vec+tot+1);
			memset(f,0x3f,sizeof(f)),memset(g,0x3f,sizeof(g));
			for(int k=1; k<=n; k++)if(k!=i&&k!=j)
				for(int l=1; l<=tot; l++) {
					if(!Inplane(L[k],vec[l]))continue;
					int r=l;
					while(r<tot&&Inplane(L[k],vec[r+1]))r++;
					g[l][r]=min(g[l][r],L[k].v);
					l=r+1;
				}
			for(int len=tot; len>=2; len--)
				for(int l=1; l+len-1<=tot; l++) {
					int r=l+len-1;
					g[l+1][r]=min(g[l+1][r],g[l][r]);
					g[l][r-1]=min(g[l][r-1],g[l][r]);
				}
			f[0]=0;
			for(int r=1; r<=tot; r++)
				for(int l=0; l<r; l++)
					f[r]=min(f[r],f[l]+g[l+1][r]);
			ans=min(ans,f[tot]+L[i].v+L[j].v);
		}
	printf("%d\n",ans>=0x3f3f3f3f?-1:ans);
	return 0;
}