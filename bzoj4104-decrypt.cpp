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

const int maxn=200005;

struct sequence {
	int x,id;
	bool operator < (const sequence& b) const {
		return x<b.x||(x==b.x&&id<b.id);
	}
} a[maxn];

int n;

int main() {
	n=Get_Int();
	Get_Int();
	for(int i=0; i<=n; i++) {
		a[i].x=Get_Int();
		a[i].id=i;
	}
	sort(a,a+n+1);
	int now=a[0].id;
	for(int i=1; i<=n; i++) {
		printf("%d ",a[now].x);
		now=a[now].id;
	}
	return 0;
} 
