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

const int maxn=1000005;

int n,a,b,sum1,sum2,ans[maxn];

int main() {
	n=Get_Int();
	a=Get_Int();
	b=Get_Int();
	sum1=sum2=-1;
	for(int i=0; i<=n; i+=a)
		if((n-i)%b==0) {
			sum1=i/a;
			sum2=(n-i)/b;
			break;
		}
	if(sum1==-1) {puts("-1");return 0;}
	int tmp=0;
	for(; sum1; sum1--,tmp+=a) {
		int l=tmp+1,r=tmp+a;
		for(int i=l; i<r; i++)ans[i]=i+1;
		ans[r]=l;
	}
	for(; sum2; sum2--,tmp+=b) {
		int l=tmp+1,r=tmp+b;
		for(int i=l; i<r; i++)ans[i]=i+1;
		ans[r]=l;
	}
	for(int i=1; i<=n; i++)printf("%d ",ans[i]);
	return 0;
}