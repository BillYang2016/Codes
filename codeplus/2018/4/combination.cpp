#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int x,k;

int main() {
	x=Get_Int();
	k=Get_Int();
	for(int i=1; i<k; i++)printf("%d 0\n",i);
	printf("%d 1\n",x-k+1);
	return 0;
}