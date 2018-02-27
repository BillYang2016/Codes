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

LL n;
vector<LL>ans;

void Solve(LL x) {
	for(LL i=x; i<=n; i+=x) {
		if((i-2)%(n/x)==0)ans.push_back(i-1);
		if(i<n&&(i+2)%(n/x)==0)ans.push_back(i+1);
	}
}

int main() {
	n=Get_Int();
	for(int i=1; i<=sqrt(n); i++)
		if(n%i==0)Solve(n/i);
	ans.push_back(1);
	sort(ans.begin(),ans.end());
	auto it=unique(ans.begin(),ans.end());
	ans.erase(it,ans.end());
	for(LL num:ans)printf("%lld\n",num);
	return 0;
} 
