#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int n,m,k; 

int main() {
	n=Get_Int();
	m=Get_Int();
	k=Get_Int();
	if(min(m,k)>=n)puts("Yes");
	else puts("No");
	return 0;
}

