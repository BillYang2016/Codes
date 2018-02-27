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

const int MAX_BASE=50;

struct Linear_Bases {
	LL b[MAX_BASE+5];
	void build(vector<LL> a) {
		for(LL num:a)
			for(int j=MAX_BASE; j>=0; j--)
				if(num>>j&1) {
					if(b[j]) { //该位存在基
						num^=b[j];
						continue;
					}
					b[j]=num;
					for(int k=j-1; k>=0; k--)if(b[j]>>k&1)b[j]^=b[k];
					for(int k=j+1; k<=MAX_BASE; k++)if(b[k]>>j&1)b[k]^=b[j];
					break;
				}
	}
	LL cal() { //最大异或和
		LL ans=0;
		for(int i=0; i<=MAX_BASE; i++)ans^=b[i];
		return ans;
	}
} lb;

int n;
vector<LL>a;

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)a.push_back(Get_Int());
	lb.build(a);
	printf("%lld\n",lb.cal());
	return 0;
} 
