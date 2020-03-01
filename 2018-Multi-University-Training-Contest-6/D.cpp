#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef long long LL;

const int maxn=605;

struct Point {
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y) {}
	bool operator == (const Point &b) const {return 1ll*x*b.y==1ll*y*b.x;}
	bool operator < (const Point &b) const {return 1ll*x*b.y<1ll*y*b.x;}
} p[maxn];

LL f[maxn][maxn];
int n,h[maxn],l[maxn],r[maxn],v[maxn],lp[maxn],rp[maxn];

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		for(int i=1; i<=n; i++) {
			h[i]=Get_Int();
			l[i]=Get_Int();
			r[i]=Get_Int();
			v[i]=Get_Int();
			p[(i<<1)-1]=Point(l[i],h[i]);
			p[i<<1]=Point(r[i],h[i]);
		}
		sort(p+1,p+2*n+1);
		int cnt=unique(p+1,p+2*n+1)-p-1;
		for(int i=1; i<=n; i++) {
			lp[i]=lower_bound(p+1,p+cnt+1,Point(l[i],h[i]))-p;
			rp[i]=lower_bound(p+1,p+cnt+1,Point(r[i],h[i]))-p;
		}
		for(int len=1; len<=cnt; len++)
			for(int i=1; i+len-1<=cnt; i++) {
				int j=i+len-1,Max=0,id=0;
				for(int k=1; k<=n; k++)
					if(i<=lp[k]&&j>=rp[k]&&v[k]>Max) {
						Max=v[k];
						id=k;
					}
				if(Max==0) {f[i][j]=0;continue;}
				f[i][j]=LLONG_MAX/2;
				for(int k=lp[id]; k<=rp[id]; k++)f[i][j]=min(f[i][j],f[i][k-1]+f[k+1][j]+Max);
			}
		printf("%lld\n",f[1][cnt]);
	}
	return 0;
}