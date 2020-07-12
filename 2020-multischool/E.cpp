#include<bits/stdc++.h>

using namespace std;

const int maxn=100005;

long long da[maxn],db[maxn];
int n,m,mod;

struct BIT {
	int c[maxn];
#define lowbit(x) (x&(-x))
	void init() {
		fill(c,c+m+1,0);
	}
	void add(int x,int v) {
		for(int i=x; i>=1; i-=lowbit(i))c[i]+=v;
	}
	int query(int x) {
		int ans=0;
		for(int i=x; i<=m; i+=lowbit(i))ans+=c[i];
		return ans;
	}
} bit;

int main() {
	ios::sync_with_stdio(false);
	while(cin>>n>>m>>mod) {
		bit.init();
		for(int i=1; i<=n; i++) {
			cin>>da[i];
			bit.add(da[i],1);
		}
		for(int i=1; i<=m; i++)db[i]=bit.query(i);
		sort(da+1,da+n+1,greater<int>());
		sort(db+1,db+m+1,greater<int>());
		long long ans=1;
		for(int i=2; i<=n; i++)ans=ans*da[i]%mod;
		for(int i=2; i<=m; i++)ans=ans*db[i]%mod;
		printf("%lld\n",ans);
	}
	return 0;
}