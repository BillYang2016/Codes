#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int n=5,N=10;

int M[105][105];

int main() {
	int a[15]= {1,2,3,4,5,6,7,8},p=0;
	for(int i=0; i<N; i++)
		for(int j=0; j<=i; j++) {
			M[j][i-j]=a[p];
			p=(p+1)%n;
		}
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++)printf("%d ",M[i][j]);
		putchar('\n');
	}
	return 0;
}