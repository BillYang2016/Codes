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
	int n=Get_Int(),m=n;
	printf("%d\n",m);
	for(int i=1; i<n; i++)printf("%d %d\n",-i,i+1);
	printf("%d %d\n",-n,-n);
	return 0;
}