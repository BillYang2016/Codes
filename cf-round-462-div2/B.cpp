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

int n;

int main() {
	n=Get_Int();
	if(n>36) {
		puts("-1");
		return 0;
	}
	while(n>=2) {
		putchar('8');
		n-=2;
	}
	if(n)putchar('4');
	return 0;
}