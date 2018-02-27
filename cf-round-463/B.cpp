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
#include<set>

using namespace std;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=1000005;

vector<int> S[maxn];
int g[maxn];

int Solve(int x) {
	int sum=1;
	while(x) {
		int tmp=x%10;
		if(tmp==0)tmp=1;
		sum=sum*tmp;
		x/=10;
	}
	return sum;
}

int main() {
	for(int i=1; i<=1000000; i++) {
		if(i<10)g[i]=i;
		else g[i]=g[Solve(i)];
		S[g[i]].push_back(i);
	}
	int q=Get_Int();
	for(int i=1; i<=q; i++) {
		int l=Get_Int(),r=Get_Int(),k=Get_Int();
		auto it1=lower_bound(S[k].begin(),S[k].end(),l),it2=upper_bound(S[k].begin(),S[k].end(),r);
		if(it1==it2)puts("0");
		else printf("%d\n",(int)distance(it1,it2)+(*it2==r));
	}
	return 0;
}