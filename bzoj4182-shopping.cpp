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

const int maxn=10005,maxk=505,maxv=5005;

int n,k,a[maxn],f[maxn][maxk],Max=0,ans=0;

struct BIT {
	int c[maxv+maxk][maxk];
#define lowbit(x) x&-x
	void add(int x,int y,int v) {
		y++;
		for(int i=x; i<=Max; i+=lowbit(i))
			for(int j=y; j<=k+1; j+=lowbit(j))
				c[i][j]=max(c[i][j],v);
	}
	int sum(int x,int y) {
		y++;
		int sum=0;
		for(int i=x; i>=1; i-=lowbit(i))
			for(int j=y; j>=1; j-=lowbit(j))
				sum=max(sum,c[i][j]);
		return sum;
	}
} bit;

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=1; i<=n; i++) {
		a[i]=Get_Int();
		Max=max(Max,a[i]);
	}
	Max+=k+1;
	for(int i=1; i<=n; i++) {
		for(int j=0; j<=k; j++) {
			f[i][j]=bit.sum(a[i]+j,j)+1;
			ans=max(ans,f[i][j]);
		}
		for(int j=0; j<=k; j++)bit.add(a[i]+j,j,f[i][j]);
	}
	printf("%d\n",ans);
	return 0;
} 
