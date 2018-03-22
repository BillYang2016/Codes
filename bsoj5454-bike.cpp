#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

struct Point {
	LL x,y;
	Point(LL x=0,LL y=0):x(x),y(y) {}
};

double Slope(Point a,Point b) {
	if(b.x-a.x==0) {return b.y>a.y?LLONG_MAX:LLONG_MIN;}
	return (double)(b.y-a.y)/(b.x-a.x);
}

struct Queue {
	Point Q[maxn];
	int Left,Right;
	Queue() {Left=1,Right=0;}
	void pop(LL k) {while(Left<Right&&Slope(Q[Left],Q[Left+1])<k)Left++;}
	void push(Point p) {
		while(Left<Right&&Slope(Q[Right-1],Q[Right])>=Slope(Q[Right],p))Right--;
		Q[++Right]=p;
	}
	Point top() {return Q[Left];}
} Q1[25],Q2[25];

int n,K;
LL a[maxn],l[maxn],sum[maxn],f[maxn][25],g[maxn][25];

int main() {
	n=Get_Int();
	K=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=2; i<=n; i++)l[i]=l[i-1]+Get_Int();
	for(int i=1; i<=n; i++)sum[i]=sum[i-1]+a[i]*l[i];
	for(int i=1; i<=n; i++)a[i]+=a[i-1];
	Q1[0].push(Point(a[0],g[0][0]+sum[0]));
	Q2[0].push(Point(l[0],f[0][0]-sum[0]+a[0]*l[0])); //(0,0)
	for(int j=1; j<=K; j++) {
		Q1[j].push(Point(a[0],g[0][j]+sum[0]));
		Q2[j].push(Point(l[0],f[0][j]-sum[0]+a[0]*l[0])); //(0,0)
		for(int i=1; i<=n; i++) {
			Q1[j-1].pop(l[i]);
			Point p=Q1[j-1].top();
			f[i][j]=p.y-p.x*l[i]+a[i]*l[i]-sum[i];
			Q2[j].pop(a[i]);
			p=Q2[j].top();
			g[i][j]=min(p.y-p.x*a[i]+sum[i],f[i][j]);
			Q1[j].push(Point(a[i],g[i][j]+sum[i]));
			Q2[j].push(Point(l[i],f[i][j]-sum[i]+a[i]*l[i]));
		}
	}
	LL ans=LLONG_MAX/2;
	for(int i=1; i<=K; i++)ans=min(ans,g[n][i]);
	printf("%lld\n",ans);
	return 0;
}