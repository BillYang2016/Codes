#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=200005;

LL sum[maxn];
int n,k;

#define mp make_pair
#define pii pair<int,LL>

struct BIT {
	pii c[maxn];
	#define lowbit(x) (x&(-x))
	void add(int x,LL v) {
		for(int i=x; i<=n; i+=lowbit(i))
			if(v>c[i].second||(v==c[i].second&&x<c[i].first))c[i]=mp(x,v);
	}
	pii query(int x) {
		pii ans=mp(n+1,0);
		for(int i=x; i>=1; i-=lowbit(i))if(c[i].second>ans.second||(c[i].second==ans.second&&c[i].first<ans.first))ans=c[i];
		return ans;
	}
} bit;

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=1; i<=n; i++)sum[i]=sum[i-1]+Get_Int();
	for(int i=1; i<=n-k+1; i++)bit.add(i,sum[i+k-1]-sum[i-1]);
	LL ans=0;
	int a,b;
	for(int i=n-k+1; i>=k+1; i--) {
		pii x=bit.query(i-k);
		if(sum[i+k-1]-sum[i-1]+x.second>ans||(x.first<=a&&sum[i+k-1]-sum[i-1]+x.second==ans)) {
			ans=sum[i+k-1]-sum[i-1]+x.second;
			a=x.first;
			b=i;
		}
	}
	printf("%d %d\n",a,b);
	return 0;
}