#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int main() {
	int n=Get_Int();
	if(n==1) {puts("1\n1");return 0;}
	if(n==2) {puts("2\n0\n11");return 0;}
	printf("%d\n",n-1);
	for(int i=2; i<=n; i++) {
		putchar('0');
		for(int j=2; j<i; j++)putchar('1');
		putchar('0');
		putchar('\n');
	}
	return 0;
}