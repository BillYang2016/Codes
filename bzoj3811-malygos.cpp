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

typedef unsigned long long LL;

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

const int maxn=100005;

int n,k;
LL a[maxn];

namespace Solve1 {
	void solve() {
		LL ans=0;
		for(int i=1; i<=n; i++)ans|=a[i];
		printf("%llu",ans>>1);
		if(ans&1)puts(".5");
	}
}

namespace Solve2 {
	const int MAX_BASE=32;

	LL ans=0,remain=0;

	void solve() {
		for(int i=0; i<MAX_BASE; i++)
			for(int j=0; j<MAX_BASE; j++) {
				bool bj=0;
				for(int k=1; k<=n; k++)
					if(a[k]>>i&1) {
						bj=1;
						break;
					}
				if(!bj)continue;
				bj=0;
				for(int k=1; k<=n; k++)
					if(a[k]>>j&1) {
						bj=1;
						break;
					}
				if(!bj)continue;
				bj=0; //统计是否全为$(1,1),(0,0)$
				for(int k=1; k<=n; k++)
					if((a[k]>>i&1)!=(a[k]>>j&1)) {
						bj=1;
						break;
					}
				if(i+j-1-bj<0)remain++;
				else ans+=1ll<<(i+j-1-bj);
			}
		ans+=remain>>1;
		printf("%llu",ans);
		if(remain&1)puts(".5");
	}
}

namespace Solve3 {
	const int MAX_BASE=22;
	
	LL ans=0,remain=0;

	struct Linear_Bases {
		vector<LL>a;
		LL b[MAX_BASE+5];
		void add(LL num) {
			for(int j=MAX_BASE; j>=0; j--)
				if(num>>j&1) {
					if(b[j]) {
						num^=b[j];
						continue;
					}
					b[j]=num;
					for(int k=j-1; k>=0; k--)if(b[j]>>k&1)b[j]^=b[k];
					for(int k=j+1; k<=MAX_BASE; k++)if(b[k]>>j&1)b[k]^=b[j];
					break;
				}
		}
		void build(int n,LL* a) {
			for(int i=1; i<=n; i++)add(a[i]);
		}
		void split() {
			for(int j=MAX_BASE; j>=0; j--)if(b[j])a.push_back(b[j]);
		}
	} lb;

	void solve() {
		lb.build(n,a);
		lb.split();
		int size=lb.a.size();
		for(int i=(1<<size)-1; i>=0; i--) {
			int val=0;
			for(int j=0; j<size; j++)if(i>>j&1)val^=lb.a[j];
			LL a=0,b=1;
			for(int j=1; j<=k; j++) {
				b*=val;
				a=a*val+(b>>size);
				b&=(1<<size)-1;
			}
			remain+=b;
			ans+=a+(remain>>size);
			remain&=(1<<size)-1;
		}
		printf("%llu",ans);
		if(remain)puts(".5");
	}
}

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	if(k==1)Solve1::solve();
	else if(k==2)Solve2::solve();
	else Solve3::solve();
	return 0;
} 