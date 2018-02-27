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
#include<list>
using namespace std;

typedef int int_t;
#define int unsigned int
typedef long long LL;

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

struct Hash_Table {
	list<int> L;
	LL Cal() {
		LL ans=0;
		for(auto x:L) {
			ans+=((LL)f[x]*(f[x]-1))>>1;
			id[x]=0;
		}
		L.clear();
	}
	void insert(int sum,int pos,int S) {
		while(id[sum]&&!check(id[sum],pos,S))sum++;
		if(!id[sum]) {
			id[sum]=pos;
			L.push_back(sum);
		}
		f[sum]++;
	}
} Hash;

LL Cal(int S) {
	for(int i=1; i<=n; i++) {
		int sum=0;
		for(int j=1; j<=6; j++) {
			sum=sum*BASE;
			if(S&(1<<(j-1)))sum+=a[i][j]+1;
		}
		Hash.insert(sum,i,S);
	}
	return Hash.cal();
}

int_t main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=6; j++)
			a[i][j]=Get_Int();
	C[0][0]=1;
	for(int i=1; i<=6; i++) {
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; j++)C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	for(int i=1; i<(1<<6); i++)bitcnt[i]=bitcnt[i>>1]+(i&1);
	for(int i=0; i<(1<<6); i++)
		if(bitcnt[i]>=k)ans+=(((bitcnt[i]-k)&1)?-1:1)*Cal(i)*C[bitcnt[i]][k];
	printf("%lld\n",ans);
	return 0;
}
