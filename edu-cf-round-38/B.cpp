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

int n,ans=0;

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		int x=Get_Int();
		ans=max(ans,min(x-1,1000000-x));
	}
	printf("%d\n",ans);
	return 0;
}