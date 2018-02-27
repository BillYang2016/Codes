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

typedef int int_t;
#define int unsigned int

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

const int maxn=100005,maxk=15;

struct Point {
	int x,y,id;
} p[maxn];

bool cmpx(const Point& a,const Point& b) {
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}

bool cmpy(const Point& a,const Point& b) {
	return a.y<b.y||(a.y==b.y&&a.x<b.x);
}

int n,k,Left[maxn],Right[maxn],Up[maxn],Down[maxn];

struct BIT {
	int c[maxn];
#define lowbit(x) x&(-x)
	void add(int x,int v) {
		for(int i=x; i<=n; i+=lowbit(i))c[i]+=v;
	}
	int sum(int x) {
		int sum=0;
		for(int i=x; i>=1; i-=lowbit(i))sum+=c[i];
		return sum;
	}
} bit;

int a[maxn],Max=0;
int C[maxn][maxk],ans=0;

int_t main() {
	Get_Int();
	Get_Int();
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		p[i].x=a[i]=Get_Int()+1;
		p[i].y=Get_Int()+1;
		p[i].id=i;
	}
	k=Get_Int();
	sort(a+1,a+n+1);
	int cnt=unique(a+1,a+n+1)-a-1;
	for(int i=1; i<=n; i++)p[i].x=lower_bound(a+1,a+cnt+1,p[i].x)-a;
	sort(p+1,p+n+1,cmpx);
	for(int i=2; i<=n; i++)
		if(p[i].x==p[i-1].x)Down[p[i].id]=Down[p[i-1].id]+1,Max=max(Max,Down[p[i].id]);
	for(int i=n-1; i>=1; i--)
		if(p[i].x==p[i+1].x)Up[p[i].id]=Up[p[i+1].id]+1,Max=max(Max,Up[p[i].id]);
	sort(p+1,p+n+1,cmpy);
	for(int i=2; i<=n; i++)
		if(p[i].y==p[i-1].y)Left[p[i].id]=Left[p[i-1].id]+1,Max=max(Max,Left[p[i].id]);
	for(int i=n-1; i>=1; i--)
		if(p[i].y==p[i+1].y)Right[p[i].id]=Right[p[i+1].id]+1,Max=max(Max,Right[p[i].id]);
	for(int i=0; i<=Max+1; i++) {
		C[i][0]=1;
		for(int j=1; j<=min(k,i); j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	for(int i=1,j; j=i,i<=n; i=j+1) {
		bit.add(p[i].x,C[Down[p[i].id]+1][k]*C[Up[p[i].id]][k]-C[Down[p[i].id]][k]*C[Up[p[i].id]+1][k]);
		while(p[j+1].y==p[j].y) {
			j++;
			ans+=C[Left[p[j-1].id]+1][k]*C[Right[p[j].id]+1][k]*(bit.sum(p[j].x-1)-bit.sum(p[j-1].x));
			bit.add(p[j].x,C[Down[p[j].id]+1][k]*C[Up[p[j].id]][k]-C[Down[p[j].id]][k]*C[Up[p[j].id]+1][k]);
		}
	}
	printf("%d\n",ans&0x7fffffff);
	return 0;
} 
