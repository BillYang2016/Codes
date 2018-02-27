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

int main() {
	int t=Get_Int();
	for(int i=1; i<=t; i++) {
		int x=Get_Int();
		bool bj=0;
		for(int n=sqrt(x); n<=50000; n++) {
			int m=n*n-x,tmp=sqrt(m);
			if(tmp&&tmp*tmp==m) {
				int ans=n/tmp;
				if(n/ans!=tmp)continue;
				bj=1;
				printf("%d %d\n",n,ans);
				break;
			}
		}
		if(!bj)puts("-1");
	}
	return 0;
}