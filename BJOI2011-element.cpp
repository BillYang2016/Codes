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

inline const LL Get_Int() {
	LL num=0,bj=1;
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

const int maxn=1005,MAX_BASE=64;

struct Stone {
	LL num,val;
	bool operator < (const Stone& b) const {
		return val>b.val;
	}
} a[maxn];

struct Linear_Bases {
	LL b[MAX_BASE+5];
	Linear_Bases() {
		fill(b,b+MAX_BASE+1,0);
	}
	bool add(LL num) {
		bool bj=0;
		for(int j=MAX_BASE; j>=0; j--)
			if(num>>j&1) {
				if(b[j]) {
					num^=b[j];
					continue;
				}
				b[j]=num;
				for(int k=j-1; k>=0; k--)if(b[j]>>k&1)b[j]^=b[k];
				for(int k=j+1; k<=MAX_BASE; k++)if(b[k]>>j&1)b[k]^=b[j];
				bj=1;
				break;
			}
		return bj;
	}
} lb;

int n;
LL sum=0;

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		a[i].num=Get_Int();
		a[i].val=Get_Int();
	}
	sort(a+1,a+n+1);
	for(int i=1; i<=n; i++)
		if(lb.add(a[i].num))sum+=a[i].val;
	printf("%lld\n",sum);
	return 0;
} 
